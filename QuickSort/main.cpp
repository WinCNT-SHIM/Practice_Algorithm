#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

/// <summary>
/// �⺻���� �� ���� �˰���
/// 2021-12-14 SSShim
/// </summary>
/// <param name="arr">������ �迭</param>
/// <param name="low">������ �迭�� ���� �ε���</param>
/// <param name="high">������ �迭�� ������ �ε���</param>
void QuickSort(int arr[], int low, int high)
{
    if (low >= high) return;    // ��� Ż�� ����: ����� ���� �ε��� >= ������ �ε���

    int left = low; // �ǹ����� ���� ���� ��ġ�� �ε���(���ҵ� ������ �̵��Ѵ�)
    int current = low; // ���� Ȯ�� ���� �ε���(�� ó������ �̵��Ѵ�)
    int& pivot = arr[high]; // �迭�� �������� ���� �����ڸ� �̿��� pivot���� ����
    
    // ���� ����� ���� ���� ���ں��� ������ ���ڱ��� �˻�
    for (; current < high; current++)
    {
        // ���� Ȯ�� ���� ���ڰ� �ǹ����� ���� ���, 
        if (arr[current] < pivot)
        {
            // ���ڰ� �ǹ����� ������ ������ ������ �ǹ����� ���� ���� ��ġ�� �ε����� +1�Ѵ�
            // ��, �ǹ����� ���� ���� ��ġ�� �ε����� ������ �׻� �ǹ����� ���� ���� ���� �ȴ�
            swap(arr[left++], arr[current]);
        }
    }
    swap(arr[left], pivot);

    QuickSort(arr, low, left - 1);
    QuickSort(arr, left + 1, high);
}

int main()
{
    int N, K;
    int res = scanf("%d %d", &N, &K);

    int* arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        int res = scanf("%d", &arr[i]);
    }

    // �� ����
    QuickSort(arr, 0, N - 1);
    printf("%d", arr[K]);

    //for (int i = 0; i < N; i++)
    //{
    //    printf("%d\n", arr[i]);
    //}

    delete[] arr;
    //system("pause");
    return 0;
}