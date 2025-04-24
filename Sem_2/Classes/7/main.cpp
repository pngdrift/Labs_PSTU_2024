/* 11 вариант
Класс- контейнер СПИСОК с ключевыми значениями типа int.
Реализовать операции:
[]– доступа по индексу;
int() – определение размера списка;
+ вектор – сложение элементов списков a[i]+b[i];
Пользовательский класс Money для работы с денежными суммами. Число должно
быть представлено двумя полями: типа long для рублей и типа int для копеек.
Дробная часть числа при выводе на экран должна быть отделена от целой части
запятой
*/

#include "List.h"
#include "Money.h"
#include <iostream>

int main()
{
    int k = 1;
    int size = 5;
    List<int> A(size);
    std::cout << "List A: " << A;
    std::cout << "List A[k]" << A[k] << '\n';
    std::cout << "Size A: " << A() << '\n';

    List<int> B(size);
    std::cout << "List B: ";
    B = B + 10;
    std::cout << B;
    std::cout << "Size B: " << B() << '\n';

    List<Money> AM(2);
    std::cin >> AM;
    std::cout << AM << '\n';
    List<Money> BM(10);
    std::cout << "BM: " << BM << '\n';
    BM = AM;
    std::cout << "BM: " << BM << '\n';
    std::cout << "AM: " << AM[1] << '\n';
    std::cout << "size=" << A() << '\n';

    return 0;
}
