#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

// Rastgele bir dizi oluşturan fonksiyonu tanımla
vector<double> generateRandomArray(int size);

// Paralel konvolüsyon işlemini yapan fonksiyonu tanımla
DWORD WINAPI paralelKonv(LPVOID thread_args);

// Giriş dizileri ve çıkış dizisi ile ilgili değişkenleri tanımla
vector<double> x, h, y;
int N, M, y_size;
int thread_sayisi = 16; 

int main() {
    // Rastgele sayı üretebilmek için rasgele sayı üreticiyi başlat
    srand(static_cast<unsigned int>(time(nullptr)));

    // Giriş dizilerinin boyutlarını belirle
    N = 10;
    M = 10;

    // Rastgele giriş dizilerini oluştur
    x = generateRandomArray(N);
    h = generateRandomArray(M);

    // Zaman ölçümü başlat
    auto start_time = high_resolution_clock::now();

    // Çıkış dizisinin boyutunu belirle ve sıfırla
    y_size = N + M - 1;
    y.resize(y_size, 0);

    // Paralel konvolüsyon işlemini yapan thread'leri oluştur
    HANDLE threads[thread_sayisi];
    int thread_args[thread_sayisi];

    for (int i = 0; i < thread_sayisi; ++i) {
        
        thread_args[i] = i;
        threads[i] = CreateThread(NULL, 0, paralelKonv, &thread_args[i], 0, NULL);
    }

    
    WaitForMultipleObjects(thread_sayisi, threads, TRUE, INFINITE);// Thread'lerin bitmesini bekle

    
    auto end_time = high_resolution_clock::now();// Zaman ölçümü bitir

    
   auto duration = end_time - start_time;
   double duration_in_milliseconds = chrono::duration<double, milli>(duration).count();

   cout << "Programın Çalışma Süresi: " << duration_in_milliseconds << " milisaniye" << endl;




    return 0;
}

// Belirtilen boyutta rastgele bir dizi oluşturan fonksiyon
vector<double> generateRandomArray(int size) {
    vector<double> arr;
    for (int i = 0; i < size; ++i) {
        // Diziye rastgele bir double değer ekle
        arr.push_back(static_cast<double>(rand()));
    }
    return arr;
}


DWORD WINAPI paralelKonv(LPVOID thread_args) {// Paralel konvolüsyon işlemini yapan fonksiyon
    int tid = *((int*)thread_args);

    
    for (int n = tid; n < y_size; n += thread_sayisi) {// Her bir thread'in sorumlu olduğu çıkış dizisi elemanlarını hesapla
        for (int k = 0; k <= n && k < M; ++k) {
            if (n - k < N) {
                
                y[n] += x[n - k] * h[k]; // Konvolüsyon işlemi yaparak çıkış dizisini güncelle
            }
        }
    }

    return 0;
}
