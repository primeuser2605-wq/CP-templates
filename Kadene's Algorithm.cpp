ll maxSubArray(vector<ll> &a) {
    ll current = a[0];
    ll best = a[0];

    for (int i = 1; i < (int)a.size(); i++) {
        current = max(a[i], current + a[i]);
        best = max(best, current);
    }
    return best;
}
