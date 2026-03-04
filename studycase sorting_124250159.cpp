#include <iostream>
#include <string>
using namespace std;

void bubbleSortAscending(string arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partitionDesc(string arr[], int low, int high) {
    string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] > pivot) { 
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortDescending(string arr[], int low, int high) {
    if (low < high) {
        int pi = partitionDesc(arr, low, high);
        quickSortDescending(arr, low, pi - 1);
        quickSortDescending(arr, pi + 1, high);
    }
}

int main() {
    int n;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore();

    string nama[n];

    cout << "Masukkan daftar nama mahasiswa:\n";
    for (int i = 0; i < n; i++) {
        cout << "Nama ke-" << i + 1 << ": ";
        getline(cin, nama[i]);
    }

    string namaQuick[n];
    for (int i = 0; i < n; i++) {
        namaQuick[i] = nama[i];
    }

    bubbleSortAscending(nama, n);

    cout << "\nHasil Bubble Sort (Ascending):\n";
    for (int i = 0; i < n; i++) {
        cout << nama[i] << endl;
    }

    quickSortDescending(namaQuick, 0, n - 1);

    cout << "\nHasil Quick Sort (Descending):\n";
    for (int i = 0; i < n; i++) {
        cout << namaQuick[i] << endl;
    }

}
