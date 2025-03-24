#include <iostream>

void quickSortOrig(int arr[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    quickSortOrig(arr, low, i);
    quickSortOrig(arr, i + 2, high);
}

void merge(int arr[], int low, int mid, int high)
{
    int leftRange = mid - low + 1;
    int left[leftRange];

    int rightRange = high - mid;
    int right[rightRange];

    for (int i = 0; i < leftRange; ++i)
    {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < rightRange; ++j)
    {
        right[j] = arr[mid + 1 + j];
    }

    int leftIndex = 0, rightIndex = 0;
    int mergeIndex = low;
    while (leftIndex < leftRange && rightIndex < rightRange)
    {
        if (left[leftIndex] <= right[rightIndex])
        {
            arr[mergeIndex++] = left[leftIndex++];
        }
        else
        {
            arr[mergeIndex++] = right[rightIndex++];
        }
    }

    while (leftIndex < leftRange)
    {
        arr[mergeIndex++] = left[leftIndex++];
    }
    while (rightIndex < rightRange)
    {
        arr[mergeIndex++] = right[rightIndex++];
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void bucketSort(int arr[], int len)
{
    const int BUCKET_NUM = 10;
    const int BUCKET_SIZE = 10;
    int buckets[BUCKET_NUM][BUCKET_SIZE];
    int bucketSizes[BUCKET_NUM] = {0};
    for (int i = 0; i < len; ++i)
    {
        int bucketIndex = arr[i] / BUCKET_NUM;
        buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;
    }
    for (int i = 0; i < BUCKET_NUM; ++i)
    {
        for (int j = 0; j < bucketSizes[i]; ++j)
        {
            int tmp = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > tmp)
            {
                buckets[i][k + 1] = buckets[i][k];
                --k;
            }
            buckets[i][k + 1] = tmp;
        }
    }

    int idx = 0;
    for (int i = 0; i < BUCKET_NUM; ++i)
    {
        for (int j = 0; j < bucketSizes[i]; ++j)
        {
            arr[idx++] = buckets[i][j];
        }
    }
}
void countingSort(int arr[], int len)
{
    int *output = new int[len];
    int max = arr[0];
    for (int i = 1; i < len; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int *count = new int[max + 1];
    for (int i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }
    for (int i = 0; i < len; ++i)
    {
        count[arr[i]]++;
    }
    for (int i = 0; i <= max; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = len - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < len; i++)
    {
        arr[i] = output[i];
    }
    delete[] count;
    delete[] output;
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
    std::srand(len);

    std::cout << "--Сорт. быстрая по Ломуто--\n";
    initArr(arr, len);
    quickSortOrig(arr, 0, len - 1);
    printArrAfter(arr, len);

    std::cout << "--Сорт. слиянием--\n";
    initArr(arr, len);
    mergeSort(arr, 0, len - 1);
    printArrAfter(arr, len);

    std::cout << "--Сорт. блочная--\n";
    initArr(arr, len);
    bucketSort(arr, len);
    printArrAfter(arr, len);

    std::cout << "--Сорт. подсчётом--\n";
    initArr(arr, len);
    countingSort(arr, len);
    printArrAfter(arr, len);

    return 0;
}
