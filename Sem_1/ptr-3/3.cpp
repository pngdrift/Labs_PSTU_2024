#include <iostream>

int main()
{
    float a, b;
    std::cin >> a >> b;

    float *a_ptr = &a;
    float *b_ptr = &b;

    std::cout << *a_ptr + *b_ptr << '\n';

    return 0;
}
