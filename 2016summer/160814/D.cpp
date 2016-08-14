#pragma GCC optimize("Ofast")
#include <functional>
#include <iostream>
#include <queue>
#include <utility>

int arr[17];

void work()
{
    int n;
    std::cin >> n;
    std::priority_queue<std::pair<int, int> > pq;
    int ttl = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ttl += x;
        pq.emplace(x, i);
    }
    int i = 1;
    int ttl2 = ttl / 2;
    int prev = -1;
    for (; i <= ttl2; ++i) {
        if (pq.empty())
            break;
        auto tp = pq.top();
        pq.pop();
        if (tp.second == prev) {
            if (pq.empty())
                break;
            auto tq = pq.top();
            pq.pop();
            prev = tq.second;
            pq.push(tp);
            --tq.first;
            if (tq.first)
                pq.push(tq);
        } else {
            --tp.first;
            prev = tp.second;
            if (tp.first)
                pq.push(tp);
        }
    }
    std::cout << i - 1 << std::endl;
}

int main()
{
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)  {
        std::cout << "Case #" << i + 1 << ": ";
        work();
    }
}
