#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "N слишком мал";
    }
    else
    {
        for(int x = 1; x <= n; ++x)
        {
            for(int y = 1; y <= n; ++y)
            {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }
}
