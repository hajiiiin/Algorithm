#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

struct Edge {
    int u, v, weight;
};

// 대표 원소 찾기
int findParent(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = findParent(parent, parent[v]);
}

void unionVertices(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    // 사이클이 있는지 확인
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main() {
    // 간선 정의
    vector<Edge> edges = {
        {0, 1, 8}, {0, 3, 2}, {1, 2, 1}, {1, 3, 4}, {1, 5, 2},
        {2, 5, 1}, {3, 4, 3}, {3, 5, 7}, {4, 5, 9}
    };

    int vertices = 6; //a:0, b:1, c:2, d:3, e:4, f:5

    auto start = high_resolution_clock::now();

    // 간선 기준으로 정렬
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });

    vector<int> parent(vertices);
    vector<int> rank(vertices, 0);
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
    }

    vector<Edge> mst;

    for (const auto& edge : edges) {
        if (findParent(parent, edge.u) != findParent(parent, edge.v)) {
            unionVertices(parent, rank, edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // 트리 출력
    cout << "Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")" << endl;
    }

    // running time 출력
    cout << "Running time: " << duration.count() << " ms" << endl;
   
    return 0;
}
