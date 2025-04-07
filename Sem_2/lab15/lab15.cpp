#include <algorithm>
#include <ctime>
#include <iostream>

int linear_search(int arr[], int arrLen, int x)
{
    for (int i = 0; i < arrLen; ++i)
    {
        if (arr[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(int arr[], int low, int high, int x)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x)
        {
            return mid;
        }
        if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

//             (x - arr[low]) * (high - low)
// pos = low + -----------------------------
//                 arr[high] - arr[low]
int interpolation_search(int arr[], int low, int high, int x)
{
    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        if (low == high)
        {
            if (arr[high] == x)
            {
                return high;
            }
            return -1;
        }
        int pos = low + ((x - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[pos] == x)
        {
            return pos;
        }
        if (arr[pos] < x)
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }
    return -1;
}

int main()
{
    int N = 33;
    int arr[N];
    std::srand(time(0));
    for (int i = 0; i < N; ++i)
    {
        arr[i] = ((double)std::rand() / RAND_MAX) * (99 - 10) + 10;
    }
    std::sort(arr, arr + N);
    for (int i = 0; i < N; ++i)
    {
        std::cout << arr[i] << " ";
    }
    int x;
    std::cout << std::endl << "Число для поиска: ";
    std::cin >> x;
    int result;
    std::cout << "Результаты>" << std::endl;

    result = linear_search(arr, N, x);
    std::cout << "  По линейному поиску: " << result << std::endl;

    result = binary_search(arr, 0, N - 1, x);
    std::cout << "  По бинарному поиску: " << result << std::endl;

    result = interpolation_search(arr, 0, N - 1, x);
    std::cout << "По интерполяц. поиску: " << result << std::endl;

    return 0;
}
