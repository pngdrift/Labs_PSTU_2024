#include <cmath>
#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int sum = 0;
    for (int num = 1; num < n; ++num)
    {
        if(num % 2 == 0)
        {
            sum += num;
        }
        else
        {
            sum -= num;
        }
    }
    std::cout << sum << '\n';
    return 0;
}
