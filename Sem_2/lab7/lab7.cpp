// 11. Написать перегруженные функции и основную программу,
// которая их вызывает
// а) для умножения десятичных дробей;
// б) для умножения обыкновенных дробей.

#include <iostream>

double multiply(double a, double b)
{
    return a * b;
}

double multiply(double numerA, double denomA, double numerB, double denomB)
{
    return (numerA * numerB) / (denomA * denomB);
}


int main()
{
    std::cout << "Input two numbers: ";
    double a, b;
    std::cin >> a >> b;
    double result1 = multiply(3, 4);
    std::cout << "multiply Result " << result1 << '\n';
    std::cout << '\n';
    double numerA, denomA, numerB, denomB;
    std::cout << "Input two numbers with numerator and denominator (1 2 -> 1/2): ";
    std::cin >> numerA >> denomA >> numerB >> denomB;
    double result2 = multiply(numerA,denomA,  numerB,denomB);
    std::cout << "multiply Result " << result2 << '\n';

    return 0;
}
