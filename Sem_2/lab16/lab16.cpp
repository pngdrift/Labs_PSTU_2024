#include <algorithm>
#include <iostream>
#include <string>

int *calcPrefixFunc(std::string pat, int size)
{
    int *lps = new int[size];
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < size)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int kmpSearch(std::string text, std::string pattern)
{
    int strSize = text.size();
    int patSize = pattern.size();
    int *lps = calcPrefixFunc(pattern, patSize);
    int strIdx = 0, patIdx = 0;
    while ((strSize - strIdx) >= (patSize - patIdx))
    {
        if (pattern[patIdx] == text[strIdx])
        {
            patIdx++;
            strIdx++;
        }
        if (patIdx == patSize)
        {
            return strIdx - patIdx;
        }
        else if (strIdx < strSize && pattern[patIdx] != text[strIdx])
        {
            if (patIdx != 0)
            {
                patIdx = lps[patIdx - 1];
            }
            else
            {
                strIdx++;
            }
        }
    }
    return -1;
}

const int CHAR_NUM = 256;

void calcCharTable(std::string pattern, int size, int charTable[CHAR_NUM])
{
    for (int i = 0; i < CHAR_NUM; ++i)
    {
        charTable[i] = size;
    }
    for (int i = 0; i < size; ++i)
    {
        charTable[pattern[i]] = size - i - 1;
    }
}

int bmSearch(std::string text, std::string pattern)
{
    int textSize = text.size();
    int patternSize = pattern.size();
    int shiftTable[CHAR_NUM];
    calcCharTable(pattern, patternSize, shiftTable);

    int shift = 0;
    while (shift <= (textSize - patternSize))
    {
        int j = patternSize - 1;
        while (j >= 0 && pattern[j] == text[shift + j])
        {
            --j;
        }
        if (j < 0)
        {
            return shift;
        }
        else
        {
            shift += std::max(1, j - shiftTable[(int)text[shift + j]]);
        }
    }
    return -1;
}

int main()
{
    std::string text;
    std::cout << "Текст: ";
    std::getline(std::cin, text);
    std::string textToFind;
    std::cout << "Текст для поиска: ";
    std::getline(std::cin, textToFind);

    std::cout << "Результаты>\n";
    int result;
    result = kmpSearch(text, textToFind);
    std::cout << "По Кнут-Моррис-Пратт: " << result << std::endl;
    result = bmSearch(text, textToFind);
    std::cout << "По         Бойер-Мур: " << result << std::endl;

    return 0;
}
