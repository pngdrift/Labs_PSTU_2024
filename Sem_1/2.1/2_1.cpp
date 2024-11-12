#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int result = 0;
    for (int i = 1; i <= n; ++i)
    {
        result += i;
    }

    std::cout << result << '\n';

    return 0;
}