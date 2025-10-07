#include <iostream>
#include <string>
using namespace std;

struct Node {
    string dokumen;
    Node* next;
};

// Tambahkan ke belakang antrian
void enqueue(Node*& depan, Node*& belakang, string dokumen) {
    Node* baru = new Node{dokumen, nullptr};
    if (depan == nullptr) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }
    cout << "Menambahkan ke antrian: " << dokumen << endl;
}

// Keluarkan dari depan antrian
string dequeue(Node*& depan, Node*& belakang) {
    if (depan == nullptr) return "";
    string hasil = depan->dokumen;
    Node* hapus = depan;
    depan = depan->next;
    if (depan == nullptr) belakang = nullptr;
    delete hapus;
    return hasil;
}

// Proses seluruh antrian printer
void prosesSemua(Node*& depan, Node*& belakang) {
    while (depan != nullptr) {
        string dok = dequeue(depan, belakang);
        cout << "Memproses: " << dok << endl;
    }
}

int main() {
    Node* depan = nullptr;
    Node* belakang = nullptr;

    enqueue(depan, belakang, "Document1.pdf");
    enqueue(depan, belakang, "Report.docx");
    enqueue(depan, belakang, "Presentation.pptx");

    cout << "\nMemulai pemrosesan antrian printer:\n";
    prosesSemua(depan, belakang);
    return 0;
}
