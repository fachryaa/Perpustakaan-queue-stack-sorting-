#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
#define MAX 5
#define MAX_PEMINJAM 100

char huruf[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Perpustakaan{
private:
    int jmlBukuPendidikan = 0;
    int jmlBukuHiburan = 0;
    string bukuPendidikan[MAX];
    string bukuHiburan[MAX];

    int jmlAntrian=0;
    string namaAntrian[MAX];

    int countPeminjam=0;
    string namaPeminjam[MAX_PEMINJAM];
    int countBukuDipinjam=0;
    string bukuDipinjam[MAX_PEMINJAM];

    int denda;
public:
    void addBuku();
    void pushBuku(int kelompok,string buku);
    void printBuku();

    void pinjamBuku();
    void cariBuku();
    void pushPeminjam();
    void popPeminjam();
    void pengembalian();

    void switchData(string *a , string *b);
    void sortBuku();
    int findIndex(char bukuAt0);

    void menu();
};

void Perpustakaan::addBuku() {
    string buku;
    int kelompok;

    cout<<"\n======================== Tambah Buku ========================\n\n";

    cout<<"1. Kelompok Pendidikan\n";
    if(jmlBukuPendidikan>MAX) cout<<"Buku Pendidikan Sudah Penuh...\n";
    else{
        kelompok=1;
        cout<<"Masukan Judul Buku\t:\n";
        for(int i=0 ; i<MAX ; i++){
            cout<<i+1<<". ";
            getline(cin,buku);
            transform(buku.begin() , buku.end() , buku.begin() , ::toupper);
            pushBuku(kelompok,buku);
        }
    }

    cout<<"\n2. Kelompok Hiburan\n";
    if(jmlBukuHiburan>MAX) cout<<"Buku Hiburan Sudah Penuh...\n";
    else {
        kelompok=2;
        cout<<"Masukan Judul Buku\t:\n";
        for(int i=0 ; i<MAX ; i++){
            cout<<i+1<<". ";
            getline(cin,buku);
            transform(buku.begin() , buku.end() , buku.begin() , ::toupper);
            pushBuku(kelompok,buku);
        }
    }
    sortBuku();
}

void Perpustakaan::pushBuku(int kelompok,string buku) {
    if(kelompok==1){
        bukuPendidikan[jmlBukuPendidikan] = buku;
        jmlBukuPendidikan++;
    }
    else{
        bukuHiburan[jmlBukuHiburan] = buku;
        jmlBukuHiburan++;
    }
}

void Perpustakaan::cariBuku() {
    bool found=false;
    int kelompok;
    string buku;
    cout<<"Kelompok\n1. Pendidikan\n2. Hiburan\n\nPilih : ";
    cin>>kelompok;
    cin.get();
    cout<<"\nMasukan Judul Buku\t: ";
    getline(cin,buku);
    transform(buku.begin() , buku.end() , buku.begin() , ::toupper);

    if(kelompok==1){
        for(int i=0 ; i < jmlBukuPendidikan ; i++){
            if(bukuPendidikan[i].find(buku,0) != string::npos){
                bukuDipinjam[countBukuDipinjam]=bukuPendidikan[i];
                countBukuDipinjam++;
                buku = bukuPendidikan[i];
                for(int j=i ; j < jmlBukuPendidikan-1 ; j++){
                    bukuPendidikan[j]=bukuPendidikan[j+1];
                }
                jmlBukuPendidikan--;
                found = true;
            }
        }
    }
    else {
        for(int i=0 ; i < jmlBukuHiburan ; i++){
            if(bukuHiburan[i].find(buku,0) != string::npos){
                bukuDipinjam[countBukuDipinjam]=bukuHiburan[i];
                countBukuDipinjam++;
                buku = bukuHiburan[i];
                for(int j=i ; j < jmlBukuHiburan-1 ; j++){
                    bukuHiburan[j]=bukuHiburan[j+1];
                }
                jmlBukuHiburan--;
                found = true;
            }
        }
    }

    if(!found) {
        cout<<"Tidak dapat menemukan judul buku :((\n\nMasukan lagi...\n";
        cariBuku();
    }
    else{
        cout<<"Buku ("<<buku<<") berhasil dipinjam"<<endl<<endl;
        popPeminjam();
    }
}

void Perpustakaan::pinjamBuku() {
    cout<<"\n======================== Pinjam Buku ========================\n\n";
    if(jmlAntrian == 0){
        cout<<"Antrian masih kosong...\nSilahkan tambahkan antrian\n\n";
        pushPeminjam();
    }

    if(jmlBukuHiburan==0 || jmlBukuPendidikan==0) cout<<"Buku kosong... :(\n";
    else{
        string buku;

        cout << "Antrian sekarang\t: " << namaAntrian[0] << endl << endl;
        cout<<"Cari buku...\n\n";
        cariBuku();
    }
}

void Perpustakaan::printBuku() {
    cout<<"\n======================== Lihat Daftar Buku ========================\n\n";
    cout<<"Kelompok Pendidikan\n";
    if(jmlBukuPendidikan==0) cout<<"(KOSONG)\n";
    else{
        for(int i=0 ; i<jmlBukuPendidikan ; i++){
            cout<<i+1<<". "<<bukuPendidikan[i]<<endl;
        }
    }
    cout<<"\nKelompok Hiburan\n";
    if(jmlBukuHiburan==0) cout<<"(KOSONG)\n\n";
    else{
        for(int i=0 ; i<jmlBukuHiburan ; i++){
            cout<<i+1<<". "<<bukuHiburan[i]<<endl;
        }
        cout<<endl;
    }
}

void Perpustakaan::pushPeminjam() {
    cout<<"\n======================== Tambah Antrian ========================\n\n";
    if(jmlAntrian>MAX-1) cout<<"Antrian Penuh...\n\n";
    else{
        string nama;
        cout<<"Masukan nama\t: ";
        getline(cin,nama);
        namaAntrian[jmlAntrian] = nama;
        jmlAntrian++;
        namaPeminjam[countPeminjam] = nama;
        countPeminjam++;
        cout<<endl;
    }
}

void Perpustakaan::popPeminjam() {
        for(int i=0 ; i < jmlAntrian-1 ; i++)
            namaAntrian[i]=namaAntrian[i + 1];
        jmlAntrian--;
}

void Perpustakaan::pengembalian() {
    cout<<"\n======================== Pengembalian Buku ========================\n\n";
    if(countPeminjam==0) cout<<"Tidak ada Buku yang dipinjam\n\n";
    else{
        string nama;
        bool found = false;

        menu:
        cout<<"Masukan Nama\t: ";
        getline(cin,nama);
        cout<<endl;

        for(int i=0 ; i<countPeminjam ; i++){
            if(namaPeminjam[i].find(nama) != string::npos) {
                cout<<"Nama peminjam\t: "<<namaPeminjam[i]<<endl
                    <<"Buku yang dipinjam\t: "<<bukuDipinjam[i]<<endl;
                found = true;
            }
        }
        //jika nama tidak ditemukan
        if(!found) {
            cout<<"Nama tidak ditemukan, silahkan masukan nama lagi...\n\n";
            goto menu;
        }

        int hari;
        cout<<"\nMeminjam buku berapa hari? ";
        cin>>hari;

        if(hari>5){
            denda = (hari-5)*1000;
            cout<<"\nAnda meminjam buku lebih dari 5 hari...\nAnda dikenakan denda Rp"<<denda<<endl;
        }
        else cout<<"\nAnda mengembalikan buku tepat waktu\n";

        cout<<"\nBerhasil Mengembalikan buku...\n\n";
    }
}

void Perpustakaan::switchData(string *a, string *b) {
    string temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int Perpustakaan::findIndex(char bukuAt0) {
    int n = sizeof(huruf)/ sizeof(huruf[0]);
    for(int i=0 ; i<n-1 ; i++){
        if(bukuAt0 == huruf[i]) return i;
    }
}

void Perpustakaan::sortBuku() {
    for(int i=0 ; i<MAX ; i++){
        for(int j=0 ; j<MAX ; j++){
            int bukuPenA = findIndex(bukuPendidikan[i].at(0));
            int bukuPenB = findIndex(bukuPendidikan[j].at(0));
            int bukuHibA = findIndex(bukuHiburan[i].at(0));
            int bukuHibB = findIndex(bukuHiburan[j].at(0));

            if(bukuPenA<bukuPenB) switchData(&bukuPendidikan[i], &bukuPendidikan[j]);
            if(bukuHibA<bukuHibB) switchData(&bukuHiburan[i],&bukuHiburan[j]);
        }
    }
}

void Perpustakaan::menu() {
    menu:
    cout<<"======================== PERPUSTAKAAN ========================\n\n";

    cout<<"Menu"<<endl
        <<"1. Tambah buku"<<endl
        <<"2. Tampilkan semua buku"<<endl
        <<"3. Tambah antrian"<<endl
        <<"4. Pinjam buku"<<endl
        <<"5. Pengembalian buku"<<endl
        <<"6. EXIT"<<endl<<endl;
    int pilih;
    cout<<"Pilih\t: ";
    cin>>pilih;
    cin.get();

    switch (pilih){
        case 1:
            addBuku();
            goto menu;
        case 2:
            printBuku();
            goto menu;
        case 3:
            pushPeminjam();
            goto menu;
        case 4:
            pinjamBuku();
            goto menu;
        case 5:
            pengembalian();
            goto menu;
        default:
            cout<<"\nTerima Kasih... :)\n\n";
            cout<<"======================== EXIT ========================\n\n";
            break;
    }
}

int main() {
    Perpustakaan p;
    p.menu();
    return 0;
}