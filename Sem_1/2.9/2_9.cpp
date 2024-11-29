#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int d = n / 2;

    // Back face
    for (int i = 0; i < d; ++i)
    {
        std::cout << " ";
    }
    for (int i = 0; i < n; ++i)
    {
        std::cout << "* ";
    }
    std::cout << "\n";

    // Upper diagonals
    for (int i = 0; i < (d - 1); ++i)
    {
        for (int j = 1; j < (d - i); ++j)
        {
            std::cout << " ";
        }
        std::cout << "*";
        for (int j = 0; j < (n - 2); ++j)
        {
            std::cout << " " << " ";
        }
        std::cout << "* ";
        for (int j = 0; j < i; ++j)
        {
            std::cout << " ";
        }
        std::cout << "*" << "\n";
    }

    // Front top face + piece back face
    for (int i = 0; i < n; ++i)
    {
        std::cout << "* ";
    }
    for (int i = 0; i < (d - 2); ++i)
    {
        std::cout << " ";
    }
    std::cout << "*" << '\n';

    // Side faces
    for (int i = 0; i < (n - d - 1); ++i)
    {
        std::cout << "* ";
        for (int j = 0; j < (n - 2); ++j)
        {
            std::cout << " " << " ";
        }
        std::cout << "* ";
        for (int i = 0; i < (d - 2); ++i)
        {
            std::cout << " ";
        }
        std::cout << "*" << '\n';
    }

    // Bottom diagonals
    for (int i = 0; i < (d - 1); ++i)
    {
        std::cout << "* ";
        for (int j = 0; j < (n - 2); ++j)
        {
            std::cout << " " << " ";
        }
        std::cout << "* ";
        for (int j = 1; j < (d - i - 1); ++j)
        {
            std::cout << " ";
        }
        std::cout << "*" << "\n";
    }

    // Bottom face
    for (int i = 0; i < n; i++)
    {
        std::cout << "* ";
    }
    std::cout << "\n";

    return 0;
}
