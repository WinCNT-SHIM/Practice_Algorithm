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

// �׷��� ���带 ���� �迭
Node* Graph[10];

/// <summary>
/// �׷��� �ʱ�ȭ
/// </summary>
void InitGraph()
{
    for (int i = 0; i < sizeof(Graph) / sizeof(Graph[0]); i++)
    {
        Graph[i] = nullptr;
    }
}

/// <summary>
/// ���� ���� ��� ����� ������ ���� ����
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
bool nameComp(Node* lhs, Node* rhs) {
    return lhs->name < rhs->name;
}

/// <summary>
/// �Է°��� ���� �׷����� ����
/// </summary>
/// <param name="name"></param>
void BuildGraph(char input1, char input2)
{
    int indexInput1 = input1 - 'A';
    int indexInput2 = input2 - 'A';

    // �׷����� ��尡 ���� �� ����
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

    // ù��° �Է°� ��带 ã�� �� ����� ���� ���� ��� ��Ͽ�
    // �ι�° �Է°� ��带 �߰�(�ߺ��� ���� ó�� �� ��)
    // �ߺ��� ��� �������� Ȯ��
    auto iter = find(Graph[indexInput1]->accessibleNode.begin(), 
        Graph[indexInput1]->accessibleNode.end(), 
        Graph[indexInput2]);
    // �ߺ��� ��ΰ� ���� ���
    if (iter == Graph[indexInput1]->accessibleNode.end())
    {
        // ���� ���� ��� ��Ͽ� �ι�° �Է°� ��带 �߰�
        Graph[indexInput1]->accessibleNode.push_back(Graph[indexInput2]);
        // ���� ���� ��� ����� ������
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
        cout << "A~J������ ���ĺ� �� 2���� �Է��� �ּ���\n";
        cin >> input1;
        cin >> input2;

        // �߸��� �Է��� ���� �ٽ� �Է��ϰ� ó��
        if ((input1 < 'A' || input1 > 'J')
            || (input2 < 'A' || input2 > 'J')
            )
        {
            cout << "�߸��� �Է��Դϴ�.\n";
            continue;
        }

        BuildGraph(input1, input2);
        printGraph();
    }
    system("pause");
    return 0;
}