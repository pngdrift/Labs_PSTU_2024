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

#include "Time.h"
#include "Vector.h"
#include <iostream>


int main()
{
    Triad triad;

    std::cin >> triad;
    std::cout << triad << '\n';

    Object *someObj = &triad;
    someObj->Show();

    Time time;
    std::cin >> time;
    std::cout << time << '\n';

    someObj = &time;
    someObj->Show();

    Vector vector(5);
    Triad tr;
    std::cin >> tr;
    Time ti;
    std::cin >> ti;

    someObj = &tr;
    vector.Add(someObj);
    someObj = &ti;
    vector.Add(someObj);

    std::cout << "Vector:\n";
    std::cout << vector;
    return 0;
}
