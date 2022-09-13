#ifndef __HASH_H__
#define __HASH_H__
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/* 
	key = 6-digits number
	value = pair<title, cost>
	collision match = chain list
*/
struct goods
{
	int code;
	string title;
	int cost;
	goods(int _code = NULL, string _title = "no such a product", int _cost = NULL) : code(_code), title(_title), cost(_cost) {};
};

struct Node
{
	goods product;
	Node* next;
	Node(goods _product) : product(_product), next(nullptr) {};
};

struct list
{
    Node* first;
    Node* last;
    list() : first(nullptr), last(nullptr) {};
    bool is_empty();
	void push_back(goods product);
	void print();
	Node* find(int _code);
	Node* operator[](const int index);
	void delete_node(int code);
};

class Hash
{
	map<int, list> hash_table;
	vector<goods> data; // important data storage
	vector<list> table; // buckets
public:
	int hash_func(int key);
	void rehash(int size);
	void update_data(goods product);
	void insert(goods product);
	void erase(int key);
	goods value(int key);
	void output();
};
#endif