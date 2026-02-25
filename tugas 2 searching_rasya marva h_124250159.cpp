#include <iostream>
using namespace std;

struct Buku {
    string nama;
    int harga;
};

int main() {
    Buku buku[5] = {
        {"Sistem Informasi", 50000},
        {"Bahasa Pemrograman", 60000},
        {"Jaringan Komputer", 55000},
        {"Pemrograman Web", 75000},
        {"Struktur Data", 65000} };

    int n = 5;
    int pilihan;
    string cari;

    cout << "Masukkan nama buku: ";
    getline(cin, cari);

    cout << "\nPilih metode pencarian\n";
    cout << "1. Sequential Search\n";
    cout << "2. Binary Search\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cout << endl;

                      //SEQUENTIAL SEARCH//
    if (pilihan == 1) {
        int i = 0;
        bool found = false;

        while (i < n && found == false) {
            if (buku[i].nama == cari) {
                found = true;
            } else {
                i++;
            }
        }

        if (found == true) {
            cout << "Buku ditemukan\n";
            cout << "Nama  : " << buku[i].nama << endl;
            cout << "Harga : Rp " << buku[i].harga << endl;
        } else {
            cout << "Buku tidak ditemukan" << endl;
        }
    }

                     //BINARY SEARC//
    else if (pilihan == 2) {
        int awal = 0, akhir = n - 1, tengah;
        bool found = false;

        while ((awal <= akhir) && (found == false)) {
            tengah = (awal + akhir) / 2;

            if (buku[tengah].nama == cari) {
                found = true;
            }
            else if (cari < buku[tengah].nama) {
                akhir = tengah - 1;
            }
            else {
                awal = tengah + 1;
            }
        }

        if (found == true) {
            cout << "Buku ditemukan\n";
            cout << "Nama  : " << buku[tengah].nama << endl;
            cout << "Harga : Rp " << buku[tengah].harga << endl;
        } else {
            cout << "Buku tidak ditemukan" << endl;
        }
    }

    else {
        cout << "Pilihan tidak valid" << endl;
    }

    return 0;
}
