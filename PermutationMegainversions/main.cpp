#include <fstream>
using namespace std;

void fillTree(int arr[], long long tree[], int current, int lower, int upper)
{
    if (lower == upper)
    {
        tree[current] = arr[lower];
        return;
    }
    fillTree(arr, tree, (current << 1) + 1, lower, (lower + upper) >> 1);
    fillTree(arr, tree, (current << 1) + 2, ((lower + upper) >> 1) + 1, upper);
    tree[current] = tree[(current << 1) + 1] + tree[(current << 1) + 2];
}

void Add(int arr[], long long tree[], int index, int value, int current, int lower, int upper)
{
    if (lower == upper)
    {
        arr[index] += value;
        tree[current] += value;
        return;
    }
    if (index > (lower + upper) >> 1)
    {
        Add(arr, tree, index, value, (current << 1) + 2, ((lower + upper) >> 1) + 1, upper);
    }
    else
    {
        Add(arr, tree, index, value, (current << 1) + 1, lower, (lower + upper) >> 1);
    }
    tree[current] = tree[(current << 1) + 1] + tree[(current << 1) + 2];
}

long long FindSum(long long tree[], int current, int lower, int upper, int queryLower, int queryUpper)
{
    if (upper < queryLower || lower > queryUpper - 1) return 0;
    if (lower >= queryLower && upper <= queryUpper - 1) return tree[current];
    return FindSum(tree, (current << 1) + 1, lower, (lower + upper) >> 1, queryLower, queryUpper) + FindSum(tree, (current << 1) + 2, ((lower + upper) >> 1) + 1, upper, queryLower, queryUpper);
}

int main()
{
    ifstream in("input.txt");
    int n;
    in >> n;
    int* p = new int[n];
    for (int i = 0; i < n; i++) in >> p[i];
    in.close();
    int* arr1 = new int[n];
    int* arr2 = new int[n];
    auto* tree1 = new long long[n << 2];
    auto* tree2 = new long long[n << 2];
    auto* leftGreater = new long long[n];
    auto* rightLesser = new long long[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = 0;
        arr2[i] = 0;
        leftGreater[i] = 0;
        rightLesser[i] = 0;
    }
    fillTree(arr1, tree1, 0, 0, n - 1);
    fillTree(arr2, tree2, 0, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        leftGreater[i] = FindSum(tree1, 0, 0, n - 1, p[i], n);
        Add(arr1, tree1, p[i] - 1, 1, 0, 0, n - 1);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        rightLesser[i] = FindSum(tree2, 0, 0, n - 1, 0, p[i] - 1);
        Add(arr2, tree2, p[i] - 1, 1, 0, 0, n - 1);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += leftGreater[i] * rightLesser[i];
    delete[] p;
    delete[] arr1;
    delete[] arr2;
    delete[] tree1;
    delete[] tree2;
    delete[] leftGreater;
    delete[] rightLesser;
    ofstream out("output.txt");
    out << ans << endl;
    out.close();
    return 0;
}