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
    char idAnggota[20];
    printf("Masukkan ID Anggota: ");
    scanf("%s", idAnggota);

    Peminjaman daftar[100]; // asumsi maksimal 100 peminjaman
    int total = 0;

    FILE *f = fopen("data_peminjaman.txt", "r");
    if (!f) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

    /* bisa one liner gini tapi kurang aman dan sangat ribet
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n",            %[^|], %[ untuk scan, ^ = kecuali,
                                                                         jadi %[^|] untuk scanf semua kecuali |
                  daftar[total].id_pinjam,
                  daftar[total].id_anggota,
                  daftar[total].id_buku,
                  daftar[total].tgl_pinjam,
                  daftar[total].tgl_kembali,
                  &daftar[total].denda,
                  &daftar[total].status) != EOF) {
    */
    while (1) {
            if (fscanf(f, "%[^|]|", daftar[total].id_pinjam) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].id_anggota) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].id_buku) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].tgl_pinjam) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].tgl_kembali) != 1) break;
            if (fscanf(f, "%d|",   &daftar[total].denda) != 1) break;
            if (fscanf(f, "%d\n",  &daftar[total].status) != 1) break;

        if (strcmp(daftar[total].id_anggota, idAnggota) == 0) {
            total++;
        }
    }
    fclose(f);

    if (total == 0) {
        printf("Tidak ada riwayat peminjaman untuk anggota ini.\n");
        return;
    }

    printf("\n=== RIWAYAT PEMINJAMAN ANGGOTA %s ===\n", idAnggota);
    printf("ID Peminjaman | ID Buku | Tgl Pinjam | Tgl Kembali | Denda | Status\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%s | %s | %s | %s | %d | %s\n",
               daftar[i].id_pinjam,
               daftar[i].id_buku,
               daftar[i].tgl_pinjam,
               daftar[i].tgl_kembali,
               daftar[i].denda,
               daftar[i].status == 0 ? "Dipinjam" : "Kembali");
    }
}
void kembalikanBuku() {
    //minta id peminjaman yang ada agar bisa dicek ada ga di file txtnya
    char idPinjam[10];
    printf("Masukkan ID Peminjaman: ");
    scanf("%9s", idPinjam);

    // Baca semua peminjaman
    Peminjaman daftar[200];
    int total = 0;
    FILE *f = fopen("data_peminjaman.txt", "r");
    if (!f) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

        //versi one liner lebih simpel tapi ribet
        /*while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n",     
                    daftar[total].id_pinjam,
                    daftar[total].id_anggota,
                    daftar[total].id_buku,
                    daftar[total].tgl_pinjam,
                    daftar[total].tgl_kembali,
                    &daftar[total].denda,
                    &daftar[total].status) != EOF) {
            total++;
            if (total >= 200) break; // safety } 
        */

    //lebih bagus readibilitynya
        while (1) {
            if (fscanf(f, "%[^|]|", daftar[total].id_pinjam) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].id_anggota) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].id_buku) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].tgl_pinjam) != 1) break;
            if (fscanf(f, "%[^|]|", daftar[total].tgl_kembali) != 1) break;
            if (fscanf(f, "%d|", &daftar[total].denda) != 1) break;
            if (fscanf(f, "%d\n", &daftar[total].status) != 1) break;

            total++;
            if (total >= 200) break; // batas maksimal jaga2
    }
    fclose(f);

    //cek apakah id yang diinputkan ada atau nggak di file txtnya
    int idx = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(daftar[i].id_pinjam, idPinjam) == 0) {
            idx = i;
            break;
        }
    }
    //kalo ga ada
    if (idx == -1) {
        printf("ID peminjaman tidak ditemukan.\n");
        return;
    }
    
    //kalo udah dikembalikan
    if (daftar[idx].status == 1) {
        printf("Peminjaman ini sudah dikembalikan sebelumnya.\n");
        return;
    }


    //Bagian paling ribet------HITUNG DENDA
    // parse tgl_pinjam format: dd/mm/yyyy
    int d=0, m=0, y=0;
    time_t now = time(NULL);   //ini biar variabel "now" itu isinya waktu realtime pas user pakek sistem ini
    struct tm tm_pinjam = {0};
    int parsed = 0;

    //baca disini
    if (sscanf(daftar[idx].tgl_pinjam, "%d/%d/%d", &d, &m, &y) == 3) {
        if (y < 100) y += 2000; // jaga2 kalo pengguna masukin 2 angka untuk tahun, misal 24 atau 25

        //  bulan 0-11, tahun - 1900,  udah dijelaskan di atas
        tm_pinjam.tm_mday = d;
        tm_pinjam.tm_mon = m - 1;
        tm_pinjam.tm_year = y - 1900;
        tm_pinjam.tm_hour = 12; 
        parsed = 1;
    }

    int days_elapsed = 0;
    if (parsed) {
        time_t t_pinjam = mktime(&tm_pinjam); // fungsi mktime() untuk ubah ke detik
        if (t_pinjam != (time_t)-1) {           //cek berhasil ga ubah ke detik, kalo gagal kan dia jadi -1
            double diff = difftime(now, t_pinjam);      //hitung selisih waktu sekarang ma pas pinjam...now itu waktu realtime pengguna sekarang
            days_elapsed = (int)(diff / (60 * 60 * 24));  //ini untuk konversi detik ke hari hbistu dibagi biar tau total harinya
            if (days_elapsed < 0) days_elapsed = 0;         // kalo misalnya negatif, diset aja jadi 0
        } else {
            parsed = 0;
        }
    }

    // hitung pengembaliannya dah lewat berapa hari dari jadwal yg dibolehkan
    int overdue = 0;
    extern int durasiMaksimal; // ini dari file utilitas.c, bisa diubah disitu
    if (parsed) {
        if (days_elapsed > durasiMaksimal) overdue = days_elapsed - durasiMaksimal;
    } else {
        // If date cannot be parsed, we won't compute overdue; just set returned date
        overdue = 0;
    }

    const int denda_per_hari = 1000; // sehari kita set denda 1000 rupiah
    daftar[idx].denda = overdue * denda_per_hari;       //simpan hasil denda
    daftar[idx].status = 1;                     //kalo udah dikembalikan jadi 1

    // set tgl_kembali ke tanggal hari ini
    struct tm *tm_now = localtime(&now);
    if (tm_now) {
        int hari  = tm_now->tm_mday;
        int bulan = tm_now->tm_mon + 1;
        int tahun = tm_now->tm_year + 1900;

        snprintf(daftar[idx].tgl_kembali, sizeof(daftar[idx].tgl_kembali),
                "%02d/%02d/%04d", hari, bulan, tahun);
    } else {
        strcpy(daftar[idx].tgl_kembali, "-");
    }

    // Tulis ulang file data_peminjaman.txt
    FILE *fw = fopen("data_peminjaman.txt", "w");
    if (!fw) {
        printf("Gagal membuka file data_peminjaman.txt untuk menulis.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        fprintf(fw, "%s|%s|%s|%s|%s|%d|%d\n",
                daftar[i].id_pinjam,
                daftar[i].id_anggota,
                daftar[i].id_buku,
                daftar[i].tgl_pinjam,
                daftar[i].tgl_kembali,
                daftar[i].denda,
                daftar[i].status);
    }
    fclose(fw);

    // Update data_buku.txt karena bagian dipinjamnya kan kurang 1 jadinya karena udah dibalikin
    Buku bukuList[200];
    int totalBuku = 0;
    FILE *fb = fopen("data_buku.txt", "r");
    if (fb) {

        /* while (fscanf(fb, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",         //masi perlu perbaikan
                      bukuList[totalBuku].id,
                      bukuList[totalBuku].judul,
                      bukuList[totalBuku].penulis,
                      bukuList[totalBuku].kategori,
                      &bukuList[totalBuku].tahun,
                      &bukuList[totalBuku].stok,
                      &bukuList[totalBuku].dipinjam) != EOF) {
            totalBuku++;
            if (totalBuku >= 200) break; 
        } */
        while (1) {
            if (fscanf(fb, "%[^|]|", bukuList[totalBuku].id) != 1) break;
            if (fscanf(fb, "%[^|]|", bukuList[totalBuku].judul) != 1) break;
            if (fscanf(fb, "%[^|]|", bukuList[totalBuku].penulis) != 1) break;
            if (fscanf(fb, "%[^|]|", bukuList[totalBuku].kategori) != 1) break;
            if (fscanf(fb, "%d|", &bukuList[totalBuku].tahun) != 1) break;
            if (fscanf(fb, "%d|", &bukuList[totalBuku].stok) != 1) break;
            if (fscanf(fb, "%d\n", &bukuList[totalBuku].dipinjam) != 1) break;

            totalBuku++;
            if (totalBuku >= 200) break; // jaga2
        }
        fclose(fb);

        //disini "dipinjam" nya dikurangin
        for (int i = 0; i < totalBuku; i++) {
            if (strcmp(bukuList[i].id, daftar[idx].id_buku) == 0) {
                if (bukuList[i].dipinjam > 0) bukuList[i].dipinjam--;
                break;
            }
        }

        // tulis ulang file buku
        FILE *fbw = fopen("data_buku.txt", "w");
        if (fbw) {
            for (int i = 0; i < totalBuku; i++) {
                fprintf(fbw, "%s|%s|%s|%s|%d|%d|%d\n",
                        bukuList[i].id,
                        bukuList[i].judul,
                        bukuList[i].penulis,
                        bukuList[i].kategori,
                        bukuList[i].tahun,
                        bukuList[i].stok,
                        bukuList[i].dipinjam);
            }
            fclose(fbw);
        } else {
            printf("Gagal menulis file data_buku.txt setelah pengembalian.\n");
        }
    } else {
        // file buku tidak ditemukan, hanya informasikan pengembalian
        printf("File data_buku.txt tidak ditemukan saat memperbarui stok buku.\n");
    }

    printf("Buku berhasil dikembalikan. Denda: %d\n", daftar[idx].denda);
}