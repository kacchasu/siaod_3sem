#include <iostream>
#include <bitset>
using namespace std;
int main()
{
    int n;
    cout << "enter amount of numbers: ";
    cin >> n; // ввод количества чисел

    unsigned char x = 0; // создание 8 битовой 00000000
    unsigned char maska = 1; // создание 8 битовой 00000001

    cout << "enter numbers: ";
    for (int i = 0; i < n; i++) // ввод чисел
    {
        int temp;
        cin >> temp; 
        x = x | (maska << 7 - temp); // бит с индексом = числу становится 1
    }

    cout << "sorted numbers: ";
    for (int i = 0; i < 8; i++)
    {
        if (bitset<8>(x)[7 - i] == 1) cout << i << " "; // вывод последовательно номеров битов равных 1
    }
}
