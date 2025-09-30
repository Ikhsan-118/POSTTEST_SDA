// GENAP_2409106118.cpp
// Sistem Jadwal Penerbangan (GENAP) - Double Linked List + Traversal belakang + Detail by ID/Nama
// Nama : (masukkan saat program jalan)
// NIM  : (masukkan saat program jalan)

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>   // setw
#include <limits>    // numeric_limits
using namespace std;

// Banner angka besar (tetap menggunakan 2409106118 pada banner)
void tampilkanBannerAngka(const string& angka) {
    unordered_map<char, vector<string>> d;
    d['0'] = {"  _____  ", " / ____| ", "| |  _   ", "| | | |  ", "| |_| |  ", " \\____|  ", "         "};
    d['1'] = {"   __    ", "  /_ |   ", "   | |   ", "   | |   ", "   | |   ", "   |_|   ", "         "};
    d['2'] = {"  _____  ", " |___  \\ ", "    / /  ", "   / /   ", "  / /__  ", " |_____| ", "         "};
    d['3'] = {"  _____  ", " |___ /  ", "   |_ \\  ", "  ___) | ", " |____/  ", "         ", "         "};
    d['4'] = {"  _  _   ", " | || |  ", " | || |_ ", " |__   _|", "    | |  ", "    |_|  ", "         "};
    d['5'] = {"  _____  ", " | ____| ", " | |__   ", " |___ \\  ", "  ___) | ", " |____/  ", "         "};
    d['6'] = {"   __    ", "  / /    ", " / /_    ", "| '_ \\   ", "| (_) |  ", " \\___/   ", "         "};
    d['7'] = {"  ______ ", " |____  |", "     / / ", "    / /  ", "   / /   ", "  /_/    ", "         "};
    d['8'] = {"  ___    ", " ( _ )   ", " / _ \\   ", "| (_) |  ", " \\___/   ", "         ", "         "};
    d['9'] = {"  ___    ", " / _ \\   ", "| (_) |  ", " \\__, |  ", "   / /   ", "  /_/    ", "         "};
    for (char c : angka) if (d.find(c) == d.end()) d[c] = {"        ","        ","  ??    ","  ??    ","        ","        ","        "};
    cout << "\n";
    for (int baris = 0; baris < 7; ++baris) {
        for (char c : angka) cout << d[c][baris] << "  ";
        cout << "\n";
    }
    cout << "\n";
    cout << "           SISTEM JADWAL PENERBANGAN (GENAP)\n\n";
}

void tampilkanPesawatKecil() {
    cout << R"(
       __|__
  --@--(_)--@--
    )" << "\n";
}

// Struktur data penerbangan
struct Penerbangan {
    string kode;
    string tujuan;
    string status;
};

// Node double linked list
struct NodeP {
    Penerbangan data;
    NodeP* next;
    NodeP* prev;
    NodeP(const Penerbangan& p) : data(p), next(nullptr), prev(nullptr) {}
};

// Kelas daftar penerbangan (Double Linked List)
class DaftarPenerbangan {
private:
    NodeP* kepala;
    NodeP* ekor;
    int jumlah;
    string kodeDasar; // ex "JT-118"
    int penghitungKode;

public:
    DaftarPenerbangan(const string& dasar) : kepala(nullptr), ekor(nullptr), jumlah(0), kodeDasar(dasar), penghitungKode(0) {}

    // buat kode unik
    string buatKode() {
        string kode;
        if (penghitungKode == 0) kode = kodeDasar;
        else kode = kodeDasar + "-" + to_string(penghitungKode);
        penghitungKode++;
        return kode;
    }

    // tambah di akhir (append)
    void tambahAkhir(const string& tujuan, const string& status) {
        Penerbangan p; p.kode = buatKode(); p.tujuan = tujuan; p.status = status;
        NodeP* node = new NodeP(p);
        if (!kepala) {
            kepala = ekor = node;
        } else {
            ekor->next = node;
            node->prev = ekor;
            ekor = node;
        }
        jumlah++;
        cout << "Jadwal dengan kode \"" << p.kode << "\" berhasil ditambahkan.\n";
    }

    // sisip pada posisi (1-based)
    void sisipPadaPosisi(const string& tujuan, const string& status, int posisi) {
        if (posisi <= 1) {
            Penerbangan p; p.kode = buatKode(); p.tujuan = tujuan; p.status = status;
            NodeP* node = new NodeP(p);
            node->next = kepala;
            if (kepala) kepala->prev = node;
            kepala = node;
            if (!ekor) ekor = node;
            jumlah++;
            cout << "Jadwal \"" << p.kode << "\" disisipkan di posisi 1.\n";
            return;
        }
        if (posisi > jumlah + 1) posisi = jumlah + 1; // append

        // temukan node pada posisi-1
        NodeP* cur = kepala;
        int idx = 1;
        while (cur && idx < posisi - 1) { cur = cur->next; idx++; }

        Penerbangan p; p.kode = buatKode(); p.tujuan = tujuan; p.status = status;
        NodeP* node = new NodeP(p);

        if (!cur) {
            // list kosong -> jadi kepala dan ekor
            kepala = ekor = node;
        } else if (!cur->next) {
            // sisip di akhir (cur = ekor)
            cur->next = node;
            node->prev = cur;
            ekor = node;
        } else {
            node->next = cur->next;
            node->prev = cur;
            cur->next->prev = node;
            cur->next = node;
        }
        jumlah++;
        cout << "Jadwal \"" << p.kode << "\" berhasil disisipkan di posisi " << posisi << ".\n";
    }

