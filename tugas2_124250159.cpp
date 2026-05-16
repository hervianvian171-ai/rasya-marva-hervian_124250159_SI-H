#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 100;
const int KAPASITAS = 3;

// ================== STRUCT ==================
struct Kendaraan {
    string noPolisi;
    string namaPemilik;
    string status;
};

struct Node {
    Kendaraan data;
    Node* kiri;
    Node* kanan;
};

struct Aktivitas {
    string aksi;
    string noPolisi;
};

struct Stack {
    Aktivitas data[MAX];
    int top;
};

struct Queue {
    string data[MAX];
    int depan;
    int belakang;
};

// ================== GLOBAL ==================
Node* root = NULL;

Stack riwayat;
Queue antrian;

int jumlahParkir = 0;

// ================== GARIS ==================
void garis() {
    cout << "======================================================" << endl;
}

// ================== STACK ==================
void initStack() {
    riwayat.top = -1;
}

bool stackKosong() {
    return riwayat.top == -1;
}

void push(string aksi, string noPolisi) {

    riwayat.top++;

    riwayat.data[riwayat.top].aksi = aksi;
    riwayat.data[riwayat.top].noPolisi = noPolisi;
}

Aktivitas pop() {
    return riwayat.data[riwayat.top--];
}

// ================== QUEUE ==================
void initQueue() {

    antrian.depan = 0;
    antrian.belakang = -1;
}

bool queueKosong() {
    return antrian.belakang < antrian.depan;
}

void enqueue(string noPolisi) {

    antrian.belakang++;

    antrian.data[antrian.belakang] = noPolisi;
}

string dequeue() {
    return antrian.data[antrian.depan++];
}

// ================== BST ==================
Node* buatNode(Kendaraan data) {

    Node* baru = new Node;

    baru->data = data;
    baru->kiri = NULL;
    baru->kanan = NULL;

    return baru;
}

Node* insert(Node* root, Kendaraan data) {

    if (root == NULL) {
        return buatNode(data);
    }

    if (data.noPolisi < root->data.noPolisi) {
        root->kiri = insert(root->kiri, data);
    }

    else if (data.noPolisi > root->data.noPolisi) {
        root->kanan = insert(root->kanan, data);
    }

    return root;
}

Node* cari(Node* root, string noPolisi) {

    if (root == NULL) {
        return NULL;
    }

    if (root->data.noPolisi == noPolisi) {
        return root;
    }

    if (noPolisi < root->data.noPolisi) {
        return cari(root->kiri, noPolisi);
    }

    return cari(root->kanan, noPolisi);
}

Node* cariMin(Node* root) {

    while (root->kiri != NULL) {
        root = root->kiri;
    }

    return root;
}

Node* hapus(Node* root, string noPolisi) {

    if (root == NULL) {
        return NULL;
    }

    if (noPolisi < root->data.noPolisi) {
        root->kiri = hapus(root->kiri, noPolisi);
    }

    else if (noPolisi > root->data.noPolisi) {
        root->kanan = hapus(root->kanan, noPolisi);
    }

    else {

        if (root->kiri == NULL) {

            Node* temp = root->kanan;

            delete root;

            return temp;
        }

        else if (root->kanan == NULL) {

            Node* temp = root->kiri;

            delete root;

            return temp;
        }

        Node* temp = cariMin(root->kanan);

        root->data = temp->data;

        root->kanan = hapus(root->kanan, temp->data.noPolisi);
    }

    return root;
}

// ================== TAMPIL DATA ==================
void tampilData(Node* root) {

    if (root != NULL) {

        tampilData(root->kiri);

        cout << left;
        cout << setw(15) << root->data.noPolisi;
        cout << setw(20) << root->data.namaPemilik;
        cout << setw(20) << root->data.status << endl;

        tampilData(root->kanan);
    }
}

