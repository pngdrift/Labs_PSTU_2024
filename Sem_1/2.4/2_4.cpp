#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int height = n / 2 + 1;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            int middle = (n - 1) / 2;
            if ((x + y) == middle || (x - y) == middle || y == (height - 1))
            {
                std::cout << '*';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    return 0;
}
