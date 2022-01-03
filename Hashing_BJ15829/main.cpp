#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

const unsigned long long int M = 1234567891;
const unsigned long long int r = 31;

unsigned long long int Hashing(int L, char arr[])
{
    unsigned long long int H = 0;
    for (int i = 0; i < L; i++)
    {
        unsigned long long int a = (unsigned long long int)(arr[i] - 'a' + 1);
        unsigned long long int r_i = 1;
        for (int j = 1; j <= i; j++)
        {
            r_i = r_i * r % M;
        }
        H = (H + a * r_i) % M;
    }
    return H;
}

int main()
{
    // 문자열 길이 입력
    int L = 0;
    std::cin >> L;
    // 문자열 길이만큼의 배열 생성
    char* str = new char[L + 1];
    //char* str = new char(L + 1);  //잘못된 동적할당의 예시
    // 문자열 입력
    std::cin >> str;

    std::cout << Hashing(L, str) << std::endl;
    delete[] str;
    
    //system("pause");
    return 0;
}