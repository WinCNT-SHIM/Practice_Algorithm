/// <summary>
/// A* 알고리즘(그리드 기반)
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

    float g_cost; // 기존 distance
    float h_cost; // 휴리스틱 추정값
    float f_cost;
};

// 그리드 기반
Cell GridBoard[MAX][MAX];
// 셀을 방문하기 전의 셀(부모)
pair<int, int> ParentTable[MAX][MAX];

// 다익스트라: 최소 비용 저장용 - 업데이트 필요
float MinDistanceTable[MAX][MAX];
bool AStarClosedTable[MAX][MAX];

// 경로 확인용 테이블
char PathTable[MAX][MAX];

// 셀(그리드) 방식이므로 자식 셀들을 찾아갈 방향이 필요
// 우, 하, 좌, 상 + 우상, 우하, 좌상, 좌하
int dx[8] = { 1, 0, -1,  0,  1, 1, -1, -1 };
int dy[8] = { 0, 1,  0, -1, -1, 1,  1, -1 };
// 거리(비용), 대각선이 좀 더 비용이 비싸다
float DirCost[8] = { 1, 1, 1, 1, 1.4, 1.4, 1.4, 1.4 };
/// <summary>
/// 방문할 방향에 따라 거리 비용을 반환함
/// </summary>
float GetNextCost(int dirIndex)
{
    //return 1.0f;
    return DirCost[dirIndex];
}


/// <summary>
/// 0: 갈 수 있는 길
/// 1: 갈 수 없는 길
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

// 우선 순위 큐에 넣는 노드
class Node
{
public:
    // 생성자
    Node(float  _cost, int _y, int _x) : cost(_cost), x(_x), y(_y) {}
    // 멤버 변수
    float cost;   // 비용(거리 등)
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

void InitGrid()
{
    // 각각의 셀에 대해서, 갈 수 있는지 없는지를 그리드에 저장한다
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            // 동적인 정보
            // 시작점에서 각 셀에 대한 최단 거리
            GridBoard[j][i].g_cost = 0;
            GridBoard[j][i].h_cost = 0;
            GridBoard[j][i].f_cost = INF;
            // 최소 비용 초기화
            MinDistanceTable[j][i] = INF;

            // 정적인 정보
            // 방문이 가능 여부 플래그
            GridBoard[j][i].bflag = CellAttrTable[j][i];

            // 갈 수 있는 길, 갈 수 없는 길 설정
            if (GridBoard[j][i].bflag)
                PathTable[j][i] = '@'; // 갈 수 없는 길
            else
                PathTable[j][i] = '_'; // 갈 수 있는 길
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
/// 그리드의 이동 가능 여부를 출력
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
/// 목적지까지의 경로를 출력
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

        if (nextX == _destX && nextY == _destY) break; // 출발지

        _destY = nextY;
        _destX = nextX;
    }

    printf("========== Visit Order ==========\n");
    // 출발 지점에 $를 출력
    int startIndex = path.size() - 1;
    PathTable[path[startIndex].second][path[startIndex].first] = '$';
    // 출발 지점 좌표 출력
    printf("[%c%d]", 'A' + path[startIndex].first, path[startIndex].second);
    // 도착 지점 => 출발 지점으로 경로와 좌표를 출력
    for (int i = startIndex - 1; i >= 0; i--)
    {
        // 좌표
        printf("->[%c%d]", 'A' + path[i].first, path[i].second);
        if (i != 0)
        {
            // 경로
            PathTable[path[i].first][path[i].second] = '*';
        }
        // 도착 지점에는 #을 출력
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
/// 다익스트라 알고리즘
/// 모든 셀을 방문할 것이기 때문에 시작점은 어디로든 설정 가능
/// </summary>
/// <param name="startY">시작점 행</param>
/// <param name="startX">시작점 렬</param>
void Dijkstra(int startY, int startX)
{
    priority_queue<Node> priorityQ;

    // 출발지
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].g_cost = 0;
    MinDistanceTable[y][x] = 0;

    // 출발지의 부모 노드를 자기 자신으로 설정
    ParentTable[y][x] = { y, x }; 

    // 우선 순위 큐에 출발지 설정
    priorityQ.push(Node(1, y, x));  // 출발지 비용과 좌표

    // 우선 순위 큐가 빌 때까지(= 모든 노드를 방문할 때까지) 반복
    while (!priorityQ.empty())
    {
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // 상하좌우 대각선 탐색
        //for (int i = 0; i < 4; i++)
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // 다음 인접 노드의 비용을 계산
            float nextCost = cost + GetNextCost(i);

            // 배열 범위, 이동 가능 여부 체크
            // (방문한 곳도 최소 비용 계산 위해 다시 방문할 필요 있기에 방문 여부는 체크 안 함)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // 현재 탐색 중인 경로의 비용이 기록해둔 비용보다 작으면 갱신함
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // 경로의 비용을 최소값으로 갱신
                MinDistanceTable[nextY][nextX] = nextCost;

                // 탐색한 인접 노드의 비용(거리)도 갱신
                GridBoard[nextY][nextX].g_cost = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // 경로를 추적하기 위한 부모 설정
                ParentTable[nextY][nextX] = { y, x };
            }
        }
    }
}

