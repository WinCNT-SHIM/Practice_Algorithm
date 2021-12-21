#include <iostream>
#include <stdlib.h>
#include <random>
#include <vector>

using namespace std;

// Random Device�� ���� �õ尪
random_device rd;
// �õ� ���� �������� �޸��� Ʈ�����ͷ� �ǻ� ���� ����
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
    // 1~100���� �յ� ���� �ǻ� ���� ���ϱ�
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
    cout << "������ 10���� ��: "; 
    print(v);
    
    // ������ 10���� ������ �ִ� ���� ���(make_heap ���)
    make_heap(v.begin(), v.end());
    cout << "�ִ� ���� ���(make_heap ���): ";
    cout << v.front() << "\n";
    cout << "���� ������ ���� ���� ����: ";
    print(v);
    cout << "\n";

    int input = 100;
    do 
    {
        cout << "����� �Է°� �߰�(100���� ���� ��): ";
        cin >> input;
    } while (input >= 100);
    
    v.push_back(input);
    push_heap(v.begin(), v.end());
    cout << "�ִ� ���� ���(push_heap ���): ";
    cout << v.front() << "\n";
    cout << "���� ������ ���� ���� ����: ";
    print(v);
    cout << "\n";

    do
    {
        cout << "����� �Է°� �߰�(100���� ū ��): ";
        cin >> input;
    } while (input <= 100);

    v.push_back(input);
    push_heap(v.begin(), v.end());
    cout << "�ִ� ���� ���(push_heap ���): ";
    cout << v.front() << "\n";
    cout << "���� ������ ���� ���� ����: ";
    print(v);
    cout << "\n";

    cout << "\npop �ϰ� �ִ� �����: ";
    pop_heap(v.begin(), v.end());
    cout << v.front() << "\n";
    cout << "���� ������ ���� ���� ����(pop_back ��): ";
    print(v);
    v.pop_back();
    cout << "���� ������ ���� ���� ����(pop_back ��): ";
    print(v);
    cout << "\n";

    cout << "���� ������ ���� ���� ����(sort_heap ��): ";
    print(v);
    cout << "���� ������ ���� ���� ����(sort_heap ��): ";
    sort_heap(v.begin(), v.end());
    print(v);

    system("pause");
    return 0;
}