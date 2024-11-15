#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    unsigned int f = 1;

    int *n_ptr = &n;
    unsigned int *f_ptr = &f;

    for (int i = 1; i <= *n_ptr; ++i)
    {
        *f_ptr *= i;
    }

    std::cout << *f_ptr << '\n';

    return 0;
}
