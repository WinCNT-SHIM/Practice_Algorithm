#include <iostream>
#include <stdlib.h>
#include <random>
#include <vector>

using namespace std;

// Random Device로 인한 시드값
random_device rd;
// 시드 값을 바탕으로 메르센 트위스터로 의사 난수 생성
mt19937 gen(rd()); 

void print(vector<int> v)
{
    for (auto item : v)
    {
        cout << item << " ";
    }
    cout << "\n";
}

int main()
{
    // 1~100까지 균등 분포 의사 난수 구하기
    uniform_int_distribution<int> dist(1, 100);
    
    vector<int> v;
    for (;v.size() < 10;)
    {
        int tmp = dist(gen);
        if (v.size() > 0)
        {
            auto it = find(v.begin(), v.end(), tmp);
            if (it != v.end())
            {
                continue;
            }
        }
        v.push_back(tmp);
    }
    cout << "선택한 10개의 수: "; 
    print(v);
    
    // 선택한 10개의 수에서 최대 값을 출력(make_heap 사용)
    make_heap(v.begin(), v.end());
    cout << "최대 값을 출력(make_heap 사용): ";
    cout << v.front() << "\n";
    cout << "현재 선택한 수의 정렬 상태: ";
    print(v);
    cout << "\n";

    int input = 100;
    do 
    {
        cout << "사용자 입력값 추가(100보다 작은 수): ";
        cin >> input;
    } while (input >= 100);
    
    v.push_back(input);
    push_heap(v.begin(), v.end());
    cout << "최대 값을 출력(push_heap 사용): ";
    cout << v.front() << "\n";
    cout << "현재 선택한 수의 정렬 상태: ";
    print(v);
    cout << "\n";

    do
    {
        cout << "사용자 입력값 추가(100보다 큰 수): ";
        cin >> input;
    } while (input <= 100);

    v.push_back(input);
    push_heap(v.begin(), v.end());
    cout << "최대 값을 출력(push_heap 사용): ";
    cout << v.front() << "\n";
    cout << "현재 선택한 수의 정렬 상태: ";
    print(v);
    cout << "\n";

    cout << "\npop 하고 최대 값출력: ";
    pop_heap(v.begin(), v.end());
    cout << v.front() << "\n";
    cout << "현재 선택한 수의 정렬 상태(pop_back 전): ";
    print(v);
    v.pop_back();
    cout << "현재 선택한 수의 정렬 상태(pop_back 후): ";
    print(v);
    cout << "\n";

    cout << "현재 선택한 수의 정렬 상태(sort_heap 전): ";
    print(v);
    cout << "현재 선택한 수의 정렬 상태(sort_heap 후): ";
    sort_heap(v.begin(), v.end());
    print(v);

    system("pause");
    return 0;
}