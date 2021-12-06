#include <stdio.h>
#include <stdlib.h>


/// <summary>
/// 유클리드 알고리즘
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int GCD(int a, int b)
{
    // a에 항상 큰 수가 오도록 교체
    if (a < b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    // a/b의 나머지
    int Remainder = a % b;
    // a가 b로 나누어 떨어진 경우(최대공약수)
    if (Remainder == 0) return b;
    // 나머지가 1, 즉 최대공약수가 1인 경우
    else if (Remainder == 1) return 1;
    // 그 외의 나머지가 발생한 경우, 재귀로 유클리드 호제법을 호출
    else GCD(b, Remainder);
}

int main()
{
    int a, b;
    printf("숫자를 입력하세요: ");
    scanf_s("%d %d", &a, &b);

    printf("%d\n", GCD(a, b));

    system("pause");
    return 0;
}