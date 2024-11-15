#include <iostream>

int main()
{
    int len, num, *ptr = &num;
    std::cin >> len >> *ptr;
    int max = *ptr, min = *ptr;
    for (int i = 2; i <= len; ++i)
    {
        std::cin >> *ptr;
        if (*ptr > max){
            max = *ptr;
        }
        else if (*ptr < min){
            min = *ptr;
        }
    }
    std::cout << "Max: " << max << '\n';
    std::cout << "Min: " << min << '\n';
    return 0;
}
