/// <summary>
/// ���ͽ�Ʈ�� �˰���(�׸��� ���)
/// </summary>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <list>

using namespace std;
#define MAX	10

struct Cell
{
    int distance;   // ���������� �� ���� ���� �ִ� �Ÿ�
    bool bVisit;    // �ߺ� �湮�� ���� ���� �湮 ���� �÷���
    bool bflag;     // �湮�� ���� ���� �÷���
    int visitOrder; // �湮 ����
};

Cell GridBoard[MAX][MAX];
// ���� �湮�ϱ� ���� ��(�θ�)
pair<int, int> ParentTable[MAX][MAX];

/// <summary>
/// ���ͽ�Ʈ�� �˰����� ���� �߰��� �ʿ��� ���̺�
/// </summary>
// ��� �ּ� ��� ���̺�
int MinDistanceTable[MAX][MAX];
// ��� ���̺�
int CostTable[MAX][MAX];
// ��� Ȯ�ο� ���̺�
char PathTable[MAX][MAX];


// ��(�׸���) ����̹Ƿ� �ڽ� ������ ã�ư� ������ �ʿ�
// ��, ��, ��, �� + ���, ����, �»�, ����
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };

// �켱 ���� ť�� �ִ� ���
class Node
{
public:
    // ������
    Node(int _cost, int _y, int _x) : cost(_cost), x(_x), y(_y) {}
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

/// <summary>
/// 0: �� �� �ִ� ��
/// 1: �� �� ���� ��
/// </summary>
char CellAttrTable[MAX][MAX] =
{
    // �� ���� 1
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    // �� ���� 2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    // �� ���� 3
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


void InitGrid()
{
    // ������ ���� ���ؼ�, �� �� �ִ��� �������� �׸��忡 �����Ѵ�
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            // ������ ����
            // ���������� �� ���� ���� �ִ� �Ÿ�
            GridBoard[j][i].distance = 0;
            // �ߺ� �湮�� ���� ���� �湮 ���� �÷���
            GridBoard[j][i].bVisit = false;
            // ������ ����
            // �湮�� ���� ���� �÷���
            GridBoard[j][i].bflag = CellAttrTable[j][i];

            // �� �� �ִ� ��, �� �� ���� �� ����
            if (GridBoard[j][i].bflag)
                PathTable[j][i] = '@'; // �� �� ���� ��
            else
                PathTable[j][i] = '_'; // �� �� �ִ� ��

            // ���Ƿ� ��� ����
            CostTable[j][i] = i;
            MinDistanceTable[j][i] = 1000; //INF
        }
    }
}

/// <summary>
/// �湮�� ���� �迭�� ���� �ȿ� �ִ����� üũ�ϴ� �Լ�
/// </summary>
/// <param name="nextY">�湮�� ���� Y</param>
/// <param name="nextX">�湮�� ���� X</param>
/// <returns></returns>
bool IsInside(int nextY, int nextX)
{
    return 0 <= nextY && nextY < MAX && 0 <= nextX && nextX < MAX;
}

/// <summary>
/// ���������� ������ �ִ� �Ÿ� ���
/// </summary>
void PrintGrid()
{
    printf("========== Distance ==========\n");
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            printf("[%02d]", GridBoard[j][i].distance);
        }
        printf("\n");
    }
}

