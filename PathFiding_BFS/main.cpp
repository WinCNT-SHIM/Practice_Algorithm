#include <stdio.h>
#include <windows.h>
#include <queue>
using namespace std;

#define MAX	10

struct Cell
{
    int distance;   // ���������� �� ���� ���� �ִ� �Ÿ�
    bool bVisit;    // �ߺ� �湮�� ���� ���� �湮 ���� �÷���
    bool bflag;     // �湮�� ���� ���� �÷���
};

Cell GridBoard[MAX][MAX];

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
            GridBoard[i][j].bflag = CellAttrTable[i][j];
            //GridBoard[i][j].bflag = CellAttrTable2[i][j];
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
    queue<pair<int, int>> que; // �湮�� ���� ��(y)�� ��(x)
    //que.push(make_pair(y, x));
    que.push({ y, x });

    // ť�� �� ������(= ��� ��带 �湮�� ������) �ݺ�
    while (!que.empty())
    {
        y = que.front().first;
        x = que.front().second;

        que.pop();

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
                que.push(make_pair(nextY, nextX));
            }
        }
    }
}

void main()
{
    InitGrid();
    BFS(0, 0);
    PrintGrid();
    

}