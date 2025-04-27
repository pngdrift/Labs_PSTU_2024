#pragma once
#include "Object.h"
#include <iostream>
#include <string>

class Person : public Object
{
  protected:
    std::string name;
    int age;

  public:
    Person(void);
    Person(std::string, int);
    Person(const Person &);
    ~Person(void);
    std::string getName();
    int getAge();
    void setName(std::string);
    void setAge(int);
    Person &operator=(const Person &);
    void show();
    void input();
};