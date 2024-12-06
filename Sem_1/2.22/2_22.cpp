#include <cmath>
#include <iostream>

int main()
{
    int n, nomer;
    std::cin >> n;
    float max = -1;
    for (int i = 1; i <= n; ++i)
    {
        float elem = sin(n + (i / n));
        if (elem > max)
        {
            max = elem;
            nomer = i;
        }
    }
    std::cout << "Макс:" << max << " Номер:" << nomer << '\n';
    return 0;
}
