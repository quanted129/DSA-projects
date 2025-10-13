#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int size, upper, middle, lower;
    in >> size;
    int* arr = new int[size];
    int* comp = new int[size];
    for (int i = 0; i < size; i++)
    {
        in >> arr[i];
    }
    in.close();
    comp[0] = arr[0];
    int len = 1;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > comp[len - 1])
        {
            comp[len] = arr[i];
            len++;
        }
        else
        {
            lower = 0;
            upper = len - 1;
            while (lower <= upper)
            {
                middle = (lower + upper) >> 1;
                if (comp[middle] >= arr[i]) upper = middle - 1;
                else lower = middle + 1;
            }
            comp[lower] = arr[i];
        }
    }
    out << len;
    out.close();
    return 0;
}