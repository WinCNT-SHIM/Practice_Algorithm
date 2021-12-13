#include "ReadCSV.h"

ReadCSV::ReadCSV(string setPath)
{
    this->regexFormat = "^[0-9]*,[0-9]*$";
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
        cerr << "CSV������ �ƴմϴ�." << endl
            << "CSV������ �������ּ���.";
        exit(100);
    }
}

void ReadCSV::ReadCsvFile()
{
    fileInput.open(this->filePath);

    if (fileInput.fail())
    {
        cerr << "������ ã�� �� �����ϴ�." << endl;
        exit(100);
    }
}

void ReadCSV::ReadCsvLine(string RawCsvDatas[], int maxItemNum)
{
    int i = 0;
    while (!fileInput.eof())
    {
        getline(fileInput, RawCsvDatas[i++]);
    }
}

void ReadCSV::CheckData(string RawCsvDatas[], int itemTable[][2], int maxItemNum)
{
    bool isErr = false;

    // CSV(2��)�� ����ǥ������ ����
    regex csvFormat(this->regexFormat);

    // ������ �� üũ
    for (int i = 1; i < maxItemNum; i++)
    {
        if (RawCsvDatas[i] == "")
        {
            cerr << "CSV������ ����� ������ ������ ���� " << maxItemNum << "�� �������ּ���.\n";
            return;
        }
    }

    // ��� üũ
    if (regex_match(RawCsvDatas[0], csvFormat))
    {
        cerr << RawCsvDatas[0]
            << ": ù��° ���� ����� �Է����ּ���." << endl;
        isErr = true;
    }

    //for (int i = 1; i < sizeof(RawCsvDatas); i++)
    // CSV���� üũ
    for (int i = 1; i < maxItemNum; i++)
    {
        if (!regex_match(RawCsvDatas[i], csvFormat))
        {
            cerr << RawCsvDatas[i] << ": "
                << i << "��° ���� CSV(2��) ������ �ƴմϴ�." << endl;
            isErr = true;
        }
    }

    // CSV���Ͽ� ������ ���� ���
    if (!isErr)
    {
        for (int i = 1; i < maxItemNum; i++)
        {
            size_t tmp = RawCsvDatas[i].find(',');
            itemTable[i - 1][0] = stoi(RawCsvDatas[i].substr(0, tmp - 1));
            itemTable[i - 1][1] = stoi(RawCsvDatas[i].substr(tmp + 1));
        }
    }
    else
    {
        return;
    }
}

void ReadCSV::Close()
{
    fileInput.close();
}
