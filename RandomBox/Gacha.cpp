#include "Gacha.h"

Gacha::Gacha(vector<int> tmpArr)
{
    this->tmpArr = tmpArr;
}

Gacha::~Gacha()
{
}

void Gacha::GetItemByRandomBox(mt19937& gen)
{
    discrete_distribution<int> discreteDist(tmpArr.begin(), tmpArr.end());
    //int rndVal = discreteDist(gen);
    //return ItemInfo[rndVal];
}
