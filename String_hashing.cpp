ll mod_mul(ll a, ll b, ll m){ return (a % m) * (b % m) % m; }
ll mod_sub(ll a, ll b, ll m){ a %= m; b %= m; return (a - b + m) % m; }

ll binpow(ll a, ll b, ll m){
    ll res = 1;
    while(b){
        if(b & 1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

ll mminvprime(ll a, ll m){
    return binpow(a, m - 2, m);
}

struct Hashing {
    string s;
    int n;
    int primes;
    vector<ll> hashPrimes = {1000000009LL, 1000000007LL};
    const ll base = 31;

    vector<vector<ll>> hashValues;
    vector<vector<ll>> powersOfBase;
    vector<vector<ll>> inversePowersOfBase;

    Hashing(string a) {

        s = a;
        n = s.length();
        primes = hashPrimes.size();

        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);

        // Precompute powers and inverse powers
        for (int i = 0; i < primes; i++) {

            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);

            powersOfBase[i][0] = 1;

            // base^j
            for (int j = 1; j <= n; j++) {
                powersOfBase[i][j] = mod_mul(powersOfBase[i][j - 1], base, hashPrimes[i]);
            }

            // Compute inverse of base^n
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);

            // inverse(base^j) = inverse(base^(j+1)) * base
            for (int j = n - 1; j >= 0; j--) {
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            }
        }

        // Compute prefix hash values
        for (int i = 0; i < primes; i++) {

            hashValues[i].resize(n);

            for (int j = 0; j < n; j++) {
                ll here = mod_mul(s[j] - 'a' + 1LL, powersOfBase[i][j], hashPrimes[i]);

                hashValues[i][j] = (here + (j > 0 ? hashValues[i][j - 1] : 0LL)) % hashPrimes[i];
            }
        }
    }

    vector<ll> substringHash(int l, int r) {
        vector<ll> hash(primes);

        for (int i = 0; i < primes; i++) {

            ll val1 = hashValues[i][r];
            ll val2 = (l > 0 ? hashValues[i][l - 1] : 0LL);

            ll diff = mod_sub(val1, val2, hashPrimes[i]);

            hash[i] = mod_mul(diff, inversePowersOfBase[i][l], hashPrimes[i]);
        }

        return hash;
    }
};

     
