#include <iostream>
using namespace std;

int main()
{
    unsigned char x = 255; // создание 8 битовой переменной 11111111

    cout << (int)x << endl; // вывод ее значения

    unsigned char maska = 1; // создание 8 битовой переменной 00000001
    x = x & (~(maska << 4)); // изменение 5го бита х на 0

    cout << (int)x << endl; //вывод измененной х
}
