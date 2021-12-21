// C++ program for implementation of Heap Sort
#include <iostream>

using namespace std;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/// <summary>
/// 특정 노드 < 자식 노드들이 되도록 만드는 작업을 하는 함수
/// </summary>
/// <param name="arr">정렬할 대상</param>
/// <param name="n">정렬할 대상의 수</param>
/// <param name="i">잎 노드가 아닌 가장 마지막 노드의 인덱스</param>
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int light = 2 * i + 1;
    int right = 2 * i + 2;

    // 왼쪽 자식 노드가 가장 마지막 인덱스보다 작고(즉, 자식 노드가 있고)
    // 왼쪽 자식 노드의 값이 부모 노드의 값보다 큰 경우
    // 가장 같은 노드의 인덱스를 바꿈
    if (light < n && arr[largest] < arr[light])
    {
        largest = light;
    }
    // 오른쪽 자식 노드가 가장 마지막 인덱스보다 작고(즉, 자식 노드가 있고)
    // 오른쪽 자식 노드의 값이 부모 노드의 값보다 큰 경우
    // 가장 같은 노드의 인덱스를 바꿈
    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }

    // 노드의 교체가 필요하게 된 경우
    if (i != largest)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

//Function to build a Heap from array.
void buildHeap(int arr[], int n)
{
    // 정렬 대상을 우선 힙 구조(Max Heap)로 바꾼다
    int rootInx = (n - 2) / 2;
    for (int i = rootInx; i >=0; i--)
    {
        heapify(arr, n, i);
    }

    // 힙 구조(Max Heap)의 정렬은 Root의 숫자가 가장 큰 수이므로
    // 가장 뒤의 숫자와 교체하고 정렬 대상에서 제외한다
    // 교체된 Root의 숫자는 가장 큰 수가 아닐 수 있으므로
    // 다시 힙 구조(Max Heap)로 만든 뒤 Root의 숫자와 정렬 대상의 마지막 숫자를 교체한다
    // 위의 작업을 정렬 대상이 1개(Root) 남을 때까지 반복한다
    for (int maxInx = n - 1; maxInx > 0; maxInx--)
    {
        // Root의 숫자(최대값)과 정렬 대상의 마지막 숫자과 교체한다
        swap(&arr[0], &arr[maxInx]);
        // 다시 힙 구조로 정렬한다(대상 정렬의 개수는 maxInx -1 + 1 = maxInx)
        heapify(arr, maxInx, 0);
    }
}


void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver code
int main()
{
    // 참고 사이트
    // https://www.geeksforgeeks.org/heap-sort/
    // https://m.blog.naver.com/ndb796/221228342808

    //int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
    int n = sizeof(arr) / sizeof(arr[0]);

    buildHeap(arr, n);

    cout << "Sorted array is \n";
    printArray(arr, n);

    system("pause");
    return 0;
}