// ================== TAMBAH ==================
void tambahKendaraan() {

    int jumlah;

    garis();
    cout << "                TAMBAH KENDARAAN" << endl;
    garis();

    cout << "Jumlah data yang ingin ditambah : ";
    cin >> jumlah;

    cin.ignore();

    for (int i = 1; i <= jumlah; i++) {

        Kendaraan k;

        cout << endl;

        garis();
        cout << "Data Kendaraan Ke-" << i << endl;
        garis();

        cout << "Nomor Polisi  : ";
        getline(cin, k.noPolisi);

        cout << "Nama Pemilik  : ";
        getline(cin, k.namaPemilik);

        k.status = "Di Luar Parkiran";

        root = insert(root, k);

        cout << endl;
        cout << "Data kendaraan berhasil ditambahkan" << endl;
        cout << endl;
    }

    garis();
    cout << "Semua data kendaraan berhasil ditambahkan" << endl;
    garis();

    cout << endl;
}

// ================== TAMPIL ==================
void tampilKendaraan() {

    garis();
    cout << "                 DATA KENDARAAN" << endl;
    garis();

    cout << left;

    cout << setw(15) << "NO POLISI";
    cout << setw(20) << "NAMA PEMILIK";
    cout << setw(20) << "STATUS" << endl;

    garis();

    tampilData(root);

    garis();

    cout << endl;
}

// ================== MASUK ==================
void kendaraanMasuk() {

    string noPolisi;

    cin.ignore();

    garis();
    cout << "                KENDARAAN MASUK" << endl;
    garis();

    cout << "Masukkan Nomor Polisi : ";
    getline(cin, noPolisi);

    Node* ditemukan = cari(root, noPolisi);

    if (ditemukan == NULL) {

        cout << endl;
        cout << "Kendaraan tidak ditemukan" << endl;
        cout << endl;

        return;
    }

    if (ditemukan->data.status == "Di Parkiran") {

        cout << endl;
        cout << "Kendaraan sudah di parkiran" << endl;
        cout << endl;

        return;
    }

    if (jumlahParkir < KAPASITAS) {

        ditemukan->data.status = "Di Parkiran";

        jumlahParkir++;

        push("masuk", noPolisi);

        cout << endl;
        cout << "Kendaraan berhasil masuk" << endl;
        cout << endl;
    }

    else {

        enqueue(noPolisi);

        cout << endl;
        cout << "Parkiran penuh, kendaraan masuk antrian" << endl;
        cout << endl;
    }
}

// ================== KELUAR ==================
void kendaraanKeluar() {

    string noPolisi;

    cin.ignore();

    garis();
    cout << "               KENDARAAN KELUAR" << endl;
    garis();

    cout << "Masukkan Nomor Polisi : ";
    getline(cin, noPolisi);

    Node* ditemukan = cari(root, noPolisi);

    if (ditemukan == NULL) {

        cout << endl;
        cout << "Kendaraan tidak ditemukan" << endl;
        cout << endl;

        return;
    }

    ditemukan->data.status = "Di Luar Parkiran";

    jumlahParkir--;

    push("keluar", noPolisi);

    cout << endl;
    cout << "Kendaraan berhasil keluar" << endl;
    cout << endl;

    if (!queueKosong()) {

        string berikutnya = dequeue();

        Node* next = cari(root, berikutnya);

        next->data.status = "Di Parkiran";

        jumlahParkir++;

        cout << "Kendaraan berikutnya masuk parkiran" << endl;
        cout << endl;
    }
}

