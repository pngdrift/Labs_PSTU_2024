struct Salary
{
    float first;  // оклад
    unsigned int second; // кол. отработанных дн.

    void Init(float, unsigned int);
    void Read();
    void Show();

    float summa();
};
