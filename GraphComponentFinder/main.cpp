#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, q, u, v, temp;
    in >> n >> q;
    int* parent = new int[n + 1];
    int* path = new int[n];
    for (int i = 1; i <= n; i++) parent[i] = -1;
    for (int i = 0; i < q; i++)
    {
        in >> u >> v;
        temp = 0;
        while (parent[u] > 0)
        {
            path[temp++] = u;
            u = parent[u];
        }
        for (int i = 0; i < temp; i++) parent[path[i]] = u;
        temp = 0;
        while (parent[v] > 0)
        {
            path[temp++] = v;
            v = parent[v];
        }
        for (int i = 0; i < temp; i++) parent[path[i]] = v;
        if (u != v)
        {
            if (u > v)
            {
                temp = u;
                u = v;
                v = temp;
            }
            parent[u] += parent[v];
            parent[v] = u;
            n--;
        }
        out << n << endl;
    }
    in.close();
    out.close();
    return 0;
}