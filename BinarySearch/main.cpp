#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

//�Է�: ���� �迭, �迭�� ũ��, �־��� ��
//��� : �־��� ������  ū ���� �����ϴ� ó�� ��ġ(�ε���)
int Upper_Bound(int array[], int size, int val)
{
    // ��� �迭 ����
    sort(array, array + size);
    // ���� Ž�� ������ ù��° �ε���
    int first = 0;
    // ���� Ž�� ������ ������ �ε���
    int last = size - 1;
    // ���� Ž�� ������ ��� �ε���
    int root = (first + last) / 2;

    while (first < last)
    {
        if (array[root] <= val)
        {
            first = root + 1;
        }
        else
        {
            last = root - 1;
        }
        root = (first + last) / 2;
    }

    if (array[root] <= val)
    {
        return root + 1;
    }
    else
    {
        return root;
    }
}

//�Է�: ���� �迭, �迭�� ũ��, �־��� ��
//��� : �־��� ������  ���ų� ū ���� ������ ó�� ��ġ(�ε���)
int Lower_Bound(int array[], int size, int val)
{
    // ��� �迭 ����
    sort(array, array + size);
    // ���� Ž�� ������ ù��° �ε���
    int first = 0;
    // ���� Ž�� ������ ������ �ε���
    int last = size - 1;
    // ���� Ž�� ������ ��� �ε���
    int root = (first + last) / 2;
    
    while (first < last)
    {
        if (array[root] >= val)
        {
            last = root - 1;
        }
        else
        {
            first = root + 1;
        }
        root = (first + last) / 2;
    }

    if (array[root] >= val)
    {
        return root;
    }
    else
    {
        return root + 1;
    }
}

int main()
{
    cout << "�Է�: ";
    int array[] = { 6, 3, 5, 3, 7, 2, 2, 2, 2, 9 };
    //int array[] = { 1, 2, 2, 2, 2, 2, 2, 2, 2, 9 };

    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "���\n";
    cout << "Val: 1 = " << Upper_Bound(array, 10, 1) << endl;
    cout << "Val: 2 = " << Upper_Bound(array, 10, 2) << endl;
    cout << "Val: 3 = " << Upper_Bound(array, 10, 3) << endl;
    cout << "Val: 4 = " << Upper_Bound(array, 10, 4) << endl;
    cout << "Val: 5 = " << Upper_Bound(array, 10, 5) << endl;
    cout << "Val: 6 = " << Upper_Bound(array, 10, 6) << endl;
    cout << "Val: 7 = " << Upper_Bound(array, 10, 7) << endl;
    cout << "Val: 8 = " << Upper_Bound(array, 10, 8) << endl;
    cout << "Val: 9 = " << Upper_Bound(array, 10, 9) << endl;
    cout << "Val:10 = " << Upper_Bound(array, 10, 10) << endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << endl;

    array[0] = 6;
    array[1] = 3;
    array[2] = 5;
    array[3] = 3;
    array[4] = 7;
    array[5] = 2;
    array[6] = 2;
    array[7] = 2;
    array[8] = 2;
    array[9] = 9;
    cout << "�Է�: ";
    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "���\n";
    cout << "Val: 1 = " << Lower_Bound(array, 10, 1) << endl;
    cout << "Val: 2 = " << Lower_Bound(array, 10, 2) << endl;
    cout << "Val: 3 = " << Lower_Bound(array, 10, 3) << endl;
    cout << "Val: 4 = " << Lower_Bound(array, 10, 4) << endl;
    cout << "Val: 5 = " << Lower_Bound(array, 10, 5) << endl;
    cout << "Val: 6 = " << Lower_Bound(array, 10, 6) << endl;
    cout << "Val: 7 = " << Lower_Bound(array, 10, 7) << endl;
    cout << "Val: 8 = " << Lower_Bound(array, 10, 8) << endl;
    cout << "Val: 9 = " << Lower_Bound(array, 10, 9) << endl;
    cout << "Val:10 = " << Lower_Bound(array, 10, 10) << endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }

    system("pause");
    return 0;
}