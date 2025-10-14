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

// Traversal pre-order (kunjungi akar, kiri, lalu kanan)
void traversalPreOrder(Node* akar) {
    if (akar == nullptr) return; // basis rekursi
    cout << akar->data << " ";        // langkah 1: cetak akar
    traversalPreOrder(akar->kiri);    // langkah 2: ke kiri
    traversalPreOrder(akar->kanan);   // langkah 3: ke kanan
}

int main() {
    Node* akar = nullptr;
    akar = tambahNode(akar, 50);
    tambahNode(akar, 30);
    tambahNode(akar, 70);
    tambahNode(akar, 20);
    tambahNode(akar, 40);
    tambahNode(akar, 60);
    tambahNode(akar, 80);

    cout << "Hasil traversal pre-order: ";
    traversalPreOrder(akar); // Output: 50 30 20 40 70 60 80
    cout << endl;
    return 0;
}
