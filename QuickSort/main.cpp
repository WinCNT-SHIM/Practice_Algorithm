#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

void QuickSort(int arr[], int low, int high)
{
    if (low >= high)
    {
        return;
    }
    // 왼쪽과 오른쪽을 설정
    int left = low, right = low;
    int pivot = arr[high];
    
    for (; right < high; right++)
    {
        // 피봇보다 오른쪽 포인터의 수가 작을 경우
        if (arr[right] < pivot)
        {
            swap(arr[left++], arr[right]);
        }
    }
    swap(arr[left], pivot);

    QuickSort(arr, low, left - 1);
    QuickSort(arr, left + 1, high);
}

int main()
{
    //int arrMax, int SearchIndex;
    //scanf_s("%d %d", &arrMax, &SearchIndex);

    int arr[5] = { 3, 4, 5, 2, 1 };

    QuickSort(arr, 0, 4);

    system("pause");
    return 0;
}