#include <fstream>
#include <iostream>
#include <stack>

void mergeFiles(std::string file1, std::string file2, std::string outputFile)
{
    std::ifstream in1(file1);
    std::ifstream in2(file2);
    int elem1, elem2;
    in1 >> elem1;
    in2 >> elem2;
    std::ofstream out(outputFile);
    while (!in1.eof() && !in2.eof())
    {
        if (elem1 < elem2)
        {
            out << elem1 << '\n';
            in1 >> elem1;
        }
        else
        {
            out << elem2 << '\n';
            in2 >> elem2;
        }
    }
    while (!in1.eof())
    {
        out << elem1 << '\n';
        in1 >> elem1;
    }
    while (!in2.eof())
    {
        out << elem2 << '\n';
        in2 >> elem2;
    }
    in1.close();
    in2.close();
    out.close();
}

void naturalSort(std::string unsortedFile, std::string sortedFile)
{
    std::ifstream inFile(unsortedFile);
    std::ofstream outFile(sortedFile);
    int elem1, elem2;
    inFile >> elem1;
    if (inFile.eof())
    {
        std::cout << unsortedFile << " is empty!\n";
    }
    std::stack<std::string> filesToMerge;
    for (int i = 0; !inFile.eof(); ++i)
    {
        std::string tempFileName = "temp_F" + std::to_string(i) + ".txt";
        filesToMerge.push(tempFileName);
        std::ofstream tempFile(tempFileName);
        inFile >> elem2;
        tempFile << elem1 << '\n';
        while (elem1 < elem2)
        {
            tempFile << elem2 << '\n';
            elem1 = elem2;
            inFile >> elem2;
            if (inFile.eof())
            {
                return;
            }
        }
        tempFile.close();
        elem1 = elem2;
    }
    std::string lastMergeName;
    while (filesToMerge.size() >= 2)
    {
        std::string f1 = filesToMerge.top();
        filesToMerge.pop();
        std::string f2 = filesToMerge.top();
        filesToMerge.pop();
        lastMergeName = "temp_merged" + f1 + f2 + ".txt";
        mergeFiles(f1, f2, lastMergeName);
        filesToMerge.push(lastMergeName);
    }
    std::ifstream finalMerged(lastMergeName);
    int elem;
    for (;;)
    {
        finalMerged >> elem;
        if (finalMerged.eof())
        {
            break;
        }
        outFile << elem << '\n';
    }
    finalMerged.close();
    outFile.close();
}

// const int FICT_SER_IDENT = 999999;
// const int FIBONACCI2p[13] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
// void mergeFilesPolyphase(std::string file1, std::string file2, std::string outputFile)
// {
//     std::ifstream in1(file1);
//     std::ifstream in2(file2);
//     std::ofstream out(outputFile);
//     int elem1, elem2;
//     for (;;)
//     {
//         in1 >> elem1;
//         in2 >> elem2;
//         if (in1.eof() || in2.eof())
//         {
//             break;
//         }
//         if (elem1 < elem2)
//         {
//             out << elem1 << '\n';
//             out << elem2 << '\n';
//         }
//         else
//         {
//             out << elem2 << '\n';
//             if (elem1 != FICT_SER_IDENT)
//             {
//                 out << elem1 << '\n';
//             }
//         }
//     }
//     if (in2.eof())
//     {
//         in2.close();
//         std::ofstream clear(file2);
//         clear.close();
//         std::ofstream remain_out("remain");
//         do
//         {
//             remain_out << elem1 << '\n';
//         } while (in1 >> elem1);
//         remain_out.close();
//         std::ifstream remain_in("remain");
//         std::ofstream f1(file1);
//         while (remain_in >> elem1)
//         {
//             std::cout << elem1 << remain_in.eof() << '\n';
//             f1 << elem1 << "\n";
//         }
//         remain_in.close();
//         f1.close();
//     }
//     else if (in1.eof())
//     {
//         in1.close();
//         std::ofstream clear(file1);
//         clear.close();
//         std::ofstream remain_out("remain");
//         do
//         {
//             remain_out << elem2 << '\n';
//         } while (in2 >> elem2);
//         remain_out.close();
//         std::ifstream remain_in("remain");
//         std::ofstream f2(file2);
//         while (remain_in >> elem2)
//         {
//             std::cout << elem2 << remain_in.eof() << '\n';
//             f2 << elem2 << "\n";
//         }
//         remain_in.close();
//         f2.close();
//     }
// }

// void polyphaseSort(std::string unsortedFile, std::string sortedFile)
// {
//     int elemCount = 0;
//     std::ifstream inFile(unsortedFile);
//     int tmp;
//     while (inFile >> tmp)
//     {
//         ++elemCount;
//     }
//     inFile.clear();
//     inFile.seekg(0);
//     int nearestFibIndex = 0;
//     for (int i = 0; i < 13; ++i)
//     {
//         if (FIBONACCI2p[i] >= elemCount)
//         {
//             nearestFibIndex = i;
//             break;
//         }
//     }
//     int nearestFib = FIBONACCI2p[nearestFibIndex];
//     int fictSerCount = nearestFib - elemCount;
//     int firstFileSeries = FIBONACCI2p[nearestFibIndex - 1];
//     int secondFileSeries = FIBONACCI2p[nearestFibIndex - 2];

//     std::ofstream firstTemp("poly1");
//     std::ofstream secondTemp("poly2");
//     std::cout << fictSerCount << " " << firstFileSeries << " " << secondFileSeries;
//     for (int i = 0; i < fictSerCount; ++i)
//     {
//         firstTemp << FICT_SER_IDENT << '\n';
//     }
//     int elem;
//     for (int i = 0; i < (firstFileSeries - fictSerCount); ++i)
//     {
//         inFile >> elem;
//         firstTemp << elem << '\n';
//     }
//     for (int i = 0; i < secondFileSeries; ++i)
//     {
//         inFile >> elem;
//         secondTemp << elem << '\n';
//     }
//     firstTemp.close();
//     secondTemp.close();
//     mergeFilesPolyphase("poly1", "poly2", "poly3");
//     mergeFilesPolyphase("poly1", "poly3", "poly2");
// }

int main()
{
    naturalSort("unsorted.txt", "sorted1.txt");
    // polyphaseSort("unsorted.txt", "sorted2.txt");
    return 0;
}
