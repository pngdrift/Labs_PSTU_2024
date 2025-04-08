#include <string>

class Car
{
    std::string brand;
    std::string model;
    int price;

  public:
    Car();
    Car(std::string, std::string, int);
    ~Car();
    Car(const Car&);

    std::string getBrand();
    void setBrand(std::string);
    std::string getModel();
    void setModel(std::string);
    int getPrice();
    void setPrice(int);

    void show();
};
