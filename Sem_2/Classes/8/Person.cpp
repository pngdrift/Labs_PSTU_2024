#include "Person.h"
#include <iostream>


Person::Person(void)
{
    name = "";
    age = 0;
}

Person::Person(std::string N, int A)
{
    name = N;
    age = A;
}

Person::Person(const Person &person)
{
    name = person.name;
    age = person.age;
}

Person::~Person(void)
{
}

std::string Person::getName()
{
    return name;
}

int Person::getAge()
{
    return age;
}

void Person::setName(std::string value)
{
    name = value;
}

void Person::setAge(int value)
{
    age = value;
}

Person &Person::operator=(const Person &person)
{
    if (&person == this)
    {
        return *this;
    }
    name = person.name;
    age = person.age;
    return *this;
}

void Person::show()
{
    std::cout << "Person:\n";
    std::cout << " name: " << name << "\n";
    std::cout << " age: " << age << "\n";
}

void Person::input()
{
    std::cout << "Person name: ";
    std::cin >> name;
    std::cout << "Person age: ";
    std::cin >> age;
}