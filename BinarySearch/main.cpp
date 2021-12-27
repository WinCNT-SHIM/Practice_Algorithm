#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

//입력: 숫자 배열, 배열의 크기, 주어진 값
//출력 : 주어진 값보다  큰 값이 존재하는 처음 위치(인덱스)
int Upper_Bound(int array[], int size, int val)
{
    // 대상 배열 정렬
    sort(array, array + size);
    // 이진 탐색 범위의 첫번째 인덱스
    int first = 0;
    // 이진 탐색 범위의 마지막 인덱스
    int last = size - 1;
    // 이진 탐색 범위의 가운데 인덱스
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

//입력: 숫자 배열, 배열의 크기, 주어진 값
//출력 : 주어진 값보다  같거나 큰 값이 나오는 처음 위치(인덱스)
int Lower_Bound(int array[], int size, int val)
{
    // 대상 배열 정렬
    sort(array, array + size);
    // 이진 탐색 범위의 첫번째 인덱스
    int first = 0;
    // 이진 탐색 범위의 마지막 인덱스
    int last = size - 1;
    // 이진 탐색 범위의 가운데 인덱스
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
    cout << "입력: ";
    int array[] = { 6, 3, 5, 3, 7, 2, 2, 2, 2, 9 };
    //int array[] = { 1, 2, 2, 2, 2, 2, 2, 2, 2, 9 };

    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "출력\n";
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
    cout << "입력: ";
    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "출력\n";
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