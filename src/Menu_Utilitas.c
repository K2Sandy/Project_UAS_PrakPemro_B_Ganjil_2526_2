#include "perpustakaan.h"

int durasiMaksimal = 7; // ini defaultnya tujuh hari
int dendaPerhari = 1000; // default juga 1000
0
void menuUtilitas(){
    int pilihan;
    do {
        printf("\n ===- MENU UTILITAS -===\n");
        printf("1.Tambah Akun Admin\n");
        printf("2. Ubah Password\n");
        printf("3. Lihat Ranking Buku\n");
        printf("4. Atur Durasi Peminjaman Maksimal\n");
        printf("5. Atur Denda Per Hari Keterlambatan\n");
        printf("0. kembali Ke Menu Utama\n");
        printf("Pilihan: "); scanf("%d", &pilihan);

        switch (Pilihan) {
            case 1: tambahAkun(); break;
            case 2: ubahPassword(); break;
            case 3: rankingBuku(); break;
            case 4: setDurasiMaksimal(); break;
            case 5: setDendaPerhari(); break;
            case 0: printf("Kembali ke menu utama...\n"); break;
            default: printf("Pilihan tidak valid! \n");
        }
    } while (pilihan != 0)
}