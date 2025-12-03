#include <fstream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

struct Coords
{
    int x;
    int y;
};

struct Pos
{
    int node;
    int state; //index of prev crossroads
    bool operator==(const Pos& other) const { return (node == other.node) && (state == other.state); }
};

int main()
{
    ifstream in("input.txt");
    int n, m, x1, x2, y1, y2, n1, n2, start, finish;
    long long inVector_x, inVector_y, outVector_x, outVector_y, crossProduct, dotProduct;
    bool push;
    in >> n >> m;
    vector<Coords> crossroads(n + 1);
    vector<vector<bool>> adjMatrix(n + 1, vector<bool>(n + 1, 0));
    for (int i = 0; i < m; i++)
    {
        in >> x1 >> y1 >> x2 >> y2 >> n1 >> n2;
        crossroads[n1] = {x1, y1};
        crossroads[n2] = {x2, y2};
        adjMatrix[n1][n2] = adjMatrix[n2][n1] = 1;
    }
    in >> start >> finish;
    in.close();
    vector<vector<Pos>> path(n + 1);
    queue<Pos> q;
    path[start] = {{0, 0}};
    q.push({start, 0});
    while (!q.empty() && q.front().node != finish)
    {
        for (int i = 1; i <= n; i++)
        {
            if (adjMatrix[q.front().node][i])
            {
                if (q.front().state == 0)
                {
                    inVector_x = 0;
                    inVector_y = 1;
                }
                else
                {
                    inVector_x = crossroads[q.front().node].x - crossroads[q.front().state].x;
                    inVector_y = crossroads[q.front().node].y - crossroads[q.front().state].y;
                }
                outVector_x = crossroads[i].x - crossroads[q.front().node].x;
                outVector_y = crossroads[i].y - crossroads[q.front().node].y;
                crossProduct = inVector_x * outVector_y - inVector_y * outVector_x;
                dotProduct = inVector_x * outVector_x + inVector_y * outVector_y;
                if ((crossProduct == 0 && dotProduct > 0) || crossProduct < 0)
                {
                    push = 1;
                    for (int j = 0; j < path[i].size() && push; j++)
                    {
                        if (path[i][j].node == q.front().node) push = 0;
                    }
                    if (push)
                    {
                        q.push({i, q.front().node});
                        path[i].push_back(q.front());
                    }
                }
            }
        }
        q.pop();
    }
    ofstream out("output.txt");
    if (!q.empty())
    {
        stack<int> result;
        out << "Yes\n";
        int current = q.front().state;
        while (finish != 0)
        {
            result.push(finish);
            int resultNode = 0;
            push = 1;
            for (int i = 0; i < path[finish].size() && push; i++)
            {
                if (path[finish][i].node == current)
                {
                    resultNode = path[finish][i].state;
                    push = 0;
                }
            }
            finish = current;
            current = resultNode;
        }
        while (!result.empty())
        {
            out << result.top() << ' ';
            result.pop();
        }
    }
    else out << "No";
    out.close();
    return 0;
}