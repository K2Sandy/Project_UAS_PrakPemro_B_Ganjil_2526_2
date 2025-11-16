#include "perpustakaan.h"

void menuAnggota() { //menampilkan menu anggota yang dapat dipilih
    int pilihan;
    do {
        printf("\n==== MENU ANGGOTA ====\n");
        printf("1. Daftar Anggota Baru\n");
        printf("2. Lihat Daftar Anggota\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
      //menjalankan aksi berdasarkan pilihan user
            case 1: daftarAnggota(); break;
            case 2: lihatAnggota(); break;
            case 0: printf("Kembali ke menu utama...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void daftarAnggota() {
//menambah data anggota pada file .txt
    Anggota a;
    FILE *f = fopen("data_anggota.txt", "a");
    if (!f) {
        printf("Gagal membuka file data_anggota.txt\n");
        return;
    }
    printf("Masukkan ID Anggota: "); scanf("%s", a.id);//menerima input ID anggota dari User
    getchar();
    printf("Nama: "); fgets(a.nama, sizeof(a.nama), stdin); strtok(a.nama, "\n");
//menerima input nama berupa huruf dari user
    printf("Alamat: "); fgets(a.alamat, sizeof(a.alamat), stdin); strtok(a.alamat, "\n");
    printf("No Telepon: "); scanf("%s", a.no_telp);
   //menerima input nomor telepon berupa angka
    fprintf(f, "%s|%s|%s|%s\n", a.id, a.nama, a.alamat, a.no_telp);
    fclose(f);
    printf("Anggota berhasil didaftarkan!\n");
}

void lihatAnggota() {
//menampilkan data anggota yang sudah tersimpan
    Anggota a;
    FILE *f = fopen("data_anggota.txt", "r");
  //membuka file dengan mode read-only untuk membaca isi file
    if (!f) {
        printf("Belum ada data anggota.\n");
       //menghentikan proses jika file gagal dibuka
        return;
    }
    printf("\n===== DAFTAR ANGGOTA =====\n");
//menampilkan menu daftar anggota
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%s\n", a.id, a.nama, a.alamat, a.no_telp) != EOF) {
//mengambil input yang telah diinput oleh user
        printf("%s - %s | %s | %s\n", a.id, a.nama, a.alamat, a.no_telp);
//menampilkan data anggota yang sudah diinput user
    }
    fclose(f);
}

