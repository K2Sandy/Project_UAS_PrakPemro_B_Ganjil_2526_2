#include "perpustakaan.h"

void menuAnggota() {
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
            case 1: daftarAnggota(); break;
            case 2: lihatAnggota(); break;
            case 0: printf("Kembali ke menu utama...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void daftarAnggota() {
    Anggota a;
    FILE *f = fopen("data_anggota.txt", "a");
    if (!f) {
        printf("Gagal membuka file data_anggota.txt\n");
        return;
    }
    printf("Masukkan ID Anggota: "); scanf("%s", a.id);
    getchar();
    printf("Nama: "); fgets(a.nama, sizeof(a.nama), stdin); strtok(a.nama, "\n");
    printf("Alamat: "); fgets(a.alamat, sizeof(a.alamat), stdin); strtok(a.alamat, "\n");
    printf("No Telepon: "); scanf("%s", a.no_telp);
    fprintf(f, "%s|%s|%s|%s\n", a.id, a.nama, a.alamat, a.no_telp);
    fclose(f);
    printf("Anggota berhasil didaftarkan!\n");
}

void lihatAnggota() {
    Anggota a;
    FILE *f = fopen("data_anggota.txt", "r");
    if (!f) {
        printf("Belum ada data anggota.\n");
        return;
    }
    printf("\n===== DAFTAR ANGGOTA =====\n");
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%s\n", a.id, a.nama, a.alamat, a.no_telp) != EOF) {
        printf("%s - %s | %s | %s\n", a.id, a.nama, a.alamat, a.no_telp);
    }
    fclose(f);
}

