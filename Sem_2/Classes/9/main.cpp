/* 11 вариант
Класс- контейнер СПИСОК с ключевыми значениями типа
int.
Реализовать операции:
[]– доступа по индексу;
int() – определение размера списка;
+ вектор – сложение элементов списков a[i]+b[i];
- n - переход влево к элементу c номером n
*/

#include "List.h"
#include "error.h"
#include <iostream>

int main()
{
    try
    {
		int listSize;
		std::cout << "List size: ";
		std::cin >> listSize;
        List x(listSize), y;
        int i;
        std::cout << "List x: " << x << "\n";
        std::cout << "i: ";
        std::cin >> i;
        std::cout << "x[i]: " << x[i] << "\n";
        y = x + x;
        std::cout << "y = " << y;
    }
    catch (error &e)
    {
		std::cout << "\nERR! ";
        e.what();
    }
    return 0;
}