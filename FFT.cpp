const int MAXN=440000;
const double PI = acos(-1);
int arrA[50005],arrB[50005];

struct FastFourierTransform {
    complex<double> omega[MAXN], omegaInverse[MAXN];

    void init(const int n) {
        for (int i = 0; i < n; i++) {
            omega[i] = std::complex<double>(cos(2 * PI / n * i), sin(2 * PI / n * i));
            omegaInverse[i] = std::conj(omega[i]);
        }
    }

    void transform(std::complex<double> *a, const int n, const std::complex<double> *omega) {
        int k = 0;
        while ((1 << k) < n) k++;
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < k; j++) if (i & (1 << j)) t |= (1 << (k - j - 1));
            if (i < t) std::swap(a[i], a[t]);
        }

        for (int l = 2; l <= n; l *= 2) {
            int m = l / 2;
            for (std::complex<double> *p = a; p != a + n; p += l) {
                for (int i = 0; i < m; i++) {
                    std::complex<double> t = omega[n / l * i] * p[m + i];
                    p[m + i] = p[i] - t;
                    p[i] += t;
                }
            }
        }
    }

    void dft(std::complex<double> *a, const int n) {
        transform(a, n, omega);
    }

    void idft(std::complex<double> *a, const int n) {
        transform(a, n, omegaInverse);
        for (int i = 0; i < n; i++) a[i] /= n;
    }
};
FastFourierTransform fft;

void multiply(const int *a1, const int n1, const int *a2, const int n2, int *res) {

    int n = 1;
    while (n < n1 + n2) n *= 2;
    static std::complex<double> c1[MAXN], c2[MAXN];
    for(int i=0;i<n;++i){c1[i].real(0);c2[i].real(0);c1[i].imag(0);c2[i].imag(0);}
    for (int i = 0; i < n1; i++) c1[i].real(a1[i]);
    for (int i = 0; i < n2; i++) c2[i].real(a2[i]);
    fft.init(n);
    fft.dft(c1, n), fft.dft(c2, n);
    for (int i = 0; i < n; i++) c1[i] *= c2[i];
    fft.idft(c1, n);
    for (int i = 0; i < n1 + n2 - 1; i++) res[i] = static_cast<int>(floor(c1[i].real() + 0.5));
}
