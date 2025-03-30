#include <iostream>

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int num = 0;
    for (int i = low + 1; i <= high; i++)
    {
        if (arr[i] < pivot)
        {
            num++;
        }
    }
    int pos = low + num;
    std::swap(arr[pos], arr[low]);
    int i = low, j = high;
    while (i < pos && j > pos)
    {
        while (arr[i] < pivot)
        {
            i++;
        }
        while (arr[j] > pivot)
        {
            j--;
        }
        if (i < pos && j > pos)
        {
            std::swap(arr[j--], arr[i++]);
        }
    }
    return pos;
}

void quickSort(int arr[], int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int partitionIndex = partition(arr, low, high);
    quickSort(arr, low, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, high);
}

void shellSort(int arr[], int len)
{
    for (int h = len / 2; h > 0; h /= 2)
    {
        for (int i = h; i < len; ++i)
        {
            int tmp = arr[i];
            int j;
            for (j = i; j >= h && arr[j - h] > tmp; j -= h)
            {
                arr[j] = arr[j - h];
            }
            arr[j] = tmp;
        }
    }
}

void initArr(int arr[], int len)
{
    std::cout << "   До: ";
    for (int i = 0; i < len; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
        std::cout << arr[i] << ' ';
    }
}

void printArrAfter(int arr[], int len)
{
    std::cout << "\nПосле: ";
    for (int i = 0; i < len; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";
}

int main()
{
    int len;
    std::cout << "Размер массива: ";
    std::cin >> len;
    int arr[len];
    std::srand(-len + 2);

    std::cout << "--Сорт. быстрая по Хоара--\n";
    initArr(arr, len);
    quickSort(arr, 0, len - 1);
    printArrAfter(arr, len);

    std::cout << "--Сорт. Шелла--\n";
    initArr(arr, len);
    shellSort(arr, len);
    printArrAfter(arr, len);

    return 0;
}
