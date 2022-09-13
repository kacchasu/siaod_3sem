#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <bitset>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25; 
    const int n = sizeof(int) * 8; // =32 количество разрядов в числе типа int
    unsigned maska = (1 << n - 1); // 1 в старшем бите 32-разрядной сетки
    cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) { // 32 раза по количеству разрядов: 
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1; // смещение 1 в маске на разряд вправо
    }
    cout << endl;
    system("pause");
    return 0;
}
