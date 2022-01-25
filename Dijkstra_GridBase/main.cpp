/// <summary>
/// 다익스트라 알고리즘(그리드 기반)
/// </summary>
#include <stdio.h>
#include <iostream>
#include <queue>
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

/// <summary>
/// 다익스트라 알고리즘을 위해 추가로 필요한 테이블
/// </summary>
// 경로 최소 비용 테이블
int MinDistanceTable[MAX][MAX];
// 비용 테이블
int CostTable[MAX][MAX];
// 경로 확인용 테이블
char PathTable[MAX][MAX];


// 셀(그리드) 방식이므로 자식 셀들을 찾아갈 방향이 필요
// 우, 하, 좌, 상 + 우상, 우하, 좌상, 좌하
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };

// 우선 순위 큐에 넣는 노드
class Node
{
public:
    // 생성자
    Node(int _cost, int _y, int _x) : cost(_cost), x(_x), y(_y) {}
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

/// <summary>
/// 0: 갈 수 있는 길
/// 1: 갈 수 없는 길
/// </summary>
char CellAttrTable[MAX][MAX] =
{
    // 길 설정 1
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

    // 길 설정 2
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

    // 길 설정 3
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
    // 각각의 셀에 대해서, 갈 수 있는지 없는지를 그리드에 저장한다
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            // 동적인 정보
            // 시작점에서 각 셀에 대한 최단 거리
            GridBoard[j][i].distance = 0;
            // 중복 방문을 막기 위한 방문 여부 플래그
            GridBoard[j][i].bVisit = false;
            // 정적인 정보
            // 방문이 가능 여부 플래그
            GridBoard[j][i].bflag = CellAttrTable[j][i];

            // 갈 수 있는 길, 갈 수 없는 길 설정
            if (GridBoard[j][i].bflag)
                PathTable[j][i] = '@'; // 갈 수 없는 길
            else
                PathTable[j][i] = '_'; // 갈 수 있는 길

            // 임의로 비용 설정
            CostTable[j][i] = i;
            MinDistanceTable[j][i] = 1000; //INF
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

/// <summary>
/// 목적지까지의 경로를 출력
/// </summary>
void PrintPath(int startY, int startX, int destY, int destX)
{
    // 목적지까지 도달하지 못 했을 경우
    if (GridBoard[destY][destX].distance <= 0)
    {
        printf("path is not found!\n");
        return;
    }

    int _destY = destY;
    int _destX = destX;

    // 부모 셀를 보관하기 위한 vector
    vector<pair<int, int>> path;
    // 목적지의 부모 셀의 정보를 보관(목적지 -> 출발지 순)
    while (true)
    {
        path.push_back({ _destY, _destX });
        // 목적지에서 출발지까지의 역순(부모 노드)을 벡터 넣음
        //if (destY == 0 && destX == 0) break;
        if (_destY == startY && _destX == startX) break;

        int nextY = ParentTable[_destY][_destX].first;
        int nextX = ParentTable[_destY][_destX].second;

        _destY = nextY;
        _destX = nextX;
    }

    // 경로 출력
    // 목적지 -> 출발지 순으로 보관한 부모의 정보를 역순으로 출력하면
    // 출발지 -> 목적지까지의 경로가 된다
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (i == 0) printf("{%d,%d}", path.at(i).first, path.at(i).second);
        else printf("{%d,%d}->", path.at(i).first, path.at(i).second);
        //PathTable[path.at(i).second][path.at(i).first] = '*';
        PathTable[path.at(i).first][path.at(i).second] = '*';
    }

    // 출발점과 도착점은 특별하게 표시
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
/// 시작점에서 각각의 그리드를 방문한 순서
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
///// 너비 우선 알고리즘(BFS)을 위한 큐 클래스
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
/// 다익스트라 알고리즘
/// 모든 셀을 방문할 것이기 때문에 시작점은 어디로든 설정 가능
/// </summary>
/// <param name="startY">시작점 Y</param>
/// <param name="startX">시작점 X</param>
void Dijkstra(int startY, int startX)
{
    priority_queue<Node> priorityQ;

    // 출발지
    int y = startY;
    int x = startX;
    int cost = 0;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].bVisit = true;
    GridBoard[y][x].distance = 1;
    MinDistanceTable[y][x] = 1;

    // 우선 순위 큐에 출발지 설정
    priorityQ.push(Node(1, y, x));  // 출발지 비용과 좌표

    // 우선 순위 큐가 빌 때까지(= 모든 노드를 방문할 때까지) 반복
    while (!priorityQ.empty())
    {
        //bfsQue.PrintTrace();
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++)
        //// 상하좌우 대각선 탐색
        //for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // 다음 인접 노드의 비용을 계산
            int nextCost = cost + CostTable[nextY][nextX];

            // 배열 범위, 이동 가능 여부 체크
            // (방문한 곳도 최소 비용 계산 위해 다시 방문할 필요 있기에 방문 여부는 체크 안 함)
            //if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // 현재 탐색 중인 경로의 비용이 기록해둔 비용보다 작으면 갱신함
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // 경로의 비용을 최소값으로 갱신
                MinDistanceTable[nextY][nextX] = nextCost;

                // 방문한 셀의 플래그를 true로 변경
                GridBoard[nextY][nextX].bVisit = true;
                // 탐색한 인접 노드의 비용(거리)도 갱신
                GridBoard[nextY][nextX].distance = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // 경로를 추적하기 위한 부모 설정
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

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
    int startY = 4, startX = 5;
    int destY = 9, destX = 9;

    InitGrid();
    Dijkstra(startY, startX);
    PrintPath(startY, startX, destY, destX);

    system("pause");
    return 0;
}