/** 11 вариант
Создать класс Money для работы с денежными суммами. Число должно быть
представлено двумя полями: типа long для рублей и типа int для копеек. Дробная часть
числа при выводе на экран должна быть отделена от целой части запятой. Реализовать:
 операции сравнения (<, >).
 добавление копеек (++) (постфиксная и префиксная формы)
Задание:
 Удалить все записи большие заданного значения.
 Уменьшить все записи с заданным значением в два раза.
 Добавить K записей после элемента с заданным номером.
*/

#include "Money.h"
#include "file_work.h"
#include <iostream>

int main()
{
    Money money;
    int tmp, choise, num;
    char file_name[30];
    do
    {
        std::cout << "\n1. Make file";
        std::cout << "\n2. Print file";
        std::cout << "\n3. Delete record from file";
        std::cout << "\n4. Add record to file";
        std::cout << "\n5. Change record in file";
        std::cout << "\n0. Exit\n";
        std::cin >> choise;
        switch (choise)
        {
        case 1:
            std::cout << "file name?";
            std::cin >> file_name;
            tmp = make_file(file_name);
            if (tmp < 0)
            {
                std::cout << "Can't make file";
            }
            break;
        case 2:
            std::cout << "file name?";
            std::cin >> file_name;
            tmp = make_file(file_name);
            if (tmp == 0)
            {
                std::cout << "Empty file\n";
            }
            else if (tmp < 0)
            {
                std::cout << "Can't read file\n";
            }
            break;
        case 3:
            std::cout << "file name?";
            std::cin >> file_name;
            std::cout << "num?";
            std::cin >> num;
            tmp = del_file(file_name, num);
            if (tmp < 0)
            {
                std::cout << "Can't read file\n";
            }
            break;
        case 4: {
            Money money;
            std::cout << "file name?";
            std::cin >> file_name;
            std::cout << "num?";
            std::cin >> num;
            std::cout << "New money sum: ";
            std::cin >> money;
            tmp = add_file(file_name, num, money);
            if (tmp < 0)
            {
                std::cout << "Can't read file\n";
            }
            else if (tmp == 0)
            {
                tmp = add_end(file_name, money);
            }
            break;
        }
        case 5: {
            Money m2;
            std::cout << "file name?";
            std::cin >> file_name;
            std::cout << "num?";
            std::cin >> num;
            std::cout << "\nNew money sum: ";
            std::cin >> m2;
            tmp = change_file(file_name, m2, num);
            if (tmp < 0)
            {
                std::cout << "Can't read file\n";
            }
            if (tmp == 0)
            {
                std::cout << "\nNot such record\n";
            }
            break;
        }
        }
    } while (choise != 0);

    return 0;
}
