#include <iostream>
#include <stdlib.h>
#include <string>
#include "ReadCSV.h"

using namespace std;

const int maxItemNum = 100;
const int maxCell = 2;

string RawCsvData[maxItemNum];
int itemTable[maxItemNum][maxCell];

int main()
{
    string fileName;
    cout << "Ȯ�� ���̺� CSV ���ϸ��� �Է��� �ּ���: ";
    cin >> fileName;

    ReadCSV CsvFile(fileName);

    CsvFile.CheckFile();
    CsvFile.ReadCsvFile();
    CsvFile.ReadCsvLine(RawCsvData, maxItemNum);



    //for (int i = 0; i < maxItemNum; i++)
    //{
    //    cout << i << " : " << RawCsvData[i] << endl;
    //}
    
    CsvFile.Close();
    system("pause");
    return 0;
}
