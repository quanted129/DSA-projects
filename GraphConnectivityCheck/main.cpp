#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m, q, temp_x, temp_y, temp, root_x, root_y, root_v, next;
    in >> n >> m >> q;
    int* edge1 = new int[m + 1];
    int* edge2 = new int[m + 1];
    int* edgeNum = new int[q];
    auto* isRemovedEdge = new bool[m + 1];
    for (int i = 1; i <= m; i++)
    {
        in >> edge1[i] >> edge2[i];
        isRemovedEdge[i] = 0;
    }
    for (int i = 0; i < q; i++)
    {
        in >> edgeNum[i];
        isRemovedEdge[edgeNum[i]] = 1;
    }
    int* parent = new int[n + 1];
    for (int i = 0; i <= n; i++) parent[i] = -1;
    int compCount = n;
    for (int i = 1; i <= m; i++)
    {
        if (!isRemovedEdge[i])
        {
            root_x = edge1[i];
            while (parent[root_x] > 0) root_x = parent[root_x];
            temp_x = edge1[i];
            while (temp_x != root_x)
            {
                next = parent[temp_x];
                parent[temp_x] = root_x;
                temp_x = next;
            }
            temp_y = edge2[i];
            root_y = edge2[i];
            while (parent[root_y] > 0) root_y = parent[root_y];
            while (temp_y != root_y)
            {
                next = parent[temp_y];
                parent[temp_y] = root_y;
                temp_y = next;
            }
            if (root_x != root_y)
            {
                if (parent[root_x] > parent[root_y])
                {
                    temp = root_x;
                    root_x = root_y;
                    root_y = temp;
                }
                parent[root_x] += parent[root_y];
                parent[root_y] = root_x;
                compCount--;
            }
        }
    }
    auto* result = new bool[q + 1];
    result[0] = (compCount == 1) ? 1 : 0;
    for (int i = q - 1; i >= 0; i--)
    {
        root_x = edge1[edgeNum[i]];
        while (parent[root_x] > 0) root_x = parent[root_x];
        temp_x = edge1[edgeNum[i]];
        while (temp_x != root_x)
        {
            next = parent[temp_x];
            parent[temp_x] = root_x;
            temp_x = next;
        }
        root_v = edge2[edgeNum[i]];
        while (parent[root_v] > 0) root_v = parent[root_v];
        temp_y = edge2[edgeNum[i]];
        while (temp_y != root_v)
        {
            next = parent[temp_y];
            parent[temp_y] = root_v;
            temp_y = next;
        }
        if (root_x != root_v)
        {
            if (parent[root_x] > parent[root_v])
            {
                temp = root_x;
                root_x = root_v;
                root_v = temp;
            }
            parent[root_x] += parent[root_v];
            parent[root_v] = root_x;
            compCount--;
        }
        result[q - i] = (compCount == 1) ? 1 : 0;
    }
    for (int i = 0; i < q; i++) out << result[q - i - 1];
    delete[] edge1;
    delete[] edge2;
    delete[] edgeNum;
    delete[] parent;
    delete[] result;
    delete[] isRemovedEdge;
    in.close();
    out.close();
    return 0;
}