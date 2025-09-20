// INI NYAMPE 400+ LINES CUMAN KARNA ASCI ART :V
// Nama : IKHSAN
// NIM  : 2409106118

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>   // setw
#include <limits>    // numeric_limits
using namespace std;

// Tampilkan banner yang berisi angka besar sesuai input (mis: "2409106118")
void tampilkanBannerAngka(const string& angka) {
    // Representasi setiap digit (tinggi 7 baris, spacing antar digit)
    unordered_map<char, vector<string>> d;
    d['0'] = {
        "  _____  ",
        " / ____| ",
        "| |  _   ",
        "| | | |  ",
        "| |_| |  ",
        " \\____|  ",
        "         "
    };
    d['1'] = {
        "   __    ",
        "  /_ |   ",
        "   | |   ",
        "   | |   ",
        "   | |   ",
        "   |_|   ",
        "         "
    };
    d['2'] = {
        "  _____  ",
        " |___  \\ ",
        "    / /  ",
        "   / /   ",
        "  / /__  ",
        " |_____| ",
        "         "
    };
    d['3'] = {
        "  _____  ",
        " |___ /  ",
        "   |_ \\  ",
        "  ___) | ",
        " |____/  ",
        "         ",
        "         "
    };
    d['4'] = {
        "  _  _   ",
        " | || |  ",
        " | || |_ ",
        " |__   _|",
        "    | |  ",
        "    |_|  ",
        "         "
    };
    d['5'] = {
        "  _____  ",
        " | ____| ",
        " | |__   ",
        " |___ \\  ",
        "  ___) | ",
        " |____/  ",
        "         "
    };
    d['6'] = {
        "   __    ",
        "  / /    ",
        " / /_    ",
        "| '_ \\   ",
        "| (_) |  ",
        " \\___/   ",
        "         "
    };
    d['7'] = {
        "  ______ ",
        " |____  |",
        "     / / ",
        "    / /  ",
        "   / /   ",
        "  /_/    ",
        "         "
    };
    d['8'] = {
        "  ___    ",
        " ( _ )   ",
        " / _ \\   ",
        "| (_) |  ",
        " \\___/   ",
        "         ",
        "         "
    };
    d['9'] = {
        "  ___    ",
        " / _ \\   ",
        "| (_) |  ",
        " \\__, |  ",
        "   / /   ",
        "  /_/    ",
        "         "
    };

    // Jika ada karakter lain, tampilkan blok kosong
    for (char c : angka) {
        if (d.find(c) == d.end()) {
            d[c] = {
                "        ",
                "        ",
                "  ??    ",
                "  ??    ",
                "        ",
                "        ",
                "        "
            };
        }
    }

    // Print baris demi baris, menggabungkan setiap digit
    cout << "\n";
    for (int baris = 0; baris < 7; ++baris) {
        for (char c : angka) {
            cout << d[c][baris] << "  ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "           SISTEM JADWAL PENERBANGAN (GENAP)\n\n";
}

// Pesawat kecil untuk header menu
void tampilkanPesawatKecil() {
    cout << R"(
       __|__
  --@--(_)--@--
    )" << "\n";
}

// Struktur data untuk menyimpan info penerbangan
struct Penerbangan {
    string kode;
    string tujuan;
    string status;
};

// Node untuk linked list
struct NodeP {
    Penerbangan data;
    NodeP* next;
    NodeP(const Penerbangan& p) : data(p), next(nullptr) {}
};

// Kelas daftar penerbangan (singly linked list)
class DaftarPenerbangan {
private:
    NodeP* kepala;
    int jumlah;
    string kodeDasar; // contoh: "JT-118"
    int penghitungKode; // 0 => JT-118, 1 => JT-118-1, dst.

public:
    DaftarPenerbangan(const string& dasar) : kepala(nullptr), jumlah(0), kodeDasar(dasar), penghitungKode(0) {}

    // Buat kode unik otomatis
    string buatKode() {
        string kode;
        if (penghitungKode == 0) kode = kodeDasar;
        else kode = kodeDasar + "-" + to_string(penghitungKode);
        penghitungKode++;
        return kode;
    }

    // Tambah jadwal di akhir
    void tambahAkhir(const string& tujuan, const string& status) {
        Penerbangan p;
        p.kode = buatKode();
        p.tujuan = tujuan;
        p.status = status;

        NodeP* node = new NodeP(p);
        if (!kepala) kepala = node;
        else {
            NodeP* cur = kepala;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        jumlah++;
        cout << "Jadwal dengan kode \"" << p.kode << "\" berhasil ditambahkan.\n";
    }

    // Sisipkan pada posisi (1-based). Jika posisi > jumlah+1 => append
    void sisipPadaPosisi(const string& tujuan, const string& status, int posisi) {
        if (posisi <= 1) {
            Penerbangan p; p.kode = buatKode(); p.tujuan = tujuan; p.status = status;
            NodeP* node = new NodeP(p);
            node->next = kepala;
            kepala = node;
            jumlah++;
            cout << "Jadwal \"" << p.kode << "\" disisipkan di posisi 1.\n";
            return;
        }

        if (posisi > jumlah + 1) posisi = jumlah + 1; // jadikan append

        NodeP* cur = kepala;
        int idx = 1;
        while (cur && idx < posisi - 1) { cur = cur->next; idx++; }

        Penerbangan p; p.kode = buatKode(); p.tujuan = tujuan; p.status = status;
        NodeP* node = new NodeP(p);

        if (!cur) {
            // list kosong -> jadi kepala
            kepala = node;
        } else {
            node->next = cur->next;
            cur->next = node;
        }
        jumlah++;
        cout << "Jadwal \"" << p.kode << "\" berhasil disisipkan di posisi " << posisi << ".\n";
    }

    // Hapus jadwal paling awal (kepala)
    void hapusPalingAwal() {
        if (!kepala) {
            cout << "Belum ada jadwal untuk dihapus.\n";
            return;
        }
        NodeP* hapus = kepala;
        kepala = kepala->next;
        cout << "Jadwal \"" << hapus->data.kode << "\" dihapus (paling awal).\n";
        delete hapus;
        jumlah--;
    }

    // Update status berdasarkan kode
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
                if (statusBaru.size() == 0) getline(cin, statusBaru); // fallback
                cur->data.status = statusBaru;
                cout << "Status berhasil diperbarui.\n";
                return;
            }
            cur = cur->next;
        }
        cout << "Kode penerbangan \"" << kodeDicari << "\" tidak ditemukan.\n";
    }

    // Tampilkan semua jadwal
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

    // Opsional: cari berdasarkan tujuan (persis)
    void cariBerdasarkanTujuan(const string& tujuanCari) {
        if (!kepala) {
            cout << "Daftar kosong.\n";
            return;
        }
        bool ketemu = false;
        NodeP* cur = kepala;
        while (cur) {
            if (cur->data.tujuan == tujuanCari) {
                if (!ketemu) {
                    cout << "Hasil pencarian:\n";
                    cout << left << setw(20) << "Kode" << setw(25) << "Tujuan" << setw(20) << "Status" << endl;
                    cout << "------------------------------------------------------------------\n";
                }
                cout << left << setw(20) << cur->data.kode
                     << setw(25) << cur->data.tujuan
                     << setw(20) << cur->data.status << endl;
                ketemu = true;
            }
            cur = cur->next;
        }
        if (!ketemu) cout << "Tidak ditemukan jadwal dengan tujuan \"" << tujuanCari << "\".\n";
    }

    // Hapus semua node saat destruksi
    ~DaftarPenerbangan() {
        NodeP* cur = kepala;
        while (cur) {
            NodeP* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
};

// Ambil 3 digit terakhir NIM sebagai string (pad dengan nol bila perlu)
string tigaDigitTerakhir(const string& nim) {
    if (nim.length() >= 3) return nim.substr(nim.length() - 3);
    if (nim.length() == 2) return "0" + nim;
    if (nim.length() == 1) return "00" + nim;
    return "000";
}

// Ambil digit terakhir NIM sebagai integer
int digitTerakhir(const string& nim) {
    if (nim.empty()) return 0;
    char c = nim[nim.length() - 1];
    if (c >= '0' && c <= '9') return c - '0';
    return 0;
}

int main() {
    // Tampilkan banner angka (sesuaikan di sini kalau mau angka lain)
    tampilkanBannerAngka("2409106118");

    string nama, nim;
    cout << "Masukkan Nama : ";
    getline(cin, nama);
    if (nama.size() == 0) getline(cin, nama); // fallback
    cout << "Masukkan NIM  : ";
    getline(cin, nim);
    if (nim.size() == 0) getline(cin, nim);

    // Data personalisasi
    string tigaTerakhir = tigaDigitTerakhir(nim);         // misal "118"
    int dTerakhir = digitTerakhir(nim);                  // misal 8
    int posisiSisip = (dTerakhir == 0) ? 2 : (dTerakhir + 1); // aturan: digit terakhir + 1, 0 -> 2
    string kodeDasar = "JT-" + tigaTerakhir;             // misal "JT-118"

    DaftarPenerbangan daftar(kodeDasar);

    int pilihan;
    while (true) {
        // Header menu dengan pesawat kecil
        cout << "\n";
        tampilkanPesawatKecil();
        cout << "  Nama : " << nama << "    NIM : " << nim << "\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "| 1. Tambah Jadwal Penerbangan (Akhir)                       |\n";
        cout << "| 2. Sisipkan Jadwal (Posisi otomatis berdasarkan NIM)       |\n";
        cout << "| 3. Hapus Jadwal Paling Awal                                |\n";
        cout << "| 4. Ubah Status Penerbangan                                 |\n";
        cout << "| 5. Tampilkan Semua Jadwal                                  |\n";
        cout << "| 6. (Opsional) Cari Jadwal berdasarkan Tujuan               |\n";
        cout << "| 0. Keluar                                                  |\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        cin.ignore(); // buang newline

        if (pilihan == 0) {
            cout << "Terima kasih. Program selesai.\n";
            break;
        }

        if (pilihan == 1) {
            cout << "-- Tambah Jadwal Baru --\n";
            cout << "Masukkan tujuan: ";
            string tujuan; getline(cin, tujuan);
            if (tujuan.size() == 0) getline(cin, tujuan);
            cout << "Masukkan status (misal: Tepat Waktu / Terlambat / Naik Pesawat): ";
            string status; getline(cin, status);
            if (status.size() == 0) getline(cin, status);
            daftar.tambahAkhir(tujuan, status);
        }
        else if (pilihan == 2) {
            cout << "-- Sisipkan Jadwal --\n";
            cout << "Posisi sisip otomatis dari NIM (digit terakhir + 1) = " << posisiSisip << "\n";
            cout << "Masukkan tujuan: ";
            string tujuan; getline(cin, tujuan);
            if (tujuan.size() == 0) getline(cin, tujuan);
            cout << "Masukkan status: ";
            string status; getline(cin, status);
            if (status.size() == 0) getline(cin, status);
            daftar.sisipPadaPosisi(tujuan, status, posisiSisip);
        }
        else if (pilihan == 3) {
            cout << "-- Hapus Jadwal Paling Awal --\n";
            daftar.hapusPalingAwal();
        }
        else if (pilihan == 4) {
            cout << "-- Ubah Status Penerbangan --\n";
            cout << "Masukkan kode penerbangan (contoh: " << kodeDasar << " atau " << kodeDasar << "-1): ";
            string kode; getline(cin, kode);
            if (kode.size() == 0) getline(cin, kode);
            daftar.ubahStatus(kode);
        }
        else if (pilihan == 5) {
            daftar.tampilkanSemua();
        }
        else if (pilihan == 6) {
            cout << "-- Cari Jadwal berdasarkan Tujuan (Opsional) --\n";
            cout << "Masukkan tujuan (harus persis sama): ";
            string tujuan; getline(cin, tujuan);
            if (tujuan.size() == 0) getline(cin, tujuan);
            daftar.cariBerdasarkanTujuan(tujuan);
        }
        else {
            cout << "Pilihan tidak tersedia. Silakan pilih nomor yang ada di menu.\n";
        }
    }

    return 0;
}
