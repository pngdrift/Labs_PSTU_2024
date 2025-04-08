/* 11 вариант
Пользовательский класс АВТОМОБИЛЬ
Марка – string
Модель – string
Стоимость– int
*/

#include <iostream>
#include "Car.cpp"

int main()
{
    Car priora("Lada", "VAZ-2170", 500000);
    priora.show();

    Car prioraCoupe = priora;
    prioraCoupe.setModel("VAZ-2172");
    prioraCoupe.setPrice(539000);
    prioraCoupe.show();

    Car userCar;
    std::cout << "Enter car brand> ";
    std::string brand;
    std::cin >> brand;
    userCar.setBrand(brand);
    std::cout << "Enter car model> ";
    std::string model;
    std::cin >> model;
    userCar.setModel(model);
    std::cout << "Enter car price> ";
    int price;
    std::cin >> price;
    userCar.setPrice(price);
    userCar.show();
    return 0;
}
