#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");
    int dTax, iTax, rTax, temp;
    string A, B;
    in >> dTax >> iTax >> rTax >> A >> B;
    in.close();
    int sizeA = A.size() + 1;
    int sizeB = B.size() + 1;
    int** M = new int*[sizeB];
    for (int i = 0; i < sizeB; i++) M[i] = new int[sizeA];
    M[0][0] = 0;
    for (int i = 1; i < sizeB; i++)M[i][0] = i * iTax;
    for (int i = 1; i < sizeA; i++) M[0][i] = i * dTax;
    for (int i = 1; i < sizeB; i++)
        for (int j = 1; j < sizeA; j++)
        {
            M[i][j] = M[i - 1][j - 1] + ((A[j - 1] == B[i - 1]) ? 0 : rTax);
            if (M[i - 1][j] + iTax < M[i][j]) M[i][j] = M[i - 1][j] + iTax;
            if (M[i][j - 1] + dTax < M[i][j]) M[i][j] = M[i][j - 1] + dTax;
        }
    out << M[sizeB - 1][sizeA - 1];
    return 0;
}