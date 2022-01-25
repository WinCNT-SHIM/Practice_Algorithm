/// <summary>
/// A* �˰���(�׸��� ���)
/// </summary>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define MAX	10
#define INF 10000

struct Cell
{
    bool bflag;

    float g_cost; // ���� distance
    float h_cost; // �޸���ƽ ������
    float f_cost;
};

// �׸��� ���
Cell GridBoard[MAX][MAX];
// ���� �湮�ϱ� ���� ��(�θ�)
pair<int, int> ParentTable[MAX][MAX];

// ���ͽ�Ʈ��: �ּ� ��� ����� - ������Ʈ �ʿ�
float MinDistanceTable[MAX][MAX];
bool AStarClosedTable[MAX][MAX];

// ��� Ȯ�ο� ���̺�
char PathTable[MAX][MAX];

// ��(�׸���) ����̹Ƿ� �ڽ� ������ ã�ư� ������ �ʿ�
// ��, ��, ��, �� + ���, ����, �»�, ����
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };
// �Ÿ�(���), �밢���� �� �� ����� ��δ�
float DirCost[8] = { 1, 1, 1, 1, 1.4, 1.4, 1.4, 1.4 };
/// <summary>
/// �湮�� ���⿡ ���� �Ÿ� ����� ��ȯ��
/// </summary>
float GetNextCost(int dirIndex)
{
    //return 1.0f;
    return DirCost[dirIndex];
}


/// <summary>
/// 0: �� �� �ִ� ��
/// 1: �� �� ���� ��
/// </summary>
char CellAttrTable[MAX][MAX] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// �켱 ���� ť�� �ִ� ���
class Node
{
public:
    // ������
    Node(float  _cost, int _y, int _x) : cost(_cost), x(_x), y(_y) {}
    // ��� ����
    float cost;   // ���(�Ÿ� ��)
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

void InitGrid()
{
    // ������ ���� ���ؼ�, �� �� �ִ��� �������� �׸��忡 �����Ѵ�
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            // ������ ����
            // ���������� �� ���� ���� �ִ� �Ÿ�
            GridBoard[j][i].g_cost = 0;
            GridBoard[j][i].h_cost = 0;
            GridBoard[j][i].f_cost = INF;
            // �ּ� ��� �ʱ�ȭ
            MinDistanceTable[j][i] = INF;

            // ������ ����
            // �湮�� ���� ���� �÷���
            GridBoard[j][i].bflag = CellAttrTable[j][i];

            // �� �� �ִ� ��, �� �� ���� �� ����
            if (GridBoard[j][i].bflag)
                PathTable[j][i] = '@'; // �� �� ���� ��
            else
                PathTable[j][i] = '_'; // �� �� �ִ� ��
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
/// �׸����� �̵� ���� ���θ� ���
/// </summary>
void PrintGrid()
{
    printf("========== Grid Info ==========\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("[%c]", (GridBoard[i][j].bflag ? '@' : '_'));
        }
        printf("\n");
    }
    printf("\n");
}

/// <summary>
/// ������������ ��θ� ���
/// </summary>
void PrintPath(int destY, int destX)
{
    if (GridBoard[destY][destX].g_cost <= 0)
    {
        printf("path is not found!\n");
        return;
    }

    int _destY = destY;
    int _destX = destX;

    vector<pair<int, int>> path;
    while (true)
    {
        path.push_back({ _destY, _destX });

        int nextY = ParentTable[_destY][_destX].first;
        int nextX = ParentTable[_destY][_destX].second;

        if (nextX == _destX && nextY == _destY) break; // �����

        _destY = nextY;
        _destX = nextX;
    }

    printf("========== Visit Order ==========\n");
    // ��� ������ $�� ���
    int startIndex = path.size() - 1;
    PathTable[path[startIndex].second][path[startIndex].first] = '$';
    // ��� ���� ��ǥ ���
    printf("[%c%d]", 'A' + path[startIndex].first, path[startIndex].second);
    // ���� ���� => ��� �������� ��ο� ��ǥ�� ���
    for (int i = startIndex - 1; i >= 0; i--)
    {
        // ��ǥ
        printf("->[%c%d]", 'A' + path[i].first, path[i].second);
        if (i != 0)
        {
            // ���
            PathTable[path[i].first][path[i].second] = '*';
        }
        // ���� �������� #�� ���
        else
        {
            PathTable[path[i].first][path[i].second] = '#';
        }
    }
    printf("\nCost: %f\n", GridBoard[destY][destX].g_cost);

    printf("========== Path ==========\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("[%c]", PathTable[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


/// <summary>
/// ���ͽ�Ʈ�� �˰���
/// ��� ���� �湮�� ���̱� ������ �������� ���ε� ���� ����
/// </summary>
/// <param name="startY">������ ��</param>
/// <param name="startX">������ ��</param>
void Dijkstra(int startY, int startX)
{
    priority_queue<Node> priorityQ;

    // �����
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].g_cost = 0;
    MinDistanceTable[y][x] = 0;

    // ������� �θ� ��带 �ڱ� �ڽ����� ����
    ParentTable[y][x] = { y, x }; 

    // �켱 ���� ť�� ����� ����
    priorityQ.push(Node(1, y, x));  // ����� ���� ��ǥ

    // �켱 ���� ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!priorityQ.empty())
    {
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // �����¿� �밢�� Ž��
        //for (int i = 0; i < 4; i++)
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // ���� ���� ����� ����� ���
            float nextCost = cost + GetNextCost(i);

            // �迭 ����, �̵� ���� ���� üũ
            // (�湮�� ���� �ּ� ��� ��� ���� �ٽ� �湮�� �ʿ� �ֱ⿡ �湮 ���δ� üũ �� ��)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // ���� Ž�� ���� ����� ����� ����ص� ��뺸�� ������ ������
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // ����� ����� �ּҰ����� ����
                MinDistanceTable[nextY][nextX] = nextCost;

                // Ž���� ���� ����� ���(�Ÿ�)�� ����
                GridBoard[nextY][nextX].g_cost = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // ��θ� �����ϱ� ���� �θ� ����
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

/// <summary>
/// A* �˰���(�޸���ƽ ��� �� �ϴ� �˰���)
/// </summary>
void AStar1(int startY, int startX, int DestY, int DestX)
{
    priority_queue<Node> priorityQ;

    // �����
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].g_cost = 1;
    MinDistanceTable[y][x] = 1;

    // ������� �θ� ��带 �ڱ� �ڽ����� ����
    ParentTable[y][x] = { y, x };

    // �켱 ���� ť�� ����� ����
    priorityQ.push(Node(1, y, x));  // ����� ���� ��ǥ

    // �켱 ���� ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!priorityQ.empty())
    {
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // �����¿� �밢�� Ž��
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // ���� ���� ����� ����� ���
            float nextCost = cost + GetNextCost(i);

            // �迭 ����, �̵� ���� ���� üũ
            // (�湮�� ���� �ּ� ��� ��� ���� �ٽ� �湮�� �ʿ� �ֱ⿡ �湮 ���δ� üũ �� ��)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // ���� Ž�� ���� ����� ����� ����ص� ��뺸�� ������ ������
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // ����� ����� �ּҰ����� ����
                MinDistanceTable[nextY][nextX] = nextCost;

                // Ž���� ���� ����� ���(�Ÿ�)�� ����
                GridBoard[nextY][nextX].g_cost = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // ��θ� �����ϱ� ���� �θ� ����
                ParentTable[nextY][nextX] = { y, x };
            }

            // �湮�� ��尡 ���� ��忴�� ��� Ž���� ������
            if (nextY == DestY && nextX == DestX) break;
        }
    }
}

/// <summary>
/// �޸���ƽ�� ����ϴ� �Լ�
/// </summary>
int CalculateHeuristicCost(int startY, int startX, int DestY, int DestX)
{
    return 0;
    // (??) ����ź �Ÿ�?
    //return abs(startY - DestY) + abs(startX - DestX);
}

/// <summary>
/// ��� ��� �κ��� �����ؾ� ��
/// ���� ����Ʈ(�˻��ؾ� �ϴ� �͵�) => ��� ��� �ؾ� ��
/// ���� ����Ʈ(�˻��� �͵�) => ��� ��� �� => �ּ� ��� ���� �ʿ�
/// </summary>
void AStar2(int startY, int startX, int DestY, int DestX)
{
    priority_queue<Node> OpenQ;

    // �����
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].g_cost = 1;
    MinDistanceTable[y][x] = 1;

