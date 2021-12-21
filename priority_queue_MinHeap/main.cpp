#include <iostream>
#include <queue>

using namespace std;

int main()
{
    //priority_queue<pair<int, string>> priorityQ;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> priorityQ;
    priorityQ.push(make_pair(1, "I"));
    priorityQ.push(make_pair(2, "Am"));
    priorityQ.push(make_pair(3, "Your"));
    priorityQ.push(make_pair(4, "Cat"));

    cout << "priorityQ\n";
    while (priorityQ.size())
    {
        cout << priorityQ.top().second << ' ';
        priorityQ.pop();
    }
}
