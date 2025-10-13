#include <iostream>
#include <list>
using namespace std;

int main()
{
    int size;
    cin >> size;
    int* arr = new int[size];
    int* path = new int[size];
    for (int i = 0; i < size; i++) cin >> arr[i];
    if (size == 1) cout << arr[0] << '\n' << 1;
    else if (size == 2) cout << -1;
    else
    {
        int* sums = new int[size];
        sums[0] = arr[0];
        path[0] = -1;
        sums[1] = -2147483648;
        for (int i = 2; i < size; i++) sums[i] = 0;
        for (int i = 0; i < size - 3; i++)
        {
            if (sums[i] + arr[i + 2] > sums[i + 2])
            {
                sums[i + 2] = sums[i] + arr[i + 2];
                path[i + 2] = i;
            }
            if (sums[i] + arr[i + 3] > sums[i + 3])
            {
                sums[i + 3] = sums[i] + arr[i + 3];
                path[i + 3] = i;
            }
        }

        if (sums[size - 4] >= sums[size - 3])
        {
            sums[size - 1] = sums[size - 4] + arr[size - 1];
            path[size - 1] = size - 4;
        }
        else
        {
            sums[size - 1] = sums[size - 3] + arr[size - 1];
            path[size - 1] = size - 3;
        }
        cout << sums[size - 1] << '\n';
        list<int> sequence;
        int current = size - 1;
        while (current >= 0)
        {
            sequence.push_front(current + 1);
            current = path[current];
        }

        for (auto it = sequence.begin(); it != sequence.end(); ++it)
        {
            if (it != sequence.begin()) cout << ' ';
            cout << *it;
        }
    }
    delete[] arr;
    delete[] path;
    return 0;
}