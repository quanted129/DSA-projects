#include <fstream>
#include <queue>
#include <set>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n, next = 1;
    in >> n;
    queue<int> q;
    set<int> used;
    int* result = new int[n + 1];
    auto** matrix = new bool*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new bool[n];
        for (int j = 0; j < n; j++) in >> matrix[i][j];
    }
    in.close();
    for (int i = 1; i <= n; i++)
    {
        if (q.empty())
        {
            while (used.contains(next)) next++;
            q.push(next);
            used.insert(next);
        }
        for (int j = 1; j <= n; j++)
        {
            if (matrix[q.front() - 1][j - 1] && !used.contains(j))
            {
                q.push(j);
                used.insert(j);
            }
        }
        result[q.front()] = i;
        q.pop();
    }
    ofstream out("output.txt");
    for (int i = 1; i <= n; i++) out << result[i] << ' ';
    out.close();
    return 0;
}