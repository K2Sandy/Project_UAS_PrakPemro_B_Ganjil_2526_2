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

        switch (Pilihan) {     //susun ulang fungsi sesuai menu
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

//ini fungsi untuk tambah akun baru
void tambahAkun(){
    login log;
    FILE *f; 
    f = fopen("data_login.txt", "a"); 
    if (!f){
        printf("File tidak ditemukan!\n");
        return;
    }

    printf("Masukkan username baru: "); scanf("%s", log.username);
    printf("Masukkan password baru: "); scanf("%s", log.password);

    fprintf(f, "%s|%s\n", log.username, log.password);
    fclose(f);
    printf("Akun baru berhasil ditambahkan!\n");
}

//ini fungsi untuk unah password akun yang udah terdaftar
void ubahPassword(){
    char username_dicari[50], passwordBaru[50];
    int ditemukan = 0;

    FILE *f;
    f = fopen("data_login.txt", "r");
    if (!f){
        printf("File tidak ditemukan!\n");
        return;
    }

    //sebelum ubah passwordnya, kita baca dulu semua akun yang ada
    login daftar[100]; // kita asumsikan ada 100 akun
    int i = 0
    while(fscanf(f, "%[^|] %s\n", daftar[i].username, daftar[i].password) != EOF){
        i++;
    }
    int totalAkun = i;
    fclose(f);

    //nah sekarang pilih akkun yang mmau diubah
    printf("Masukkan username: "); scanf("%s", username_dicari);
    printf("Masukkan password baru: "); scanf("%s", passwordBaru);

    for (i = 0; i < totalAkun; i++){
        if (strcmp(daftar[i].username, username_dicari) == 0){
            strcpy(daftar[i].password, passwordBaru);
            ditemukan = 1;
            break;
        }
    }

    if(!ditemukan){ //ini artinya kalau ketemu berarti !1 kalo ga ketemu !0
        printf("Username tidak ditemukan!\n");
        return;
    }

    //nah sekarang kita tulis ulang semua akunnya
    FILE *fw;
    f w= fopen("data_login.txt", "w");
    for (i = 0; i < totalAkun; i++){
        fprintf(fw, "%s|%s\n", daftar[i].username, daftar[i].password);
    } 
    fclose(fw);
    printf("password berhasil diubah!\n");
}

void rankingBuku(){
    Buku daftar[100];
    int totalBuku = 0;

    FILE *f;
    f = fopen("data_buku.txt", "r");
    if (!f) {
        printf("beelum ada data buku.\n"); 
        return;
    }

    while (fscanf(f, "%[^|] %[^|] %[^|] %[^|] %d %d %d\n",
                    daftar[totalBuku].id,
                    daftar[totalBuku].judul,
                    daftar[totalBuku].penulis,
                    daftar[totalBuku].kategori,
                    &daftar[totalBuku].tahun,
                    &daftar[totalBuku].stok
                    &daftar[totalBuku].dipinjam) != EOF) {
            totalBuku++;
    }
    fclose(f);

    // nah sekarang kita sorting descending berdasarkan jumlah dipinjam
    buku temp;
    int i, j;
    
    for (i = 0; i < totalBuku - 1; i++){
        for (j = i; j < totalBuku; j++){
            if (daftar[i].dipinjam < daftar[j].dipinjam) {
                temp = daftar[i];
                daftar[i] = daftar[j];
                daftar[j] = temp
            }
        }
    }

    printf("\n================================================\n");
    printf("\n    RANKING BUKU YANG PALING SERING DIPINJAM    \n");
    printf("\n================================================\n");
    printf("Rank | ID Buku | Judul | Penulis | Jumlah Dipinjam\n");
    printf("--------------------------------------------------\n");
    for  (int i = 0; i < totalBuku; i++){
        printf("%d | %s | %s | %s | %d\n", i + 1
                daftar[i].id,
                daftar[i].judul,
                daftar[i].penulis,
                daftar[i].dipinjam);
    }
}