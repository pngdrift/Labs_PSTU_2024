#include <cmath>
#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int sum = 0, divider = 10;
    while (n != 0)
    {
        int remain = n % divider;
        sum += remain / (divider / 10);
        n -= remain;
        divider *= 10;
    }
    std::cout << sum << "\n";
    return 0;
}
