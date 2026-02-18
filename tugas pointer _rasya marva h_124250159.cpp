#include <iostream>  
using namespace std;  

int main() {

    // 1. Membuat array integer   
    int arr[] = {10, 5, 20, 8, 15};   // Array integer dengan panjang dan nilai bebas
    int n = 5;                        // Menyimpan jumlah elemen array

    int *ptr = arr;                   // Pointer menunjuk ke alamat awal array

    // 2. Mencetak semua elemen array menggunakan pointer

    cout << "Isi array: " << endl;    // Menampilkan judul output

    for(int i = 0; i < n; i++) {      // Perulangan sebanyak jumlah elemen
        cout << *(ptr + i) << " ";    // Mengakses nilai array dengan pointer
    }

    cout << endl << endl;             // Memberi jarak output

  
    // 3. Mencari nilai maksimum dan minimum
    
    int max = *ptr;                   // Inisialisasi max dengan elemen pertama
    int min = *ptr;                   // Inisialisasi min dengan elemen pertama

    for(int i = 1; i < n; i++) {      // Perulangan mulai dari elemen kedua
        if(*(ptr + i) > max) {        // Jika nilai lebih besar dari max
            max = *(ptr + i);         // Update nilai max
        }

        if(*(ptr + i) < min) {        // Jika nilai lebih kecil dari min
            min = *(ptr + i);         // Update nilai min
        }
    }

    cout << "Nilai maksimum = " << max << endl;  // Menampilkan nilai maksimum
    cout << "Nilai minimum = " << min << endl;   // Menampilkan nilai minimum

    cout << endl;

    // 4. Menghitung jumlah dan rata-rata

    int jumlah = 0;                   // Variabel untuk menyimpan total

    for(int i = 0; i < n; i++) {      // Perulangan untuk menjumlahkan
        jumlah += *(ptr + i);         // Menambahkan nilai menggunakan pointer
    }

    double rata = (double)jumlah / n;      // Menghitung rata-rata

    cout << "Jumlah = " << jumlah << endl;       // Menampilkan jumlah
    cout << "Rata-rata = " << rata << endl;      // Menampilkan rata-rata

    return 0;       // Mengakhiri program
}
