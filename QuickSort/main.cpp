#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int sortedArr[5000000];

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
    
/// <summary>
/// 빠른 선택(Quick Selection) 알고리즘 구현해보기
/// </summary>
/// <param name="arr">정렬할 배열</param>
/// <param name="low">정렬할 배열의 시작 인덱스</param>
/// <param name="high">정렬할 배열의 마지막 인덱스</param>
/// <param name="K">탐색할 인덱스</param>
/// <returns></returns>
int QuickSelect(int arr[], int low, int high, int K)
{
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
    //for (int i = low; i < high; i++)
    //{
    //    printf("%d ", arr[i]);
    //}
    //printf("\n");

    // 피벗의 인덱스가 탐색할 인덱스와 같다면 그 값을 리턴
    if (left == K)
    {
        // 재귀 탈출 조건
        return arr[left];
    }
    // 피벗의 인덱스가 탐색할 인덱스보다 작다면 작은 쪽의 파티션만 퀵 셀렉션
    else if (K < left)
    {
        return QuickSelect(arr, low, left - 1, K);
    }
    // 피벗의 인덱스가 탐색할 인덱스보다 크다면 큰 쪽의 파티션만 퀵 셀렉션
    else
    {
        return QuickSelect(arr, left + 1, high, K);
    }
}

/// <summary>
/// 빠른 선택(Quick Selection) 알고리즘 + 정렬, 역정렬 고려
/// </summary>
/// <param name="arr">정렬할 배열</param>
/// <param name="low">정렬할 배열의 시작 인덱스</param>
/// <param name="high">정렬할 배열의 마지막 인덱스</param>
/// <param name="K">탐색할 인덱스</param>
/// <returns></returns>
int QuickSelect_Mk2(int arr[], int low, int high, int K)
{
    // 정렬된 배열인지 확인
    bool isSorted = true;
    for (int i = low; i < high - 1; i++)
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
    // 역정렬된 배열인지 확인
    for (int i = low; i < high - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            isSorted = false;
            break;
        }
    }
    if (isSorted)
    {
        return arr[high - K];
    }

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
    //for (int i = low; i < high; i++)
    //{
    //    printf("%d ", arr[i]);
    //}
    //printf("\n");

    // 피벗의 인덱스가 탐색할 인덱스와 같다면 그 값을 리턴
    if (left == K)
    {
        // 재귀 탈출 조건
        return arr[left];
    }
    // 피벗의 인덱스가 탐색할 인덱스보다 작다면 작은 쪽의 파티션만 퀵 셀렉션
    else if (K < left)
    {
        // return을 안 하면 메모리가 초과된다(그런데 VS에선 돌아감)
        return QuickSelect(arr, low, left - 1, K);
    }
    // 피벗의 인덱스가 탐색할 인덱스보다 크다면 큰 쪽의 파티션만 퀵 셀렉션
    else
    {
        // return을 안 하면 메모리가 초과된다(그런데 VS에선 돌아감)
        return QuickSelect(arr, left + 1, high, K);
    }
}

int main()
{
    int N, K;
    int res = scanf("%d %d", &N, &K);

    int* arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        int res = scanf("%d", &arr[i]);
        //int res = scanf("%d", &sortedArr[i]);
        //int tmp;
        //int res = scanf("%d", &tmp);
        //sortedVector.push_back(tmp);
    }

#pragma region 퀵 정렬
    //QuickSort(arr, 0, N - 1);
    //printf("%d", arr[K - 1]);
#pragma endregion

#pragma region 빠른 선택(Quick Selection)
    //printf("%d", QuickSelect(arr, 0, N - 1, K - 1));
    //int kValue = QuickSelect(sortedArr, 0, N - 1, K - 1);
    int kValue = QuickSelect_Mk2(sortedArr, 0, N - 1, K - 1);
    printf("%d", kValue);
#pragma endregion

    //for (int i = 0; i < N; i++)
    //{
    //    printf("%d\n", arr[i]);
    //}

    delete[] arr;
    //system("pause");
    return 0;
}