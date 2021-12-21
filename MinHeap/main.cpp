#include <iostream>
#include <stdlib.h>
#include <iomanip> // setw

using namespace std;

/// <summary>
/// 특정 노드 < 자식 노드들이 되도록 만드는 작업을 하는 함수
/// </summary>
/// <param name="arr">정렬할 대상</param>
/// <param name="n">정렬할 대상의 수</param>
/// <param name="i">잎 노드가 아닌 가장 마지막 노드의 인덱스</param>
void MinHeapify(int arr[], int n, int i)
{
    int smallestInx = i;
    int leftInx = 2 * i + 1;
    int rightInx = 2 * i + 2;

    // 왼쪽 자식 노드가 가장 마지막 인덱스보다 작고(즉, 자식 노드가 있고)
    // 왼쪽 자식 노드의 값이 부모 노드의 값보다 작은 경우
    // 가장 같은 노드의 인덱스를 바꿈
    if (leftInx < n && arr[leftInx] < arr[smallestInx])
    {
        smallestInx = leftInx;
    }

    // 오른쪽 자식 노드가 가장 마지막 인덱스보다 작고(즉, 자식 노드가 있고)
    // 오른쪽 자식 노드의 값이 부모 노드의 값보다 작은 경우
    // 가장 같은 노드의 인덱스를 바꿈
    if (rightInx < n && arr[rightInx] < arr[smallestInx])
    {
        smallestInx = rightInx;
    }

    // 노드의 교체가 필요하게 된 경우
    if (smallestInx != i)
    {
        // 가장 작은 수가 부모 노드의 값이 되도록 교체
        swap(arr[i], arr[smallestInx]);
        // Recursively heapify the affected sub-tree
        // 값이 교체된 자식 노드에 대해서도 재귀 호출을 이용해서 다시 정렬해준다
        MinHeapify(arr, n, smallestInx);
    }
}

void buildMinHeap(int arr[], int n)
{
    // Index of last non-leaf node
    // 잎 노드가 아닌 가장 마지막 노드의 인덱스
    // 즉, 자식 노드가 있는 부모 노드 중 가장 마지막 노드의 인덱스
    // 완전 이진 트리에서 각 노드와 자식 노드의 인덱스의 관계는
    //   부모 노드 : n
    //   왼쪽 자식 노드 : 2n + 1
    //   오른쪽 자식 노드 : 2n + 2이므로
    // 역산하면 자식 노드가 있는 부모 노드 중 가장 마지막 노드의 인덱스를 구할 수 있다
    int startInx = (n - 2) / 2;

    // Heapify: 특정 노드를 중심으로 그 밑의 트리들의 힙 성질을 만족하게끔 만드는 작업
    // Min Heap을 구할 경우는, 특정 노드 < 자식 노드들이 되도록 만드는 작업을 해야 한다
    for (int i = startInx; i >=0; i--)
    {
        MinHeapify(arr, n, i);
    }

}

int main()
{
    //int arr[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
    int arr[] = { 17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1 };

    // 배열의 요소의 개수
    int n = sizeof(arr) / sizeof(arr[0]);

    // Min Heap 출력
    cout << "정렬할 배열의 요소: ";
    for (int i = 0; i < n; ++i)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << "\n";

    // Min Heap 빌드
    buildMinHeap(arr, n);

    // Min Heap 출력
    cout << "Min Heap 후의 결과: ";
    for (int i = 0; i < n; ++i)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << "\n";

    system("pause");
    return 0;
}