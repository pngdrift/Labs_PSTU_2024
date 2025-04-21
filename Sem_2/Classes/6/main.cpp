/* Вариант 11
Класс- контейнер СПИСОК с ключевыми значениями типа int.
Реализовать операции:
[]– доступа по индексу;
int() – определение размера списка;
+ вектор – сложение элементов списков a[i]+b[i];
- n - переход влево к элементу c номером n ( с помощью класса-итератора).
*/

#include "List.h"
#include <iostream>

int main()
{
    List a(5);
    std::cout << a << "\n";

    std::cin >> a;
    std::cout << "List a: " << a << "\n";

    a[2] = 100;
    std::cout << "List a:  " << a << '\n';

    List b(10);
    std::cout << "List b: " << b << '\n';

    b = a;
    std::cout << "List b: " << b << '\n';

    List c(10);
    c = b + 100;

    std::cout << "List c: " << c << '\n';
    std::cout << "the length of a: " << a() << '\n';

    std::cout << *(a.first()) << '\n';
    Iterator i = a.first();
    ++i;
    std::cout << *i << '\n';
    for (i = a.first(); i != a.last(); ++i)
    {
        std::cout << *i << '\n';
    }

    return 0;
}
