#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Node
{
    int num;
    long long cost;
    bool operator>(const Node& other) const { return cost > other.cost; }
};

int main()
{
    ifstream in("input.txt");
    int n, m, u, v, w;
    in >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        in >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    in.close();
    vector<long long> dist(n + 1, LLONG_MAX);
    priority_queue<Node, vector<Node>, greater<Node>> heap;
    dist[1] = 0;
    heap.push({1, 0});
    while (!heap.empty())
    {
        Node current = heap.top();
        heap.pop();
        u = current.num;
        if (current.cost <= dist[u])
        {
            for (int i = 0; i < adj[u].size(); i++)
            {
                v = adj[u][i].first;
                if (dist[u] + adj[u][i].second < dist[v])
                {
                    dist[v] = dist[u] + adj[u][i].second;;
                    heap.push({v, dist[v]});
                }
            }
        }
    }
    ofstream out("output.txt");
    out << dist[n] << endl;
    out.close();
    return 0;
}