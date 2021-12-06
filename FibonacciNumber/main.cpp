/*
* 채점 결과 : 맞았습니다!!
*   처음에는 시간 복잡도 2^n의 함수로 제출하여
*   채점 결과가"틀렸습니다"였으나 다이나믹 프로그래밍으로
*   피보나치 수를 구하는 함수를 수정하여 재채점)
* 
* 시간 복잡도
*   중복 계산을 허용하는 함수의 시간 복잡도: 2^n
*   중복 계산을 기억하여 불러오는 함수의 시간 복잡도: n
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>

using namespace std;

int fibonacciNum[41] = { 0, 1, 1, };

#pragma region 피보나치 수를 구하는 함수, 시간 복잡도 2^n
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

#pragma region 피보나치 수를 구하는 함수, 다이나믹 프로그래밍 적용
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

#pragma region 피보나치 함수(반복문), 시간 복잡도: n
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