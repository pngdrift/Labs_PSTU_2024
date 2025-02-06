// 11. Написать функцию, проверяющую по возрастанию или
// убыванию упорядочена указанная строка двумерного
// массива. Упорядочить по возрастанию все строки
// двумерного массива, которые неупорядочены по убыванию.

#include <iostream>

bool isSortedAscending(int arr[], int len)
{
    bool result = true;
    for (int i = 1; i < len; ++i)
    {
        if (arr[i] < arr[i - 1])
        {
            result = false;
            break;
        }
    }
    return result;
}

void sortAscending(int arr[], int len)
{
    int tmp;
    for (int i = 0; i < len - 1; ++i)
    {
        for (int j = 0; j < len - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    int len1, len2;
    std::cout << "Форма двумерного массива: ";
    std::cin >> len1 >> len2;

    int arr[len1][len2];

    for (int i = 0; i < len1; ++i)
    {
        for (int j = 0; j < len2; ++j)
        {
            arr[i][j] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < len1; ++i)
    {
        if (!isSortedAscending(arr[i], len2))
        {
            sortAscending(arr[i], len2);
        }
    }

    std::cout << "Результат:\n";
    for (int i = 0; i < len1; ++i)
    {
        for (int j = 0; j < len2; ++j)
        {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
