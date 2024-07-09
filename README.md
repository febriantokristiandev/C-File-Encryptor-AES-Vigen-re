# C-File-Encryptor-AES-Vigenère

## Deskripsi

**C-File-Encryptor-AES-Vigenère** adalah aplikasi command-line yang memungkinkan pengguna untuk mengenkripsi dan mendekripsi file menggunakan algoritma AES-256-CBC. Program ini juga mendukung perubahan ekstensi file untuk menandakan status enkripsi atau dekripsi. 

## Fitur

- Enkripsi dan dekripsi file menggunakan AES-256.
- Menghapus file input setelah enkripsi atau dekripsi selesai.
- Menyimpan dan mengembalikan ekstensi file asli setelah dekripsi.
- Menyediakan antarmuka pengguna berbasis teks sederhana.

## Instalasi

### Di Windows

1. **Install OpenSSL**:
   - Unduh installer dari situs web resmi [OpenSSL](https://slproweb.com/products/Win32OpenSSL.html).
   - Jalankan installer dan ikuti petunjuknya.
   - Tambahkan path ke OpenSSL bin folder (`C:\Program Files\OpenSSL-Win64\bin`) ke dalam variabel lingkungan `PATH`.

2. **Kompilasi Program**:
   - Buka Command Prompt atau terminal.
   - Arahkan ke direktori yang berisi kode sumber.
   - Gunakan perintah berikut untuk mengkompilasi program:
     ```sh
     gcc -o file_encryptor main.c -lssl -lcrypto
     ```

### Di Linux

1. **Install OpenSSL**:
   - Buka terminal.
   - Instal OpenSSL menggunakan manajer paket:
     ```sh
     sudo apt update
     sudo apt install libssl-dev
     ```

2. **Kompilasi Program**:
   - Arahkan ke direktori yang berisi kode sumber.
   - Gunakan perintah berikut untuk mengkompilasi program:
     ```sh
     gcc -o file_encryptor main.c -lssl -lcrypto
     ```

## Penggunaan

1. **Jalankan Program**:
   - Buka terminal atau Command Prompt.
   - Arahkan ke direktori project. 
     ```sh
     cd c-file-encryptor-aes-vigenere
     ./main.exe
     ```
   - Jalankan program dengan perintah berikut:
     ```sh
     ./main.exe
     ```

2. **Operasi**:
   - Pilih operasi yang diinginkan:
     - Masukkan `1` untuk enkripsi.
     - Masukkan `2` untuk dekripsi.
     - Masukkan `3` untuk keluar dari program.
   - Masukkan path file yang akan diproses. Program akan secara otomatis menambahkan ekstensi `.encrypted` untuk file terenkripsi dan mengembalikan ekstensi asli untuk file yang didekripsi.

## Contoh

1. **Enkripsi File**:
   - Masukkan `1` untuk enkripsi.
   - Masukkan path file yang akan dienkripsi, misalnya `document.txt`.
   - File hasil enkripsi akan disimpan sebagai `document.encrypted`.

2. **Dekripsi File**:
   - Masukkan `2` untuk dekripsi.
   - Masukkan path file yang akan didekripsi, misalnya `document.encrypted`.
   - File hasil dekripsi akan dikembalikan ke nama aslinya, yaitu `document.txt`.