    // hapus jadwal paling awal (head)
    void hapusPalingAwal() {
        if (!kepala) {
            cout << "Belum ada jadwal untuk dihapus.\n";
            return;
        }
        NodeP* hapus = kepala;
        kepala = kepala->next;
        if (kepala) kepala->prev = nullptr;
        else ekor = nullptr; // list menjadi kosong
        cout << "Jadwal \"" << hapus->data.kode << "\" dihapus (paling awal).\n";
        delete hapus;
        jumlah--;
    }

    // ubah status berdasarkan kode
    void ubahStatus(const string& kodeDicari) {
        if (!kepala) {
            cout << "Daftar jadwal masih kosong.\n";
            return;
        }
        NodeP* cur = kepala;
        while (cur) {
            if (cur->data.kode == kodeDicari) {
                cout << "Ditemukan: " << cur->data.kode << " | Tujuan: " << cur->data.tujuan
                     << " | Status sekarang: " << cur->data.status << endl;
                cout << "Masukkan status baru: ";
                string statusBaru;
                getline(cin, statusBaru);
                if (statusBaru.size() == 0) getline(cin, statusBaru);
                cur->data.status = statusBaru;
                cout << "Status berhasil diperbarui.\n";
                return;
            }
            cur = cur->next;
        }
        cout << "Kode penerbangan \"" << kodeDicari << "\" tidak ditemukan.\n";
    }

    // tampilkan semua dari depan -> belakang
    void tampilkanSemua() {
        if (!kepala) {
            cout << "Belum ada jadwal untuk ditampilkan.\n";
            return;
        }
        cout << "+----------------------------------------------------------------+\n";
        cout << "|                          DAFTAR JADWAL                          |\n";
        cout << "+----------------------------------------------------------------+\n";
        cout << left << setw(20) << "Kode" << setw(25) << "Tujuan" << setw(20) << "Status" << endl;
        cout << "------------------------------------------------------------------\n";
        NodeP* cur = kepala;
        while (cur) {
            cout << left << setw(20) << cur->data.kode
                 << setw(25) << cur->data.tujuan
                 << setw(20) << cur->data.status << endl;
            cur = cur->next;
        }
        cout << "------------------------------------------------------------------\n";
        cout << "Total jadwal: " << jumlah << "\n";
    }

    // traversal dari belakang -> depan (menggunakan pointer ekor)
    void tampilkanDariBelakang() {
        if (!ekor) {
            cout << "Belum ada jadwal untuk ditampilkan.\n";
            return;
        }
        cout << "+----------------------------------------------------------------+\n";
        cout << "|                   DAFTAR JADWAL (DARI BELAKANG)                |\n";
        cout << "+----------------------------------------------------------------+\n";
        cout << left << setw(20) << "Kode" << setw(25) << "Tujuan" << setw(20) << "Status" << endl;
        cout << "------------------------------------------------------------------\n";
        NodeP* cur = ekor;
        while (cur) {
            cout << left << setw(20) << cur->data.kode
                 << setw(25) << cur->data.tujuan
                 << setw(20) << cur->data.status << endl;
            cur = cur->prev;
        }
        cout << "------------------------------------------------------------------\n";
        cout << "Total jadwal: " << jumlah << "\n";
    }

    // tampilkan detail berdasarkan input: jika input cocok kode -> tampil 1 item,
    // jika bukan kode, cek tujuan (nama) dan tampil semua yang cocok (bisa lebih dari 1)
    void tampilkanDetailByIdAtauNama(const string& input) {
        if (!kepala) {
            cout << "Daftar jadwal masih kosong.\n";
            return;
        }
        // pertama coba cari berdasarkan kode (exact match)
        NodeP* cur = kepala;
        while (cur) {
            if (cur->data.kode == input) {
                cout << "+--------------------- DETAIL JADWAL ---------------------+\n";
                cout << "Kode   : " << cur->data.kode << "\n";
                cout << "Tujuan : " << cur->data.tujuan << "\n";
                cout << "Status : " << cur->data.status << "\n";
                cout << "+---------------------------------------------------------+\n";
                return;
            }
            cur = cur->next;
        }
        // jika tidak ditemukan kode, cari berdasarkan tujuan (nama) exact match
        bool ketemu = false;
        cur = kepala;
        while (cur) {
            if (cur->data.tujuan == input) {
                if (!ketemu) {
                    cout << "+----------------- HASIL PENCARIAN BERDASARKAN NAMA -----------------+\n";
                    cout << left << setw(20) << "Kode" << setw(25) << "Tujuan" << setw(20) << "Status" << endl;
                    cout << "---------------------------------------------------------------------\n";
                }
                cout << left << setw(20) << cur->data.kode
                     << setw(25) << cur->data.tujuan
                     << setw(20) << cur->data.status << endl;
                ketemu = true;
            }
            cur = cur->next;
        }
        if (!ketemu) {
            cout << "Tidak ditemukan jadwal dengan KODE atau TUJUAN = \"" << input << "\".\n";
        } else {
            cout << "---------------------------------------------------------------------\n";
        }
    }

