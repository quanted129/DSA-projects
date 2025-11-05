#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    int truesize, size = 2;
    in >> truesize;
    while (size - 1 < truesize) size <<= 1;
    size--;
    int* arr = new int[size];
    for (int i = 0; i < truesize; i++) in >> arr[i];
    in.close();
    for (int i = truesize; i < size; i++) arr[i] = 2147483647;
    bool isHeap = 1;
    for (int i = 0; i < size >> 1 && isHeap; i++)
    {
        if (arr[i] > arr[(i << 1) + 1] || arr[i] > arr[(i + 1) << 1]) isHeap = 0;
    }
    ofstream out("output.txt");
    (isHeap) ? out << "Yes" : out << "No";
    return 0;
}