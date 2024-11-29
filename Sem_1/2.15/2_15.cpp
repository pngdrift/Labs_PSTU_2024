#include <cmath>
#include <iostream>

int main()
{
    int n, s;
    std::cin >> n >> s;
    int divider = 10;
    bool result = false;
    while (n != 0 && !result)
    {
        int remain = n % divider;
        int digit = remain / (divider / 10);
        if (s == digit)
        {
            result = true;
        }
        n -= remain;
        divider *= 10;
    }
    if (result)
    {
        std::cout << "Входит" << "\n";
    }
    else
    {
        std::cout << "Не Входит" << "\n";
    }
    return 0;
}
