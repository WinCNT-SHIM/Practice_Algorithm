#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<string, int> um;

    for (int i = 100; i < 999; i++)
    {
        //숫자를 문자열로 만들어서 넣어 보기
        um.insert({ to_string(i), i});
    }

    // 결과 확인해 보기
    // unordered_map에 잡혀있는 bucket(저장 공간)을 반환함
    int bucketCnt = um.bucket_count();

    for (int i = 0; i < bucketCnt; i++)
    {
        cout << "bucket #" << i << " contains: ";
        // bucket에 저장된 값들을 가져옴
        // bucket에 있는 모든 데이터를 가져오도록 for문 이용
        // (해시 충돌이 일어난 경우를 고려)
        for (auto item = um.begin(i); item != um.end(i); ++item)
        {
            cout << "[" << item->first << ":" << item->second << "] ";
        }
        cout << "\n";
    }
    return 0;
}