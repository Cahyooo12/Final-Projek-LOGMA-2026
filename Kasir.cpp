#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include <windows.h> // PENTING: Library untuk mengatur mode Windows

using namespace std;

// Struktur data untuk menu
struct MenuItem {
    string nama;
    double harga;
    int stok;
};

// Struktur data untuk menampung pesanan di keranjang
struct Pesanan {
    string namaMenu;
    int jumlah;
    double hargaSatuan;
    double subtotal;
};

// Data Global Menu
vector<MenuItem> daftarMenu = {
    {"Nasi Goreng Spesial", 25000, 10},
    {"Ayam Bakar Madu    ", 22000, 8},
    {"Es Teh Manis       ", 5000, 50},
    {"Kopi Hitam         ", 8000, 20}
};

void garis() {
    cout << "========================================" << endl;
}

// --- FUNGSI CETAK QRIS (TAMPILAN KEREN) ---
void cetakQRIS() {
    cout << endl;
    cout << "      SILAKAN SCAN QRIS DI BAWAH      " << endl;
    cout << " ____________________________________ " << endl;
    cout << "|                                   |" << endl;
    cout << "|          AMIKOM SEJAHTERA         |" << endl;
    cout << "|                                   |" << endl;
    cout << "|      ███████████████████████      |" << endl;
    cout << "|      ██ ▄▄▄▄▄ █ ▄ █ ▄▄▄▄▄ ██      |" << endl;
    cout << "|      ██ █   █ █  ▀█ █   █ ██      |" << endl;
    cout << "|      ██ █▄▄▄█ █ ▀ █ █▄▄▄█ ██      |" << endl;
    cout << "|      ██▄▄▄▄▄▄▄█▄█▄█▄▄▄▄▄▄▄██      |" << endl;
    cout << "|      ██ ▀ ▄ ▀▄▄▀ ▄▀ ▄ ▀ ▄ ██      |" << endl;
    cout << "|      ██ █ █▀ ▀▀▀▀ ▀▀▀ █ █ ██      |" << endl;
    cout << "|      ██ ▄▄▄▄▄ █ ▄ █ ▀ ▀ █ ██      |" << endl;
    cout << "|      ██ █   █ █ ▄▄▀ ▄ ▀ █ ██      |" << endl;
    cout << "|      ██▄▄▄▄▄▄▄█▄▄▄█▄▄▄▄▄▄▄██      |" << endl;
    cout << "|                                   |" << endl;
    cout << "|___________________________________|" << endl;
    cout << "       NMID: ID1234567890123          " << endl;
    cout << endl;
}

