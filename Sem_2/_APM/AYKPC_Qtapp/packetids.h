#include <cstdint>
constexpr char PacketHeaderSize = 5;

// app/arduino -> server
constexpr uint8_t PacketID_HELLO = 0;
constexpr uint8_t PacketID_PING = 1;

// server -> app/arduino
constexpr uint8_t PacketID_HI = 10;
constexpr uint8_t PacketID_PONG = 11;

// server -> app
constexpr uint8_t PacketID_INIT_ROW = 20;
constexpr uint8_t PacketID_UPDATE_ROW_CELL_VALUE = 21;
constexpr uint8_t PacketID_SEND_FULL_INFO = 22;

// arduino -> server
constexpr uint8_t PacketID_UPDATE_SENSOR_VALUE = 30;

// app -> server
constexpr uint8_t PacketID_GET_FULL_INFO = 40;
constexpr uint8_t PacketID_EDIT_NOTE = 41;
