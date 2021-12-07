#include <stdlib.h>
#include <iomanip>
#include <random>
#include <iostream>
#include <map>
#define GACHAMAX 100000

using namespace std;

// 확률 테이블
map<char, double> gachaTable;
/// <summary>
/// 시드값을 얻기 위한 random_device 생성
///   Random Device는 운영체제가 제공하는 진짜 난수를 사용할 수 있다
///   단, 진짜 난수는 생성 속도가 매우 느리기 때문에 주로 시드 값으로 사용한다
/// </summary>
random_device rd;
/// <summary>
/// random_device에서 얻은 객체(진짜 난수)로 의사 난수 생성 엔진의 객체를 정의
///   mt19937는 메르센 트위스터 알고리즘을 사용하는 엔진으로 양질의 의사 난수를 생성한다
///   (단, 객체 크기가 2KB 이상이므로, 메모리가 부족할 경우는 minstd_rand가 적합할 수 있음)
/// </summary>
mt19937 gen(rd());
/// <summary>
/// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의
/// </summary>
uniform_real_distribution<> dist(0, 1);

void Init()
{
    // 가챠 테이블 설정
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
    // 확률 테이블 설정
    Init();
    // 가챠 결과 보관 변수
    map<char, int> gachaResult;

    cout << GACHAMAX << "번 가챠" << endl;
    for (int i = 0; i < GACHAMAX; i++)
    {
        char tmpRes = gachaUniform();
        ++gachaResult[tmpRes];
    }

    cout << "가챠 결과" << endl;
    cout << "A: " << gachaResult['A'] << "번(" << (double)gachaResult['A'] * 100 / GACHAMAX << "%)" << endl;
    cout << "B: " << gachaResult['B'] << "번(" << (double)gachaResult['B'] * 100 / GACHAMAX << "%)" << endl;
    cout << "C: " << gachaResult['C'] << "번(" << (double)gachaResult['C'] * 100 / GACHAMAX << "%)" << endl;
    cout << "D: " << gachaResult['D'] << "번(" << (double)gachaResult['D'] * 100 / GACHAMAX << "%)" << endl;
    cout << "E: " << gachaResult['E'] << "번(" << (double)gachaResult['E'] * 100 / GACHAMAX << "%)" << endl;
    cout << "F: " << gachaResult['F'] << "번(" << (double)gachaResult['F'] * 100 / GACHAMAX << "%)" << endl;
    cout << "G: " << gachaResult['G'] << "번(" << (double)gachaResult['G'] * 100 / GACHAMAX << "%)" << endl;
    cout << "H: " << gachaResult['H'] << "번(" << (double)gachaResult['H'] * 100 / GACHAMAX << "%)" << endl;


    return 0;
}