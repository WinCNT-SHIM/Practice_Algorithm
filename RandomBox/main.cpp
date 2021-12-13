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

//�ǻ� ���� ����
random_device rd;   // ���� ����̽�(�õ� ��)
mt19937 gen;  // �޸��� Ʈ����Ʈ�� �ǻ� ���� ����

int main()
{
    string fileName;
    cout << "Ȯ�� ���̺� CSV ���ϸ��� �Է��� �ּ���: ";
    cin >> fileName;

    // Ȯ�� ���̺� �о����
    ReadCSV CsvFile(fileName);
    CsvFile.CheckFile();
    CsvFile.ReadCsvFile();
    CsvFile.ReadCsvLine(RawCsvDatas, maxItemNum);
    CsvFile.CheckData(RawCsvDatas, itemTable, maxItemNum + 1);
    CsvFile.Close();

    // ���� �ڽ� ����
    int cntRandomBox = 0;
    cout << "������ Ƚ���� �����ּ���: ";
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
        cout << "������ID : " << iter->first << " ���� Ƚ�� : " << iter->second << endl;
    }

    system("pause");
    return 0;
}
