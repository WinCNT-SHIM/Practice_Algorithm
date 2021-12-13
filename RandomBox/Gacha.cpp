#include "Gacha.h"

Gacha::Gacha(int maxItemNum, int maxCell)
{
    this->maxItemNum = maxItemNum;
    this->maxCell = maxCell;
}

Gacha::~Gacha()
{
}

void Gacha::GetItemByRandomBox(mt19937& gen)
{
    //int rndVal = discreteDist(gen);
    //return ItemInfo[rndVal];
}
