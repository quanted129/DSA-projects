#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n, m, u, v, temp;
    in >> n >> m;
    int** matrix = new int*[n - 1];
    for (int i = 1; i < n; i++)
    {
        matrix[i - 1] = new int[i];
        for (int j = 0; j < i; j++) matrix[i - 1][j] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        in >> u >> v;
        if (u > v)
        {
            temp = v;
            v = u;
            u = temp;
        }
        matrix[v - 2][u - 1] = 1;
    }
    in.close();
    ofstream out("output.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                out << '0';
            }
            else if (i > j)
            {
                out << matrix[i - 1][j];
            }
            else
            {
                out << matrix[j - 1][i];
            }
            if (j < n - 1) out << ' ';
        }
        out << '\n';
    }
    out.close();
    return 0;
}