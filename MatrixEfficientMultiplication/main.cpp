#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int size, temp;
    in >> size;
    int* input = new int[size << 1];
    for (int i = 0; i < size << 1; i++)
    {
        in >> input[i];
    }
    in.close();
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
        matrix[i][i] = 0;
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) matrix[i][j] = 0;

    int old = input[0];
    for (int i = 1, index = 1; i < size; i++)
    {
        matrix[i - 1][i] = old * input[index];
        old = input[++index];
        matrix[i - 1][i] *= input[++index];
    }

    for (int last = 2; last < size; last++)
        for (int i = 0; i < size - last; i++)
        {
            for (int k = i; k < i + last; k++)
            {
                temp = matrix[i][k] + matrix[k + 1][i + last] + input[i << 1] * input[(k << 1) + 1] * input[((i + last) << 1) + 1];
                if (temp < matrix[i][i + last] || matrix[i][i + last] == 0) matrix[i][i + last] = temp;
            }
        }
    out << matrix[0][size - 1];
    out.close();
    return 0;
}