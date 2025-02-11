// 8 ферзей ♕

#include <iostream>
#include <unistd.h>

bool checkQueen(int row, int column, bool table[8][8])
{
    // up check
    for (int i = 0; i < row; ++i)
    {
        if (table[i][column])
        {
            return false;
        }
    }

    // up left
    for (int i = 1; i <= row && (column - i) >= 0; ++i)
    {
        if (table[row - i][column - i])
        {
            return false;
        }
    }

    // up right
    for (int i = 1; i <= row && (column + i) < 8; ++i)
    {
        if (table[row - i][column + i])
        {
            return false;
        }
    }

    return true;
}

void printChess(bool table[8][8])
{
    std::cout << " A  B  C  D  E  F  G  H\n";
    for (int row = 0; row < 8; ++row)
    {
        for (int column = 0; column < 8; ++column)
        {
            if (table[row][column])
            {
                std::cout << "[ф]";
            }
            else
            {
                std::cout << "[ ]";
            }
        }
        std::cout << 8 - row << '\n';
    }
    std::cout << '\n';
}

void set(int row, bool table[8][8], int *counter)
{
    if (row == 8)
    {
        std::cout << ++(*counter) << ":\n";
        printChess(table);
        // usleep(500000);
    }
    else
    {
        for (int column = 0; column < 8; ++column)
        {
            if (checkQueen(row, column, table))
            {
                table[row][column] = true;
                set(row + 1, table, counter);
                table[row][column] = false;
            }
        }
    }
}

int main()
{
    bool queensTable[8][8];
    for (int row = 0; row < 8; ++row)
    {
        for (int column = 0; column < 8; ++column)
        {
            queensTable[row][column] = false;
        }
    }

    int counter = 0;
    set(0, queensTable, &counter);

    return 0;
}
