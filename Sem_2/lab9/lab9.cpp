// 11.
// 1) Скопировать из файла F1 в файл F2 все строки, кроме той
// строки, которая содержит самое короткое слово.
// 2) Напечатать номер этой строки.

#include <cstdio>
#include <iostream>

int main()
{
    FILE *input = fopen("./F1.txt", "r");
    FILE *output = fopen("./F2.txt", "w");

    char buff[300];
    int i = 0, lineLength = 0, minLen = 100000;
    int minlineEndPos, lineNum = 1, minLineNum;
    for (char ch; (ch = fgetc(input)) != EOF; ++i)
    {
        if (ch != '\n')
        {
            ++lineLength;
        }
        else
        {
            if (lineLength < minLen)
            {
                minlineEndPos = i;
                minLen = lineLength;
                minLineNum = lineNum;
            }
            ++lineNum;
            lineLength = 0;
        }
        buff[i] = ch;
    }
    buff[i] = '\0';
    i = 0;
    for (char ch; (ch = buff[i]) != 0; ++i)
    {
        if (i < (minlineEndPos - minLen) || minlineEndPos < i)
        {
            fputc(ch, output);
        }
    }
    fclose(output);
    std::cout << "Result: " << minLineNum << '\n';
    return 0;
}