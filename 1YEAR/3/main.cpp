#include <iostream>
#include <queue>
#include <limits>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

struct Graph {
    int nvertices;
    int *m;
    int *visited;
    vector<int> d;

    Graph(int n) : nvertices(n), m(new int[n * n]), visited(new int[n]), d(vector<int>(n, numeric_limits<int>::max())) {
        graph_clear();
    }

    void graph_clear() {
        for (int i = 0; i < nvertices; ++i) {
            visited[i] = 0;
            for (int j = 0; j < nvertices; ++j) {
                m[i * nvertices + j] = 0;
            }
        }
    }

    ~Graph() {
        delete[] m;
        delete[] visited;
    }

    void addEdge(int v1, int v2) {
        m[(v1-1) * nvertices + (v2-1)] = 1;
        m[(v2-1) * nvertices + (v1-1)] = 1;
    }

};

void Show(Graph& G) {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < G.nvertices; ++i) {
        for (int j = 0; j < G.nvertices; ++j) {
            cout << G.m[i * G.nvertices + j] << " ";
        }
        cout << endl;
    }
}

void AutoFill(Graph& G){
    for(int i = 0; i < G.nvertices; i++){
        for(int j = 0; j < G.nvertices; j++){
            if(i != j)
                G.addEdge((i+1), (j+1));
        }
    }
}

void AutoFillR(Graph& G, int vertices) {
    int rows = sqrt(vertices);
    int cols = rows;

    for(int i = 0; i < vertices; ++i) {
        int row = i / cols;
        int col = i % cols;

        if(row > 0) G.addEdge(i+1, i-cols+1);
        if(row < rows-1) G.addEdge(i+1, i+cols+1);
        if(col > 0) G.addEdge(i+1, i-1+1);
        if(col < cols-1) G.addEdge(i+1, i+1+1);
    }
}




void Dijkstra(Graph& G, int source) {
    source -=1;
    G.d[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (G.visited[u]) continue;

        G.visited[u] = 1;

        for (int v = 0; v < G.nvertices; ++v) {
            if (G.m[u * G.nvertices + v] && !G.visited[v] && G.d[u] + 1 < G.d[v]) {
                G.d[v] = G.d[u] + 1;
                pq.push({G.d[v], v});
            }
        }
    }

    cout << "Shortest distances from vertex " << source + 1 << ":" << endl;
    for (int i = 0; i < G.nvertices; ++i) {
        cout << "Vertex " << i + 1 << ": " << G.d[i] << endl;
    }
}

void FirstExp(){
    int vertices = 20;
    Graph GS(vertices);

    AutoFill(GS);
    Show(GS);

    Dijkstra(GS, 1);
}

void SecondExp(){
    int vertices = 10000;
    Graph GR(vertices);

    AutoFillR(GR, vertices);
    // Show(GR);

    Dijkstra(GR, 1);

}
int main() {

    high_resolution_clock::time_point start, end;

    start = high_resolution_clock::now();

    SecondExp();
    // FirstExp();

    end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start).count();

    cout << "Time taken by program is: " << duration << " nanoseconds or " << (duration/1000000000.0) << " seconds" << endl;

    return 0;
}