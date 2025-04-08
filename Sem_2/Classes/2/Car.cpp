#include "Car.h"
#include <iostream>

Car::Car()
{
    brand = model = "";
    price = -1;
}

Car::Car(std::string b, std::string m, int p)
{
    brand = b;
    model = m;
    price = p;
}

Car::Car(const Car &c)
{
    std::cout << "Copy car" << this << '\n';
    brand = c.brand;
    model = c.model;
    price = c.price;
}

Car::~Car()
{
    std::cout << "Destroy car" << this << "\n";
}

std::string Car::getBrand()
{
    return brand;
}

std::string Car::getModel()
{
    return model;
}

int Car::getPrice()
{
    return price;
}

void Car::setBrand(std::string value)
{
    brand = value;
}

void Car::setModel(std::string value)
{
    model = value;
}

void Car::setPrice(int value)
{
    price = value;
}

void Car::show()
{
    std::cout << "Car:";
    std::cout << "\n brand: " << brand;
    std::cout << "\n model: " << model;
    std::cout << "\n price: " << price;
    std::cout << '\n';
}
