#include <iostream>
using namespace std;
#define MAX 10

char huruf[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Perpustakaan{
private:
    int noBukuPendidikan = 0;
    int noBukuHiburan = 0;
    string bukuPendidikan[MAX];
    string bukuHiburan[MAX];

    int countPeminjam=0;
    string namaPeminjam[MAX];
    int hariPeminjaman;


public:
    void addBuku();
    void deleteBuku();
    void addPeminjam(string nama);
};

void Perpustakaan::addBuku() {
    string buku;
    int kelompok;

    cout<<"Masukan Judul Buku\t: ";
    getline(cin,buku);
    cout<<"Kelompok\n1. Pendidikan\n2. Hiburan\n\nPilih : ";
    cin>>kelompok;
    cin.get();

    if(kelompok==1){
        bukuPendidikan[noBukuPendidikan] = buku;
        noBukuPendidikan++;
    }
    else{
        bukuHiburan[noBukuHiburan] = buku;
        noBukuHiburan++;
    }
}

void Perpustakaan::addPeminjam(string nama) {
    namaPeminjam[countPeminjam] = nama;
    countPeminjam++;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}