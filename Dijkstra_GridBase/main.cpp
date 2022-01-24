#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;
#define MAX	10

// 우선순위 큐는 비교 연산이 필요
class Node
{
public:
    // 생성자
    Node(int _cost, int _x, int _y): cost(_cost), x(_x), y(_y){}
    // 멤버 변수
    int cost;   // 비용(거리 등)
    int x, y;

    // 우선 순위 큐의 우선 순위 비교를 위해 연산자를 재정의
    // (안 하면 컴파일 에러 발생)
    // cost가 작은 쪽이 앞으로 가도록 설정
    bool operator<(const Node node) const
    {
        if (cost > node.cost) return true;
        return false;
    }
};

// 템플릿 함수
template <typename T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
};

/// <summary>
/// 메인 함수
/// </summary>
int main()
{
    // 우선 순위 큐는 디폴트가 Max Heap
    // 우선 순위가 가장 큰 요소를 앞으로 배치함(정렬은 안 함)
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