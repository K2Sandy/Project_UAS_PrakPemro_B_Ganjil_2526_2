#include "perpustakaan.h"
//ini untuk konfigurasi kategorinya
static const char *DAFTAR_KATEGORI[20] = {
    "01 - Fiksi Umum",
    "02 - Fiksi Anak & Remaja",
    "03 - Komik & Manga",
    "04 - Sains & Teknologi",
    "05 - Matematika & Statistik",
    "06 - Ekonomi & Bisnis",
    "07 - Hukum",
    "08 - Sosial & Politik",
    "09 - Sejarah & Budaya",
    "10 - Pendidikan",
    "11 - Biografi",
    "12 - Agama",
    "13 - Psikologi",
    "14 - Novel",
    "15 - Ensiklopedia",
    "16 - Kesehatan",
    "17 - Olahraga",
    "18 - Seni & Desain",
    "19 - Memasak",
    "20 - Majalah"
};
//  ini untuk buat id otomatis, supaya user tidak asal inoput
static void generateIdBuku(char *outId, int kodeKategori) {
    FILE *f = fopen("data_buku.txt", "r");
    int maxUrut = 0;

    if (f) {
        Buku b;
        while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                       b.id, b.judul, b.penulis, b.kategori,
                       &b.tahun, &b.stok, &b.dipinjam) != EOF) {
            int kk = (b.id[0] - '0') * 10 + (b.id[1] - '0');
            if (kk == kodeKategori) {
                int urut = atoi(b.id + 2);
                if (urut > maxUrut) maxUrut = urut;
            }
        }
        fclose(f);
    }

    int next = maxUrut + 1;
    sprintf(outId, "%02d%04d", kodeKategori, next);
}
void menuBuku() {
    int pilihan;
    do {  //untuk memulai loop yang pasti dijalankan minimal 1 kali.
        printf("\n================================\n");
        printf("             MENU BUKU            \n");
        printf("==================================\n");
        printf("1. Tambah Buku\n");
        printf("2. Lihat Daftar Buku\n");
        printf("3. Cari Buku\n");
        printf("4. Edit Buku\n");
        printf("5. Hapus Buku\n");
        printf("0. Kembali\n");
        printf("================================\n");

        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        // Untuk menjalankan fungsi sesuai pilihan  
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

    printf("\n=== TAMBAH BUKU ===\n");
    printf("Pilih Kategori (1-20):\n");
    for (int i = 0; i < 20; i++) printf("%s\n", DAFTAR_KATEGORI[i]);

    int pilih;
    printf("Masukkan nomor kategori: ");
    scanf("%d", &pilih);
    getchar();

    if (pilih < 1 || pilih > 20) {
        printf("Kategori tidak valid!\n");
        return;
    }

     strcpy(b.kategori, DAFTAR_KATEGORI[pilih - 1]);
    generateIdBuku(b.id, pilih);

    printf("Masukkan Judul Buku: ");
    fgets(b.judul, sizeof(b.judul), stdin);
    strtok(b.judul, "\n"); //hapus karakter '\n' dari hasil fgets

    printf("Masukkan Penulis: ");
    fgets(b.penulis, sizeof(b.penulis), stdin);
    strtok(b.penulis, "\n");
    printf("Masukkan Tahun Terbit: "); scanf("%d", &b.tahun);
    printf("Masukkan Stok Buku: "); scanf("%d", &b.stok);
    b.dipinjam = 0;

   FILE *f = fopen("data_buku.txt", "a");
    fprintf(f, "%s|%s|%s|%s|%d|%d|%d\n",
            b.id, b.judul, b.penulis, b.kategori,
            b.tahun, b.stok, b.dipinjam);
    fclose(f);

    printf("Buku berhasil ditambahkan. ID: %s\n", b.id);
}

void lihatDaftarBuku() {
    printf("\n=== LIHAT DAFTAR BUKU  ===\n");
    for (int i = 0; i < 20; i++) {
        printf("%2d. %s\n", i + 1, DAFTAR_KATEGORI[i]);
    }
     int pilih;
    printf("Pilih kategori (1-20): ");
    scanf("%d", &pilih);
    getchar();

    if (pilih < 1 || pilih > 20) {
        printf("Kategori tidak valid!\n");
        return;
    }
     const char *kategoriDipilih = DAFTAR_KATEGORI[pilih - 1];

    Buku b;
    int found = 0; 
    FILE *f = fopen("data_buku.txt", "r");
    if (!f) {
        printf("Belum ada data buku.\n");
        return;
    }
    

    // untuk print header tabel 
    printf("\n===== DAFTAR BUKU: %s =====\n", kategoriDipilih);
    
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  b.id, b.judul, b.penulis, b.kategori, &b.tahun, &b.stok, &b.dipinjam) != EOF) {
        // Untuk menampilkan data
        if (strcmp(b.kategori, kategoriDipilih) == 0) {
            found = 1;
            printf("%-7s | %-25s | %-20s | %-10s | %-5d | %-5d | %-5d\n",
               b.id, b.judul, b.penulis, b.kategori, b.tahun, b.stok, b.dipinjam);
        }
    }
    fclose(f);

    if (!found){
        printf("Tidak ada buku dalam kategori ini.\n");
    }
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
    if (!f) { printf("Belum ada data buku.\n"); return; }// pastikan file dibuka

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
    // Untuk menulis ulang file tanpa data yang dihapus
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

    // Untuk membaca seluruh data buku
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
            fgets(daftar[i].judul, sizeof(daftar[i].judul), stdin); //sizeof mengukur ukuran array 'judul' dalam struktur 'Buku'
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

    // Untuk menulis ulang semua buku ke file
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
