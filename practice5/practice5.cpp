#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// Class to represent a graph
class Graph {
private:
    int V;
    map<pair<string, string> , int> graph; // Map to store graph
    vector<string> vertices; // vector with all vertices
public:
    Graph(int vertices) {
        V = vertices; // No. of vertices
        for (int i = 0; i < V; i++) {
            string tmp;
            cout << "enter " << i + 1 << " vertex: ";
            cin >> tmp;
            this->vertices.push_back(tmp);
        }
    }

    // function to add an edge to graph
    void addEdge(string u, string v, int w) {
        graph[make_pair(u, v)] = w;
    }

    // utility function used to print the solution
    void printArr(map<string, int> dist) {
        cout << "vertex     distance from source" << endl;
        for (auto el : dist)
            cout << left << setw(20) << el.first << el.second << endl;
    }

    // The main function that finds shortest distances from src to
    // all other vertices using Bellman - Ford algorithm. The function
    // also detects negative weight cycle
    void BellmanFord(string src) {
        map<string, int> dist;

        // Step 1: Initialize distances from src to all other vertices
        // as ~inf
        for (string v : vertices)
            dist[v] = 10000000;
        dist[src] = 0;

        // Step 2: Relax all edges |V| - 1 times. A simple shortest
        // path from src to any other vertex can have at-most |V| - 1
        // edges
        for (int i = 0; i < V - 1; i++)
            // Update dist value and parent index of the adjacent vertices of
            // the picked vertex. Consider only those vertices which are still in
            // queue
            for (auto el : graph)
                if (dist[el.first.first] != 10000000 && dist[el.first.first] + el.second < dist[el.first.second])
                    dist[el.first.second] = dist[el.first.first] + el.second;

        // Step 3: check for negative-weight cycles. The above step 
		// guarantees shortest distances if graph doesn't contain 
		// negative weight cycle. If we get a shorter path, then there 
		// is a cycle.
        for (auto el : graph)
            if (dist[el.first.first] != 10000000 && dist[el.first.first] + el.second < dist[el.first.second]) {
                cout << "Graph contains negative weight cycle";
                return;
            }

        // print all distance
        printArr(dist);
    }
};
int main()
{
    cout << "enter amount of vertices: ";
    int n;
    cin >> n;
    Graph* graph = new Graph(n);
    cout << "enter amount of edges: ";
    int n_edges;
    cin >> n_edges;
    for (int i = 0; i < n_edges; i++) {
        cout << "--- entering " << i + 1 << " edge ---" << endl;
        string u, v;
        int w;
        cout << "enter 1st vertex: ";
        cin >> u;
        cout << "enter 2nd vertex: ";
        cin >> v;
        cout << "enter edge weight: ";
        cin >> w;
        graph->addEdge(u, v, w);
    }
    cout << "enter src vertex to use Bellman Ford alg: ";
    string src;
    cin >> src;
    graph->BellmanFord(src);
}