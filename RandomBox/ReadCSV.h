#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

class ReadCSV
{
private:
    string filePath;
    ifstream fileInput;
    string regexFormat;
public:
    // 생성자, 소멸자
    ReadCSV(string setPath);
    ~ReadCSV();
    // 함수
    void CheckFile();
    void ReadCsvFile();
    void ReadCsvLine(string RawCsvDatas[], int maxItemNum);
    void CheckData(string RawCsvDatas[], int itemTable[][2], int maxItemNum);
    void Close();
};

