#include "perpustakaan.h"


void menuPeminjaman() {
    int pilihan;
    do {
        printf("\n=== MENU PEMINJAMAN ===\n");
        printf("1. Pinjam Buku\n");
        printf("2. Kembalikan Buku\n");
        printf("3. Riwayat Peminjaman Anggota\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1: pinjamBuku(); break;
            case 2: kembalikanBuku(); break;
            case 3: riwayatPeminjamanAnggota(); break;
            case 0: printf("Kembali ke menu utama...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

// fungi untuk Untuk validasi ID Anggota
int cekIdAnggota(char *idAnggota) {
    Anggota a;
    FILE *f = fopen("data_anggota.txt", "r");
    if (!f) {
        return 0;               // kalo misalnya blm ada data anggota nya
    }

    int ditemukan = 0;
    // Baca anggota satu per satu, pakek 1 liner gitu
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%s\n", a.id, a.nama, a.alamat, a.no_telp) != EOF) {
        if (strcmp(a.id, idAnggota) == 0) {      //kalo sama, berarti id anggota sudah ada di file txtnya
            ditemukan = 1;
            break;
        }
    }
    fclose(f);
    return ditemukan;   // kedepannya nanti dipanggil pas sebut variabel "idanggpta"
}
//fungsi utama pertama untuk peminjaman  buku
void pinjamBuku() {
       char idBuku[10], idAnggota[10];
    Buku daftar[100];               // asumsi maksimal 100 buku
    int totalBuku = 0;

    // Input peminjaman
    printf("ID Anggota: "); scanf("%s", idAnggota);

    // biar kalo pinjam harus udah ada ID Anggota di file txtnya, kalo blm hrus daftar dlu
    if (!cekIdAnggota(idAnggota)) {
        printf("ID Anggota tidak ditemukan. Harap daftarkan anggota terlebih dahulu.\n");
        return;
    }


    // Baca data buku ke memory
    FILE *fb = fopen("data_buku.txt", "r");
    if (!fb) { printf("Belum ada data buku.\n"); return; }
    while (1) {                             //masukin data ke dtruct biar bsa dicek smua buku yg bsa dipinjam
        if (fscanf(fb, "%[^|]|", daftar[totalBuku].id) != 1) break;
        if (fscanf(fb, "%[^|]|", daftar[totalBuku].judul) != 1) break;
        if (fscanf(fb, "%[^|]|", daftar[totalBuku].penulis) != 1) break;
        if (fscanf(fb, "%[^|]|", daftar[totalBuku].kategori) != 1) break;
        if (fscanf(fb, "%d|",  &daftar[totalBuku].tahun) != 1) break;
        if (fscanf(fb, "%d|",  &daftar[totalBuku].stok) != 1) break;
        if (fscanf(fb, "%d\n", &daftar[totalBuku].dipinjam) != 1) break;

        totalBuku++;
    }

    fclose(fb);

    printf("ID Buku yang ingin dipinjam: ");
        scanf("%s", idBuku);

    // Cari buku
    int found = 0;
    for (int i = 0; i < totalBuku; i++) {
        if (strcmp(daftar[i].id, idBuku) == 0) {
            found = 1;
            if (daftar[i].dipinjam <= daftar[i].stok) {
                daftar[i].dipinjam++;           // update jumlah buku yang dipinjam, biar bisa dibandingkan nntik sama stok buku yang disediakan

                // Simpan perubahan ke file
                FILE *fw = fopen("data_buku.txt", "w");
                for (int j = 0; j < totalBuku; j++) {
                    fprintf(fw, "%s|%s|%s|%s|%d|%d|%d\n",       //pakek 1 liner biar efisien
                            daftar[j].id, daftar[j].judul, daftar[j].penulis,
                            daftar[j].kategori, daftar[j].tahun,
                            daftar[j].stok, daftar[j].dipinjam);
                }
                fclose(fw);

                // Catat peminjaman
                Peminjaman p;
                FILE *fp = fopen("data_peminjaman.txt", "a");
                printf("ID Peminjaman: "); scanf("%s", p.id_pinjam);
                strcpy(p.id_anggota, idAnggota);
                strcpy(p.id_buku, idBuku);
                printf("Tanggal Pinjam (dd/mm/yyyy): "); scanf("%s", p.tgl_pinjam);
                // Hitung tanggal kembali yang ada di variabel "durasiMaksimal", durasi maksimal nya default 7 hari..bsa diganti di utilitas.c
                // format input: dd/mm/yyyy
                int dd=0, mm=0, yy=0;
                if (sscanf(p.tgl_pinjam, "%d/%d/%d", &dd, &mm, &yy) == 3) {
                    if (yy < 100) yy += 2000;
                    struct tm tm_pinjam = {0};      //INI STRUCT BAWAAN DARI LIBRARY time.h, yang kita buat smua isinya jadi o,
                                                    //jdi dibawah kan tmmday, tmmon itu emang dari time.h sudah ada 
                    //
                    tm_pinjam.tm_mday = dd;
                    tm_pinjam.tm_mon = mm - 1;          // - 1 karena tm_mon di c itu mulainya dari 0, jadi kalau bulan november...kita buatnya = 10
                    tm_pinjam.tm_year = yy - 1900;       //karena c selalu mulai dari 1990, pengguna kan inputnya 2020, jadi perlu kita set jadi 0 dulu
                    tm_pinjam.tm_hour = 12;
                    time_t t = mktime(&tm_pinjam);      //mktime() itu adalah fungsi di time.c yang mengubah smuanya ke detik
                    if (t != (time_t)-1) {
                        // tambah "durasiMaksimal" hari
                        extern int durasiMaksimal;
                        t += (time_t)durasiMaksimal * 24 * 60 * 60;
                        struct tm *tm_kembali = localtime(&t);          //fungsi local time itu ngubah format tanggal contoh 
                                                                        //Misalnya t = 1731585500 detik diubah jdi 14 Nov 2024
                        if (tm_kembali) {
                            snprintf(p.tgl_kembali, sizeof(p.tgl_kembali), "%02d/%02d/%04d",        //print ke buffer array format dd/mm/yyyy
                                     tm_kembali->tm_mday, tm_kembali->tm_mon + 1, tm_kembali->tm_year + 1900);
                        } else {
                            strcpy(p.tgl_kembali, "-");
                        }
                    } else {
                        strcpy(p.tgl_kembali, "-"); 
                    }
                } else {
                    strcpy(p.tgl_kembali, "-");
                }
                p.denda = 0;
                p.status = 0;
                //masukin datanya ke txt
                fprintf(fp, "%s|%s|%s|%s|%s|%d|%d\n",       //one liner
                        p.id_pinjam, p.id_anggota, p.id_buku,
                        p.tgl_pinjam, p.tgl_kembali, p.denda, p.status);
                fclose(fp);

                printf("Peminjaman berhasil!\n");
            } else {
                printf("Maaf, stok buku ini sedang habis.\n");
            }
            break;
        }
    }

    if (!found) printf("ID buku tidak ditemukan.\n");
}


void riwayatPeminjamanAnggota() {
             printf("Fitur riwayat peminjaman belum siap ee\n");  
}
void kembalikanBuku() {
          printf("Fitur pengembalian buku belum tersedia.\n");
}