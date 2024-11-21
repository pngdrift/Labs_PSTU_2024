#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int result = 0;
    for (int i = 1; i <= n; ++i)
    {
        int s = 1;
        for (int j = i; j <= i * 2; ++j)
        {
            s *= j;
        }
        result += s;
    }

    std::cout << result << '\n';

    return 0;
}
