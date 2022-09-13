// bit_sort_1a.cpp : 1a
//

#include <iostream>
using namespace std;

int main()
{
    unsigned char x = 0; // создание 8 битовой переменной 00000000

    cout << (int)x << endl; // вывод х

    unsigned char maska = 1; // создание 8 битовой переменной 00000001
    x = x | (maska << 6); // изменение 7го бита х на 1

    cout << (int)x << endl; // вывод х
}