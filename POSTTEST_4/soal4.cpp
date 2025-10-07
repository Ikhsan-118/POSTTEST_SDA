#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sisipTerurut(Node*& head, int nilai) {
    Node* baru = new Node{nilai, nullptr, nullptr};

    // Jika list kosong
    if (head == nullptr) {
        baru->next = baru;
        baru->prev = baru;
        head = baru;
        return;
    }

    Node* tail = head->prev;

    // Jika nilai lebih kecil dari head
    if (nilai < head->data) {
        baru->next = head;
        baru->prev = tail;
        tail->next = baru;
        head->prev = baru;
        head = baru;
        return;
    }

    // Cari posisi penyisipan
    Node* sekarang = head;
    while (sekarang->next != head && sekarang->next->data < nilai) {
        sekarang = sekarang->next;
    }

    baru->next = sekarang->next;
    baru->prev = sekarang;
    sekarang->next->prev = baru;
    sekarang->next = baru;
}

void tampil(Node* head) {
    if (head == nullptr) {
        cout << "List kosong\n";
        return;
    }
    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

int main() {
    Node* head = nullptr;

    sisipTerurut(head, 30);
    sisipTerurut(head, 10);
    sisipTerurut(head, 40);
    sisipTerurut(head, 20);

    cout << "Circular Doubly Linked List (terurut): ";
    tampil(head); // Output: 10 20 30 40

    return 0;
}
