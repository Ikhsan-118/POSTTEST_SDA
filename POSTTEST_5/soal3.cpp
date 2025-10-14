#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* kiri;
    Node* kanan;

    Node(int nilai) {
        data = nilai;
        kiri = nullptr;
        kanan = nullptr;
    }
};

Node* tambahNode(Node* akar, int nilai) {
    if (akar == nullptr) return new Node(nilai);
    if (nilai < akar->data)
        akar->kiri = tambahNode(akar->kiri, nilai);
    else if (nilai > akar->data)
        akar->kanan = tambahNode(akar->kanan, nilai);
    return akar;
}

// Fungsi untuk mencari nilai terbesar di BST
int cariNilaiTerbesar(Node* akar) {
    if (akar == nullptr) return -1; // pohon kosong

    Node* sekarang = akar;
    // terus ke kanan sampai node paling ujung kanan
    while (sekarang->kanan != nullptr) {
        sekarang = sekarang->kanan;
    }
    return sekarang->data;
}

int main() {
    Node* akar = nullptr;
    akar = tambahNode(akar, 50);
    tambahNode(akar, 30);
    tambahNode(akar, 70);
    tambahNode(akar, 20);
    tambahNode(akar, 80);

    cout << "Nilai terbesar di dalam pohon adalah: "
         << cariNilaiTerbesar(akar) << endl; // Output: 80
    return 0;
}
