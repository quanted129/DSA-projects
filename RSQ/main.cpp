#include <iostream>
#include <string>
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
    int n, q, request1, request2;
    string query;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> q;
    auto *T = new long long[n << 2];
    fillTree(arr, T, 0, 0, n - 1);
    for (int i = 0; i < q; i++)
    {
        cin >> query >> request1 >> request2;
        if (query == "Add")
        {
            Add(arr, T, request1, request2, 0, 0, n - 1);
        }
        else
        {
            cout << FindSum(T, 0, 0, n - 1, request1, request2) << '\n';
        }
    }
    delete[] arr;
    delete[] T;
    return 0;
}