    // destructor: hapus semua node
    ~DaftarPenerbangan() {
        NodeP* cur = kepala;
        while (cur) {
            NodeP* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
};

// helper: ambil 3 digit terakhir NIM sebagai string, pad jika perlu
string tigaDigitTerakhir(const string& nim) {
    if (nim.length() >= 3) return nim.substr(nim.length() - 3);
    if (nim.length() == 2) return "0" + nim;
    if (nim.length() == 1) return "00" + nim;
    return "000";
}
int digitTerakhir(const string& nim) {
    if (nim.empty()) return 0;
    char c = nim[nim.length() - 1];
    if (c >= '0' && c <= '9') return c - '0';
    return 0;
}

// safe read helpers
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
string bacaBaris(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    if (s.size() == 0) getline(cin, s);
    return s;
}

int main() {
    tampilkanBannerAngka("2409106118");

    string nama, nim;
    cout << "Masukkan Nama : ";
    getline(cin, nama);
    if (nama.size() == 0) getline(cin, nama);
    cout << "Masukkan NIM  : ";
    getline(cin, nim);
    if (nim.size() == 0) getline(cin, nim);

    string tigaTerakhir = tigaDigitTerakhir(nim);
    int dTerakhir = digitTerakhir(nim);
    int posisiSisip = (dTerakhir == 0) ? 2 : (dTerakhir + 1);
    string kodeDasar = "JT-" + tigaTerakhir;

    DaftarPenerbangan daftar(kodeDasar);

    int pilihan;
    while (true) {
        cout << "\n";
        tampilkanPesawatKecil();
        cout << "  Nama : " << nama << "    NIM : " << nim << "\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "| 1. Tambah Jadwal Penerbangan (Akhir)                       |\n";
        cout << "| 2. Sisipkan Jadwal (Posisi otomatis berdasarkan NIM)       |\n";
        cout << "| 3. Hapus Jadwal Paling Awal                                |\n";
        cout << "| 4. Ubah Status Penerbangan                                 |\n";
        cout << "| 5. Tampilkan Semua Jadwal (depan->belakang)                |\n";
        cout << "| 6. Tampilkan Semua Jadwal (dari belakang)                  |\n";
        cout << "| 7. Tampilkan Detail berdasarkan KODE atau TUJUAN           |\n";
        cout << "| 0. Keluar                                                  |\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            bersihkanInput();
            cout << "Masukan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        bersihkanInput();

        if (pilihan == 0) {
            cout << "Terima kasih. Program selesai.\n";
            break;
        } else if (pilihan == 1) {
            cout << "-- Tambah Jadwal Baru --\n";
            string tujuan = bacaBaris("Masukkan tujuan: ");
            string status = bacaBaris("Masukkan status (misal: Tepat Waktu / Terlambat / Naik Pesawat): ");
            daftar.tambahAkhir(tujuan, status);
        } else if (pilihan == 2) {
            cout << "-- Sisipkan Jadwal --\n";
            cout << "Posisi sisip otomatis dari NIM (digit terakhir + 1) = " << posisiSisip << "\n";
            string tujuan = bacaBaris("Masukkan tujuan: ");
            string status = bacaBaris("Masukkan status: ");
            daftar.sisipPadaPosisi(tujuan, status, posisiSisip);
        } else if (pilihan == 3) {
            cout << "-- Hapus Jadwal Paling Awal --\n";
            daftar.hapusPalingAwal();
        } else if (pilihan == 4) {
            cout << "-- Ubah Status Penerbangan --\n";
            string contoh = kodeDasar + " atau " + kodeDasar + "-1";
            string kode = bacaBaris("Masukkan kode penerbangan (contoh: " + contoh + "): ");
            daftar.ubahStatus(kode);
        } else if (pilihan == 5) {
            daftar.tampilkanSemua();
        } else if (pilihan == 6) {
            daftar.tampilkanDariBelakang();
        } else if (pilihan == 7) {
            cout << "-- Cari Detail (KODE atau TUJUAN) --\n";
            string input = bacaBaris("Masukkan KODE atau TUJUAN untuk dicari (tepat sama): ");
            daftar.tampilkanDetailByIdAtauNama(input);
        } else {
            cout << "Pilihan tidak tersedia. Silakan pilih nomor yang ada di menu.\n";
        }
    }

    return 0;
}