int main() {
    // --- PENTING: MENGATUR TERMINAL AGAR BISA BACA KOTAK (UTF-8) ---
    system("chcp 65001 > nul");

    vector<Pesanan> keranjang;
    int pilihanMenu, jumlahPesanan;
    char tipeLayanan, metodeBayarChar, tambahLagi;
    string namaLayanan, namaMetodeBayar;
    double totalBelanja = 0, pajak = 0, totalBayar = 0, uangBayar = 0, kembalian = 0;
    
    // --- PROSES PEMESANAN ---
    do {
        system("cls"); 
        garis();
        cout << "      RESTO AMIKOM SEJAHTERA      " << endl;
        garis();
        
        cout << "No | Nama Menu           | Harga    | Stok" << endl;
        garis();
        for (int i = 0; i < daftarMenu.size(); ++i) {
            cout << left << setw(3) << i + 1 
                 << "| " << setw(20) << daftarMenu[i].nama 
                 << "| Rp" << setw(6) << (size_t)daftarMenu[i].harga 
                 << "| " << daftarMenu[i].stok << endl;
        }
        garis();

        if (!keranjang.empty()) {
            cout << "[ Isi Keranjang Saat Ini: " << keranjang.size() << " item ]" << endl;
        }

        cout << "Pilih nomor menu (1-" << daftarMenu.size() << "): ";
        cin >> pilihanMenu;

        if (pilihanMenu < 1 || pilihanMenu > daftarMenu.size()) {
            cout << "Menu tidak tersedia! Tekan enter..." << endl;
            cin.ignore(); cin.get();
            continue;
        }

        int idx = pilihanMenu - 1;

        if (daftarMenu[idx].stok <= 0) {
            cout << "Stok habis! Silakan pilih menu lain." << endl;
            cin.ignore(); cin.get();
            continue;
        }

        cout << "Menu: " << daftarMenu[idx].nama << endl;
        cout << "Harga: Rp " << (size_t)daftarMenu[idx].harga << endl;
        cout << "Masukkan jumlah pesanan: ";
        cin >> jumlahPesanan;

        if (jumlahPesanan > daftarMenu[idx].stok) {
            cout << "Stok tidak cukup! Sisa stok: " << daftarMenu[idx].stok << endl;
            cin.ignore(); cin.get();
            continue;
        } else if (jumlahPesanan <= 0) {
            cout << "Jumlah pesanan tidak valid!" << endl;
            cin.ignore(); cin.get();
            continue;
        }

        daftarMenu[idx].stok -= jumlahPesanan;
        
        Pesanan orderBaru;
        orderBaru.namaMenu = daftarMenu[idx].nama;
        orderBaru.jumlah = jumlahPesanan;
        orderBaru.hargaSatuan = daftarMenu[idx].harga;
        orderBaru.subtotal = daftarMenu[idx].harga * jumlahPesanan;
        
        keranjang.push_back(orderBaru);
        
        totalBelanja += orderBaru.subtotal;

        cout << ">> Berhasil menambahkan " << jumlahPesanan << " " << daftarMenu[idx].nama << " ke keranjang." << endl;
        
        cout << "Apakah ingin menambah menu lain? (y/n): ";
        cin >> tambahLagi;

    } while (tambahLagi == 'y' || tambahLagi == 'Y');

    if (keranjang.empty()) {
        cout << "Terima kasih, Anda tidak memesan apapun." << endl;
        return 0;
    }

    // --- PROSES CHECKOUT ---
    cout << endl;
    garis();
    cout << "Pilih Layanan:" << endl;
    cout << "1. Makan di Tempat (Dine In)" << endl;
    cout << "2. Bawa Pulang (Take Away)" << endl;
    cout << "Pilihan (1/2): ";
    cin >> tipeLayanan;

    namaLayanan = (tipeLayanan == '1') ? "Dine In" : "Take Away";

    pajak = totalBelanja * 0.10; 
    totalBayar = totalBelanja + pajak;

    system("cls");
    garis();
    cout << "RINCIAN PEMBAYARAN" << endl;
    for (const auto& item : keranjang) {
        cout << "- " << item.namaMenu << " (x" << item.jumlah << ") : Rp " << (size_t)item.subtotal << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Subtotal      : Rp " << (size_t)totalBelanja << endl; 
    cout << "Pajak (10%)   : Rp " << (size_t)pajak << endl;
    cout << "TOTAL TAGIHAN : Rp " << (size_t)totalBayar << endl;
    garis();

    cout << "Pilih Metode Pembayaran:" << endl;
    cout << "1. Tunai (Cash)" << endl;
    cout << "2. QRIS" << endl;
    cout << "Pilihan: ";
    cin >> metodeBayarChar;

    if (metodeBayarChar == '2') {
        namaMetodeBayar = "QRIS";
        // --- MEMANGGIL FUNGSI QRIS ---
        cetakQRIS(); 
        
        cout << "Tekan ENTER jika pembayaran QRIS berhasil...";
        cin.ignore(); cin.get(); // Menunggu user menekan enter
        uangBayar = totalBayar; // Asumsikan pas karena digital
    } else {
        namaMetodeBayar = "Tunai";
        do {
            cout << "Masukkan uang pembayaran: Rp ";
            cin >> uangBayar;

            if (uangBayar < totalBayar) {
                cout << "Uang kurang! Kurang Rp " << (size_t)(totalBayar - uangBayar) << endl;
            }
        } while (uangBayar < totalBayar);
    }

    kembalian = uangBayar - totalBayar;

    // --- CETAK STRUK AKHIR ---
    system("cls");
    cout << endl;
    garis();
    cout << "      STRUK PEMBAYARAN      " << endl;
    cout << "   RESTO AMIKOM SEJAHTERA   " << endl;
    garis();
    cout << "Layanan     : " << namaLayanan << endl;
    garis();
    
    cout << "ITEM YANG DIBELI:" << endl;
    for (const auto& item : keranjang) {
        cout << item.namaMenu << endl;
        cout << "   " << item.jumlah << " x Rp " << (size_t)item.hargaSatuan 
             << " = Rp " << (size_t)item.subtotal << endl;
    }
    
    garis();
    cout << "Subtotal    : Rp " << (size_t)totalBelanja << endl;
    cout << "Pajak (10%) : Rp " << (size_t)pajak << endl;
    cout << "----------------------------------------" << endl;
    cout << "TOTAL       : Rp " << (size_t)totalBayar << endl;
    cout << "Bayar ("<< namaMetodeBayar <<"): Rp " << (size_t)uangBayar << endl;
    cout << "Kembali     : Rp " << (size_t)kembalian << endl;
    garis();
    cout << "  Terima Kasih Atas Kunjungan Anda!  " << endl;
    garis();

    return 0;
}
