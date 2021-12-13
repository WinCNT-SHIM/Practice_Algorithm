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
    // ������, �Ҹ���
    ReadCSV(string setPath);
    ~ReadCSV();
    // �Լ�
    void CheckFile();
    void ReadCsvFile();
    void ReadCsvLine(string RawCsvDatas[], int maxItemNum);
    void CheckData(string RawCsvDatas[], int itemTable[][2], int maxItemNum);
    void Close();
};

