#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* A = new int[n];
    int* B = new int[n];
    int** M = new int*[n];
    for (int i = 0; i < n; i++) M[i] = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> B[i];
    }
    if (A[0] == B[0]) M[0][0] = 1;
    else M[0][0] = 0;
    for (int i = 1; i < n; i++)
    {
        if (A[0] == B[i]) M[0][i] = 1;
        else M[0][i] = M[0][i - 1];
        if (A[i] == B[0]) M[i][0] = 1;
        else M[i][0] = M[i - 1][0];
    }
    int debug = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
        {
            if (A[i] == B[j]) M[i][j] = M[i - 1][j - 1] + 1;
            else
            {
                if (M[i - 1][j] > M[i][j - 1]) M[i][j] = M[i - 1][j];
                else M[i][j] = M[i][j - 1];
            }
        }
    int len = M[n - 1][n - 1];
    cout << len << '\n';
    int* ind1 = new int[len];
    int* ind2 = new int[len];
    bool finished = 0;
    int i1 = n - 1;
    int i2 = n - 1;
    int ind = len - 1;
    while (i1 >= 0 && i2 >= 0 && ind >= 0)
    {
        if (A[i1] == B[i2])
        {
            ind1[ind] = i1;
            ind2[ind] = i2;
            i1--;
            i2--;
            ind--;
        }
        else if (i1 > 0 && M[i1][i2] == M[i1 - 1][i2]) i1--;
        else i2--;
    }
    for (int i = 0; i < len; i++) cout << ind1[i] << ' ';
    cout << '\n';
    for (int i = 0; i < len; i++) cout << ind2[i] << ' ';
    return 0;
}