#include "Hash.h"

bool list::is_empty()
{
    return first == nullptr;
}
void list::push_back(goods product)
{
    Node* p = new Node(product);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
}
void list::print()
{
    cout << "bucket: ";
    if (is_empty()) return;
    Node* p = first;
    while (p) {
        cout << "-------" << endl;
        cout << "product code: " << p->product.code << endl;
        cout << "product title: " << p->product.title << endl;
        cout << "product cost: " << p->product.cost << endl;
        cout << "-------" << endl;
        p = p->next;
    }
    cout << endl;
}
Node* list::find(int _code)
{
    Node* p = first;
    while (p && p->product.code != _code) p = p->next;
    return (p && p->product.code == _code) ? p : nullptr;
}

Node* list::operator[] (const int index)
{
    if (this->is_empty()) return nullptr;
    Node* p = first;
    for (int i = 0; i < index; i++) {
        p = p->next;
        if (!p) return nullptr;
    }
    return p;
}

void list::delete_node(int _code)
{
    int i = 0;
    int target = 0;
    Node* p = first;
    while (p && p->product.code != _code) p = p->next;
    (*this)[i - 1]->next = (*this)[i]->next;
    delete p;
}

int Hash::hash_func(int key)
{
    return key % table.size();
}

void Hash::rehash(int size)
{
    table.assign(size, list());
    for (int i = 0; i < data.size(); i++) {
        table[hash_func(data[i].code)].push_back(data[i]);
        hash_table.insert(make_pair(data[i].code, table[hash_func(data[i].code)]));
    }
    if ((double)(data.size() / table.size()) > 0.75)
        rehash(table.size() * 2);
}

void Hash::update_data(goods product)
{
    data.push_back(product);
}

void Hash::insert(goods product)
{
    table[hash_func(product.code)].push_back(product);
    this->update_data(product);
    hash_table.insert(make_pair(product.code, table[hash_func(product.code)]));
    if ((double)(data.size() / table.size()) > 0.75)
        rehash(table.size() * 2);
}

void Hash::erase(int key)
{
    hash_table.erase(key);
    table[hash_func(key)].delete_node(key);
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].code == key)
            data.erase(data.begin() + i);
    }
}

goods Hash::value(int key)
{
    return hash_table[key].find(key)->product;
}

void Hash::output()
{
    cout << "---- hash table ----" << endl;
    for (int i = 0; i < data.size(); i++)
        if (data[i].code != NULL) {
            goods product = value(data[i].code);
            cout << "---- " << i + 1 << " product ----" << endl;
            cout << "code: " << product.code << endl;
            cout << "title: " << product.title << " | cost: " << product.cost << endl;
        }
    cout << "--------------------" << endl;
}
