#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Base {
    char surname[40];
    int height;
    int weight;
}arr[8];

void HashWrite(int, int, int *, int *);
int HashSearch(int, int, int*, int*);

int main()
{
    setlocale(LC_ALL, "ru");
    int M = 10, H[10], p[10];
    for (int i = 0; i < 8; i++) {
        cout << "Введите фамилию:" << endl;
        cin >> arr[i].surname;
        cout << "Введите рост:" << endl;
        cin >> arr[i].height;
        cout << "Введите вес:" << endl;
        cin >> arr[i].weight;
    }
    cout << "Вспомогательный массив:" << endl;
    for (int i = 0; i < 10; i++) {
        p[i] = 1 + rand() % 9;
        cout << p[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < M; i++) {
        H[i] = -1;
    }
    for (int i = 0; i < 8; i++) {
        HashWrite(arr[i].height, M, H, p);
    }
    cout << "Хеш-таблица:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << H[i] << " ";
    }
    cout << endl;
    int search = 0, number;
    cout << "Введите рост: ";
    
    while (search != -1) {
        cin >> search;
        number = HashSearch(search, M, H, p);
        if (number == -1) cout << "Данные не найдены." << endl;
        else {
            cout << "Номер искомого человека в хеш-таблице: " << number+1 << endl;
            cout << "Фамилия: " << arr[number].surname << " Рост: " << arr[number].height << " Вес: " << arr[number].weight << endl;
            search = -1;
        }
    }
    return 0;
}

void HashWrite(int x, int m, int* H, int *p) {
    int i = abs(x % m);
    int q = 0;
    if (H[i] != -1) {
        while (H[i] != -1) {
            i = i + p[q];
            if (i>= m) i = 0;
            q++;
        }
        q = 0;
    }
    H[i] = x;
}

int HashSearch(int x, int m, int* H, int* p) {
    int i = abs(x % m);
    int q = 0;
    if (H[i] != -1) {
        while (H[i] != -1) {
            if (H[i] == x) return i;
            i = i + p[q];
            if (i >= m) i = 0;
            q++;
        }
        q = 0;
    }
        return -1;
}
