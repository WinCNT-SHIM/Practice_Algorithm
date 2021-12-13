#include "ReadCSV.h"

ReadCSV::ReadCSV(string setPath)
{
    ReadCSV::filePath = setPath;
}

ReadCSV::~ReadCSV()
{
}

void ReadCSV::CheckFile()
{
    if (this->filePath.length() < 5
        || this->filePath.substr(this->filePath.length() - 4) != ".csv")
    {
        cerr << "CSV파일이 아닙니다." << endl
            << "CSV파일을 지정해주세요.";
        exit(100);
    }
}

void ReadCSV::ReadCsvFile()
{
    fileInput.open(this->filePath);

    if (fileInput.fail())
    {
        cerr << "파일을 찾을 수 없습니다." << endl;
        exit(100);
    }
}

void ReadCSV::ReadCsvLine(string RawCsvData[], int maxItemNum)
{
    int i = 0;
    while (!fileInput.eof())
    {
        getline(fileInput, RawCsvData[i++]);
    }
}

bool ReadCSV::CheckData(string RawCsvData[], int itemTable[][2])
{
    return false;
}

void ReadCSV::Close()
{
    fileInput.close();
}
