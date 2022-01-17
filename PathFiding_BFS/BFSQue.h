#pragma once
#include <stdio.h>
#include <windows.h>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class BFSQue : public queue<pair<int, int>>
{
    BFSQue() { m_visitCount = 0; }

    void Push(int y, int x)
    {
        push({ y, x });
        m_List.push_front({ y,x });
        //GridBoard[y][x].visitOrder = ++m_visitCount;
    }

private:
    list<pair<int, int>> m_List;
    int m_visitCount = 0;
};

