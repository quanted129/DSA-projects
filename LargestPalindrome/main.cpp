#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string S;
    in >> S;
    in.close();
    int size = S.size();
    int** M = new int*[size];
    for (int i = 0; i < size; i++)
    {
        M[i] = new int[size];
        M[i][i] = 1;
    }
    for (int i = 0; i < size - 1; i++)
    {
        if (S[i] == S[i + 1]) M[i + 1][i] = 2;
        else M[i + 1][i] = 1;
    }
    for (int i = 2; i < size; i++)
        for (int j = i - 2; j >= 0; j--)
        {
            if (S[i] == S[j]) M[i][j] = M[i - 1][j + 1] + 2;
            else
            {
                if (M[i][j + 1] > M[i - 1][j]) M[i][j] = M[i][j + 1];
                else M[i][j] = M[i - 1][j];
            }
        }
    int palSize = M[size - 1][0];
    auto* pal = new char[palSize];
    int i1 = size - 1;
    int i2 = 0;
    int ind = 0;
    while (i1 >= i2 && ind < palSize >> 1)
    {
        if (S[i1] == S[i2])
        {
            pal[ind] = pal[palSize - ind - 1] = S[i1];
            i1--;
            i2++;
            ind++;
        }
        else if (M[i1][i2 + 1] > M[i1 - 1][i2]) i2++;
        else i1--;
    }
    if (palSize & 1) pal[palSize >> 1] = S[i1];
    out << palSize << '\n';
    for (int i = 0; i < palSize; i++) out << pal[i];
    out.close();
    return 0;
}