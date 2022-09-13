#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
#include <ctime>
#include <set>
#include <algorithm>
#include <random>
using namespace std;
int main()
{
    vector<int> numbersr; // создание массива случайных неповторяющихся чисел
    ofstream numbers_in("bit_sort3a.txt"); // открытие файла на его заполнение значениями
    vector<bool> x(10000000, false);
    for (int i = 1000000; i < x.size(); i++)// заполнение числами массива
       numbersr.push_back(i);
    
    // перемешиваем массив
    random_device rd;
    mt19937 g(rd());
    shuffle(numbersr.begin(), numbersr.end(), g);

    for (int i = 1000000; i < numbersr.size(); i++) // ввод случайных неповторяющихся чисел в файл
        numbers_in << numbersr[i] << " ";

    numbers_in.close(); // закрытие файла

    ifstream numbers("bit_sort3a.txt"); // открываем файл на чтение
    // инициализируем битовый массив и сортируем

    double start = clock(); // начинаем отсчет времени

    int temp; 
    while (numbers >> temp)
        x[temp] = 1;

    double end = clock(); // заканчиваем отсчет времени 
    double time = (end - start) / CLOCKS_PER_SEC; // подсчитываем в секундах время

    numbers.close(); // закрываем файл

    ofstream numbers_out("bit_sort3a.txt"); // открываем файл на запись
    
    for (int i = 1000000; i < x.size(); i++) // проходимся по всем битам в массиве
        if (x[i] == 1) // если бит единичный записываем в файл его номер
            numbers_out << i << " ";

    cout << "runtime: " << time << " seconds" << endl;

    // определяем и выводим ОЗУ выделенной под битовый массив
    cout << "RAM allocated for bit array: " << x.capacity() / (1024 * 1024 * 8)  << " mb";
}
