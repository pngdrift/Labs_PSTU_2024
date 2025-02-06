// Ханойская башня

#include <iostream>

int rods[3] = {0, 0, 0};
int numDisks = 0;

void printRods()
{
    for (int y = numDisks; y > 0; --y)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (rods[i] >= y)
            {
                std::cout << "▓▓▓▓▓";
            }
            else
            {
                std::cout << "  |  ";
            }
            std::cout << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "  0" << "\t" << "  1" << "\t" << "  2" << "\n\n";
}

void hanoi(int source, int temp, int target, int n)
{
    if (n == 0)
    {
        return;
    }
    hanoi(source, target, temp, n - 1);
    std::cout << "Move disk " << n << ": " << source << " -> " << target << '\n';
    --rods[source];
    ++rods[target];
    printRods();
    hanoi(temp, source, target, n - 1);
}

int main()
{
    std::cout << "Num of disks: ";
    std::cin >> numDisks;
    rods[0] = numDisks;
    printRods();
    hanoi(0, 1, 2, numDisks);
    return 0;
}
