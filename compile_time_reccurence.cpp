#include <iostream>
#include <string>
#include <array>

using namespace std;

template<typename T, int N>
constexpr array<T, N * N> matrixMultiplication(const array<T, N * N>& a, const array<T, N * N>& b, int mod)
{
    array<T, N * N> c{};
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                c[i * N + j] = (c[i * N + j] + a[i * N + k] * b[k * N + j]) % mod;
            }
        }
    }
    return c;
}

template<typename T, int N>
constexpr array<T, N * N> matrixPower(const array<T, N * N>& a, int n, int mod)
{
    array<T, N * N> c{};
    array<T, N * N> b = a;
    //init matrix c with the identity matrix
    for(int i = 0; i < N; ++i) {
        c[i * N + i] = 1;
    }
    
    for(int i = n; i; i >>= 1) {
        if(i & 1) {
            c = matrixMultiplication<T, N>(c, b, mod);
        }
        b = matrixMultiplication<T, N>(b, b, mod);
    }

    return c;
}

template<typename T, int N>
constexpr T computeRecurrence(const int n, const array<T, N>& coef, const array<T, N>& baseValues, int mod) {
    if(n < N) {
        return baseValues[n];
    }

    array<T, N * N> r{};

    for(int i = 0; i < N; ++i) {
        r[i] = coef[i];
    }

    for(int i = 1; i < N; ++i) {
        r[i * N + (i - 1)] = 1;
    }

    r = matrixPower<T, N>(r, n - N + 1, mod);

    T result{};

    for(int i = 0; i < N; ++i) {
        result = (result + r[i] * baseValues[i]) % mod;
    }
    
    return result;
}

int main() {
    constexpr int r = computeRecurrence<int, 2>(9, {1, 1}, {1, 1}, 5147);
    cout << r << endl;
	return 0;
}
