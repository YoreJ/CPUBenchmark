#include "PrimeTest.h"
using namespace std;
using ll = long long;

namespace Prime
{
    bool IsPrime(ll n, vector<ll>& PrimeList)
    {
        if(n < 2) return 0;
        else if (n == 2 || n == 3) return 1;
        ll Tmp = n % 6;
        if (Tmp != 1 && Tmp != 5) return 0;
        for (auto i : PrimeList)
        {
            if (i * i > n) break;
            if (n % i == 0) return 0;
        }
        return 1;
    }
    Tuple PrimeTest(int n, PerfCounter& pc)
    {
        pc.reset();
        pc.start();
        vector<ll> PrimeList = {2, 3};
        for (ll i = 5; i <= n; i += 6)
        {
            if (IsPrime(i, PrimeList)) PrimeList.push_back(i);
            if (IsPrime(i + 2, PrimeList)) PrimeList.push_back(i + 2);
        }
        return pc.stop();
    }
}