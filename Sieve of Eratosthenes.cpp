#Student Friendly
vector<bool> isPrime(n + 1, true);
isPrime[0] = isPrime[1] = false;

for (long long i = 2; i * i <= n; i++) {
    if (isPrime[i]) {
        for (long long j = i * i; j <= n; j += i) {
            // why iterate from i * i and not 2 * i
            isPrime[j] = false;
        }
    }
}

#Advanced Version
vector<pair<int, int>> primeFactorization(int x, vector<int>& spf){
    vector<pair<int, int>> ans;

    while(x != 1){
        int prime = spf[x];
        int cnt = 0;
        while(x % prime == 0){
            cnt++;
            x = x / prime;
        }
        ans.push_back({prime, cnt});
    }
    return ans;
}

void solve(){
    int maxN = 1e6;
    vector<bool> isPrime(maxN, true);
    vector<int> spf(1e6, 1e9);

    for(long long i = 2; i < maxN; i++){
        if(isPrime[i]){
            spf[i] = i;
            for(long long j = i * i; j < maxN; j += i){
                isPrime[i] = false;
                spf[j] = min(spf[j], (int)i);
            }
        }
    }

    vector<pair<int, int>> primeF = primeFactorization(36, spf);
}
