vector<long long> findFactors(long long n) {
    vector<long long> factors;
    for (long long d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            factors.push_back(d);
            if (n / d != d)    // d should be different from n / d
                factors.push_back(n / d);
        }
    }
    return factors;
}
