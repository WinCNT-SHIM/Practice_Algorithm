/*
* ä�� ��� : �¾ҽ��ϴ�!!
*   ó������ �ð� ���⵵ 2^n�� �Լ��� �����Ͽ�
*   ä�� �����"Ʋ�Ƚ��ϴ�"������ ���̳��� ���α׷�������
*   �Ǻ���ġ ���� ���ϴ� �Լ��� �����Ͽ� ��ä��)
* 
* �ð� ���⵵
*   �ߺ� ����� ����ϴ� �Լ��� �ð� ���⵵: 2^n
*   �ߺ� ����� ����Ͽ� �ҷ����� �Լ��� �ð� ���⵵: n
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>

using namespace std;

int fibonacciNum[41] = { 0, 1, 1, };

#pragma region �Ǻ���ġ ���� ���ϴ� �Լ�, �ð� ���⵵ 2^n
/*
int fibonacci(int n)
{
    if (n == 0)
    {
        //printf("0");
        return 0;
    }
    else if (n == 1)
    {
        //printf("1");
        return 1;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
*/
#pragma endregion

#pragma region �Ǻ���ġ ���� ���ϴ� �Լ�, ���̳��� ���α׷��� ����
int fibonacci(int n)
{
    if (n == 0)
    {
        return fibonacciNum[n];
    }
    else if (n == 1)
    {
        return fibonacciNum[n];
    }
    else if (n == 2)
    {
        return fibonacciNum[n];
    }
    else
    {
        if (fibonacciNum[n] != 0)
        {
            return fibonacciNum[n];
        }
        else
        {
            fibonacciNum[n] = fibonacci(n - 2) + fibonacci(n - 1);
            return fibonacciNum[n];
        }
    }
}
#pragma endregion

#pragma region �Ǻ���ġ �Լ�(�ݺ���), �ð� ���⵵: n
int fibonacci_Loop(int n)
{
    if (n == 0)
    {
        return fibonacciNum[n];
    }
    else if (n == 1)
    {
        return fibonacciNum[n];
    }
    else if (n == 2)
    {
        return fibonacciNum[n];
    }
    else
    {
        if (fibonacciNum[n] != 0)
        {
            return fibonacciNum[n];
        }
        else
        {
            for (int i = 3; i <= n; i++)
            {
                if (fibonacciNum[i] == 0)
                {
                    fibonacciNum[i] = fibonacciNum[i - 2] + fibonacciNum[i - 1];
                }
            }
            return fibonacciNum[n];
        }
    }
}
#pragma endregion


int main()
{
    int testCase = 0;
    int tmp = scanf("%d", &testCase);
    vector<int> vInput;

    for (int i = 0; i < testCase; i++)
    {
        int input = 0;
        int tmp = scanf("%d", &input);
        vInput.push_back(input);
    }

    for (int i = 0; i < testCase; i++)
    {
        int tmp = vInput.at(i);
        if (tmp == 0)
        {
            printf("%d %d\n", 1, 0);
        }
        else
        {
            //printf("%d %d\n", fibonacci(tmp - 1), fibonacci(tmp));
            printf("%d %d\n", fibonacci_Loop(tmp - 1), fibonacci_Loop(tmp));
        }
    }
    return 0;
}