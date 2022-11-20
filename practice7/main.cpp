#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > makeA(vector<int> w, vector<int> p, int n, int W) {
    vector<vector<int> > A(n + 1, vector<int>(W + 1, 0)); // first row is (0), first column is (0)
    for (int k = 1; k <= n; k++) {
        for (int s = 1; s <= W; s++) { // iterate over for each k all capacities
            if (s >= w[k]) // check if the weight of the item is less (equal) than the capacity
                A[k][s] = max(A[k-1][s], A[k-1][s-w[k]] + p[k]); // if it is, then we can either take it or not
            else
                A[k][s] = A[k-1][s]; // if it is not, then we cannot take it
        }
    }
    return A;
}

vector<int> findAns(vector<vector<int> > A, vector<int> w, int k, int s) {
    vector<int> ans;
    if (A[k][s] == 0) // if the value is 0, then we cannot take anything
        return ans;
    if (A[k-1][s] == A[k][s]) // if the value is the same as the value of the previous row, then we cannot take the item
        ans = findAns(A, w, k-1, s);
    else {
        ans = findAns(A, w, k-1, s-w[k]); // if the value is different, then we can take the item
        ans.push_back(k); // add the item to the answer
    }
}
int main() {
    cout << "Enter the number of items:";
    int n;
    cin >> n;
    vector<int> w(n+1), p(n+1);
    cout << "Enter the weights and profits of the items\n";
    for (int i = 1; i <= n; i++) {
        cout << "Item " << i << ":";
        cin >> w[i] >> p[i];
    }
    cout << "Enter the capacity:";
    int s;
    cin >> s;
    cout << endl;
    vector<vector<int> > A = makeA(w, p, n, s);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= s; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    vector<int> ans = findAns(A, w, n, s);
    cout << "The items that can be taken are: ";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}
