#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

vector<double> randomOlustur(int size);

vector<double> seriKonv(const vector<double>& x, const vector<double>& h);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int N = 1000;
    int M = 10;

    vector<double> x = randomOlustur(N);
    vector<double> h = randomOlustur(M);

    auto start_time = high_resolution_clock::now();

    vector<double> y = seriKonv(x, h);

    auto end_time = high_resolution_clock::now();

    cout << "x: [";
    for (int i = 0; i < x.size(); ++i) {
        cout << x[i];
        if (i < x.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout << "h: [";
    for (int i = 0; i < h.size(); ++i) {
        cout << h[i];
        if (i < h.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout << "Sonuc: [";
    for (int i = 0; i < y.size(); ++i) {
        cout << y[i];
        if (i < y.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Programın Çalışma Süresi: " << duration.count() << " milisaniye" << endl;

    return 0;
}

vector<double> randomOlustur(int size) {
    vector<double> arr;
    for (int i = 0; i < size; ++i) {
        arr.push_back(static_cast<double>(rand()));
    }
    return arr;
}

vector<double> seriKonv(const vector<double>& x, const vector<double>& h) {
    int N = x.size();
    int M = h.size();
    int y_size = N + M - 1;

    vector<double> y(y_size, 0);

    for (int n = 0; n < y_size; ++n) {
        for (int k = 0; k <= n && k < M; ++k) {
            if (n - k < N) {
                y[n] += x[n - k] * h[k];
            }
        }
    }

    return y;
}
