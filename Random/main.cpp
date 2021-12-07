#include <stdlib.h>
#include <iomanip>
#include <random>
#include <iostream>
#include <map>
#define GACHAMAX 100000

using namespace std;

// Ȯ�� ���̺�
map<char, double> gachaTable;
/// <summary>
/// �õ尪�� ��� ���� random_device ����
///   Random Device�� �ü���� �����ϴ� ��¥ ������ ����� �� �ִ�
///   ��, ��¥ ������ ���� �ӵ��� �ſ� ������ ������ �ַ� �õ� ������ ����Ѵ�
/// </summary>
random_device rd;
/// <summary>
/// random_device���� ���� ��ü(��¥ ����)�� �ǻ� ���� ���� ������ ��ü�� ����
///   mt19937�� �޸��� Ʈ������ �˰����� ����ϴ� �������� ������ �ǻ� ������ �����Ѵ�
///   (��, ��ü ũ�Ⱑ 2KB �̻��̹Ƿ�, �޸𸮰� ������ ���� minstd_rand�� ������ �� ����)
/// </summary>
mt19937 gen(rd());
/// <summary>
/// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����
/// </summary>
uniform_real_distribution<> dist(0, 1);

void Init()
{
    // ��í ���̺� ����
    gachaTable.insert({ 'A', 0.01 });
    gachaTable.insert({ 'B', 0.03 });
    gachaTable.insert({ 'C', 0.06 });
    gachaTable.insert({ 'D', 0.08 });
    gachaTable.insert({ 'E', 0.12 });
    gachaTable.insert({ 'F', 0.20 });
    gachaTable.insert({ 'G', 0.23 });
    gachaTable.insert({ 'H', 0.27 });
}

char gachaUniform()
{
    double tmp = dist(gen);
    if (tmp <= gachaTable.at('A'))
    {
        return 'A';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B'))
    {
        return 'B';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C'))
    {
        return 'C';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C') + gachaTable.at('D'))
    {
        return 'D';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C') + gachaTable.at('D')
        + gachaTable.at('E'))
    {
        return 'E';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C') + gachaTable.at('D')
        + gachaTable.at('E') + gachaTable.at('F'))
    {
        return 'F';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C') + gachaTable.at('D')
        + gachaTable.at('E') + gachaTable.at('F') + gachaTable.at('G'))
    {
        return 'G';
    }
    else if (tmp <= gachaTable.at('A') + gachaTable.at('B') + gachaTable.at('C') + gachaTable.at('D')
        + gachaTable.at('E') + gachaTable.at('F') + gachaTable.at('G') + gachaTable.at('H'))
    {
        return 'H';
    }
}

int main()
{
    // Ȯ�� ���̺� ����
    Init();
    // ��í ��� ���� ����
    map<char, int> gachaResult;

    cout << GACHAMAX << "�� ��í" << endl;
    for (int i = 0; i < GACHAMAX; i++)
    {
        char tmpRes = gachaUniform();
        ++gachaResult[tmpRes];
    }

    cout << "��í ���" << endl;
    cout << "A: " << gachaResult['A'] << "��(" << (double)gachaResult['A'] * 100 / GACHAMAX << "%)" << endl;
    cout << "B: " << gachaResult['B'] << "��(" << (double)gachaResult['B'] * 100 / GACHAMAX << "%)" << endl;
    cout << "C: " << gachaResult['C'] << "��(" << (double)gachaResult['C'] * 100 / GACHAMAX << "%)" << endl;
    cout << "D: " << gachaResult['D'] << "��(" << (double)gachaResult['D'] * 100 / GACHAMAX << "%)" << endl;
    cout << "E: " << gachaResult['E'] << "��(" << (double)gachaResult['E'] * 100 / GACHAMAX << "%)" << endl;
    cout << "F: " << gachaResult['F'] << "��(" << (double)gachaResult['F'] * 100 / GACHAMAX << "%)" << endl;
    cout << "G: " << gachaResult['G'] << "��(" << (double)gachaResult['G'] * 100 / GACHAMAX << "%)" << endl;
    cout << "H: " << gachaResult['H'] << "��(" << (double)gachaResult['H'] * 100 / GACHAMAX << "%)" << endl;


    return 0;
}