#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Sewa {
    string nama;
    string tanggal;
    string jamMulai;
    int durasi;
    int lapangan;
};

// Fungsi untuk memisahkan string berdasarkan delimiter
vector<string> split(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, delimiter)) {
        result.push_back(temp);
    }
    return result;
}

void tambahSewa() {
    Sewa s;
    cout << "Masukkan nama penyewa   : ";
    cin.ignore();
    getline(cin, s.nama);
    cout << "Masukkan tanggal (DD-MM-YYYY) : ";
    getline(cin, s.tanggal);
    cout << "Masukkan jam mulai (HH:MM)    : ";
    getline(cin, s.jamMulai);
    cout << "Masukkan durasi (jam)         : ";
    cin >> s.durasi;
    cout << "Masukkan nomor lapangan (1-5) : ";
    cin >> s.lapangan;

    ofstream file("sewa.txt", ios::app);
    file << s.nama << "|" << s.tanggal << "|" << s.jamMulai << "|"
         << s.durasi << "|" << s.lapangan << "\n";
    file.close();
    cout << "✅ Data berhasil ditambahkan.\n";
}

void tampilkanData() {
    ifstream file("sewa.txt");
    string line;
    int i = 1;
    cout << "\n===== Daftar Sewa Lapangan =====\n";
    while (getline(file, line)) {
        vector<string> data = split(line, '|');
        if (data.size() == 5) {
            cout << i++ << ". Nama     : " << data[0] << "\n"
                 << "   Tanggal  : " << data[1] << "\n"
                 << "   Jam      : " << data[2] << "\n"
                 << "   Durasi   : " << data[3] << " jam\n"
                 << "   Lapangan : " << data[4] << "\n\n";
        }
    }
    file.close();
}

void editData() {
    string nama, tanggal;
    cout << "Masukkan nama penyewa yang akan diedit: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan tanggal sewa: ";
    getline(cin, tanggal);

    ifstream file("sewa.txt");
    ofstream temp("temp.txt");
    string line;
    bool ditemukan = false;

    while (getline(file, line)) {
        vector<string> data = split(line, '|');
        if (data.size() == 5 && data[0] == nama && data[1] == tanggal) {
            ditemukan = true;
            Sewa s;
            cout << "Masukkan data baru:\n";
            cout << "Jam mulai: ";
            getline(cin, s.jamMulai);
            cout << "Durasi (jam): ";
            cin >> s.durasi;
            cout << "Nomor lapangan: ";
            cin >> s.lapangan;
            cin.ignore();

            temp << nama << "|" << tanggal << "|" << s.jamMulai
                 << "|" << s.durasi << "|" << s.lapangan << "\n";
        } else {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove("sewa.txt");
    rename("temp.txt", "sewa.txt");

    if (ditemukan)
        cout << "✅ Data berhasil diupdate.\n";
    else
        cout << "❌ Data tidak ditemukan.\n";
}

void hapusData() {
    string nama, tanggal;
    cout << "Masukkan nama penyewa yang akan dihapus: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan tanggal sewa: ";
    getline(cin, tanggal);

    ifstream file("sewa.txt");
    ofstream temp("temp.txt");
    string line;
    bool ditemukan = false;

    while (getline(file, line)) {
        vector<string> data = split(line, '|');
        if (data.size() == 5 && data[0] == nama && data[1] == tanggal) {
            ditemukan = true;
            continue; // skip baris ini
        } else {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();
    remove("sewa.txt");
    rename("temp.txt", "sewa.txt");

    if (ditemukan)
        cout << "✅ Data berhasil dihapus.\n";
    else
        cout << "❌ Data tidak ditemukan.\n";
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Aplikasi Sewa Lapangan Bulutangkis ===\n";
        cout << "1. Tambah Data Sewa\n";
        cout << "2. Lihat Semua Data Sewa\n";
        cout << "3. Edit Data Sewa\n";
        cout << "4. Hapus Data Sewa\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahSewa(); break;
          6  case 2: tampilkanData(); break;
            case 3: editData(); break;
            case 4: hapusData(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
