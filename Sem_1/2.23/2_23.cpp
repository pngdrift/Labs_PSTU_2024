#include <cmath>
#include <iostream>

int main()
{
    int n, count = 0;
    float max = -1;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        float elem = sin(n + (i / n));
        if (elem > max)
        {
            max = elem;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        float elem = sin(n + (i / n));
        if (elem == max)
        {
            count++;
        }
    }
    std::cout << count << '\n';
    return 0;
}
