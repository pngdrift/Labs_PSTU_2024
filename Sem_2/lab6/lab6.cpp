// Постановка задачи
// Задана строка, состоящая из символов. Символы
// объединяются в слова. Слова друг от друга отделяются
// одним или несколькими пробелами. В конце текста ставится
// точка. Текст содержит не более 255 символов. Выполнить
// ввод строки, используя функцию Gets(s) и обработку
// строки в соответствии со своим вариантом.
//
// Вариант 11
// Преобразовать строку таким образом, чтобы в ее
// начале были записаны слова, содержащие только цифры,
// потом слова, содержащие только буквы, а затем слова,
// которые содержат и буквы и цифры.

#include <cstdio>
#include <iostream>
#include <string.h>

int main()
{
    const int MAX_CHR_LEN = 255;
    char line[MAX_CHR_LEN];
    std::cout << "Строка: ";
    std::cin.getline(line, MAX_CHR_LEN);

    char digitWords[MAX_CHR_LEN] = "";
    char letterWords[MAX_CHR_LEN] = "";
    char mixedWords[MAX_CHR_LEN] = "";

    int start = 0;
    int len = strlen(line);
    bool hasDigit = false, hasLetter = false;
    for (int i = 0; i < len; ++i)
    {
        char symb = line[i];
        if (symb != ' ' && symb != '.')
        {
            if (48 <= symb && symb <= 57)
            {
                hasDigit = true;
            }
            else
            {
                hasLetter = true;
            }
        }
        else
        {
            int ssLen = i - start + 2;
            char substring[ssLen];
            substring[ssLen - 1] = '\0';
            strncpy(substring, line + start, ssLen - 2);
            substring[ssLen - 2] = ' ';
            if (!hasDigit && hasLetter)
            {
                strcat(letterWords, substring);
            }
            else if (!hasLetter && hasDigit)
            {
                strcat(digitWords, substring);
            }
            else
            {
                strcat(mixedWords, substring);
            }
            // std::cout << "START:" << start << " END:" << i+1 << " SS:" << substring << "\n\n";
            start = i++;
            hasDigit = hasLetter = false;
        }
    }

    line[0] = '\0';
    strcat(line, digitWords);
    strcat(line, letterWords);
    strcat(line, mixedWords);

    std::cout << "Результат: " << line << '\n';

    return 0;
}
