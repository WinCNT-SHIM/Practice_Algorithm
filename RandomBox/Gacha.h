#pragma once
#include <random>
#include <vector>
#include <map>

using namespace std;

class Gacha
{
private:
    vector<int> tmpArr;
    map<int, int> gachaRes;
public:
    Gacha(vector<int> tmpArr);
    ~Gacha();

    void GetItemByRandomBox(mt19937& gen);
};

