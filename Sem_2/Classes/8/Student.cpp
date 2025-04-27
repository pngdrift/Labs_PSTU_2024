#include "Student.h"
#include <iostream>


Student::Student(void) : Person()
{
    rating = 0;
}

Student::~Student()
{
}

void Student::show()
{
    std::cout << "Student:\n";
    std::cout << " name: " << name << "\n";
    std::cout << " age: " << age << "\n";
    std::cout << " rating: " << rating << "\n";
}

void Student::input()
{
    std::cout << "Student name: ";
    std::cin >> name;
    std::cout << "Student age: ";
    std::cin >> age;
    std::cout << "Student rating: ";
    std::cin >> rating;
}

Student::Student(std::string N, int A, float R) : Person(N, A)
{
    name = N;
    age = A;
    rating = R;
}

Student::Student(const Student &student)
{
    name = student.name;
    age = student.age;
    rating = student.rating;
}

Student &Student::operator=(const Student &student)
{
    if (&student == this)
    {
        return *this;
    }
    name = student.name;
    age = student.age;
    rating = student.rating;
    return *this;
}

float Student::getRating()
{
    return rating;
}

void Student::setRating(float value)
{
    rating = value;
}