#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n, parent, child;
    in >> n;
    int* p = new int[n];
    for (int i = 0; i < n; i++) p[i] = 0;
    for (int i = 1; i < n; i++)
    {
        in >> parent >> child;
        p[child - 1] = parent;
    }
    in.close();
    ofstream out("output.txt");
    for (int i = 0; i < n; i++) out << p[i] << ' ';
    return 0;
}