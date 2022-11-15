#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
static map<char, string> alpCode;
static map<string, char> alpDecode;
// nodes for tree
struct Node {
    string key; // node value
    // pointers for neighbors
    Node* left;
    Node* right;
    Node* parent;
    // constructor with key as arg
    Node(string key) : key(key), left(NULL), right(NULL), parent(NULL) {};
};

Node* ShannonFanoTree = new Node("");

// function for search all letters code
void ShannonFanoCode(char branch, string full_branch, int start_pos, int end_pos, vector<pair<char, int> > a, Node* current) {
    if (branch == '0')
    {
        string s;
        s = branch;
        current->left = new Node(s);
        current = current->left;
    }
    else if (branch == '1')
    {
        string s;
        s = branch;
        current->right = new Node(s);
        current = current->right;
    }
    double dS; // average array value
    int i, m, S; // m - middle letter, S - summ of numbers in left branch
    string c_branch; // current history
    c_branch = full_branch + branch;
    //cout << "middle-check: \"" << a[start_pos].first << "\" = " << c_branch << endl;
    // exit criteria
    if (start_pos == end_pos) {
        alpCode[a[start_pos].first] = c_branch;
        alpDecode.insert(make_pair(c_branch, a[start_pos].first));
        cout << "\"" << a[start_pos].first << "\" = " << c_branch << endl;
        return;
    }
    dS = 0;
    // counting frequency
    for (i = start_pos; i < end_pos; i++) dS += a[i].second;
    dS = dS / 2;

    // search for middle
    S = 0;
    i = start_pos;
    m = i;
    while (S + a[i].second < dS && i < end_pos) {
        S += a[i].second;
        i++;
        m++;
    }
    // start recursion in left and right branches
    ShannonFanoCode('0', c_branch, start_pos, m, a, current);
    ShannonFanoCode('1', c_branch, m + 1, end_pos, a, current);
}
void ShannonFanoDecode(string code, string s, Node* current) {
    if (s.length() == 0)
    {
        cout << alpDecode['\0' + code] << endl;
        return;
    }
    else if (s[0] == '0' && current->left)
        ShannonFanoDecode(code + "0", s.substr(1), current->left);
    else if (s[0] == '1' && current->right)
        ShannonFanoDecode(code + "1", s.substr(1), current->right);
    else if (s[0] == '0' || s[0] == '1')
    {
        cout << alpDecode['\0' + code];
        ShannonFanoDecode("", s, ShannonFanoTree);
    }
    else ShannonFanoDecode(code, s.substr(1), current);
}
vector<pair<char, int> > makeA(string s) {
    map<char, int> a;
    vector<pair<char, int> > b;
    int i;
    for (i = 0; i < s.length(); i++) {
        if (a.count(s[i]) == 0) a[s[i]] = 1;
        else a[s[i]]++;
    }
    copy(a.begin(), a.end(), back_inserter(b));
    sort(b.begin(), b.end(), [](pair<char, int> a, pair<char, int> b) {return a.second > b.second; });
    return b;
}
void printA(vector<pair<char, int> > a) {
    int i;
    for (i = 0; i < a.size(); i++) cout << "\"" << a[i].first << "\" = " << a[i].second << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");
    string s = "кони-кони, коникони, мы сидели на балконе, чай пили, воду пили, по-турецки говорили.";
    vector<pair<char, int> > a = makeA(s);
    //    printA(a);
    ShannonFanoCode(NULL, "", 0, a.size() - 1, a, ShannonFanoTree);
    cout << "shannon-fano code: ";
    string sCode;
    for (char c : s) {
        sCode += alpCode[c].substr(1);
        cout << alpCode[c];
    }
    cout << endl;
    cout << "before compression: " << s.length() * 8 << " bits" << endl;
    cout << "after compression: " << sCode.length() << " bits" << endl;
    cout << "compression ratio: " << (double)sCode.length() / (s.length() * 8) << endl;
    cout << "shannon-fano decode: ";
    ShannonFanoDecode("", sCode, ShannonFanoTree);
    return 0;
}
