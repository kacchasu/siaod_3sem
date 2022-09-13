#include <iostream>
#include <bitset>
using namespace std;
int main()
{
    int n; 
    cout << "enter amount of numbers: ";
    cin >> n; // ввод количества чисел

    unsigned long long x = 0; // создание 64 битового числа 0x64
    unsigned long long maska = 1; // создание 64 битового числа 00...01

    cout << "enter numbers: ";
    for (int i = 0; i < n; i++) // ввод н чисел
    {
        int temp;
        cin >> temp;
        x = x | (maska << 63 - temp); // бит по индексу равному числу становится 1
    }
    cout << "unsorted numbers: " << bitset<64>(x) << endl;
    cout << "sorted numbers: ";
    for (int i = 0; i < 64; i++)
    {
        if (bitset<64>(x)[63 - i] == 1) cout << i << " "; // вывод последовательно номеров битов равных 1
    }
}
