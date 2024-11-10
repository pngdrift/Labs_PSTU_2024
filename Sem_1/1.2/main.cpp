#include <iostream>

int main()
{
    float a, b;
    
    std::cin >> a >> b;

    if (b == 0)
    {
        std::cout << "Нелья делить на 0" << '\n';
    }
    else 
    {
        float result = a / b;

        std::cout << result << '\n'; 
    }
    
    return 0;
}