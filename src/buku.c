#include "perpustakaan.h"

void menuBuku() {
    int pilihan;
    do {  //untuk memulai loop yang pasti dijalankan minimal 1 kali.
        printf("\n=== MENU BUKU ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Lihat Daftar Buku\n");
        printf("3. Cari Buku\n");
        printf("4. Edit Buku\n");
        printf("5. Hapus Buku\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: lihatDaftarBuku(); break;
            case 3: cariBuku(); break;
            case 4: editBuku(); break;
            case 5: hapusBuku(); break;
            case 0: printf("Kembali ke menu utama...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void tambahBuku() { 
    Buku b;
    FILE *f = fopen("data_buku.txt", "a");
    if (!f) {
        printf("Gagal membuka file data_buku.txt\n");
        return;
    }
    printf("Masukkan ID Buku: "); scanf("%s", b.id);
    getchar();
    printf("Masukkan Judul Buku: "); fgets(b.judul, sizeof(b.judul), stdin);
    strtok(b.judul, "\n");
    printf("Masukkan Penulis: "); fgets(b.penulis, sizeof(b.penulis), stdin);
    strtok(b.penulis, "\n");
    printf("Masukkan Kategori (Fiksi/NonFiksi/Komik/Majalah/Referensi): "); scanf("%s", b.kategori);
    printf("Masukkan Tahun Terbit: "); scanf("%d", &b.tahun);
    printf("Masukkan Stok Buku: "); scanf("%d", &b.stok);
    b.dipinjam = 0;

    fprintf(f, "%s|%s|%s|%s|%d|%d|%d\n", b.id, b.judul, b.penulis, b.kategori, b.tahun, b.stok, b.dipinjam);
    fclose(f);
    printf("Buku berhasil ditambahkan!\n");
}

void lihatDaftarBuku() {
    Buku b;
    FILE *f = fopen("data_buku.txt", "r");
    if (!f) {
        printf("Belum ada data buku.\n");
        return;
    }

    // untuk print header tabel 
    printf("\n===== DAFTAR BUKU =====\n");
    printf("%-8s | %-25s | %-20s | %-10s | %-5s | %-5s | %-5s\n",
           "ID", "Judul", "Penulis", "Kategori", "Thn", "Stok", "Pinjam");
    printf("--------------------------------------------------------------------------\n");
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  b.id, b.judul, b.penulis, b.kategori, &b.tahun, &b.stok, &b.dipinjam) != EOF) {
        // Untuk menampilkan data
        printf("%-8s | %-25s | %-20s | %-10s | %-5d | %-5d | %-5d\n",
               b.id, b.judul, b.penulis, b.kategori, b.tahun, b.stok, b.dipinjam);
    }
    fclose(f);
}

void cariBuku() {
    char keyword[100];
    Buku b;
    FILE *f = fopen("data_buku.txt", "r");
    if (!f) {
        printf("File data_buku.txt tidak ditemukan.\n");
        return;
    }

    printf("Masukkan kata kunci (judul/penulis/kategori): ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    strtok(keyword, "\n");

    printf("\nHasil pencarian:\n");
    // Untuk membaca semua buku lalu mengecek kecocokan dengan keyword
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  b.id, b.judul, b.penulis, b.kategori, &b.tahun, &b.stok, &b.dipinjam) != EOF) {
        // Untuk mencocokkan judul, penulis, dan kategori buku
        if (strstr(b.judul, keyword) || strstr(b.penulis, keyword) || strstr(b.kategori, keyword)) {
            printf("%s - %s (%s) [%s]\n", b.id, b.judul, b.penulis, b.kategori);
        }
    }
    fclose(f);
}

void hapusBuku() {
    char idHapus[10];
    Buku daftar[100];
    int totalBuku = 0;

    FILE *f = fopen("data_buku.txt", "r");
    if (!f) { printf("Belum ada data buku.\n"); return; }

    // Baca semua buku ke memory
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  daftar[totalBuku].id,
                  daftar[totalBuku].judul,
                  daftar[totalBuku].penulis,
                  daftar[totalBuku].kategori,
                  &daftar[totalBuku].tahun,
                  &daftar[totalBuku].stok,
                  &daftar[totalBuku].dipinjam) != EOF) {
        totalBuku++;
    }
    fclose(f);

    printf("Masukkan ID Buku yang ingin dihapus: ");
    scanf("%s", idHapus);

    int found = 0;
    FILE *fw = fopen("data_buku.txt", "w");
    for (int i = 0; i < totalBuku; i++) {
        if (strcmp(daftar[i].id, idHapus) == 0) {
            found = 1; // skip buku ini (jadi terhapus)
            continue;
        }
        fprintf(fw, "%s|%s|%s|%s|%d|%d|%d\n",
                daftar[i].id, daftar[i].judul, daftar[i].penulis,
                daftar[i].kategori, daftar[i].tahun,
                daftar[i].stok, daftar[i].dipinjam);
    }
    fclose(fw);

    if (found) printf("Buku berhasil dihapus!\n");
    else printf("ID Buku tidak ditemukan.\n");
}

// Fungsi edit buku
void editBuku() {
    char idEdit[10];
    Buku daftar[100];
    int totalBuku = 0;

    FILE *f = fopen("data_buku.txt", "r");
    if (!f) { printf("Belum ada data buku.\n"); return; }

    // Baca semua buku ke memory
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  daftar[totalBuku].id,
                  daftar[totalBuku].judul,
                  daftar[totalBuku].penulis,
                  daftar[totalBuku].kategori,
                  &daftar[totalBuku].tahun,
                  &daftar[totalBuku].stok,
                  &daftar[totalBuku].dipinjam) != EOF) {
        totalBuku++;
    }
    fclose(f);

    printf("Masukkan ID Buku yang ingin diedit: ");
    scanf("%s", idEdit);

    int found = 0;
    for (int i = 0; i < totalBuku; i++) {
        if (strcmp(daftar[i].id, idEdit) == 0) {
            found = 1;
            getchar();
            printf("Judul baru (%s): ", daftar[i].judul);
            fgets(daftar[i].judul, sizeof(daftar[i].judul), stdin);
            strtok(daftar[i].judul, "\n");

            printf("Penulis baru (%s): ", daftar[i].penulis);
            fgets(daftar[i].penulis, sizeof(daftar[i].penulis), stdin);
            strtok(daftar[i].penulis, "\n");

            printf("Kategori baru (%s): ", daftar[i].kategori);
            scanf("%s", daftar[i].kategori);

            printf("Tahun baru (%d): ", daftar[i].tahun);
            scanf("%d", &daftar[i].tahun);

            printf("Stok baru (%d): ", daftar[i].stok);
            scanf("%d", &daftar[i].stok);

            break;
        }
    }

    if (!found) {
        printf("ID Buku tidak ditemukan.\n");
        return;
    }

    // Tulis ulang semua buku ke file
    FILE *fw = fopen("data_buku.txt", "w");
    for (int i = 0; i < totalBuku; i++) {
        fprintf(fw, "%s|%s|%s|%s|%d|%d|%d\n",
                daftar[i].id, daftar[i].judul, daftar[i].penulis,
                daftar[i].kategori, daftar[i].tahun,
                daftar[i].stok, daftar[i].dipinjam);
    }
    fclose(fw);

    printf("Data buku berhasil diupdate!\n");
}
