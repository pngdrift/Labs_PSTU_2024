// 11.
// 1) Сформировать одномерный массив целых чисел,
// используя датчик случайных чисел.
// 2) Распечатать полученный массив.
// 3) Удалить 5 последних элементов массива.
// 4) Добавить в начало массива 3 элемента с значением
// M[ I+1 ]+2.
// 5) Распечатать полученный массив.

#include <cstdlib>
#include <iostream>

int main()
{
    int N = 100;
    int arr[N];

    int realLength;
    std::cout << "Arr real len: ";
    std::cin >> realLength;

    // 1)
    std::srand(realLength);
    for (int i = 0; i < realLength; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
    }

    // 2)
    for (int i = 0; i < realLength; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    // 3)
    realLength -= 5;

    // 4)
    realLength += 3;
    for (int i = realLength - 1; i >= 3; --i)
    {
        arr[i] = arr[i - 3];
    }
    for (int i = 0; i < 3; ++i)
    {
        arr[i] = arr[i + 1] + 2;
    }

    // 5)
    for (int i = 0; i < realLength; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
