#include <fstream>
using namespace std;

struct element
{
    int data;
    int prevIndex;
    bool isR;
};

int main()
{
    ifstream in("bst.in");
    ofstream out("bst.out");
    int n, m, p;
    char c;
    in >> n >> m;
    auto* arr = new element[n + 1];
    arr[0] = element{ 0, -1, 0 };
    arr[1] = element{ m, 0, 0 };
    bool broken = 0;
    for (int i = 2; i < n + 1; i++)
    {
        in >> m >> p >> c;
        arr[i] = element{ m, p, c == 'R'};
        int ind = i;
        int value = arr[ind].data;
        while (arr[ind].prevIndex != 0 && !broken)
        {
            if (!((arr[ind].isR && value >= arr[arr[ind].prevIndex].data) || (!arr[ind].isR && value < arr[arr[ind].prevIndex].data))) broken = 1;
            ind = arr[ind].prevIndex;
        }
    }
    in.close();
    broken ? (out << "NO") : (out << "YES");
    out.close();
    return 0;
}