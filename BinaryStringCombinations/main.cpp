#include <iostream>
using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    if (K > N - K) K = N - K;
    long long numerator = 1;
    long long denominator = 1;
    for (int i = 1; i < K + 1; i++)
    {
        numerator = (numerator * (N - i + 1)) % 1000000007;
        denominator = (denominator * i) % 1000000007;
    }
    long long result = numerator;
    long long power = 1000000005;
    long long base = denominator;
    while (power > 0)
    {
        if (power & 1)
        {
            result = (result * base) % 1000000007;
        }
        base = (base * base) % 1000000007;
        power >>= 1;
    }
    cout << result;
    return 0;
}