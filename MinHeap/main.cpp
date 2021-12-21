#include <iostream>
#include <stdlib.h>
#include <iomanip> // setw

using namespace std;

/// <summary>
/// Ư�� ��� < �ڽ� ������ �ǵ��� ����� �۾��� �ϴ� �Լ�
/// </summary>
/// <param name="arr">������ ���</param>
/// <param name="n">������ ����� ��</param>
/// <param name="i">�� ��尡 �ƴ� ���� ������ ����� �ε���</param>
void MinHeapify(int arr[], int n, int i)
{
    int smallestInx = i;
    int leftInx = 2 * i + 1;
    int rightInx = 2 * i + 2;

    // ���� �ڽ� ��尡 ���� ������ �ε������� �۰�(��, �ڽ� ��尡 �ְ�)
    // ���� �ڽ� ����� ���� �θ� ����� ������ ���� ���
    // ���� ���� ����� �ε����� �ٲ�
    if (leftInx < n && arr[leftInx] < arr[smallestInx])
    {
        smallestInx = leftInx;
    }

    // ������ �ڽ� ��尡 ���� ������ �ε������� �۰�(��, �ڽ� ��尡 �ְ�)
    // ������ �ڽ� ����� ���� �θ� ����� ������ ���� ���
    // ���� ���� ����� �ε����� �ٲ�
    if (rightInx < n && arr[rightInx] < arr[smallestInx])
    {
        smallestInx = rightInx;
    }

    // ����� ��ü�� �ʿ��ϰ� �� ���
    if (smallestInx != i)
    {
        // ���� ���� ���� �θ� ����� ���� �ǵ��� ��ü
        swap(arr[i], arr[smallestInx]);
        // Recursively heapify the affected sub-tree
        // ���� ��ü�� �ڽ� ��忡 ���ؼ��� ��� ȣ���� �̿��ؼ� �ٽ� �������ش�
        MinHeapify(arr, n, smallestInx);
    }
}

void buildMinHeap(int arr[], int n)
{
    // Index of last non-leaf node
    // �� ��尡 �ƴ� ���� ������ ����� �ε���
    // ��, �ڽ� ��尡 �ִ� �θ� ��� �� ���� ������ ����� �ε���
    // ���� ���� Ʈ������ �� ���� �ڽ� ����� �ε����� �����
    //   �θ� ��� : n
    //   ���� �ڽ� ��� : 2n + 1
    //   ������ �ڽ� ��� : 2n + 2�̹Ƿ�
    // �����ϸ� �ڽ� ��尡 �ִ� �θ� ��� �� ���� ������ ����� �ε����� ���� �� �ִ�
    int startInx = (n - 2) / 2;

    // Heapify: Ư�� ��带 �߽����� �� ���� Ʈ������ �� ������ �����ϰԲ� ����� �۾�
    // Min Heap�� ���� ����, Ư�� ��� < �ڽ� ������ �ǵ��� ����� �۾��� �ؾ� �Ѵ�
    for (int i = startInx; i >=0; i--)
    {
        MinHeapify(arr, n, i);
    }

}

int main()
{
    //int arr[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
    int arr[] = { 17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1 };

    // �迭�� ����� ����
    int n = sizeof(arr) / sizeof(arr[0]);

    // Min Heap ���
    cout << "������ �迭�� ���: ";
    for (int i = 0; i < n; ++i)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << "\n";

    // Min Heap ����
    buildMinHeap(arr, n);

    // Min Heap ���
    cout << "Min Heap ���� ���: ";
    for (int i = 0; i < n; ++i)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << "\n";

    system("pause");
    return 0;
}