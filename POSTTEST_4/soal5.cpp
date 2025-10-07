#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void tukarHeadTail(Node*& head) {
    if (head == nullptr || head->next == head) return;

    Node* tail = head->prev;

    // Jika hanya ada 2 node
    if (head->next == tail && tail->next == head) {
        head = tail;
        return;
    }

    Node* setelahHead = head->next;
    Node* sebelumTail = tail->prev;

    // Ubah koneksi pointer
    sebelumTail->next = head;
    head->prev = sebelumTail;

    head->next = tail;
    tail->prev = head;

    tail->next = setelahHead;
    setelahHead->prev = tail;

    // Ubah head menjadi tail
    head = tail;
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

void tambahAkhir(Node*& head, int nilai) {
    Node* baru = new Node{nilai, nullptr, nullptr};
    if (head == nullptr) {
        baru->next = baru;
        baru->prev = baru;
        head = baru;
        return;
    }
    Node* tail = head->prev;
    baru->next = head;
    baru->prev = tail;
    tail->next = baru;
    head->prev = baru;
}

int main() {
    Node* head = nullptr;

    tambahAkhir(head, 1);
    tambahAkhir(head, 2);
    tambahAkhir(head, 3);
    tambahAkhir(head, 4);
    tambahAkhir(head, 5);

    cout << "List sebelum ditukar: ";
    tampil(head);

    tukarHeadTail(head);

    cout << "List setelah ditukar: ";
    tampil(head); // Output: 5 2 3 4 1

    return 0;
}