/// <summary>
/// A* 알고리즘(휴리스틱 사용 안 하는 알고리즘)
/// </summary>
void AStar1(int startY, int startX, int DestY, int DestX)
{
    priority_queue<Node> priorityQ;

    // 출발지
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].g_cost = 1;
    MinDistanceTable[y][x] = 1;

    // 출발지의 부모 노드를 자기 자신으로 설정
    ParentTable[y][x] = { y, x };

    // 우선 순위 큐에 출발지 설정
    priorityQ.push(Node(1, y, x));  // 출발지 비용과 좌표

    // 우선 순위 큐가 빌 때까지(= 모든 노드를 방문할 때까지) 반복
    while (!priorityQ.empty())
    {
        cost = priorityQ.top().cost;
        y = priorityQ.top().y;
        x = priorityQ.top().x;

        priorityQ.pop();

        // 상하좌우 대각선 탐색
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // 다음 인접 노드의 비용을 계산
            float nextCost = cost + GetNextCost(i);

            // 배열 범위, 이동 가능 여부 체크
            // (방문한 곳도 최소 비용 계산 위해 다시 방문할 필요 있기에 방문 여부는 체크 안 함)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            // 현재 탐색 중인 경로의 비용이 기록해둔 비용보다 작으면 갱신함
            if (nextCost < MinDistanceTable[nextY][nextX])
            {
                // 경로의 비용을 최소값으로 갱신
                MinDistanceTable[nextY][nextX] = nextCost;

                // 탐색한 인접 노드의 비용(거리)도 갱신
                GridBoard[nextY][nextX].g_cost = nextCost;

                priorityQ.push(Node(nextCost, nextY, nextX));

                // 경로를 추적하기 위한 부모 설정
                ParentTable[nextY][nextX] = { y, x };
            }

            // 방문한 노드가 도착 노드였을 경우 탐색을 종료함
            if (nextY == DestY && nextX == DestX) break;
        }
    }
}

/// <summary>
/// 휴리스틱을 계산하는 함수
/// </summary>
int CalculateHeuristicCost(int startY, int startX, int DestY, int DestX)
{
    return 0;
    // (??) 맨하탄 거리?
    //return abs(startY - DestY) + abs(startX - DestX);
}

/// <summary>
/// 비용 계산 부분을 수정해야 함
/// 열린 리스트(검사해야 하는 것들) => 비용 계산 해야 함
/// 닫힌 리스트(검사한 것들) => 비용 계산 함 => 최소 비용 갱신 필요
/// </summary>
void AStar2(int startY, int startX, int DestY, int DestX)
{
    priority_queue<Node> OpenQ;

    // 출발지
    int y = startY;
    int x = startX;
    float cost = 0.0f;

    // 출발지를 방문한 것으로 처리
    GridBoard[y][x].g_cost = 1;
    MinDistanceTable[y][x] = 1;

    // 출발지의 부모 노드를 자기 자신으로 설정
    ParentTable[y][x] = { y, x };

    // 우선 순위 큐에 출발지 설정
    OpenQ.push(Node(1, y, x));  // 출발지 비용과 좌표

    // 우선 순위 큐가 빌 때까지(= 모든 노드를 방문할 때까지) 반복
    while (!OpenQ.empty())
    {
        cost = OpenQ.top().cost;
        y = OpenQ.top().y;
        x = OpenQ.top().x;

        OpenQ.pop();
        AStarClosedTable[y][x] = true;

        // 상하좌우 대각선 탐색
        for (int i = 0; i < 8; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];
            // 다음 인접 노드의 비용을 계산
            float nextCost = cost + GetNextCost(i);

            // 배열 범위, 이동 가능 여부 체크
            // (방문한 곳도 최소 비용 계산 위해 다시 방문할 필요 있기에 방문 여부는 체크 안 함)
            if (!IsInside(nextY, nextX) || GridBoard[nextY][nextX].bflag) continue;

            if (AStarClosedTable[nextY][nextX] == false)
            {
                float g_NextCost = cost + GetNextCost(i);
                float h_NextCost = CalculateHeuristicCost(nextY, nextX, DestY, DestX);
                float f_NextCost = g_NextCost + h_NextCost;

                // 현재 탐색 중인 경로의 비용이 기록해둔 비용보다 작으면 갱신함
                if (f_NextCost < GridBoard[nextY][nextX].f_cost)
                {
                    // 탐색한 인접 노드의 비용(거리)도 갱신
                    GridBoard[nextY][nextX].g_cost = g_NextCost;
                    GridBoard[nextY][nextX].h_cost = h_NextCost;
                    GridBoard[nextY][nextX].f_cost = f_NextCost;

                    OpenQ.push(Node(f_NextCost, nextY, nextX));

                    // 경로를 추적하기 위한 부모 설정
                    ParentTable[nextY][nextX] = { y, x };
                }
            }

            // 방문한 노드가 도착 노드였을 경우 탐색을 종료함
            if (nextY == DestY && nextX == DestX) break;
        }
    }

}

/// <summary>
/// 메인 함수
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