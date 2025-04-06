// 11 вариант
// Поле first – дробное положительное число, оклад, поле second – целое положительное
// число, количество отработанных дней. Реализовать метод summa() –вычисление
// начисленной суммы за данное количество дней по формуле:
// оклад/количество_дней_месяца*количество_отработанных _дней

#include <iostream>
#include "Salary.cpp"

Salary make_Salary()
{
    Salary salary;
    salary.Read();
    return salary;
}

int main()
{
    Salary salary = make_Salary();
    std::cout << "summa: " << salary.summa() << '\n';
    return 0;
}
