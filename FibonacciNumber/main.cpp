#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>

using namespace std;

int fibonacciNum[40] = { 0, };

int fibonacci(int n)
{
    if (n == 0)
    {
        fibonacciNum[n] = 0;
        return fibonacciNum[n];
    }
    else if (n == 1)
    {
        fibonacciNum[n] = 1;
        return fibonacciNum[n];
    }
    else
    {
        fibonacciNum[n] = fibonacciNum[n - 1] + fibonacciNum[n - 2];
        return fibonacciNum[n];
    }
}

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
            printf("%d %d\n", fibonacci(tmp - 1), fibonacci(tmp));
        }
    }
    return 0;
}