// ================== HAPUS ==================
void hapusKendaraan() {

    string noPolisi;

    cin.ignore();

    garis();
    cout << "               HAPUS KENDARAAN" << endl;
    garis();

    cout << "Masukkan Nomor Polisi : ";
    getline(cin, noPolisi);

    Node* ditemukan = cari(root, noPolisi);

    if (ditemukan == NULL) {

        cout << endl;
        cout << "Kendaraan tidak ditemukan" << endl;
        cout << endl;

        return;
    }

    root = hapus(root, noPolisi);

    cout << endl;
    cout << "Data kendaraan berhasil dihapus" << endl;
    cout << endl;
}
// ================== UNDO ==================
void undoAktivitas() {

    garis();
    cout << "                 UNDO AKTIVITAS" << endl;
    garis();

    // CEK STACK KOSONG
    if (stackKosong()) {

        cout << endl;
        cout << "Tidak ada aktivitas yang bisa di undo" << endl;
        cout << endl;

        return;
    }

    // AMBIL DATA TERAKHIR
    Aktivitas terakhir = pop();

    // CARI KENDARAAN
    Node* kendaraan = cari(root, terakhir.noPolisi);

    // CEK KENDARAAN ADA ATAU TIDAK
    if (kendaraan == NULL) {

        cout << endl;
        cout << "Data kendaraan sudah tidak ada" << endl;
        cout << endl;

        return;
    }

    // ================== JIKA AKSI MASUK ==================
    if (terakhir.aksi == "masuk") {

        // CEK STATUS
        if (kendaraan->data.status == "Di Parkiran") {

            kendaraan->data.status = "Di Luar Parkiran";

            // AGAR TIDAK MINUS
            if (jumlahParkir > 0) {
                jumlahParkir--;
            }

            cout << endl;
            cout << "Undo kendaraan masuk berhasil" << endl;
            cout << endl;
        }

        else {

            cout << endl;
            cout << "Undo gagal" << endl;
            cout << endl;
        }
    }

    // ================== JIKA AKSI KELUAR ==================
    else if (terakhir.aksi == "keluar") {

        // CEK KAPASITAS
        if (jumlahParkir < KAPASITAS) {

            kendaraan->data.status = "Di Parkiran";

            jumlahParkir++;

            cout << endl;
            cout << "Undo kendaraan keluar berhasil" << endl;
            cout << endl;
        }

        else {

            cout << endl;
            cout << "Parkiran penuh, undo gagal" << endl;
            cout << endl;
        }
    }

    garis();
    cout << endl;
}
// ================== ANTRIAN ==================
void tampilAntrian() {

    garis();
    cout << "                 ANTRIAN PARKIR" << endl;
    garis();

    if (queueKosong()) {

        cout << endl;
        cout << "Antrian kosong" << endl;
        cout << endl;

        return;
    }

    for (int i = antrian.depan; i <= antrian.belakang; i++) {

        cout << i - antrian.depan + 1 << ". ";
        cout << antrian.data[i];
        cout << " menunggu masuk parkiran" << endl;
    }

    cout << endl;
}

// ================== MENU ==================
void menu() {

    garis();
    cout << "          SISTEM PARKIR BANDARA GSA" << endl;
    garis();

    cout << "1. Tambah Data Kendaraan" << endl;
    cout << "2. Tampil Data Kendaraan" << endl;
    cout << "3. Kendaraan Masuk" << endl;
    cout << "4. Kendaraan Keluar" << endl;
    cout << "5. Hapus Data Kendaraan" << endl;
    cout << "6. Undo Aktivitas" << endl;
    cout << "7. Tampil Antrian" << endl;
    cout << "8. Keluar" << endl;

    garis();

    cout << "Jumlah Parkir : ";
    cout << jumlahParkir;
    cout << " / ";
    cout << KAPASITAS << endl;

    garis();

    cout << "Pilih Menu : ";
}

// ================== MAIN ==================
int main() {

    initStack();
    initQueue();

    int pilih;

    do {

        menu();

        cin >> pilih;

        cout << endl;

        switch (pilih) {

            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilKendaraan();
                break;

            case 3:
                kendaraanMasuk();
                break;

            case 4:
                kendaraanKeluar();
                break;

            case 5:
                hapusKendaraan();
                break;

            case 6:
                undoAktivitas();
                break;

            case 7:
                tampilAntrian();
                break;

            case 8:

                garis();
                cout << "Program selesai" << endl;
                garis();

                break;

            default:

                cout << "Menu tidak tersedia" << endl;
                cout << endl;
        }

    } while (pilih != 8);

    return 0;
}
