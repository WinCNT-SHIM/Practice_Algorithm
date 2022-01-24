#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;
#define MAX	10

// �켱���� ť�� �� ������ �ʿ�
class Node
{
public:
    // ������
    Node(int _cost, int _x, int _y): cost(_cost), x(_x), y(_y){}
    // ��� ����
    int cost;   // ���(�Ÿ� ��)
    int x, y;

    // �켱 ���� ť�� �켱 ���� �񱳸� ���� �����ڸ� ������
    // (�� �ϸ� ������ ���� �߻�)
    // cost�� ���� ���� ������ ������ ����
    bool operator<(const Node node) const
    {
        if (cost > node.cost) return true;
        return false;
    }
};

// ���ø� �Լ�
template <typename T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
};

/// <summary>
/// ���� �Լ�
/// </summary>
int main()
{
    // �켱 ���� ť�� ����Ʈ�� Max Heap
    // �켱 ������ ���� ū ��Ҹ� ������ ��ġ��(������ �� ��)
    priority_queue<Node> priorityQ;
    
    priorityQ.push(Node(1, 0, 0));
    priorityQ.push(Node(3, 0, 1));
    priorityQ.push(Node(2, 1, 0));

    while (!priorityQ.empty())
    {
        cout << priorityQ.top().cost << " ";
        priorityQ.pop();
    }

    system("pause");
    return 0;
}