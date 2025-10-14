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

// Traversal post-order (kunjungi kiri, kanan, lalu akar)
void traversalPostOrder(Node* akar) {
    if (akar == nullptr) return; // basis rekursi
    traversalPostOrder(akar->kiri);   // langkah 1: ke kiri
    traversalPostOrder(akar->kanan);  // langkah 2: ke kanan
    cout << akar->data << " ";        // langkah 3: cetak akar
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

    cout << "Hasil traversal post-order: ";
    traversalPostOrder(akar); // Output: 20 40 30 60 80 70 50
    cout << endl;
    return 0;
}
