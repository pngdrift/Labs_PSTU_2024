#include <cmath>
#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int divider = 10;
    while (n != 0)
    {
        int remain = n % divider;
        int digit = remain / (divider / 10);
        std::cout << digit;
        n -= remain;
        divider *= 10;
    }
    std::cout << "\n";
    return 0;
}
