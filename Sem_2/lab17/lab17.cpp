// 11 вариант
// Данные: ФИО, №паспорта, №телефона
// Ключ: №паспорта

#include <iostream>
#include <string>

std::string name[25] = {"John", "Lann", "David",   "Sarah",    "Vlad",   "Sasha",  "Yuri",   "Dmitry", "Pavel",
                        "Ivan", "Alex", "Maksim",  "Vladimir", "Sergey", "Andrey", "Roman",  "Kirill", "Dave",
                        "Lavr", "Oleg", "Nikolay", "Gleb",     "Igor",   "Kostya", "Mikhail"};

std::string surname[25] = {"Ivanov",     "Petrov",   "Smirnov", "Kuznetsov", "Nikolaev",  "Mikhailov", "Alexandrov",
                           "Romanov",    "Yesutin",  "Borisov", "Sergeyev",  "Babushkin", "Dmitriev",  "Pavlov",
                           "Vladimirov", "Kirillov", "Maximov", "Duskaev",   "Karpov",    "Husainov",  "Sokolov",
                           "Vasilev",    "Zaytsev",  "Kuzmin",  "Orlov"};

std::string patronymic[25] = {"Karpovich",     "Petrovich",     "Rinatovich",   "Andreyevich",  "Vladimirovich",
                              "Nikolayevich",  "Alexandrovich", "Mikhailovich", "Viktorovich",  "Borisovich",
                              "Dmitriyevich",  "Pavlovich",     "Romanovich",   "Kirillovich",  "Maximovich",
                              "Vladimirovich", "Sergeyevich",   "Ivanovich",    "Alekseyevich", "Nazarovich",
                              "Vladimirovich", "Mikhailovich",  "Andreyevich",  "Petrovich",    "Dmitriyevich"};

std::string phone[25] = {"8-912-345-67-89", "8-901-234-56-78", "7-495-123-45-67", "8-911-765-43-21", "8-902-678-90-12",
                         "8-913-456-78-90", "7-499-234-56-78", "8-910-123-45-67", "8-903-765-43-21", "8-904-678-90-12",
                         "8-905-456-78-90", "7-496-234-56-78", "8-906-123-45-67", "8-907-765-43-21", "8-908-678-90-12",
                         "8-909-456-78-90", "7-497-234-56-78", "8-914-123-45-67", "8-915-765-43-21", "8-916-678-90-12",
                         "8-917-456-78-90", "8-918-123-45-67", "8-919-765-43-21", "8-920-678-90-12", "8-921-456-78-90"};

std::string passport[25] = {"123456", "789012", "345678", "901234", "567890", "234567", "890123", "456789", "678901",
                            "123890", "567123", "890456", "234901", "789567", "456123", "901789", "123345", "424204",
                            "428933", "100034", "111111", "222222", "333333", "444444", "824233"};

int collisions = 0;

struct Person
{
    std::string name;
    std::string phone;
    std::string passport;
    Person()
    {
        name = phone = passport = "NULL";
    }
};

struct hashTable
{
    Person *arr;
    hashTable(int size)
    {
        arr = new Person[size];
    }
    void insert(Person p, int size);
    Person pop(std::string passport, int size);
    void search(std::string passport, int size);
};

int hash(std::string passport, int size)
{
    unsigned int a = passport[0] - '0';
    unsigned int b = passport[1] - '5';
    unsigned int c = passport[2] - '9';
    unsigned int d = passport[3] - '0';
    unsigned int e = passport[4] - '8';
    unsigned int f = passport[5] - '1';
    return (a * 17 + b * 19 + c * 23 + d * 29 + e * 31 + f * 37) % size;
}

void hashTable::insert(Person p, int size)
{
    int idx = hash(p.passport, size);
    int hash = idx;
    if (arr[idx].name == "NULL")
    {
        arr[idx] = p;
        return;
    }
    while (idx < size)
    {
        if (arr[idx].name == "NULL")
        {
            arr[idx] = p;
            return;
        }
        idx++;
        collisions++;
    }
    if (idx >= size)
    {
        idx = 0;
        collisions++;
        while (idx < hash)
        {
            if (arr[idx].name == "NULL")
            {
                arr[idx] = p;
                return;
            }
            idx++;
            collisions++;
        }
    }
}

Person hashTable::pop(std::string passport, int size)
{
    int idx = hash(passport, size);
    int hash = idx;
    if (arr[idx].passport == passport)
    {
        Person tmp = arr[idx];
        arr[idx] = Person();
        return tmp;
    }
    while (idx < size)
    {
        if (arr[idx].passport == passport)
        {
            Person tmp = arr[idx];
            arr[idx] = Person();
            return tmp;
        }
        idx++;
    }
    if (idx >= size)
    {
        idx = 0;
        while (idx < hash)
        {
            if (arr[idx].passport == passport)
            {
                Person tmp = arr[idx];
                arr[idx] = Person();
                return tmp;
            }
            idx++;
        }
    };
}

void hashTable::search(std::string passport, int size)
{
    int idx = hash(passport, size);
    int hash = idx;
    while (arr[idx].passport != passport && idx < size)
    {
        idx++;
    }
    if (idx < size)
    {
        std::cout << "Person with passport " << passport << " was found, idx: " << idx << '\n';
        return;
    }
    idx = 0;
    while (arr[idx].passport != passport && idx < hash)
    {
        idx++;
    }
    if (idx < hash)
    {
        std::cout << "Person with passport " << passport << " was found, idx: " << idx << "\n";
        return;
    }
    std::cout << "Person with passport " << passport << " didn't found\n";
    return;
}

void displayPerson(Person p)
{
    std::cout << "===\n";
    std::cout << "ФИО: " << p.name << '\n';
    std::cout << "Телефон: " << p.phone << '\n';
    std::cout << "Паспорт: " << p.passport << '\n';
    std::cout << "===\n";
}

void displayHashTable(hashTable *table, int size)
{
    for (int i = 0; i < size; i++)
    {
        displayPerson(table->arr[i]);
    }
}

std::string genName()
{
    return name[rand() % 25] + " " + surname[rand() % 25] + " " + patronymic[rand() % 25];
}

int main()
{
    int sizeArr;
    std::cout << "size arr: ";
    std::cin >> sizeArr;
    srand(sizeArr);
    hashTable table(sizeArr);

    for (int i = 0; i < sizeArr; i++)
    {
        Person person;
        person.name = genName();
        person.phone = phone[rand() % 25];
        person.passport = passport[rand() % 25];
        table.insert(person, sizeArr);
    }

    displayHashTable(&table, sizeArr);
    table.search("678901", sizeArr);

    std::cout << "Collisions " << collisions << '\n';
    return 0;
}
