#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ReadCSV
{
private:
    string filePath;
    ifstream fileInput;
public:
    // ������, �Ҹ���
    ReadCSV(string setPath);
    ~ReadCSV();
    // �Լ�
    void CheckFile();
    void ReadCsvFile();
    void ReadCsvLine(string RawCsvData[], int maxItemNum);
    bool CheckData(string RawCsvData[], int itemTable[][2]);
    void Close();
};

