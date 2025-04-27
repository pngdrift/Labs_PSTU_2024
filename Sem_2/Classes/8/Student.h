#pragma once
#include "Person.h"
#include <iostream>
#include <string>



class Student : public Person
{
  protected:
    float rating;

  public:
    Student(void);
    Student(std::string, int, float);
    Student(const Student &);
    ~Student(void);
    float getRating();
    void setRating(float);
    void show();
    void input();
    Student &operator=(const Student &);
};
