#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    Mahasiswa mhs[4];

    // Input data mahasiswa
    for (int i = 0; i < 4; i++) {
        cout << "Data Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        cin >> mhs[i].nama;
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cout << endl;
    }

    // Sorting berdasarkan IPK ascending (Bubble Sort)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (mhs[j].ipk > mhs[j+1].ipk) {
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j+1];
                mhs[j+1] = temp;
            }
        }
    }

    // Tampilkan hasil
    cout << "\nData Mahasiswa setelah diurutkan berdasarkan IPK (ascending):\n";
    for (int i = 0; i < 4; i++) {
        cout << mhs[i].nama << " | " << mhs[i].nim << " | " << mhs[i].ipk << endl;
    }

    return 0;
}
