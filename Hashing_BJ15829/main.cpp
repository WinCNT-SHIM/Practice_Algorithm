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
    // ���ڿ� ���� �Է�
    int L = 0;
    std::cin >> L;
    // ���ڿ� ���̸�ŭ�� �迭 ����
    char* str = new char[L + 1];
    //char* str = new char(L + 1);  //�߸��� �����Ҵ��� ����
    // ���ڿ� �Է�
    std::cin >> str;

    std::cout << Hashing(L, str) << std::endl;
    delete[] str;
    
    //system("pause");
    return 0;
}