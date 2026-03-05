#include <iostream>   
using namespace std;  

void bubbleSortAscending(string arr[], int n) { // Fungsi Bubble Sort untuk mengurutkan data secara Ascending (A-Z)
    for (int i = 0; i < n - 1; i++) { // Perulangan untuk jumlah tahap sorting
        for (int j = 0; j < n - i - 1; j++) {  // Perulangan untuk membandingkan setiap elemen array
            if (arr[j] > arr[j + 1]) { // Jika elemen sekarang lebih besar dari elemen setelahnya
                swap(arr[j], arr[j + 1]); // Tukar posisi kedua elemen
            }
        }
    }
}

int partitionDesc(string arr[], int low, int high) { // Fungsi partition untuk Quick Sort Descending
    string pivot = arr[high];  // Menentukan elemen terakhir sebagai pivot
    int i = low - 1; // Variabel penanda posisi elemen yang lebih besar dari pivot
    for (int j = low; j < high; j++) {  // Perulangan untuk membandingkan semua elemen dengan pivot

        // Jika elemen lebih besar dari pivot (untuk urutan Z-A)
        if (arr[j] > pivot) { 
            i++; // menaikkan indeks
            swap(arr[i], arr[j]); // menukar posisi elemen
        }
    }

    // Menempatkan pivot pada posisi yang benar
    swap(arr[i + 1], arr[high]);

    // Mengembalikan posisi pivot
    return i + 1;
}

// Fungsi Quick Sort untuk mengurutkan data secara Descending
void quickSortDescending(string arr[], int low, int high) {

    // Jika indeks awal masih lebih kecil dari indeks akhir
    if (low < high) {

        // Mendapatkan posisi pivot
        int pi = partitionDesc(arr, low, high);

        // Rekursi untuk bagian kiri pivot
        quickSortDescending(arr, low, pi - 1);

        // Rekursi untuk bagian kanan pivot
        quickSortDescending(arr, pi + 1, high);
    }
}

int main() {

    // Variabel untuk menyimpan jumlah mahasiswa
    int n;

    // Meminta user memasukkan jumlah mahasiswa
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;

    // Mengabaikan newline agar getline bisa digunakan
    cin.ignore();

    // Array untuk menyimpan nama mahasiswa
    string nama[n];

    // Menampilkan instruksi input nama
    cout << "Masukkan daftar nama mahasiswa:\n";

    // Perulangan untuk menginput nama mahasiswa
    for (int i = 0; i < n; i++) {
        cout << "Nama ke-" << i + 1 << ": ";
        getline(cin, nama[i]); // membaca nama lengkap termasuk spasi
    }

    // Array kedua untuk Quick Sort agar data asli tidak berubah
    string namaQuick[n];

    // Menyalin isi array nama ke array namaQuick
    for (int i = 0; i < n; i++) {
        namaQuick[i] = nama[i];
    }

    // Memanggil fungsi Bubble Sort untuk mengurutkan Ascending
    bubbleSortAscending(nama, n);

    // Menampilkan hasil pengurutan Bubble Sort
    cout << "\nHasil Bubble Sort (Ascending):\n";
    for (int i = 0; i < n; i++) {
        cout << nama[i] << endl;
    }

    // Memanggil fungsi Quick Sort untuk mengurutkan Descending
    quickSortDescending(namaQuick, 0, n - 1);

    // Menampilkan hasil Quick Sort
    cout << "\nHasil Quick Sort (Descending):\n";
    for (int i = 0; i < n; i++) {
        cout << namaQuick[i] << endl;
    }

}
