#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct Produk{
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Produk katalog[100];
int n = 0;

void loadFile(){
    FILE *pf = fopen("shopease_db.txt","r");
    if(pf==NULL) return;

    while(fscanf(pf," %[^|]|%[^|]|%lf|%d|%f\n",
          katalog[n].name,
          katalog[n].category,
          &katalog[n].price,
          &katalog[n].stock,
          &katalog[n].rating)!=EOF){
        n++;
    }

    fclose(pf);
}

void saveFile(){
    FILE *pf = fopen("shopease_db.txt","w");

    for(int i=0;i<n;i++){
        fprintf(pf,"%s|%s|%.0lf|%d|%.1f\n",
        katalog[i].name,
        katalog[i].category,
        katalog[i].price,
        katalog[i].stock,
        katalog[i].rating);
    }

    fclose(pf);
}

void tambahProduk(){
    cout<<"\nTambah Produk Baru\n";

    cin.ignore();

    cout<<"Nama Produk : ";
    cin.getline(katalog[n].name,60);

    cout<<"Kategori : ";
    cin.getline(katalog[n].category,30);

    cout<<"Harga : ";
    cin>>katalog[n].price;

    cout<<"Stok : ";
    cin>>katalog[n].stock;

    cout<<"Rating : ";
    cin>>katalog[n].rating;

    n++;

    saveFile();

    cout<<"Produk berhasil ditambahkan!\n";
}

void bubbleSortNama(){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(strcmp(katalog[j].name,katalog[j+1].name)>0){
                swap(katalog[j],katalog[j+1]);
            }
        }
    }
}

int partition(int low,int high){
    float pivot = katalog[high].rating;
    int i = low-1;

    for(int j=low;j<high;j++){
        if(katalog[j].rating > pivot){
            i++;
            swap(katalog[i],katalog[j]);
        }
    }

    swap(katalog[i+1],katalog[high]);
    return i+1;
}

void quickSortRating(int low,int high){
    if(low<high){
        int pi = partition(low,high);
        quickSortRating(low,pi-1);
        quickSortRating(pi+1,high);
    }
}

void tampilProduk(){
    int pilih;

    cout<<"\n1. Urut Nama (Ascending - Bubble Sort)\n";
    cout<<"2. Urut Rating (Descending - Quick Sort)\n";
    cout<<"Pilih : ";
    cin>>pilih;

    if(pilih==1)
        bubbleSortNama();
    else
        quickSortRating(0,n-1);

    cout<<"\nDaftar Produk\n";

    cout<<left<<setw(20)<<"Nama"
        <<setw(15)<<"Kategori"
        <<setw(10)<<"Harga"
        <<setw(8)<<"Stok"
        <<setw(6)<<"Rating"<<endl;

    for(int i=0;i<n;i++){
        cout<<setw(20)<<katalog[i].name
            <<setw(15)<<katalog[i].category
            <<setw(10)<<katalog[i].price
            <<setw(8)<<katalog[i].stock
            <<setw(6)<<katalog[i].rating<<endl;
    }
}

void cariProduk(){
    char cari[60];
    bool ketemu=false;

    cin.ignore();

    cout<<"\nMasukkan nama produk : ";
    cin.getline(cari,60);

    for(int i=0;i<n;i++){
        if(strcasecmp(katalog[i].name,cari)==0){
			cout<<"\n================================\n";
            cout<<"\n        Produk ditemukan      \n";
            cout<<"\n================================\n";
            cout<<"Nama : "<<katalog[i].name<<endl;
            cout<<"Kategori : "<<katalog[i].category<<endl;
            cout<<"Harga : "<<katalog[i].price<<endl;
            cout<<"Stok : "<<katalog[i].stock<<endl;
            cout<<"Rating : "<<katalog[i].rating<<endl;
            cout<<"\n================================\n";
            ketemu=true;
            break;
        }
    }

    if(!ketemu)
        cout<<"Produk tidak ditemukan!\n";
}

int main(){

    loadFile();

    int menu;

    do{
		cout<<"\n==================================\n";
        cout<<"\n       SHOP EASE KATALOG     \n";
        cout<<"\n==================================\n";
        cout<<"1. Tambah Produk\n";
        cout<<"2. Tampilkan Produk\n";
        cout<<"3. Cari Produk\n";
        cout<<"4. Keluar\n";
        cout<<"Pilih : ";
        cin>>menu;

        switch(menu){
            case 1: tambahProduk(); break;
            case 2: tampilProduk(); break;
            case 3: cariProduk(); break;
            case 4:
                saveFile();
                cout<<"Terima kasih telah menggunakan program.\n";
                break;
        }

    }while(menu!=4);

}
