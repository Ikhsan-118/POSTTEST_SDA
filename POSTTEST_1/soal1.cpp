#include <iostream>
using namespace std;

// Fungsi untuk membalik array dengan pointer
void balikArray(int *arr, int n) {
    int *awal = arr;
    int *akhir = arr + n - 1;

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

bool isPrima(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int arr[7];
    int count = 0, num = 2;

    // isi dengan bilangan prima
    while (count < 7) {
        if (isPrima(num)) {
            arr[count] = num;
            count++;
        }
        num++;
    }

    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < 7; i++) cout << arr[i] << " ";

    balikArray(arr, 7);

    cout << "\nArray sesudah dibalik: ";
    for (int i = 0; i < 7; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
