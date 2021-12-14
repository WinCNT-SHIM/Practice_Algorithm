#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int sortedArr[5000000];

/*
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
*/

/*
/// <summary>
/// ���� ����(Quick Selection) �˰��� �����غ���
/// </summary>
/// <param name="arr">������ �迭</param>
/// <param name="low">������ �迭�� ���� �ε���</param>
/// <param name="high">������ �迭�� ������ �ε���</param>
/// <param name="K">Ž���� �ε���</param>
/// <returns></returns>
int QuickSelect(int arr[], int low, int high, int K)
{
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
    //for (int i = low; i < high; i++)
    //{
    //    printf("%d ", arr[i]);
    //}
    //printf("\n");

    // �ǹ��� �ε����� Ž���� �ε����� ���ٸ� �� ���� ����
    if (left == K)
    {
        // ��� Ż�� ����
        return arr[left];
    }
    // �ǹ��� �ε����� Ž���� �ε������� �۴ٸ� ���� ���� ��Ƽ�Ǹ� �� ������
    else if (K < left)
    {
        return QuickSelect(arr, low, left - 1, K);
    }
    // �ǹ��� �ε����� Ž���� �ε������� ũ�ٸ� ū ���� ��Ƽ�Ǹ� �� ������
    else
    {
        return QuickSelect(arr, left + 1, high, K);
    }
}
*/

/// <summary>
/// ���� ����(Quick Selection) �˰��� + ����, ������ ���
/// </summary>
/// <param name="arr">������ �迭</param>
/// <param name="low">������ �迭�� ���� �ε���</param>
/// <param name="high">������ �迭�� ������ �ε���</param>
/// <param name="K">Ž���� �ε���</param>
/// <returns></returns>
int QuickSelect_Mk2(int arr[], int low, int high, int K)
{
    // ���ĵ� �迭���� Ȯ��
    bool isSorted = true;
    for (int i = low; i < high; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            isSorted = false;
            break;
        }
    }
    if (isSorted)
    {
        return arr[K];
    }
    // �����ĵ� �迭���� Ȯ��
    isSorted = true;
    for (int i = low; i < high; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            isSorted = false;
            break;
        }
    }
    if (isSorted)
    {
        return arr[high - K + low];
    }

    int left = low; // �ǹ����� ���� ���� ��ġ�� �ε���(���ҵ� ������ �̵��Ѵ�)
    int current = low; // ���� Ȯ�� ���� �ε���(�� ó������ �̵��Ѵ�)
    //int& pivot = arr[high]; // �迭�� �������� ���� �����ڸ� �̿��� pivot���� ����(�ð� �ʰ�)
    // �迭�� �߰� ���� �ǹ����� ���� ��, ������ �ε����� ��ü
    swap(arr[(low + high) / 2], arr[high]);
    int& pivot = arr[high];
    
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
    //for (int i = low; i <= high; i++)
    //{
    //    printf("%d ", arr[i]);
    //}
    //printf("\n");

    // �ǹ��� �ε����� Ž���� �ε����� ���ٸ� �� ���� ����
    if (left == K)
    {
        // ��� Ż�� ����
        return arr[left];
    }
    // �ǹ��� �ε����� Ž���� �ε������� �۴ٸ� ���� ���� ��Ƽ�Ǹ� �� ������
    else if (K < left)
    {
        // return�� �� �ϸ� �޸𸮰� �ʰ��ȴ�(�׷��� VS���� ���ư�)
        return QuickSelect_Mk2(arr, low, left - 1, K);
    }
    // �ǹ��� �ε����� Ž���� �ε������� ũ�ٸ� ū ���� ��Ƽ�Ǹ� �� ������
    else
    {
        // return�� �� �ϸ� �޸𸮰� �ʰ��ȴ�(�׷��� VS���� ���ư�)
        return QuickSelect_Mk2(arr, left + 1, high, K);
    }
}

int main()
{
    int N, K;
    int res = scanf("%d %d", &N, &K);

    int* arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        //int res = scanf("%d", &arr[i]);   // ���� �Ҵ�
        int res = scanf("%d", &sortedArr[i]);
    }

#pragma region �� ����
    //QuickSort(arr, 0, N - 1);
    //printf("%d", arr[K - 1]);
#pragma endregion

#pragma region ���� ����(Quick Selection)
    //int kValue = QuickSelect(sortedArr, 0, N - 1, K - 1);
    int kValue = QuickSelect_Mk2(sortedArr, 0, N - 1, K - 1);
    //int kValue = QuickSelect_Mk2(arr, 0, N - 1, K - 1); // ���� �Ҵ�
    printf("%d", kValue);
#pragma endregion
    delete[] arr;
    return 0;
}