#include <stdio.h>
#include <stdlib.h>


/// <summary>
/// ��Ŭ���� �˰���
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int GCD(int a, int b)
{
    // a�� �׻� ū ���� ������ ��ü
    if (a < b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    // a/b�� ������
    int Remainder = a % b;
    // a�� b�� ������ ������ ���(�ִ�����)
    if (Remainder == 0) return b;
    // �������� 1, �� �ִ������� 1�� ���
    else if (Remainder == 1) return 1;
    // �� ���� �������� �߻��� ���, ��ͷ� ��Ŭ���� ȣ������ ȣ��
    else GCD(b, Remainder);
}

int main()
{
    int a, b;
    printf("���ڸ� �Է��ϼ���: ");
    scanf_s("%d %d", &a, &b);

    printf("%d\n", GCD(a, b));

    system("pause");
    return 0;
}