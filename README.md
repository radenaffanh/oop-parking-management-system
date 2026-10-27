# Advanced Parking Management System

**Mata Kuliah:** SIR203 – Pemrograman Berorientasi Objek (Praktikum)  
**Bahasa Pemrograman:** C++  

---

## 1. Deskripsi Program

Program **Advanced Parking Management System** merupakan aplikasi berbasis **C++** yang mensimulasikan sistem manajemen parkir pada **gedung bertingkat** dengan beberapa **zona parkir**, yaitu **Regular**, **EV (Electric Vehicle)**, dan **VIP**. Sistem ini mendukung proses parkir dan keluar kendaraan, reservasi slot VIP, perhitungan biaya parkir otomatis, serta penanganan error menggunakan mekanisme **exception handling**.

Program ini dikembangkan dengan pendekatan **Object-Oriented Programming (OOP)** secara menyeluruh sesuai dengan ketentuan **Ujian Akhir Praktikum (UAP)**.

---

## 2. Fitur Utama

Fitur yang tersedia dalam program ini antara lain:

- Registrasi dan parkir kendaraan (Motor, Mobil, dan EV)
- Alokasi slot parkir otomatis sesuai tipe kendaraan
- Perhitungan biaya parkir berdasarkan durasi (jam)
- Penambahan charging fee untuk kendaraan EV
- Diskon 10% untuk durasi parkir lebih dari 24 jam
- Slot VIP dengan mekanisme reservasi
- Sistem tiket parkir
- Penanganan error menggunakan custom exception
- Simulasi proses park dan unpark kendaraan

---

## 3. Konsep OOP yang Diterapkan

### a. Class dan Object
- `Vehicle`, `Motorcycle`, `Car`, `EV`
- `ParkingSlot`, `RegularSlot`, `EVSlot`, `VIPSlot`
- `ParkingFloor`
- `ParkingGarage`

### b. Abstraction
- `Vehicle` dan `ParkingSlot` merupakan **class abstrak** dengan method virtual murni.

### c. Inheritance
- `Motorcycle`, `Car`, dan `EV` mewarisi class `Vehicle`.
- `RegularSlot`, `EVSlot`, dan `VIPSlot` mewarisi class `ParkingSlot`.

### d. Polymorphism
- Penggunaan pointer/reference bertipe `Vehicle` untuk mereferensikan objek class turunan.
- Pemanggilan method `calculateRate()` dilakukan secara runtime polymorphism.

### e. Function Overloading
- Method `calculateRate()` memiliki dua versi:
  - Berdasarkan durasi jam
  - Berdasarkan waktu masuk dan keluar parkir

### f. Overriding
- Setiap class turunan kendaraan meng-override method `calculateRate()` sesuai aturan tarif.

### g. Encapsulation
- Atribut class dibuat `protected` atau `private` dan diakses melalui method publik.

### h. Exception Handling
- Custom exception yang digunakan:
  - `ParkingException`
  - `NoAvailableSlotException`
  - `InvalidTicketException`
  - `ReservationException`
  - `PaymentException`
- Menggunakan mekanisme `throw`, `try-catch`, dan `rethrow`.

---

## 4. Aturan Tarif Parkir

| Jenis Kendaraan | Tarif Dasar |
|-----------------|-------------|
| Motorcycle | Rp 2.000 / jam |
| Car | Rp 5.000 / jam |
| EV | Rp 4.000 / jam |

**Aturan tambahan:**
- EV dengan `chargingRequired = true` dikenakan **charging fee Rp 3.000**
- Parkir lebih dari 24 jam mendapatkan **diskon 10%**
- Slot VIP mendukung reservasi (surcharge dapat dikembangkan)

---

## 5. Struktur Program

Program disusun dalam **satu file `main.cpp`** yang berisi:
- Definisi class
- Implementasi method
- Custom exception
- Fungsi `main()` sebagai entry point program

Meskipun berada dalam satu file, struktur program tetap mengikuti prinsip modularitas OOP.

---

## 6. Cara Compile dan Menjalankan Program

### Compile
```bash
g++ main.cpp -o parking
