#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Tambah elemen ke atas stack
void push(Node*& top, char data) {
    Node* baru = new Node{data, top};
    top = baru;
}

// Ambil elemen dari atas stack
char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* hapus = top;
    char nilai = hapus->data;
    top = top->next;
    delete hapus;
    return nilai;
}

// Membalik string menggunakan stack (manual)
string balikString(string teks) {
    Node* top = nullptr;
    string hasil = "";

    // Masukkan setiap huruf ke stack
    for (char huruf : teks) {
        push(top, huruf);
    }

    // Keluarkan satu per satu untuk membalik
    char ambilHuruf;
    while ((ambilHuruf = pop(top)) != '\0') {
        hasil.push_back(ambilHuruf);
    }

    return hasil;
}

int main() {
    string teks = "Struktur Data";
    cout << "Teks asli     : " << teks << endl;
    cout << "Teks terbalik : " << balikString(teks) << endl;
    return 0;
}
