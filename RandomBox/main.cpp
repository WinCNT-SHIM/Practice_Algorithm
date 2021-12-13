#include <iostream>
#include <stdlib.h>
#include <string>
#include "ReadCSV.h"

using namespace std;

const int maxItemNum = 100;
const int maxCell = 2;

string RawCsvDatas[maxItemNum + 1];
int itemTable[maxItemNum][maxCell];

int main()
{
    string fileName;
    cout << "Ȯ�� ���̺� CSV ���ϸ��� �Է��� �ּ���: ";
    cin >> fileName;

    ReadCSV CsvFile(fileName);

    CsvFile.CheckFile();
    CsvFile.ReadCsvFile();
    CsvFile.ReadCsvLine(RawCsvDatas, maxItemNum);
    CsvFile.CheckData(RawCsvDatas, itemTable, maxItemNum + 1);

    for (int i = 0; i < sizeof(itemTable)/ sizeof(itemTable[0]); i++)
    {
        cout << itemTable[i][0] << " " << itemTable[i][1] << endl;
    }

    //for (int i = 0; i < maxItemNum; i++)
    //{
    //    cout << i << " : " << RawCsvData[i] << endl;
    //}
    
    CsvFile.Close();
    system("pause");
    return 0;
}
