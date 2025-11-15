#include "perpustakaan.h"

int main() {
    int pilihan;
    do {
        printf("\n================================\n");
        printf("    SISTEM PERPUSTAKAAN MINI    \n");
        printf("================================\n");
        printf("1. Menu Buku\n");
        printf("2. Menu Anggota\n");
        printf("3. Menu Peminjaman\n");
        printf("4. Login Sebagai Admin\n");
        printf("0. Keluar\n");
        printf("================================\n");

        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: menuBuku(); break;
            case 2: menuAnggota(); break;
            case 3: menuPeminjaman(); break;
            case 4: {
                    if (loginAdmin()) {   // login dulu
                        menuUtilitas();   // baru masuk menu utilitas
                    } else {
                        printf("Login gagal. Kembali ke menu utama.\n");
                    }
                    break;
            }
            case 0: printf("Terima kasih! Program selesai.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}

