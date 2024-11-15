#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;

    int *a_ptr = &a;
    int *b_ptr = &b;

    std::cout << *a_ptr + *b_ptr << '\n';

    return 0;
}