    // ������� �θ� ��带 �ڱ� �ڽ����� ����
    ParentTable[y][x] = { y, x };

    // �켱 ���� ť�� ����� ����
    OpenQ.push(Node(1, y, x));  // ����� ���� ��ǥ

    // �켱 ���� ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!OpenQ.empty())
    {
        cost = OpenQ.top().cost;
        y = OpenQ.top().y;
        x = OpenQ.top().x;

        OpenQ.pop();
        AStarClosedTable[y][x] = true;

        // �����¿� �밢�� Ž��
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // ���� ���� ����� ����� ���
            float nextCost = cost + GetNextCost(i);

            // �迭 ����, �̵� ���� ���� üũ
            // (�湮�� ���� �ּ� ��� ��� ���� �ٽ� �湮�� �ʿ� �ֱ⿡ �湮 ���δ� üũ �� ��)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            if (AStarClosedTable[nextY][nextX] == false)
            {
                float g_NextCost = cost + GetNextCost(i);
                float h_NextCost = CalculateHeuristicCost(nextY, nextX, DestY, DestX);
                float f_NextCost = g_NextCost + h_NextCost;

                // ���� Ž�� ���� ����� ����� ����ص� ��뺸�� ������ ������
                if (f_NextCost < GridBoard[nextY][nextX].f_cost)
                {
                    // Ž���� ���� ����� ���(�Ÿ�)�� ����
                    GridBoard[nextY][nextX].g_cost = g_NextCost;
                    GridBoard[nextY][nextX].h_cost = h_NextCost;
                    GridBoard[nextY][nextX].f_cost = f_NextCost;

                    OpenQ.push(Node(f_NextCost, nextY, nextX));

                    // ��θ� �����ϱ� ���� �θ� ����
                    ParentTable[nextY][nextX] = { y, x };
                }
            }

            // �湮�� ��尡 ���� ��忴�� ��� Ž���� ������
            if (nextY == DestY && nextX == DestX) break;
        }
    }

}

/// <summary>
/// ���� �Լ�
/// </summary>
int main()
{
    int startY = 4, startX = 5;
    int destY = 9, destX = 9;

    InitGrid();
    PrintGrid();

    printf("Dijkstra\n");
    Dijkstra(9, 9);
    PrintPath(0, 0);

    printf("AStar1(non-heuristic)\n");
    InitGrid();
    AStar1(9, 9, 0, 0);
    PrintPath(0, 0);

    printf("AStar2(heuristic)\n");
    InitGrid();
    AStar2(9, 9, 0, 0);
    PrintPath(0, 0);

    system("pause");
    return 0;
}