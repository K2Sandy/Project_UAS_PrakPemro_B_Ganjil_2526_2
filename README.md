# 📚 Sistem Perpustakaan Mini

Repository ini berisi **Proyek Ujian Akhir Semester (UAS)** untuk mata kuliah **Praktikum Pemrograman B 2025/2026**, dikerjakan oleh **Kelompok 2**.
Project ini mengimplementasikan **Sistem Peminjaman Buku Perpustakaan Mini** menggunakan bahasa **C**, yang berfungsi untuk mengelola data buku, anggota, peminjaman, pengembalian, login admin serta perhitungan denda keterlambatan secara otomatis.

Seluruh data pada sistem disimpan ke file eksternal berformat **.txt** secara modular.

---

# 🚀 Fitur Utama

## 👩‍💼 Admin / Pustakawan

* Login pustakawan.
* **Username default: `admin`**
* **Password default: `1234`**
* Kalo ga ada akun login, pasti akan otomatis kebuat kok.
* Kalo mau buat akun baru dengan username dan pw sendiri silahkan kakk, udah ada fiturnya kok

## 🔄 Utilitas Admin
* Menambahkan Akun Admin
* Mengubah Password Akun Admin
* Menampilkan ranking buku paling sering dipinjam.
* Mengelola batas maksimal durasi peminjaman.
* Mengatur berapa denda kalo telat per hari

## 📘 Manajemen Buku

* Menambahkan buku baru.
* Menghapus buku.
* Mengedit informasi buku.
* Melihat daftar buku.
* Mencari buku berdasarkan Keyword

## 👥 Manajemen Anggota

* Mendaftarkan anggota baru.
* Melihat daftar anggota.
* Kami sudah menyiapkan akun anggota untuk abang dan kakak-kakak aslab:
  * **Bang Hanif — 20250006**
  * **Kak Niswa — 20250007**
  * **Bang Faris — 20250008**
  * **Bang Irfan — 20250009**
* Kalo mau buat akun anggota baru juga bisa banget kok!

## 🔄 Peminjaman & Pengembalian

* Melakukan peminjaman dan pengembalian buku.
* Menghitung denda keterlambatan otomatis dengan waktu real-time.
* Melihat Riwayat Peminjaman Anggota
* Kemarin abang dan kakak-kakak juga sempat pinjam buku di PerpusMini kami ya? Jangan lupa dikembalikan bang/kak… nanti kena denda 😄



## 📂 Penyimpanan Data

* Seluruh data (buku, anggota, peminjaman, pengembalian, statistik) disimpan dalam file **.txt**.

---

# ▶️ Cara Menjalankan Program

1. **Masuk ke folder proyek**
   Pastikan sudah berada di direktori yang berisi semua file `.c` dan `perpustakaan.h`.

   ```bash
   cd nama-Project_UAS_PrakPemro_B_Ganjil_2526_2-src
   ```

2. **Compile program**
   Program terdiri dari beberapa file, maka compile dengan:

   ```bash
   gcc main.c anggota.c buku.c peminjaman.c login.c Menu_Utilitas.c -o PerpusMini.exe
   ```

3. **Jalankan program**

   ```bash
   ./PerpusMini.exe
   ```

---

# 👥 Kelompok 2

| Nama                          | NPM             |
| ----------------------------- | --------------- |
| Ibnul Jawzy                   | 250810701100021 |
| Muhammad Albharaka Putrosandy | 250810701100022 |
| Muhammad Irfan                | 250810701100023 |
| Putri Rahmatul Ulya           | 250810701100030 |
| Fitri Br Manik                | 250810701100032 |

---

# 📄 Lisensi

Project ini menggunakan **MIT License**, yaitu lisensi open-source yang mengizinkan siapa pun untuk menggunakan, memodifikasi, dan mendistribusikan kode dengan mencantumkan atribusi, tanpa jaminan apa pun.
