#include <iostream>

int main()
{
    int count, max;
    std::cin >> count >> max;
    for (int i = 2; i <= count; ++i)
    {
        int num;
        std::cin >> num;
        if (num > max)
        {
            max = num;
        }
    }
    std::cout << max << '\n';
    return 0;
}
