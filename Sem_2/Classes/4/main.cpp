/* 11 вариант
Базовый класс:
ТРОЙКА_ЧИСЕЛ (TRIAD)
Первое_число (first) - int
Второе_число (second) – int
Третье_число (third) - int
Определить методы изменения полей и увеличения полей на 1.
Создать производный класс TIME с полями часы, минуты и секунды. Переопределить
методы увеличения полей на 1 и определить методы увеличения на n секунд и минут.
*/

#include "Time.cpp"
#include "Triad.cpp"
#include <iostream>

int main()
{
    Triad userTriad;
    std::cin >> userTriad;
    std::cout << userTriad;

    Triad triad(0, 1, 42);
    triad.setFirst(103);
    std::cout << triad;

    triad = userTriad;
    triad.setThird(0);
    std::cout << triad;

    Time userTime;
    std::cin >> userTime;
    userTime.addMinute(3);
    userTime.addSec(5);
    std::cout << userTime;
    return 0;
}