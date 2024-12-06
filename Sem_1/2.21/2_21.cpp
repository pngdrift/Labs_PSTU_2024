#include <iostream>

int main()
{
    bool zeroFound = false, sorted = true;
    int prevNum = 0, num;
    while (!zeroFound)
    {
        std::cin >> num;
        if (num == 0)
        {
            zeroFound = true;
        }
        else
        {
            if (prevNum > num)
            {
                sorted = false;
            }
        }
        prevNum = num;
    }
    if(sorted)
    {
        std::cout << "упорядочены по возрастанию" << '\n';
    }
    else
    {
        std::cout << "НЕ упорядочены по возрастанию" << '\n';
    }
    return 0;
}
