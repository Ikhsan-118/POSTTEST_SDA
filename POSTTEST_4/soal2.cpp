#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* baru = new Node{data, top};
    top = baru;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* hapus = top;
    char nilai = hapus->data;
    top = top->next;
    delete hapus;
    return nilai;
}

bool cocok(char buka, char tutup) {
    return (buka == '(' && tutup == ')') ||
           (buka == '{' && tutup == '}') ||
           (buka == '[' && tutup == ']');
}

bool seimbang(string ekspresi) {
    Node* top = nullptr;

    for (char simbol : ekspresi) {
        if (simbol == '(' || simbol == '{' || simbol == '[') {
            push(top, simbol);
        } else if (simbol == ')' || simbol == '}' || simbol == ']') {
            if (top == nullptr) return false;
            char buka = pop(top);
            if (!cocok(buka, simbol)) return false;
        }
    }

    bool kosong = (top == nullptr);
    while (pop(top) != '\0'); // bersihkan sisa
    return kosong;
}

int main() {
    string s1 = "{[()]}";
    string s2 = "{[(])}";

    cout << s1 << " -> " << (seimbang(s1) ? "Seimbang" : "Tidak Seimbang") << endl;
    cout << s2 << " -> " << (seimbang(s2) ? "Seimbang" : "Tidak Seimbang") << endl;
    return 0;
}
