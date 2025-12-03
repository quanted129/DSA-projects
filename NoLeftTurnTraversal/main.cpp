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
    int state; //0 - up, 1 - right, 2 - down, 3 - left
    bool operator==(const Pos& other) const { return (node == other.node) && (state == other.state); }
};

int main()
{
    ifstream in("input.txt");
    int n, m, x1, x2, y1, y2, n1, n2, start, finish, temp;
    bool push = 1;
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
                if (crossroads[q.front().node].x == crossroads[i].x && crossroads[q.front().node].y < crossroads[i].y)
                {
                    //MOVE UP
                    if (q.front().state == 3 || q.front().state == 0)
                    {
                        for (int j = 0; j < path[i].size(); j++)
                        {
                            if (path[i][j] == q.front()) push = 0;
                        }
                        if (push)
                        {
                            q.push({i, 0});
                            path[i].push_back(q.front());
                        }
                        push = 1;
                    }
                }
                if (crossroads[q.front().node].x < crossroads[i].x && crossroads[q.front().node].y == crossroads[i].y)
                {
                    //MOVE RIGHT
                    if (q.front().state == 0 || q.front().state == 1)
                    {
                        for (int j = 0; j < path[i].size(); j++)
                        {
                            if (path[i][j] == q.front()) push = 0;
                        }
                        if (push)
                        {
                            q.push({i, 1});
                            path[i].push_back(q.front());
                        }
                        push = 1;
                    }
                }
                if (crossroads[q.front().node].x == crossroads[i].x && crossroads[q.front().node].y > crossroads[i].y)
                {
                    //MOVE DOWN
                    if (q.front().state == 1 || q.front().state == 2)
                    {
                        for (int j = 0; j < path[i].size(); j++)
                        {
                            if (path[i][j] == q.front()) push = 0;
                        }
                        if (push)
                        {
                            q.push({i, 2});
                            path[i].push_back(q.front());
                        }
                        push = 1;
                    }
                }
                if (crossroads[q.front().node].x > crossroads[i].x && crossroads[q.front().node].y == crossroads[i].y)
                {
                    //MOVE LEFT
                    if (q.front().state == 2 || q.front().state == 3)
                    {
                        for (int j = 0; j < path[i].size(); j++)
                        {
                            if (path[i][j] == q.front()) push = 0;
                        }
                        if (push)
                        {
                            q.push({i, 3});
                            path[i].push_back(q.front());
                        }
                        push = 1;
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
        result.push(finish);
        out << "Yes\n";
        while (finish != start)
        {
            int resultNode = path[finish].back().node;
            path[finish].pop_back();
            result.push(resultNode);
            finish = resultNode;
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