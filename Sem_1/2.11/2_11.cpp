#include <iostream>

int main()
{
    int count;
    std::cin >> count;
    bool negativeFirst = false, positiveFirst = false;
    for (int i = 1; i <= count; ++i)
    {
        int num;
        std::cin >> num;
        if (!negativeFirst && !positiveFirst)
        {
            if (num < 0)
            {
                negativeFirst = true;
            }
            else if (num > 0)
            {
                positiveFirst = true;
            }
        }
    }
    if (!negativeFirst && !positiveFirst)
    {
        std::cout << "В последовательности только нули!";
    }
    else if (negativeFirst)
    {
        std::cout << "Раньше отрицательное";
    }
    else
    {
        std::cout << "Раньше положительное";
    }
    std::cout << "\n";
    return 0;
}
