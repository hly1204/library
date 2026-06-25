// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/541

#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
using Matrix       = std::vector<std::vector<uint>>;
constexpr uint MOD = 1'000'000'007;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

struct Basis {
    const int dim;
    Matrix vectors; // v_0, v_1, ...
    Matrix a;
    Matrix r; // upper triangular matrix, diagonal of r = (1, ..., 1)
    // a * vectors = r

    explicit Basis(int dim) : dim(dim), a(dim), r(dim) {}

    int size() const { return (int)std::size(vectors); }

    // if V is linear combination of v_0, ..., v_(k-1) then
    // returns coefficients (a_0, ..., a_(k-1)) s.t. -(a_0v_0 + ... + a_(k-1)v_(k-1)) = V
    std::optional<std::vector<uint>> insert(const std::vector<uint> &V) {
        std::vector<uint> A(dim), RV = V;
        for (int i = 0; i < dim; ++i) {
            if (RV[i] == 0) continue;
            if (r[i].empty()) {
                A[size()]      = 1;
                const uint inv = InvMod(RV[i]);
                for (int j = i; j < dim; ++j) RV[j] = (ull)RV[j] * inv % MOD;
                for (int j = 0; j < dim; ++j) A[j] = (ull)A[j] * inv % MOD;
                a[i] = A, r[i] = RV, vectors.push_back(V);
                return {};
            }
            const uint v = RV[i];
            for (int j = i; j < dim; ++j) RV[j] = (RV[j] + MOD - (ull)v * r[i][j] % MOD) % MOD;
            for (int j = 0; j < dim; ++j) A[j] = (A[j] + MOD - (ull)v * a[i][j] % MOD) % MOD;
        }
        return A;
    }
};

int width(const Matrix &A) { return empty(A) ? 0 : (int)size(A[0]); }
int height(const Matrix &A) { return (int)size(A); }

Matrix mat_mul(const Matrix &A, const Matrix &B) {
    const int wA = width(A);
    const int hA = height(A);
    assert(height(B) == wA);
    const int wB = width(B);
    Matrix res(hA, std::vector<uint>(wB));
    for (int i = 0; i < hA; ++i)
        for (int k = 0; k < wA; ++k)
            for (int j = 0; j < wB; ++j) res[i][j] = (res[i][j] + (ull)A[i][k] * B[k][j]) % MOD;
    return res;
}

Matrix mat_pow(Matrix A, long long k) {
    const int n = width(A);
    assert(n == height(A));
    Matrix res(n, std::vector<uint>(n));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    for (;; A = mat_mul(A, A)) {
        if (k & 1) res = mat_mul(res, A);
        if ((k /= 2) == 0) return res;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // dp[width i connected][mask]
    uint dp[52][0b1000] = {};
    /*          x           x
        0b001 = . , 0b111 = x , ...
                .           x        */
    dp[1][0b001] = 1;
    dp[1][0b010] = 1;
    dp[1][0b100] = 1;
    dp[1][0b011] = 1;
    dp[1][0b110] = 1;
    dp[1][0b111] = 1;
    for (int i = 2; i < (int)std::size(dp); ++i) {
        for (int j = 0b001; j <= 0b111; ++j) {
            if (j == 0b101) {
                /*  ?xx    ?xx
                    ?x. or ?.. , ? connected
                    ?xx    ?xx                */
                dp[i][j] = ((ull)dp[i][j] + dp[i - 1][0b111] + dp[i - 1][0b101]) % MOD;
                continue;
            }
            for (int k = 0b001; k <= 0b111; ++k) {
                if (k == 0b101) {
                    if (j == 0b011 || j == 0b110) {
                        /*  x.    xx
                            .x or .x invalid
                            xx    x.          */
                        continue;
                    }
                    if (j == 0b111) {
                        /*  _xxx
                            _..x
                            _xxx  */
                        dp[i][j] = (dp[i][j] + 1) % MOD;
                        /*  ?xx                            x           .
                            ?.x + width (i - 2) and type = . or type = . ,
                            ?xx                            .           x
                        ---------------------------------------------------
                            ?xxx                            x           .
                            ?..x + width (i - 3) and type = . or type = . ,
                            ?xxx                            .           x    */
                        for (int l = 1; l <= i - 2; ++l) {
                            dp[i][j] = ((ull)dp[i][j] + dp[l][0b001] + dp[l][0b100]) % MOD;
                        }
                        continue;
                    }
                }
                if ((j & k) > 0) dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
            }
        }
    }
    std::vector<uint> A;
    for (int i = 1; i < (int)std::size(dp); ++i) {
        uint res = 0;
        for (int j = 1; j <= i; ++j) {
            uint sum = 0;
            for (int k = 0b001; k <= 0b111; ++k) sum = (sum + dp[j][k]) % MOD;
            res = (res + (ull)sum * (i - j + 1)) % MOD;
        }
        A.push_back(res);
    }
    Basis b((int)size(A) / 2);
    std::optional<std::vector<uint>> minpoly;
    for (int i = 0; i <= (int)size(A) / 2; ++i)
        if (const auto c = b.insert(std::vector(begin(A) + i, begin(A) + (i + (int)size(A) / 2)))) {
            minpoly.emplace(begin(*c), begin(*c) + i).emplace_back(1);
            break;
        }
    assert(minpoly);
    const int deg = (int)size(*minpoly) - 1;
    // M = transposed(C_minpoly)
    Matrix M(deg, std::vector<uint>(deg));
    for (int i = 0; i < deg - 1; ++i) M[i][i + 1] = 1;
    for (int i = 0; i < deg; ++i) M[deg - 1][i] = (MOD - minpoly->at(i)) % MOD;
    long long N;
    std::cin >> N;
    M        = mat_pow(M, N - 1);
    uint res = 0;
    for (int i = 0; i < deg; ++i) res = (res + (ull)M[0][i] * A[i]) % MOD;
    std::cout << res << '\n';
    return 0;
}
