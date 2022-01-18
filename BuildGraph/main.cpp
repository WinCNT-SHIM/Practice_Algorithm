#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include <algorithm> // sort

using namespace std;

typedef struct Node
{
    char name;
    //Node* accessibleNode[10];
    list<Node*> accessibleNode;
} Node;

// 그래프 빌드를 위한 배열
Node* Graph[10];

/// <summary>
/// 그래프 초기화
/// </summary>
void InitGraph()
{
    for (int i = 0; i < sizeof(Graph) / sizeof(Graph[0]); i++)
    {
        Graph[i] = nullptr;
    }
}

/// <summary>
/// 접근 가능 노드 목록의 정렬을 위한 기준
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
bool nameComp(Node* lhs, Node* rhs) {
    return lhs->name < rhs->name;
}

/// <summary>
/// 입력값에 따라 그래프를 빌드
/// </summary>
/// <param name="name"></param>
void BuildGraph(char input1, char input2)
{
    int indexInput1 = input1 - 'A';
    int indexInput2 = input2 - 'A';

    // 그래프에 노드가 없을 시 생성
    if (Graph[indexInput1] == nullptr)
    {
        Graph[indexInput1] = new Node();
        Graph[indexInput1]->name = input1;
    }
    if (Graph[indexInput2] == nullptr)
    {
        Graph[indexInput2] = new Node();
        Graph[indexInput2]->name = input2;
    }

    // 첫번째 입력값 노드를 찾고 그 노드의 접근 가능 노드 목록에
    // 두번째 입력값 노드를 추가(중복인 경우는 처리 안 함)
    // 중복된 경로 설정인지 확인
    auto iter = find(Graph[indexInput1]->accessibleNode.begin(), 
        Graph[indexInput1]->accessibleNode.end(), 
        Graph[indexInput2]);
    // 중복된 경로가 없는 경우
    if (iter == Graph[indexInput1]->accessibleNode.end())
    {
        // 접근 가능 노드 목록에 두번째 입력값 노드를 추가
        Graph[indexInput1]->accessibleNode.push_back(Graph[indexInput2]);
        // 접근 가능 노드 목록을 정렬함
        // sort(Graph[indexInput1]->accessibleNode.begin(), Graph[indexInput1]->accessibleNode.end());
        Graph[indexInput1]->accessibleNode.sort(nameComp);
    }

}

void printGraph()
{
    for (int i = 0; i < sizeof(Graph) / sizeof(Graph[0]); i++)
    {
        if (Graph[i] != nullptr)
        {
            cout << Graph[i]->name;
            if (Graph[i]->accessibleNode.size() > 0)
            {
                cout << " => ";
                for (auto iter = Graph[i]->accessibleNode.begin();
                    iter != Graph[i]->accessibleNode.end(); iter++)
                {
                    cout << (*iter)->name << " ";
                }
            }
            cout << endl;
        }
    }
    cout << endl;
}

int main()
{
    InitGraph();

    char input1, input2;
    while (true)
    {
        cout << "A~J까지의 알파벳 중 2개를 입력해 주세요\n";
        cin >> input1;
        cin >> input2;

        // 잘못된 입력일 경우는 다시 입력하게 처리
        if ((input1 < 'A' || input1 > 'J')
            || (input2 < 'A' || input2 > 'J')
            )
        {
            cout << "잘못된 입력입니다.\n";
            continue;
        }

        BuildGraph(input1, input2);
        printGraph();
    }
    system("pause");
    return 0;
}