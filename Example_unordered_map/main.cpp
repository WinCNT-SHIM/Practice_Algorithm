#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<string, int> um;

    for (int i = 100; i < 999; i++)
    {
        //���ڸ� ���ڿ��� ���� �־� ����
        um.insert({ to_string(i), i});
    }

    // ��� Ȯ���� ����
    // unordered_map�� �����ִ� bucket(���� ����)�� ��ȯ��
    int bucketCnt = um.bucket_count();

    for (int i = 0; i < bucketCnt; i++)
    {
        cout << "bucket #" << i << " contains: ";
        // bucket�� ����� ������ ������
        // bucket�� �ִ� ��� �����͸� ���������� for�� �̿�
        // (�ؽ� �浹�� �Ͼ ��츦 ���)
        for (auto item = um.begin(i); item != um.end(i); ++item)
        {
            cout << "[" << item->first << ":" << item->second << "] ";
        }
        cout << "\n";
    }
    return 0;
}