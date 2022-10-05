#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

set<char> o; // алфавит
int m; // длина шаблона
int n; // длина строки

set<char> get_alph(string y) {
    // получаем алфавит из строки
    set<char> alph;
    for (char a : y)
        alph.insert(a);
    return alph;
}

vector<int> preBmBc(string x) {
    vector<int> table(o.size());
    // заполняем значением по умолчанию, равным длине шаблона
    for (int i = 0; i < o.size(); i++)
        table[i] = m;

    // Вычисление функции по определению
    for (int i = 0; i < m - 1; i++)
        if (find(o.begin(), o.end(), x[i]) != o.end())
            table[distance(o.begin(), find(o.begin(), o.end(), x[i]))] = m - i - 1;

    return table;
}


vector<int> preBmGs(string x) {
    // таблица для сдвигов хорошего суффикса
    vector<int> table(m);
    reverse(x.begin(), x.end());
    vector<int> z(m, 0); // z-функция для суффиксов

    int l = 0, r = 1;
    // in the middle of the night in my dreams
    // you should see the things we do baby
    for (int i = 1; i < m; i++) {
        // эффективный расчет z-функции
        if (i < r)
            z[i] = min(z[i - l], r - i); 
        while (i + z[i] < m && x[i + z[i]] == x[z[i]]) 
            z[i] += 1;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }

        // вычисляем максимальный сдвиг на основе значения z-функции для текущего элемента
        // если он нулевой, то он становится равен расстоянию от начала
        if (table[z[i]] == 0)
            table[z[i]] = i;
    }
 
    table.push_back(m - 1); // добавляем нулевой элемент равный периоду шаблона
                        // шаблона на случай полного совпадения

    reverse(table.begin(), table.end());
    return table;
}

void TBM(string x, string y)
{
    int i, j, u, shift, v, turbo_shift;

    // предварительные вычисления таблиц сдвигов bad char и good suffix
    vector<int> bm_gs = { preBmGs(x) };
    vector<int> bm_bc = { preBmBc(x) };

    if (m == 1) bm_gs[0] = 1; // на случай подстроки длины 1

    i = u = 0;
    shift = m;
    while (i <= n - m) {
        j = m - 1;
        while (j >= 0 && x[j] == y[i + j]) { // справа налево сравниваем буквы
            --j; // совпали - сравниваем дальше
            if (u != 0 && j == m - 1 - shift)
                j -= u; // перепрыгиваем через запомненный сегмент
        }
        if (j < 0) { // полное совпадение
            cout << i << endl;
            shift = bm_gs[0]; // устанавливаем максимальный сдвиг на длину шаблона
            u = m - shift; 
        }
        else {
            v = m - 1 - j; // текущая подстрока
            turbo_shift = u - v; // значение турбосдвига
            // значение сдвига плохого символа
            int bc_shift = bm_bc[distance(o.begin(), find(o.begin(), o.end(), y[i + j]))] - m + j + 1;
            shift = max(turbo_shift, bc_shift);
            shift = max(shift, bm_gs[j + 1]);
            // если сдвиг хорошего суффикса не меньше турбосдвига и сдвига плохого символа
            // то запоминаем длину суффикса u на этой попытке
            if (shift == bm_gs[j + 1])
                u = min(m - shift, v);
            else {
            // если турбосдвиг меньше сдвига плохого символа
            // то сдвиг не может быть больше чем длина сегмента текста прошлого шага
                if (turbo_shift < bc_shift)
                    shift = max(shift, u + 1);
                u = 0;
            }
        }
        i += shift; // сдвигаем шаблон вправо
    }
}
int main()
{
    string x, y;
    cout << "enter template: ";
    getline(cin, x);
    cout << "enter text: ";
    getline(cin, y);
    o = get_alph(y);
    m = x.length();
    n = y.length();

    TBM(x, y);
}
