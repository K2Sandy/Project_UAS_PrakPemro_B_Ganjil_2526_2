# Project_UAS_PrakPemro_B_Ganjil_2526_2
# 📚 Sistem Peminjaman Buku – Perpustakaan Mini

Repository ini berisi **Project Ujian Akhir Semester (UAS)** untuk mata kuliah **Praktikum Pemrograman B 2025/2026**, dikerjakan oleh **Kelompok 2**.
Project ini mengimplementasikan **Sistem Peminjaman Buku Perpustakaan Mini** menggunakan bahasa **C**, yang berfungsi untuk mengelola data buku, anggota, peminjaman, pengembalian, serta perhitungan denda keterlambatan secara otomatis.

Seluruh data pada sistem disimpan ke file eksternal berformat **.txt** secara modular.

---

# 🚀 Fitur Utama

## 👩‍💼 Admin / Pustakawan

* Login pustakawan.

---

## 📘 Manajemen Buku

* Menambahkan buku baru.
* Menghapus buku.
* Mengedit informasi buku.
* Melihat daftar buku.
* Kategori buku: Fiksi, Non-Fiksi, Komik, Majalah, Referensi.
* Mengubah status buku (Tersedia / Dipinjam).
* Menampilkan ranking buku paling sering dipinjam.

---

## 👥 Manajemen Anggota

* Mendaftarkan anggota baru.
* Melihat riwayat peminjaman anggota.

---

## 🔄 Peminjaman & Pengembalian

* Melakukan peminjaman dan pengembalian buku.
* Menghitung denda keterlambatan otomatis.
* Mengelola batas maksimal durasi peminjaman.

---

## 📂 Penyimpanan Data

* Seluruh data (buku, anggota, peminjaman, pengembalian, statistik) disimpan dalam file **.txt**.

---

# ▶️ Cara Menjalankan Program

1. Pastikan Anda memiliki compiler C seperti **GCC** atau menggunakan IDE (VS Code, CodeBlocks, dll).

2. Compile program dengan perintah:

   ```bash
   gcc main.c -o perpustakaan
   ```

   *(Sesuaikan jika ada file tambahan seperti `.c` lain.)*

3. Jalankan program:

   ```bash
   ./perpustakaan
   ```

4. Pastikan file-data `.txt` berada dalam satu folder dengan executable agar sistem dapat membaca dan memperbarui data.

---

# 👥 Kelompok 2

* **Ibnul Jawzy**                       NPM: 250810701100021
* **Muhammad Albharaka Putrosandy**     NPM: 250810701100022
* **Muhammad Irfan**                    NPM: 250810701100023
* **Putri Rahmatul Ulya**               NPM: 250810701100030
* **Fitri Br Manik**                    NPM: 250810701100032

---

# 📄 Lisensi

Project ini menggunakan **MIT License**, yaitu lisensi open-source yang mengizinkan siapa pun untuk menggunakan, memodifikasi, dan mendistribusikan kode dengan mencantumkan atribusi, tanpa jaminan apa pun.
