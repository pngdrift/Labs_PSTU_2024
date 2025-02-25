// 11. Формировать двумерный массив. Добавить в него
//  строку и столбец с заданным номером.

#include <iostream>

int main()
{
    int size;
    std::cout << "size: ";
    std::cin >> size;

    int **matr = new int *[size];
    for (int i = 0; i < size; i++)
    {
        matr[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            matr[i][j] = std::rand() % 100;
            std::cout << matr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    int k;
    std::cout << "num: ";
    std::cin >> k;
    int newSize = size + 1;
    int **newMatr = new int *[newSize];
    for (int i = 0; i < newSize; i++)
    {
        newMatr[i] = new int[newSize];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMatr[i < k ? i : i + 1][j < k ? j : j + 1] = matr[i][j];
        }
    }
    for (int i = 0; i < newSize; i++)
    {
        newMatr[k][i] = -1;
        newMatr[i][k] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            std::cout << newMatr[i][j] << ' ';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < newSize; i++)
    {
        delete[] newMatr[i];
    }
    delete[] newMatr;

    return 0;
}