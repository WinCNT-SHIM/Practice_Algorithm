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

    // CSV(2열)의 정규표현식을 설정
    regex csvFormat(this->regexFormat);

    // 아이템 수 체크
    for (int i = 1; i < maxItemNum; i++)
    {
        if (RawCsvDatas[i] == "")
        {
            cerr << "CSV파일의 헤더를 제외한 아이템 수를 " << maxItemNum << "개 설정해주세요.\n";
            return;
        }
    }

    // 헤더 체크
    if (regex_match(RawCsvDatas[0], csvFormat))
    {
        cerr << RawCsvDatas[0]
            << ": 첫번째 행은 헤더를 입력해주세요." << endl;
        isErr = true;
    }

    //for (int i = 1; i < sizeof(RawCsvDatas); i++)
    // CSV포맷 체크
    for (int i = 1; i < maxItemNum; i++)
    {
        if (!regex_match(RawCsvDatas[i], csvFormat))
        {
            cerr << RawCsvDatas[i] << ": "
                << i << "번째 행이 CSV(2열) 형식이 아닙니다." << endl;
            isErr = true;
        }
    }

    // CSV파일에 문제가 없을 경우
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
