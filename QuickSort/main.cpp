#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

/// <summary>
/// 기본적인 퀵 정렬 알고리즘
/// 2021-12-14 SSShim
/// </summary>
/// <param name="arr">정렬할 배열</param>
/// <param name="low">정렬할 배열의 시작 인덱스</param>
/// <param name="high">정렬할 배열의 마지막 인덱스</param>
void QuickSort(int arr[], int low, int high)
{
    if (low >= high) return;    // 재귀 탈출 조건: 대상의 시작 인덱스 >= 마지막 인덱스

    int left = low; // 피벗보다 작은 수를 배치할 인덱스(스왑될 때마다 이동한다)
    int current = low; // 현재 확인 중인 인덱스(매 처리마다 이동한다)
    int& pivot = arr[high]; // 배열의 마지막을 참조 연산자를 이용해 pivot으로 설정
    
    // 정렬 대상의 가장 앞의 숫자부터 마지막 숫자까지 검사
    for (; current < high; current++)
    {
        // 현재 확인 중인 숫자가 피벗보다 작은 경우, 
        if (arr[current] < pivot)
        {
            // 숫자가 피벗보다 작으니 앞으로 보내고 피벗보다 작은 수를 배치할 인덱스를 +1한다
            // 즉, 피벗보다 작은 수를 배치할 인덱스의 왼쪽은 항상 피벗보다 작은 수가 오게 된다
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

    // 퀵 정렬
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