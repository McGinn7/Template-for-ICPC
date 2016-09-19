#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);

//复数结构体

struct Complex {
    double r, i;
    Complex(double r = 0.0, double i = 0.0) {
        this->r = r;
        this->i = i;
    }
    Complex operator + (const Complex &b) {
        return Complex(r + b.r, i + b.i);
    }
    Complex operator - (const Complex &b) {
        return Complex(r - b.r, i - b.i);
    }
    Complex operator * (const Complex &b) {
        return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须去2的幂
 */
void change(Complex *y, int len) {
    int i, j, k;
    for(i = 1, j = len / 2; i < len - 1; i++) {
        if(i < j) swap(y[i], y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len / 2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
/*
 * 做FFT
 * len必须为2^k形式，
 * on==1时是DFT，on==-1时是IDFT
 */
void fft(Complex *y, int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for(int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for(int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1) {
        for(int i = 0; i < len; i++)
            y[i].r /= len;
    }
}

const int N = 100005;

Complex x1[N * 4], x2[N * 4];
long long sum[N * 4];
int n, a[N], dp[N];

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r)>>1;
    cdq(l, mid);
    int len = 1;
    while (len < r - l + 1) len <<= 1;
    for (int i = 0; i < len; i++) {
        x1[i] = (l + i <= mid ? Complex(dp[l + i] * 1.0, 0.0) : Complex(0.0, 0.0));
        x2[i] = (l + i + 1 <= r ? Complex(a[i + 1] * 1.0, 0.0) : Complex(0.0, 0.0));
    }
    fft(x1, len, 1); fft(x2, len, 1);
    for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
    fft(x1, len, -1);
    for (int i = mid + 1; i <= r; i++) {
        dp[i] = (dp[i] + (long long)(x1[i - l - 1].r + 0.5) % 313) % 313;
    }
    cdq(mid + 1, r);
}

int main() {
    while (~scanf("%d", &n) && n) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            a[i] %= 313;
        }
        dp[0] = 1;
        cdq(0, n);
        printf("%d\n", dp[n]);
    }
    return 0;
}