#include "frames.h"
#include "packetids.h"
#include <Arduino_LED_Matrix.h>
#include <WiFiS3.h>

#define BULL_BIRTHDATE "04.02.2025" // ДД.MM.ГГГГ
#define ARDUINO_ID "42"

#define SENSORS_UPDATE_INTERVAL_IN_SEC 3

// данные от вайфай
#define WIFI_SSID "Somewifissid"
#define WIFI_PASS "s0mew1fip4ssw"

// конфиг сервера
#define SERVER_ADDRESS "some-address.ru"
#define SERVER_PORT 24516

// датчик препятствии
#define YL63_PIN 2
bool hasObstacle()
{
    return !digitalRead(YL63_PIN);
}

//  аналоговый датчик температуры
#define KY013_PIN A0
uint16_t Vo;
float R1 = 10000; // значение резистора R1 на модуле
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; // коэффициенты Стейнхарта — Харта для термистора
float getTemperature()
{
    Vo = analogRead(KY013_PIN);
    R2 = R1 * (1023.0 / (float)Vo - 1.0); // вычисление сопротивления термистора
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); // в Кельвинах
    T = T - 273.15;                                             // Из Кельвинов в Цельсий
    return T;
}
#define LED_PIN 13
#define COLD_TEMPERATURE 26

ArduinoLEDMatrix matrix;

WiFiClient client;

// отправка пакета серверу
void sendPacket(uint8_t id, String text = "")
{
    uint32_t textLen = text.length();
    uint32_t packetLen = PacketHeaderSize + textLen;
    byte buffer[packetLen];
    buffer[0] = (packetLen >> 24) & 0xFF;
    buffer[1] = (packetLen >> 16) & 0xFF;
    buffer[2] = (packetLen >> 8) & 0xFF;
    buffer[3] = packetLen & 0xFF;

    buffer[4] = id;

    memcpy(buffer + PacketHeaderSize, text.c_str(), textLen);
    client.write(buffer, packetLen);
}

// обработка пакета
void handlePacket(uint8_t id, const char *text)
{
    // String packetData = String(text);
    // int separatorIndex = packetData.indexOf(';');
    switch (id)
    {
    case PacketID_HI: {
        matrix.loadFrame(heart);
    }
    break;
    case PacketID_PING: {
        sendPacket(PacketID_PONG);
    }
    break;
    }
}

byte packetBuffer[255];
uint32_t packetBufferIndex = 0;
void readPacket()
{
    while (client.available())
    {
        packetBuffer[packetBufferIndex++] = client.read();
        if (packetBufferIndex >= (PacketHeaderSize - 1))
        {
            // длина хранится с порядком Big Endian
            uint32_t totalLen =
                (packetBuffer[0] << 24) | (packetBuffer[1] << 16) | (packetBuffer[2] << 8) | packetBuffer[3];
            if (packetBufferIndex >= totalLen)
            {
                uint8_t id = packetBuffer[4];
                char text[totalLen - PacketHeaderSize + 1];
                memcpy(text, packetBuffer + PacketHeaderSize, totalLen - PacketHeaderSize);
                text[totalLen - PacketHeaderSize] = '\0';
                handlePacket(id, text);
                packetBufferIndex = 0;
            }
        }
    }
}

bool connectingToServer = false;
void connectToServer()
{
    connectingToServer = true;
    Serial.println("Connecting to server...");
    while (!client.connect(SERVER_ADDRESS, SERVER_PORT))
    {
        Serial.println("Connection to server failed");
        matrix.loadFrame(danger);
        delay(2000);
        if (WiFi.status() != WL_CONNECTED)
        {
            // нет соединения с wifi, значит и к серверу никак не подключится
            connectingToServer = false;
            return;
        }
    }
    Serial.println("Connected to server");
    sendPacket(PacketID_HELLO, String("IAMARDUINO;") + String(ARDUINO_ID) + ";" + String(BULL_BIRTHDATE));
    connectingToServer = false;
}

bool connectingToWifi = false;
void connectToWifi()
{
    connectingToWifi = true;
    matrix.loadFrame(wifi);
    while (WiFi.begin(WIFI_SSID, WIFI_PASS) != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi...");
        delay(1000);
    }
    Serial.println("Connected to WiFi");
    matrix.loadFrame(chip);
    connectingToWifi = false;
}

void setup()
{
    Serial.begin(9600);
    matrix.begin();
}

uint32_t lastTime = 0;
uint32_t deltaTime;
uint32_t sensorsUpdateTimer = 0;

bool lastObstacle, currObstacle;
float lastTemperature, currTemperature = 0;

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        if (!connectingToWifi)
            connectToWifi();
        return;
    }
    else if (!client.connected())
    {
        if (!connectingToServer)
            connectToServer();
        return;
    }
    readPacket();

    deltaTime = millis() - lastTime;
    lastTime = millis();
    sensorsUpdateTimer += deltaTime;
    if (sensorsUpdateTimer >= (SENSORS_UPDATE_INTERVAL_IN_SEC * 1000))
    {
        currTemperature = getTemperature();
        digitalWrite(LED_PIN, currTemperature < COLD_TEMPERATURE);
        if (abs(currTemperature - lastTemperature) > 0.2)
        {
            Serial.print("Curr temperature: ");
            Serial.println(currTemperature);
            sendPacket(PacketID_UPDATE_SENSOR_VALUE, "temp;" + String(currTemperature, 1));
            lastTemperature = currTemperature;
        }

        currObstacle = hasObstacle();
        if (lastObstacle != currObstacle)
        {
            Serial.print("Obstacle: ");
            Serial.println(currObstacle);
            sendPacket(PacketID_UPDATE_SENSOR_VALUE, "obstacle;" + String(currObstacle));
            lastObstacle = currObstacle;
        }

        sensorsUpdateTimer = 0;
    }
}
