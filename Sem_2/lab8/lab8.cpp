// 11. Написать функцию sum с переменным числом параметров,
// которая находит сумму заданных обыкновенных дробей.
// Написать вызывающую функцию main, которая обращается к
// функции sum не менее трех раз с количеством параметров
// 5, 10, 12.

#include <iostream>
#include <cstdarg>

float sum(int firstNumer, ...)
{
    va_list a;
    va_start(a, firstNumer);
    float result = 0;
    float numer = firstNumer, denom = 0;
    int arg;
    while((arg = va_arg(a, int)) != 0)
    {
        if (numer == 0)
        {
            numer = arg;
        }
        else if (denom == 0)
        {
            denom = arg;

            result += numer / denom;
            numer = denom = 0;
        }
    }
    va_end(a);
    return result;
}

int main()
{
    float s1 = sum(3,3, 7,7, 0);
    std::cout << "Sum1: " << s1 << '\n';

    float s2 = sum(1,2, 2,4, 4,8, 8,16, 16,32, 0);
    std::cout << "Sum2: " << s2 << '\n';

    float s3 = sum(3,1, 1,3, 59,59, 50,10, 42,3, 3,3, 0);
    std::cout << "Sum3: " << s3 << '\n';

    return 0;
}
