#include <iostream>
using namespace std;

// Struktur Node untuk menyimpan data pohon
struct Node {
    int data;       // nilai data di node
    Node* kiri;     // anak kiri
    Node* kanan;    // anak kanan

    Node(int nilai) {
        data = nilai;
        kiri = nullptr;
        kanan = nullptr;
    }
};

// Fungsi untuk menambahkan data ke dalam pohon BST
Node* tambahNode(Node* akar, int nilai) {
    if (akar == nullptr) {
        return new Node(nilai); 
    }
    if (nilai < akar->data) {
        akar->kiri = tambahNode(akar->kiri, nilai);
    } else if (nilai > akar->data) {
        akar->kanan = tambahNode(akar->kanan, nilai);
    }
    return akar;
}

// Fungsi menghitung jumlah total node dalam pohon
int hitungJumlahNode(Node* akar) {
    if (akar == nullptr) return 0; // pohon kosong
    return 1 + hitungJumlahNode(akar->kiri) + hitungJumlahNode(akar->kanan);
}

int main() {
    Node* akar = nullptr;
    akar = tambahNode(akar, 50);
    tambahNode(akar, 30);
    tambahNode(akar, 70);
    tambahNode(akar, 20);

    cout << "Jumlah total simpul (node) dalam pohon adalah: "
         << hitungJumlahNode(akar) << endl; // Output: 4
    return 0;
}
