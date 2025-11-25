#include <fstream>
#include <list>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n, m, u, v;
    in >> n >> m;
    auto* lists = new list<int>[n + 1];
    for (int i = 0; i < m; i++)
    {
        in >> u >> v;
        lists[u].push_front(v);
        lists[v].push_front(u);
    }
    in.close();
    ofstream out("output.txt");
    for (int i = 1; i <= n; i++)
    {
        out << lists[i].size();
        auto current = lists[i].begin();
        auto end = lists[i].end();
        while (current != end)
        {
            out << ' ' << *current;
            current++;
        }
        out << '\n';
    }
    out.close();
    return 0;
}