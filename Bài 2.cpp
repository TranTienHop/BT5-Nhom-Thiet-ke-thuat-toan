
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Ham BFS tim duong tang luong
bool BFS(vector<vector<int>>& rGraph, int s, int t,
         vector<int>& parent) {
    int n = rGraph.size();

    vector<bool> visited(n, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);

                if (v == t)
                    return true;
            }
        }
    }

    return false;
}

// Thuat toan Ford-Fulkerson
int Ford_Fulkerson(vector<vector<int>>& graph,
                   int s, int t) {
    int n = graph.size();

    // Khoi tao do thi du
    vector<vector<int>> rGraph = graph;

    vector<int> parent(n);

    int maxFlow = 0;
    int step = 0;

    // Lap cho den khi khong con duong tang
    while (BFS(rGraph, s, t, parent)) {
        step++;

        // Tim bottleneck
        int pathFlow = INF;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        // Truy vet duong tang
        vector<int> path;

        for (int v = t; v != s; v = parent[v]) {
            path.push_back(v);
        }

        path.push_back(s);
        reverse(path.begin(), path.end());

        cout << "\n========== BUOC "
             << step << " ==========\n";

        cout << "Duong tang luong: ";

        for (int i = 0; i < path.size(); i++) {
            cout << path[i];

            if (i < path.size() - 1)
                cout << " -> ";
        }

        cout << "\nLuong tang them (Bottleneck): "
             << pathFlow << endl;

        // Cap nhat do thi du
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];

            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        // Cap nhat tong luong
        maxFlow += pathFlow;

        cout << "Tong luong hien tai: "
             << maxFlow << endl;
    }

    cout << "\nKhong con duong tang luong!\n";

    return maxFlow;
}

int main() {
    int n, m;
    int s, t;

    // Nhap so dinh va so canh
    cout << "Nhap so dinh: ";
    cin >> n;

    cout << "Nhap so canh: ";
    cin >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    // Nhap danh sach canh
    cout << "\nNhap cac canh (u v c):\n";

    for (int i = 0; i < m; i++) {
        int u, v, c;

        cin >> u >> v >> c;

        if (u < 0 || u >= n || v < 0 || v >= n ||
            c < 0) {
            cout << "Du lieu canh khong hop le!\n";
            return 0;
        }

        graph[u][v] += c;
    }

    // Nhap dinh nguon va dinh dich
    cout << "\nNhap dinh nguon s: ";
    cin >> s;

    cout << "Nhap dinh dich t: ";
    cin >> t;

    if (s < 0 || s >= n || t < 0 || t >= n || s == t) {
        cout << "Dinh nguon hoac dinh dich khong hop le!\n";
        return 0;
    }

    // Hien thi thong tin
    cout << "\n================================\n";
    cout << "DINH NGUON: " << s << endl;
    cout << "DINH DICH: " << t << endl;
    cout << "================================\n";

    // Chay thuat toan
    int maxFlow = Ford_Fulkerson(graph, s, t);

    // In ket qua
    cout << "\n================================\n";
    cout << "LUONG CUC DAI = " << maxFlow << endl;
    cout << "================================\n";

    return 0;
}

