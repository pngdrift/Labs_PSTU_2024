#include <iostream>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;
    if (sqrt(n)*sqrt(n) != n)
    {
        std::cout << "N не подходит";
    }
    else
    {
        int side = sqrt(n);
        for (int x = 1; x <= side; ++x)
        {
            for (int y = 1; y <= side; ++y)
            {
                std::cout << "* ";
            }
            std::cout << "\n";
        }
    }
}
