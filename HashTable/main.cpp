#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int m, c, n, x, current;
    in >> m >> c >> n;
    int* arr = new int[m];
    for (int i = 0; i < m; i++) arr[i] = -1;
    for (int i = 0; i < n; i++)
    {
        in >> x;
        current = x % m;
        while (arr[current] != -1 && arr[current] != x)
        {
            current += c;
            current %= m;
        }
        arr[current] = x;
    }
    in.close();
    ofstream out("output.txt");
    for (int i = 0; i < m; i++) out << arr[i] << ' ';
    out.close();
    return 0;
}