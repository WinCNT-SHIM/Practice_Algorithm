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

    // 첫번째 인덱스가 마지막 인덱스보다 
    while (first < last)
    {
        // 배열의 중간이 주어진 값보다 작거나 같은 경우
        // 배열의 중간 ~ 마지막을 다시 탐색하기 위해, 첫번째 인덱스를 중간 인덱스 + 1로 설정
        if (array[root] <= val)
        {
            first = root + 1;
        }
        // 배열의 중간이 주어진 값보다 큰 경우
        // 배열의 처음 ~ 중간을 다시 탐색하도록 설정, 마지막 인덱스를 마지막 인덱스 - 1로 설정
        else
        {
            last = root - 1;
        }
        // 배열의 중간 인덱스를 다시 설정
        root = (first + last) / 2;
    }
    // 탐색한 배열의 값이 주어진 값과 같거나 작을 경우
    // 
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
    cout << "Upper_Bound, Val: 1 = " << Upper_Bound(array, 10, 1) << endl;
    cout << "Upper_Bound, Val: 2 = " << Upper_Bound(array, 10, 2) << endl;
    cout << "Upper_Bound, Val: 3 = " << Upper_Bound(array, 10, 3) << endl;
    cout << "Upper_Bound, Val: 4 = " << Upper_Bound(array, 10, 4) << endl;
    cout << "Upper_Bound, Val: 5 = " << Upper_Bound(array, 10, 5) << endl;
    cout << "Upper_Bound, Val: 6 = " << Upper_Bound(array, 10, 6) << endl;
    cout << "Upper_Bound, Val: 7 = " << Upper_Bound(array, 10, 7) << endl;
    cout << "Upper_Bound, Val: 8 = " << Upper_Bound(array, 10, 8) << endl;
    cout << "Upper_Bound, Val: 9 = " << Upper_Bound(array, 10, 9) << endl;
    cout << "Upper_Bound, Val:10 = " << Upper_Bound(array, 10, 10) << endl;
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
    cout << "Lower_Bound, Val: 1 = " << Lower_Bound(array, 10, 1) << endl;
    cout << "Lower_Bound, Val: 2 = " << Lower_Bound(array, 10, 2) << endl;
    cout << "Lower_Bound, Val: 3 = " << Lower_Bound(array, 10, 3) << endl;
    cout << "Lower_Bound, Val: 4 = " << Lower_Bound(array, 10, 4) << endl;
    cout << "Lower_Bound, Val: 5 = " << Lower_Bound(array, 10, 5) << endl;
    cout << "Lower_Bound, Val: 6 = " << Lower_Bound(array, 10, 6) << endl;
    cout << "Lower_Bound, Val: 7 = " << Lower_Bound(array, 10, 7) << endl;
    cout << "Lower_Bound, Val: 8 = " << Lower_Bound(array, 10, 8) << endl;
    cout << "Lower_Bound, Val: 9 = " << Lower_Bound(array, 10, 9) << endl;
    cout << "Lower_Bound, Val:10 = " << Lower_Bound(array, 10, 10) << endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }

    system("pause");
    return 0;
}