/// <summary>
/// ������������ ��θ� ���
/// </summary>
void PrintPath(int startY, int startX, int destY, int destX)
{
    // ���������� �������� �� ���� ���
    if (GridBoard[destY][destX].distance <= 0)
    {
        printf("path is not found!\n");
        return;
    }

    int _destY = destY;
    int _destX = destX;

    // �θ� ���� �����ϱ� ���� vector
    vector<pair<int, int>> path;
    // �������� �θ� ���� ������ ����(������ -> ����� ��)
    while (true)
    {
        path.push_back({ _destY, _destX });
        // ���������� ����������� ����(�θ� ���)�� ���� ����
        //if (destY == 0 && destX == 0) break;
        if (_destY == startY && _destX == startX) break;

        int nextY = ParentTable[_destY][_destX].first;
        int nextX = ParentTable[_destY][_destX].second;

        _destY = nextY;
        _destX = nextX;
    }

    // ��� ���
    // ������ -> ����� ������ ������ �θ��� ������ �������� ����ϸ�
    // ����� -> ������������ ��ΰ� �ȴ�
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (i == 0) printf("{%d,%d}", path.at(i).first, path.at(i).second);
        else printf("{%d,%d}->", path.at(i).first, path.at(i).second);
        //PathTable[path.at(i).second][path.at(i).first] = '*';
        PathTable[path.at(i).first][path.at(i).second] = '*';
    }

    // ������� �������� Ư���ϰ� ǥ��
    PathTable[startY][startX] = 'S';
    PathTable[destY][destX] = 'D';

    printf("\n\n");
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            printf("[%c]", PathTable[j][i]);
        }
        printf("\n\n");
    }
    printf("\n");
}

/// <summary>
/// ���������� ������ �׸��带 �湮�� ����
/// </summary>
void PrintVisitOrder()
{
    printf("========== Visit Order ==========\n");
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            printf("[%02d]", GridBoard[j][i].visitOrder);
        }
        printf("\n");
    }
}

///// <summary>
///// �ʺ� �켱 �˰���(BFS)�� ���� ť Ŭ����
///// </summary>
//class BFSQue : public queue<pair<int, int>>
//{
//public:
//    BFSQue() { m_visitCount = 0; }
//
//    void Push(int y, int x)
//    {
//        push({ y, x });
//        m_List.push_front({ y, x });
//        GridBoard[y][x].visitOrder = ++m_visitCount;
//    }
//
//    void Pop()
//    {
//        pop();
//        m_List.pop_back();
//    }
//
//    void PrintTrace()
//    {
//        for (auto pair : m_List)
//        {
//            printf("{%d,%d}", pair.second, pair.first);
//        }
//        printf("\n");
//    }
//
//private:
//    list<pair<int, int>> m_List;
//    int m_visitCount = 0;
//};

/// <summary>
/// ���ͽ�Ʈ�� �˰���
/// ��� ���� �湮�� ���̱� ������ �������� ���ε� ���� ����
/// </summary>
/// <param name="startY">������ Y</param>
/// <param name="startX">������ X</param>
void Dijkstra(int startY, int startX)
{
    priority_queue<Node> priorityQ;

    // �����
    int y = startY;
    int x = startX;
    int cost = 0;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;
    MinDistanceTable[y][x] = 1;

    // �켱 ���� ť�� ����� ����
    priorityQ.push(Node(1, y, x));  // ����� ���� ��ǥ

    // �켱 ���� ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!priorityQ.empty())
    {
        //bfsQue.PrintTrace();
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // �����¿� Ž��
        for (int i = 0; i < 4; i++)
        //// �����¿� �밢�� Ž��
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // ���� ���� ����� ����� ���
            int nextCost = cost + CostTable[nextY][nextX];

            // �迭 ����, �̵� ���� ���� üũ
            // (�湮�� ���� �ּ� ��� ��� ���� �ٽ� �湮�� �ʿ� �ֱ⿡ �湮 ���δ� üũ �� ��)
            //if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // ���� Ž�� ���� ����� ����� ����ص� ��뺸�� ������ ������
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // ����� ����� �ּҰ����� ����
                MinDistanceTable[nextY][nextX] = nextCost;

                // �湮�� ���� �÷��׸� true�� ����
                GridBoard[nextY][nextX].bVisit = true;
                // Ž���� ���� ����� ���(�Ÿ�)�� ����
                GridBoard[nextY][nextX].distance = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // ��θ� �����ϱ� ���� �θ� ����
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

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
    int startY = 4, startX = 5;
    int destY = 9, destX = 9;

    InitGrid();
    Dijkstra(startY, startX);
    PrintPath(startY, startX, destY, destX);

    system("pause");
    return 0;
}