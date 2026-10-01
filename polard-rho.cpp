struct PollardRho {
    using ull = unsigned long long;
    using u128 = __uint128_t;

    ull seed;

    PollardRho() {
        seed = chrono::steady_clock::now().time_since_epoch().count();
    }

    ull rnd(ull l, ull r) {
        seed ^= seed << 7;
        seed ^= seed >> 9;
        return l + seed % (r - l + 1);
    }

    ull mul(ull a, ull b, ull mod) {
        return (u128)a * b % mod;
    }

    ull pw(ull a, ull b, ull mod) {
        ull res = 1;
        while (b) {
            if (b & 1) res = mul(res, a, mod);
            a = mul(a, a, mod);
            b >>= 1;
        }
        return res;
    }

    bool isPrime(ull n) {
        if (n < 2) return false;

        ull small[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

        for (int i = 0; i < 12; i++) {
            if (n % small[i] == 0) return n == small[i];
        }

        ull d = n - 1, s = 0;
        while (!(d & 1)) {
            d >>= 1;
            s++;
        }

        ull base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

        for (int i = 0; i < 7; i++) {
            ull a = base[i] % n;
            if (a == 0) continue;

            ull x = pw(a, d, n);
            if (x == 1 || x == n - 1) continue;

            bool ok = false;

            for (int j = 1; j < s; j++) {
                x = mul(x, x, n);
                if (x == n - 1) {
                    ok = true;
                    break;
                }
            }

            if (!ok) return false;
        }

        return true;
    }

    ull gcd(ull a, ull b) {
        while (b) {
            ull t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ull f(ull x, ull c, ull mod) {
        return (mul(x, x, mod) + c) % mod;
    }

    ull rho(ull n) {
        if (n % 2 == 0) return 2;
        if (n % 3 == 0) return 3;

        while (true) {
            ull x = rnd(2, n - 2);
            ull y = x;
            ull c = rnd(1, n - 1);
            ull d = 1;

            while (d == 1) {
                x = f(x, c, n);
                y = f(f(y, c, n), c, n);

                ull diff = x > y ? x - y : y - x;
                d = gcd(diff, n);
            }

            if (d != n) return d;
        }
    }

    void factor(ull n, vector<ull> &res) {
        if (n == 1) return;

        if (isPrime(n)) {
            res.push_back(n);
            return;
        }

        ull d = rho(n);

        factor(d, res);
        factor(n / d, res);
    }

    vector<ull> getFactors(ull n) {
        vector<ull> res;
        factor(n, res);
        sort(res.begin(), res.end());
        return res;
    }
};