#include <cmath>
#include <iostream>

int main()
{
    float n, s;
    std::cin >> n >> s;
    bool result = false;
    for (int i = 1; i <= n; ++i)
    {
        float a = sin(n + (i / n));
        if (a == s)
        {
            result = true;
        }
    }
    if (result)
    {
        std::cout << "Есть!" << "\n";
    }
    else
    {
        std::cout << "Нет" << "\n";
    }
    return 0;
}
