#include <iostream>
#include <stdlib.h>
#include <string>
#include <random>
#include <vector>
#include <map>
#include "ReadCSV.h"

using namespace std;

const int maxItemNum = 100;
const int maxCell = 2;

string RawCsvDatas[maxItemNum + 1];
int itemTable[maxItemNum][maxCell];

//의사 난수 생성
random_device rd;   // 랜덤 디바이스(시드 값)
mt19937 gen;  // 메르센 트위스트로 의사 난수 생성

int main()
{
    string fileName;
    cout << "확률 테이블 CSV 파일명을 입력해 주세요: ";
    cin >> fileName;

    // 확률 테이블 읽어오기
    ReadCSV CsvFile(fileName);
    CsvFile.CheckFile();
    CsvFile.ReadCsvFile();
    CsvFile.ReadCsvLine(RawCsvDatas, maxItemNum);
    CsvFile.CheckData(RawCsvDatas, itemTable, maxItemNum + 1);
    CsvFile.Close();

    // 랜덤 박스 시행
    int cntRandomBox = 0;
    cout << "시행할 횟수를 정해주세요: ";
    cin >> cntRandomBox;
    
    vector<int> tmpArr(maxItemNum);
    for (int i = 0; i < maxItemNum; i++)
    {
        tmpArr.at(i) = itemTable[i][1];
    }

    discrete_distribution<int> discreteDist(tmpArr.begin(), tmpArr.end());

    map<int, int> gachaRes;
    for (int i = 0; i < cntRandomBox; i++)
    {
        ++gachaRes[itemTable[discreteDist(gen)][0]];
    }

    map<int, int>::iterator iter;
    for (iter = gachaRes.begin(); iter != gachaRes.end(); iter++)
    {
        cout << "아이템ID : " << iter->first << " 나온 횟수 : " << iter->second << endl;
    }

    system("pause");
    return 0;
}
