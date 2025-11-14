#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== STRUCT DATA =====================
typedef struct {
    char id[10];
    char judul[100];
    char penulis[100];
    char kategori[30]; // Fiksi, Non-Fiksi, Komik, Majalah, Referensi
    int tahun;
    int stok;
    int dipinjam;
} Buku;

typedef struct {
    char id[10];
    char nama[100];
    char alamat[150];
    char no_telp[20];
} Anggota;

typedef struct {
    char id_pinjam[10];
    char id_anggota[10];
    char id_buku[10];
    char tgl_pinjam[20];
    char tgl_kembali[20];
    int denda;
    int status; // 0 = belum kembali, 1 = sudah kembali
} Peminjaman;

typedef struct {
    char username[50];
    char password[50];
} Login;

// ===================== PROTOTYPE FUNGSI =====================
// main.c
void tampilkanMenuUtama();

// buku.c
void menuBuku();
void tambahBuku();
void hapusBuku();
void editBuku();
void lihatDaftarBuku();
void cariBuku();

// anggota.c
void menuAnggota();
void daftarAnggota();
void lihatAnggota();

// peminjaman.c
void menuPeminjaman();
void pinjamBuku();
void kembalikanBuku();
void riwayatPeminjamanAnggota();
int cekIdAnggota(char *idAnggota);

// login.c
int loginAdmin();

// utilitas.c
extern int durasiMaksimal;
extern int dendaPerHari; // denda per hari keterlambatan
void menuUtilitas();
void tambahAkun();
void ubahPassword();
void setDurasiMaksimal();
void setDendaPerHari();
void rankingBuku();
void bersihkanLayar();

#endif
