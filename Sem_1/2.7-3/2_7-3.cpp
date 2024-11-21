#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    if (n <= 2)
    {
        std::cout << "N слишком мал";
    }
    else
    {
        for(int x = 1; x <= n; ++x)
        {
            for(int y = 1; y <= n; ++y)
            {
                if (x == 1 || y == 1 || x == n || y == n)
                {
                    std::cout << "*";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
}
