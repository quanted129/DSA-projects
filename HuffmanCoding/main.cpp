#include <fstream>
using namespace std;

int main()
{
    ifstream in("huffman.in");
    int n;
    long long min, minSum, length = 0;
    in >> n;
    long long* p = new long long[n];
    long long* sum = new long long[n];
    for (int i = 0; i < n; i++) in >> p[i];
    int pNext = 0, sumNext = 0, sumSize = 0;
    bool pickedSum, pickedSum2;
    for (int i = 0; i < n - 1; i++)
    {
        pickedSum = 0; pickedSum2 = 0;
        min = 9223372036854775807;
        if (pNext < n && p[pNext] < min) min = p[pNext];
        if (sumNext < sumSize && sum[sumNext] < min)
        {
            min = sum[sumNext];
            pickedSum = 1;
        }
        minSum = min;
        min = 9223372036854775807;
        if (!pickedSum)
        {
            pNext++;
            if (pNext < n && p[pNext] < min)
            {
                min = p[pNext];
                pickedSum2 = 0;
            }
            if (sumNext < sumSize && sum[sumNext] < min)
            {
                min = sum[sumNext];
                pickedSum2 = 1;
            }
            pNext--;
        }
        else
        {
            sumNext++;
            if (pNext < n && p[pNext] < min)
            {
                min = p[pNext];
                pickedSum2 = 0;
            }
            if (sumNext < sumSize && sum[sumNext] < min)
            {
                min = sum[sumNext];
                pickedSum2 = 1;
            }
            sumNext--;
        }
        minSum += min;
        length += minSum;
        sum[sumSize++] = minSum;
        if (pickedSum) sumNext++;
        else pNext++;
        if (pickedSum2) sumNext++;
        else pNext++;
    }
    delete[] p;
    delete[] sum;
    ofstream out("huffman.out");
    out << length;
    out.close();
    return 0;
}