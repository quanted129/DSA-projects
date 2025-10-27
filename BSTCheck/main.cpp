#include <fstream>
using namespace std;

struct element
{
    int data;
    int prevIndex;
    bool isR;
    int min;
    int max;
};

int main()
{
    ifstream in("bst.in");
    ofstream out("bst.out");
    int n, m, p;
    char c;
    in >> n >> m;
    auto* arr = new element[n + 1];
    arr[0] = element{0, -1, 0, 0, 0};
    arr[1] = element{m, 0, 0, -2147483648, 2147483647};
    bool broken = 0;
    for (int i = 2; i < n + 1 && !broken; i++)
    {
        in >> m >> p >> c;
        if (c == 'R') arr[i] = element{m, p, 1, (arr[p].data > arr[p].min) ? arr[p].data : arr[p].min, arr[p].max};
        else arr[i] = element{m, p, 0, arr[p].min, (arr[p].data - 1 > arr[p].max) ? arr[p].max : arr[p].data - 1};
        if (arr[i].data < arr[i].min || arr[i].data > arr[i].max) broken = 1;
    }
    in.close();
    broken ? (out << "NO") : (out << "YES");
    out.close();
    return 0;
}