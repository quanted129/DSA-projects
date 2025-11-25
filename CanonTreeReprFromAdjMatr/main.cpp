#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int n;
    bool node;
    in >> n;
    int* p = new int[n];
    for (int i = 0; i < n; i++) p[i] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            in >> node;
            if (node) p[j] = i + 1;
        }
    }
    in.close();
    ofstream out("output.txt");
    for (int i = 0; i < n; i++) out << p[i] << ' ';
    out.close();
    return 0;
}