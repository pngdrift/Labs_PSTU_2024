#include <cmath>
#include <iostream>

int main()
{
    int n, x;
    std::cout << "Введите n и x: ";
    std::cin >> n >> x;
    float result = 1;
    unsigned int factorial = 1;
    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
        result += pow(x, i) / factorial;
    }
    std::cout << result << '\n';
    return 0;
}
