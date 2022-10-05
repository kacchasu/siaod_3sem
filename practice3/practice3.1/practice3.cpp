#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int count(string a, string b) {
    int mn = min(a.size(), b.size());
    int mx = max(a.size(), b.size());
    int d = mx - mn; // разница в длине слов

    int cnt = 0;
    for (int i = 0; i < mn; i++) // проход по общей длине и подсчет разниц в позициях
    {   
        if (tolower(a[i]) != tolower(b[i])) cnt++;
    }
    return cnt + d; // возврат результата
}
int main()
{
    string sentence;
    getline(cin, sentence);
    // удаляем запятые
    while (sentence.find(",") != string::npos) {
        sentence.replace(sentence.find(","), 1, " ");
    }
    // удаляем двойные пробелы
    while (sentence.find("  ") != string::npos) {
        sentence.replace(sentence.find("  "), 2, " ");
    }
    vector<string> words; // массив слов
    vector<string> ans; // массив для ответа
    int min = 100000; // минимальное расстояние
    string word;
    istringstream ss(sentence);

    while (ss >> word) // заполнение массива слов
        words.push_back(word);

    for (int i = 0; i < words.size() - 1; i++) // перебор всех пар
        for (int j = i + 1; j < words.size(); j++) { 
            if (count(words[i], words[j]) < min) { // обновление в случае нового минимума
                min = count(words[i], words[j]);
                ans.clear();
                ans.push_back(words[i] + " and " + words[j]);
            }
            else if (count(words[i], words[j]) == min) // новая пара
                ans.push_back(words[i] + " and " + words[j]);
        }

    cout << "min distance is: " << min << endl;
    // вывод ответа
    for (string s : ans)
        cout << s << endl;
}
