#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace chrono;


vector<double> randomOlustur(int size);
void* paralelKonv(void* thread_id);


vector<double> x, h, y;
int N, M, y_size;
int thread_sayisi = 16; 
int main() {
  
    srand(static_cast<unsigned int>(time(nullptr)));

    N = 100000;
    M = 10;

    x = randomOlustur(N);
    h = randomOlustur(M);

   
    auto start_time = high_resolution_clock::now();

    y_size = N + M - 1;
    y.resize(y_size, 0);

    pthread_t threads[thread_sayisi];
    int thread_args[thread_sayisi];

    for (int i = 0; i < thread_sayisi; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], nullptr, paralelKonv, &thread_args[i]);
    }

    for (int i = 0; i < thread_sayisi; ++i) {
        pthread_join(threads[i], nullptr);
    }

 
    auto end_time = high_resolution_clock::now();

  
   auto duration = end_time - start_time;
   double duration_in_milliseconds = chrono::duration<double, milli>(duration).count();

   cout << "Programın Çalışma Süresi: " << duration_in_milliseconds << " milisaniye" << endl;
    return 0;
}


vector<double> randomOlustur(int size) {
    vector<double> arr;
    for (int i = 0; i < size; ++i) {
 
        arr.push_back(static_cast<double>(rand() ));
    }
    return arr;
}


void* paralelKonv(void* thread_id) {
    int tid = *((int*)thread_id);

    for (int n = tid; n < y_size; n += thread_sayisi) {
        for (int k = 0; k <= n && k < M; ++k) {
            if (n - k < N) {
                y[n] += x[n - k] * h[k];
            }
        }
    }

    pthread_exit(nullptr);
}
