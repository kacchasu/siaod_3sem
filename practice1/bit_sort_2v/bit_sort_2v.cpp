#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
int main()
{
    int n;
    cout << "enter amount of numbers: ";
    cin >> n; // ввод количества чисел

    unsigned char x[8] = {}; // создание линейного массива на 64 бита
    unsigned char maska = 1; // создание маски

    cout << "enter numbers: "; 
    for (int i = 0; i < n; i++) // ввод чисел
    {
        int temp;
        cin >> temp;
        x[temp / 8] = x[temp / 8] | (maska << 7 - temp % 8); // бит соответствующий числу = 1
    }

    cout << "sorted numbers: ";
    for (int i = 0; i < 64; i++) 
    {
        if (bitset<8>(x[i / 8])[7 - i % 8] == 1) cout << i << " "; // последовательный вывод номеров битов если бит = 1
    }
}
