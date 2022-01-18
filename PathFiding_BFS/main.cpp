#include <stdio.h>
#include <windows.h>
#include <queue>
#include <stack>
#include <list>

using namespace std;

#define MAX	10

struct Cell
{
    int distance;   // 시작점에서 각 셀에 대한 최단 거리
    bool bVisit;    // 중복 방문을 막기 위한 방문 여부 플래그
    bool bflag;     // 방문이 가능 여부 플래그
    int visitOrder; // 방문 순서
};

Cell GridBoard[MAX][MAX];
// 셀을 방문하기 전의 셀(부모)
pair<int, int> ParentTable[MAX][MAX];

// 셀(그리드) 방식이므로 자식 셀들을 찾아갈 방향이 필요
// 우, 하, 좌, 상 + 우상, 우하, 좌상, 좌하
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };

/// <summary>
/// 0: 갈 수 있는 길
/// 1: 갈 수 없는 길
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
    // 각각의 셀에 대해서, 갈 수 있는지 없는지를 그리드에 저장한다
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            // 동적인 정보
            // 시작점에서 각 셀에 대한 최단 거리
            GridBoard[i][j].distance = 0;
            // 중복 방문을 막기 위한 방문 여부 플래그
            GridBoard[i][j].bVisit = false;
            // 정적인 정보
            // 방문이 가능 여부 플래그
            //GridBoard[i][j].bflag = CellAttrTable[i][j];
            GridBoard[i][j].bflag = CellAttrTable2[i][j];
            //GridBoard[i][j].bflag = CellAttrTable3[i][j];
        }
    }
}

/// <summary>
/// 방문할 셀이 배열의 범위 안에 있는지를 체크하는 함수
/// </summary>
/// <param name="nextY">방문할 셀의 Y</param>
/// <param name="nextX">방문할 셀의 X</param>
/// <returns></returns>
bool IsInside(int nextY, int nextX)
{
    return 0 <= nextY && nextY < MAX && 0 <= nextX && nextX < MAX;
}

/// <summary>
/// 시작점에서 셀과의 최단 거리 출력
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
    // 목적지까지 도달하지 못 했을 경우
    if (GridBoard[curY][curX].distance <= 0)
    {
        printf("path is not found!\n");
        return;
    }

    // 부모 셀를 보관하기 위한 vector
    vector<pair<int, int>> path;
    // 목적지의 부모 셀의 정보를 보관(목적지 -> 출발지 순)
    while (true)
    {
        path.push_back({ curY, curX });
        if (curY == 0 && curX == 0) break;

        int nextY = ParentTable[curY][curX].first;
        int nextX = ParentTable[curY][curX].second;

        curY = nextY;
        curX = nextX;
    }

    // 경로 출력
    // 목적지 -> 출발지 순으로 보관한 부모의 정보를 역순으로 출력하면
    // 출발지 -> 목적지까지의 경로가 된다
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (i == 0) printf("{%d,%d}", path.at(i).second, path.at(i).first);
        else printf("{%d,%d}->", path.at(i).second, path.at(i).first);
    }
}

/// <summary>
/// 너비 우선 알고리즘(BFS)을 위한 큐 클래스
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
/// 너비 우선 탐색 알고리즘(BFS)
/// 모든 셀을 방문할 것이기 때문에 시작점은 어디로든 설정 가능
/// </summary>
/// <param name="startY">시작점 Y</param>
/// <param name="startX">시작점 X</param>
void BFS(int startY, int startX)
{
    // 출발지
    int y = startX;
    int x = startX;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;

    // 큐
    //queue<pair<int, int>> que; // 방문할 셀의 행(y)과 열(x)
    //que.push({ y, x });
    BFSQue bfsQue;
    bfsQue.Push(y, x);

    // 큐가 빌 때까지(= 모든 노드를 방문할 때까지) 반복
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

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++)
        //// 상하좌우 대각선 탐색
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];

            // 배열 범위, 이동 가능 여부, 방문 여부를 체크
            if (IsInside(nextY, nextX)
                && !GridBoard[nextY][nextX].bflag
                && !GridBoard[nextY][nextX].bVisit)
            {
                // 방문한 셀의 플래그를 true로 변경
                GridBoard[nextY][nextX].bVisit = true;
                // 부모 셀의 거리에서 +1를 함
                GridBoard[nextY][nextX].distance = GridBoard[y][x].distance + 1;
                //que.push(make_pair(nextY, nextX));
                bfsQue.Push(nextY, nextX);

                // 경로를 추적하기 위한 부모 설정
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

/// <summary>
/// 깊이 우선 탐색
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
/// 깊이 우선 탐색 알고리즘(DFS)
/// 모든 셀을 방문할 것이기 때문에 시작점은 어디로든 설정 가능
/// </summary>
/// <param name="startY">시작점 Y</param>
/// <param name="startX">시작점 X</param>
void DFS(int startY, int startX)
{
    // 출발지
    int y = startX;
    int x = startX;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;

    // 스택
    DFSStack dfsStack;
    dfsStack.Push(y, x);

    // 스택이 빌 때까지(= 모든 노드를 방문할 때까지) 반복
    while (!dfsStack.empty())
    {
        dfsStack.PrintTrace();

        y = dfsStack.top().first;
        x = dfsStack.top().second;

        dfsStack.Pop();

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++)
        //// 상하좌우 대각선 탐색
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];

            // 배열 범위, 이동 가능 여부, 방문 여부를 체크
            if (IsInside(nextY, nextX)
                && !GridBoard[nextY][nextX].bflag
                && !GridBoard[nextY][nextX].bVisit)
            {
                // 방문한 셀의 플래그를 true로 변경
                GridBoard[nextY][nextX].bVisit = true;
                // 부모 셀의 거리에서 +1를 함
                GridBoard[nextY][nextX].distance = GridBoard[y][x].distance + 1;
                dfsStack.Push(nextY, nextX);

                // 경로를 추적하기 위한 부모 설정
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
    PrintPath(5, 5); // 경로 찾기

    printf("\n\n===== DFS =====\n");
    InitGrid();
    DFS(0, 0);
    PrintGrid();
    PrintVisitOrder();
    PrintPath(5, 5);
}