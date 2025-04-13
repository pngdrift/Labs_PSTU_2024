/* 11 вариант
Создать класс Money для работы с денежными суммами. Число должно быть
представлено двумя полями: типа long для рублей и типа int для копеек. Дробная часть
числа при выводе на экран должна быть отделена от целой части запятой. Реализовать:
     операции сравнения (<, >).
     добавление копеек (++) (постфиксная и префиксная формы)
 */

#include "Money.cpp"
#include <iostream>

int main()
{
    Money money(349, 50);
    std::cout << money;
    money++;
    std::cout << money;
    Money userMoney;
    std::cin >> userMoney;
    std::cout << userMoney;
    userMoney = money;
    ++userMoney;
    std::cout << userMoney;
    std::cout << userMoney + userMoney;
    bool test = money < userMoney;
    std::cout << test;
    return 0;
}
