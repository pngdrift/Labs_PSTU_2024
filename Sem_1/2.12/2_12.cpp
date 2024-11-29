#include <iostream>

int main()
{
    int count, max, min;
    std::cin >> count >> max;
    min = max;
    for (int i = 2; i <= count; ++i)
    {
        int num;
        std::cin >> num;
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
    }
    std::cout << max + min << '\n';
    return 0;
}
