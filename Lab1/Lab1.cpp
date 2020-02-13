#include <iostream>
#include <fstream>
#include "CBor.h"
#include <ctime>
#include <string>
#include <algorithm>
// Смиренский А.Р ПСм-21. Ахо-Корасик.

int main()
{
    Bor myBor; // создание бора

    //
    setlocale(LC_ALL, "rus");
    std::ifstream inputFile("input1.txt");
    int countwords;
    char buff[101];    

    inputFile >> countwords;
    inputFile.getline(buff, 101);

    // считывание слов
    for (int i = 0; i < countwords; i++)
    {
        inputFile.getline(buff, 101);
        myBor.addStrToBor(buff);
    }

    // считывание текста
    inputFile.getline(buff, 101);
    std::string fileWithText = buff;

    std::ifstream textFile(fileWithText);
    
    std::string text = std::string(std::istreambuf_iterator<char> (textFile), std::istreambuf_iterator<char>());    

    

    // поиск вхождений
    unsigned int startTime = clock();
    myBor.findAllInStr(text);
    unsigned int endTime = clock();
    int kek = 1;
    std::cout << std::endl << "Work time: " << (endTime - startTime) << std::endl;
}