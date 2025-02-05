// Простые сортировки

#include <iostream>

int main()
{
    int len;
    std::cout << "Размер массива: ";
    std::cin >> len;

    int arr[len];


    std::cout << "--Сортировка пузырьком--\n";

    std::cout << "До: \n";
    for (int i = 0; i < len; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

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

    std::cout << "После:\n";
    for (int i = 0; i < len; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";



    std::cout << "--Сортировка выбором--\n";

    std::cout << "До: \n";
    for (int i = 0; i < len; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    int min_index; // индекс (текущий) наименьшего по значению элемента
    for (int i = 0; i < len - 1; ++i)
    {
        min_index = i;
        for (int j = i + 1; j < len; ++j)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        int tmp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = tmp;
    }

    std::cout << "После:\n";
    for (int i = 0; i < len; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";



    std::cout << "--Сортировка вставкой--\n";

    std::cout << "До: \n";
    for (int i = 0; i < len; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    int key;
    for (int i = 0; i < len; ++i)
    {
        key = arr[i];
        int j = i - 1; // индекс элемента перед arr[i]
        while (j >= 0 && arr[j] > key)
        {
            // надо обменять элементы
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }

    std::cout << "После:\n";
    for (int i = 0; i < len; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";

    return 0;
}
