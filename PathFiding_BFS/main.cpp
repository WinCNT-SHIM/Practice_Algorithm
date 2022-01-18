#include <stdio.h>
#include <windows.h>
#include <queue>
#include <stack>
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

// ��(�׸���) ����̹Ƿ� �ڽ� ������ ã�ư� ������ �ʿ�
// ��, ��, ��, �� + ���, ����, �»�, ����
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };

/// <summary>
/// 0: �� �� �ִ� ��
/// 1: �� �� ���� ��
/// </summary>
char CellAttrTable[MAX][MAX] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char CellAttrTable2[MAX][MAX] =
{
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
};

char CellAttrTable3[MAX][MAX] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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
            GridBoard[i][j].distance = 0;
            // �ߺ� �湮�� ���� ���� �湮 ���� �÷���
            GridBoard[i][j].bVisit = false;
            // ������ ����
            // �湮�� ���� ���� �÷���
            //GridBoard[i][j].bflag = CellAttrTable[i][j];
            GridBoard[i][j].bflag = CellAttrTable2[i][j];
            //GridBoard[i][j].bflag = CellAttrTable3[i][j];
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

void PrintPath(int curY, int curX)
{
    // ���������� �������� �� ���� ���
    if (GridBoard[curY][curX].distance <= 0)
    {
        printf("path is not found!\n");
        return;
    }

    // �θ� ���� �����ϱ� ���� vector
    vector<pair<int, int>> path;
    // �������� �θ� ���� ������ ����(������ -> ����� ��)
    while (true)
    {
        path.push_back({ curY, curX });
        if (curY == 0 && curX == 0) break;

        int nextY = ParentTable[curY][curX].first;
        int nextX = ParentTable[curY][curX].second;

        curY = nextY;
        curX = nextX;
    }

    // ��� ���
    // ������ -> ����� ������ ������ �θ��� ������ �������� ����ϸ�
    // ����� -> ������������ ��ΰ� �ȴ�
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (i == 0) printf("{%d,%d}", path.at(i).second, path.at(i).first);
        else printf("{%d,%d}->", path.at(i).second, path.at(i).first);
    }
}

/// <summary>
/// �ʺ� �켱 �˰���(BFS)�� ���� ť Ŭ����
/// </summary>
class BFSQue : public queue<pair<int, int>>
{
public:
    BFSQue() { m_visitCount = 0; }

    void Push(int y, int x)
    {
        push({ y, x });
        m_List.push_front({ y, x });
        GridBoard[y][x].visitOrder = ++m_visitCount;
    }

    void Pop()
    {
        pop();
        m_List.pop_back();
    }

    void PrintTrace()
    {
        for (auto pair : m_List)
        {
            printf("{%d, %d}", pair.second, pair.first);
        }
        printf("\n");
    }

private:
    list<pair<int, int>> m_List;
    int m_visitCount = 0;
};

/// <summary>
/// �ʺ� �켱 Ž�� �˰���(BFS)
/// ��� ���� �湮�� ���̱� ������ �������� ���ε� ���� ����
/// </summary>
/// <param name="startY">������ Y</param>
/// <param name="startX">������ X</param>
void BFS(int startY, int startX)
{
    // �����
    int y = startX;
    int x = startX;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;

    // ť
    //queue<pair<int, int>> que; // �湮�� ���� ��(y)�� ��(x)
    //que.push({ y, x });
    BFSQue bfsQue;
    bfsQue.Push(y, x);

    // ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    //while (!que.empty())
    while (!bfsQue.empty())
    {
        bfsQue.PrintTrace();

        //y = que.front().first;
        //x = que.front().second;
        y = bfsQue.front().first;
        x = bfsQue.front().second;

        //que.pop();
        bfsQue.Pop();

        // �����¿� Ž��
        for (int i = 0; i < 4; i++)
        //// �����¿� �밢�� Ž��
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];

            // �迭 ����, �̵� ���� ����, �湮 ���θ� üũ
            if (IsInside(nextY, nextX)
                && !GridBoard[nextY][nextX].bflag
                && !GridBoard[nextY][nextX].bVisit)
            {
                // �湮�� ���� �÷��׸� true�� ����
                GridBoard[nextY][nextX].bVisit = true;
                // �θ� ���� �Ÿ����� +1�� ��
                GridBoard[nextY][nextX].distance = GridBoard[y][x].distance + 1;
                //que.push(make_pair(nextY, nextX));
                bfsQue.Push(nextY, nextX);

                // ��θ� �����ϱ� ���� �θ� ����
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

/// <summary>
/// ���� �켱 Ž��
/// </summary>
class DFSStack : public stack<pair<int, int>>
{
public:
    DFSStack() { m_visitCount = 0; }

    void Push(int y, int x)
    {
        push({ y, x });
        m_List.push_front({ y, x });
        GridBoard[y][x].visitOrder = ++m_visitCount;
    }

    void Pop()
    {
        pop();
        m_List.pop_back();
    }

    void PrintTrace()
    {
        for (auto pair : m_List)
        {
            printf("{%d,%d}", pair.first, pair.second);
        }
        printf("\n");
    }

private:
    list<pair<int, int>> m_List;
    int m_visitCount = 0;
};

/// <summary>
/// ���� �켱 Ž�� �˰���(DFS)
/// ��� ���� �湮�� ���̱� ������ �������� ���ε� ���� ����
/// </summary>
/// <param name="startY">������ Y</param>
/// <param name="startX">������ X</param>
void DFS(int startY, int startX)
{
    // �����
    int y = startX;
    int x = startX;

    // ������� �湮�� ������ ó��
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;

    // ����
    DFSStack dfsStack;
    dfsStack.Push(y, x);

    // ������ �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!dfsStack.empty())
    {
        dfsStack.PrintTrace();

        y = dfsStack.top().first;
        x = dfsStack.top().second;

        dfsStack.Pop();

        // �����¿� Ž��
        for (int i = 0; i < 4; i++)
        //// �����¿� �밢�� Ž��
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];

            // �迭 ����, �̵� ���� ����, �湮 ���θ� üũ
            if (IsInside(nextY, nextX)
                && !GridBoard[nextY][nextX].bflag
                && !GridBoard[nextY][nextX].bVisit)
            {
                // �湮�� ���� �÷��׸� true�� ����
                GridBoard[nextY][nextX].bVisit = true;
                // �θ� ���� �Ÿ����� +1�� ��
                GridBoard[nextY][nextX].distance = GridBoard[y][x].distance + 1;
                dfsStack.Push(nextY, nextX);

                // ��θ� �����ϱ� ���� �θ� ����
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

void main()
{
    printf("\n\n===== BFS =====\n");
    InitGrid();
    BFS(0, 0);
    PrintGrid();
    PrintVisitOrder();
    PrintPath(5, 5); // ��� ã��

    printf("\n\n===== DFS =====\n");
    InitGrid();
    DFS(0, 0);
    PrintGrid();
    PrintVisitOrder();
    PrintPath(5, 5);
}