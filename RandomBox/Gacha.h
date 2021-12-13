#pragma once
#include <random>

using namespace std;

class Gacha
{
private:
    int maxItemNum, maxCell;
public:
    Gacha(int maxItemNum, int maxCell);
    ~Gacha();

    void GetItemByRandomBox(mt19937& gen);
};

