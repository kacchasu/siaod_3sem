#include "Hash.h"
#include <iostream>
using namespace std;

int GetRandomNumber(int min, int max)
{
    unsigned rand_gen = rand();
    srand(rand_gen);
    return min + rand() % (max - min + 1);
}

int main()
{
    Hash ans;
    string command;
    cout << "choose input way: keyboard/random" << endl;
    while(getline(cin, command)) {
        if (command == "random") {
            int amount;
            cout << "enter amount of random products to fill: ";
            cin >> amount;
            for (int i = 0; i < amount; i++) {
                ans.update_data(goods(GetRandomNumber(100000, 999999), "random_" + to_string(i), GetRandomNumber(0, 100000)));
            }
            break;
        }
        else if (command == "keyboard") {
            cout << "enter amount of goods: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int code;
                cout << "enter " << i + 1 << " product code: ";
                cin >> code;
                string title;
                cout << "enter " << i + 1 << " product title: ";
                cin >> title;
                int cost;
                cout << "enter " << i + 1 << " product cost: ";
                cin >> cost;
                ans.update_data(goods(code, title, cost));
            }
            break;
        }
        else
            cout << "wrong input tipe. try again" << endl;
    }
    ans.rehash(3);
    ans.output();
    cout << "list of commands" << endl;
    cout << "-----------" << endl;
    cout << "/insert - adding new product" << endl;
    cout << "/erase - deleting product" << endl;
    cout << "/value - searching value by key" << endl;
    cout << "/output - display hash table" << endl;
    cout << "/end - ending programm" << endl;
    cout << "-----------" << endl;
    getline(cin, command);
    cout << "-> enter next command: ";
    while (getline(cin, command)) {
        if (command == "/insert") {
            cout << "-----------" << endl;
            int code;
            cout << "enter product code: ";
            cin >> code;
            string title;
            cout << "enter product title: ";
            cin >> title;
            int cost;
            cout << "enter product cost: ";
            cin >> cost;
            cout << "-----------" << endl;
            ans.insert(goods(code, title, cost));
            getline(cin, command);
            cout << "-> enter next command: ";
        }
        else if (command == "/erase") {
            int code;
            cout << "-----------" << endl;
            cout << "enter product code: ";
            cin >> code;
            ans.erase(code);
            cout << "-----------" << endl;
            getline(cin, command);
            cout << "-> enter next command: ";
        }
        else if (command == "/value") {
            int code;
            cout << "-----------" << endl;
            cout << "enter product code: ";
            cin >> code;
            goods product = ans.value(code);
            cout << "code: " << product.code << endl;
            cout << "title: " << product.title << " | cost: " << product.cost << endl;
            cout << "-----------" << endl;
            getline(cin, command);
            cout << "-> enter next command: ";
        }
        else if (command == "/output") {
            ans.output();
            cout << "-> enter next command: ";
        }
        else if (command == "/end") {
            cout << "-----------" << endl;
            cout << "programm ended", exit(0);
        }
        else {
            cout << "-----------" << endl;
            cout << "wrong command" << endl;
            cout << "-----------" << endl;
            cout << "-> enter next command: ";
        }
    }
    return 0;
}