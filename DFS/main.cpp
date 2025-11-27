#include <fstream>
using namespace std;

void DFS(int node, int* visited, auto** matrix, int &n, int &index)
{
    visited[node] = index++;
    for (int i = 0; i < n; i++)
    {
        if (matrix[node][i] && !visited[i]) DFS(i, visited, matrix, n, index);
    }
}

int main()
{
    ifstream in("input.txt");
    int n, index = 1;
    in >> n;
    int* visited = new int[n];
    auto** matrix = new bool*[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        matrix[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            in >> matrix[i][j];
        }
    }
    in.close();
    for (int i = 0; i < n; i++)
    {
        if (!visited[i]) DFS(i, visited, matrix, n, index);
    }
    ofstream out("output.txt");
    for (int i = 0; i < n; i++) out << visited[i] << ' ';
    out.close();
    return 0;
}