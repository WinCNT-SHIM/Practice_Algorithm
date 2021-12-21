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
/// Ư�� ��� < �ڽ� ������ �ǵ��� ����� �۾��� �ϴ� �Լ�
/// </summary>
/// <param name="arr">������ ���</param>
/// <param name="n">������ ����� ��</param>
/// <param name="i">�� ��尡 �ƴ� ���� ������ ����� �ε���</param>
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int light = 2 * i + 1;
    int right = 2 * i + 2;

    // ���� �ڽ� ��尡 ���� ������ �ε������� �۰�(��, �ڽ� ��尡 �ְ�)
    // ���� �ڽ� ����� ���� �θ� ����� ������ ū ���
    // ���� ���� ����� �ε����� �ٲ�
    if (light < n && arr[largest] < arr[light])
    {
        largest = light;
    }
    // ������ �ڽ� ��尡 ���� ������ �ε������� �۰�(��, �ڽ� ��尡 �ְ�)
    // ������ �ڽ� ����� ���� �θ� ����� ������ ū ���
    // ���� ���� ����� �ε����� �ٲ�
    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }

    // ����� ��ü�� �ʿ��ϰ� �� ���
    if (i != largest)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

//Function to build a Heap from array.
void buildHeap(int arr[], int n)
{
    // ���� ����� �켱 �� ����(Max Heap)�� �ٲ۴�
    int rootInx = (n - 2) / 2;
    for (int i = rootInx; i >=0; i--)
    {
        heapify(arr, n, i);
    }

    // �� ����(Max Heap)�� ������ Root�� ���ڰ� ���� ū ���̹Ƿ�
    // ���� ���� ���ڿ� ��ü�ϰ� ���� ��󿡼� �����Ѵ�
    // ��ü�� Root�� ���ڴ� ���� ū ���� �ƴ� �� �����Ƿ�
    // �ٽ� �� ����(Max Heap)�� ���� �� Root�� ���ڿ� ���� ����� ������ ���ڸ� ��ü�Ѵ�
    // ���� �۾��� ���� ����� 1��(Root) ���� ������ �ݺ��Ѵ�
    for (int maxInx = n - 1; maxInx > 0; maxInx--)
    {
        // Root�� ����(�ִ밪)�� ���� ����� ������ ���ڰ� ��ü�Ѵ�
        swap(&arr[0], &arr[maxInx]);
        // �ٽ� �� ������ �����Ѵ�(��� ������ ������ maxInx -1 + 1 = maxInx)
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
    // ���� ����Ʈ
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