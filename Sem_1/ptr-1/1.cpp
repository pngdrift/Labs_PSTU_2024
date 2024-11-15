#include <iostream>

int main()
{
    int a, b;

    int *a_ptr = &a, *b_ptr = &b;

    std::cin >> *a_ptr >> *b_ptr;

    int temp = *a_ptr;

    *a_ptr = *b_ptr;
    *b_ptr = temp;

    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    return 0;
}
