#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <algorithm>
#include<climits>
using namespace std;


class Graph {
    vector<vector<pair<int, float>>> adj;

    vector<vector<pair<int, float>>> mst;

    vector<vector<pair<int, float>>> res;

    size_t root;
public:
    Graph(fstream &fin) {
        string line;
        getline(fin, line);
        istringstream iss(line);
        int n, m;
        iss >> n >> m >> root;
        adj.resize(n);

        // 逐行读取数据
        int u, v;
        float weight;
        
        while (getline(fin, line)) {
        istringstream lineStream(line); // 使用字符串流从当前行中读取数据

        // 依次读取整数和浮点数
        if (!(lineStream >> u >> v >> weight)) {
            cout << "数据格式错误。" << endl;
        }

        // 存储数据到 adj 中
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // 因为是无向图，所以要加上反向边
    }

    }// TODO: 读取文件，构造图
    
    /*
    void print(){
        for (int u = 0; u < (int)adj.size(); ++u) {
        // 遍历当前顶点的所有相邻边
        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            float weight = neighbor.second;
            printf("%d, %d, %f\n",u , v, weight);
        }
    }
    }*/

    void writeGraph(fstream &fout) {
        size_t vertex_num = res.size();
        for (size_t i = 0; i < vertex_num; ++i) {
            fout << "{source: '" << i << "', target: '" << i << "', 'rela': '', type: 'resolved'}," << endl;
        }

        for (size_t i = 0; i < vertex_num; ++i) {
            for (size_t j = 0; j < res[i].size(); ++j)
            fout << "{source: '" << i << "', target: '" << res[i][j].first << "', 'rela': '" << res[i][j].second << "', type: 'resolved'}," << endl;
        }
    }

    void saveGraph(const string &filename) {
        fstream fout(filename, ios::out);
        if (!fout) {
            cout << "Failed to open file " << filename << "!" << endl;
            exit(0);
        }
        fstream fh("head.txt", ios::in);
        if (!fh) {
            cout << "Failed to open file head.txt!" << endl;
            exit(0);
        }
        string line;
        while (getline(fh, line)) {
            fout << line << endl;
        }
        fh.close();
        fout << endl << endl << "var links = " << endl << "[" << endl;
        writeGraph(fout);
        fout << endl << "];";

        fstream ft("tail.txt", ios::in);
        if (!ft) {
            cout << "Failed to open file tail.txt!" << endl;
            exit(0);
        }
        while (getline(ft, line)) {
            fout << line << endl;
        }
        ft.close();
        fout.close();
        cout << "Save graph to " << filename << " successfully!" << endl;
    };

    void prim() {
        vector<bool> inMST(adj.size(), false);
        vector<float> lowcost(adj.size(), INT_MAX);
        vector<int> adjvex(adj.size(), -1);

        lowcost[root] = 0; // 从顶点开始

        for (size_t count = 0; count < adj.size() - 1; ++count) {
            size_t u = -1;
            float mincost = INT_MAX;

        // 找到不在MST中且具有最小lowcost值的顶点
            for (size_t v = 0; v < adj.size(); ++v) {
                if (!inMST[v] && lowcost[v]< mincost) {
                    u = v;
                    mincost = lowcost[v];
            }
        }

            inMST[u] = true;

        // 更新与u相邻的顶点的lowcost值
            for (const auto& neighbor : adj[u]) {
                size_t v = neighbor.first;
                float weight = neighbor.second;
                if (!inMST[v] && weight < lowcost[v]) {
                adjvex[v] = u;
                lowcost[v] = weight;
            }
        }
    }

    // 构造MST
    mst.resize(adj.size());
    for (size_t i = 0; i < adj.size(); ++i) {
        if (i == root)
        continue;
        mst[i].push_back(make_pair(adjvex[i], lowcost[i]));
        mst[adjvex[i]].push_back(make_pair(i, lowcost[i]));
    }
        // TODO: Prim算法
    }

    //运用并行集判断是否有环

    // 查找根节点
    int find(vector<int>& parent, int u) {
        if (parent[u] != u)
            parent[u] = find(parent, parent[u]);
        return parent[u];
    }

    // 合并两个集合
    void Union(vector<int>& parent, vector<int>& rank, int u, int v) {
        int uRoot = find(parent, u);
        int vRoot = find(parent, v);

        if (rank[uRoot] < rank[vRoot])
            parent[uRoot] = vRoot;
        else if (rank[uRoot] > rank[vRoot])
            parent[vRoot] = uRoot;
        else {
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
    }

    void kruskal() {
        // 初始化父节点和秩（用于优化Union操作）
        vector<int> parent(adj.size());
        vector<int> rank(adj.size(), 0);
        for (size_t i = 0; i < adj.size(); ++i)
            parent[i] = i;

        // 保存每个顶点已经被访问的情况
        vector<bool> visited(adj.size(), false);

        // 对边按权重排序
        vector<pair<float, pair<int, int>>> edges;
        for (size_t u = 0; u < adj.size(); ++u) {
            visited[u] = true;
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                float weight = neighbor.second;
                if (!visited[v])
                edges.push_back({weight, {u, v}});
            }
        }
        sort(edges.begin(), edges.end());

        mst.resize(adj.size());
        for (auto edge : edges) {
            float weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            
            if (find(parent, u) != find(parent, v)) {
                mst[u].push_back(make_pair(v, weight));
                mst[v].push_back(make_pair(u, weight));
                Union(parent, rank, u, v);
            }
        }
        // TODO: Kruskal算法
    }

    void process_prim() {
        prim(); // 使用Prim算法得到最小生成树

    res.resize(adj.size());
    // 保存每个顶点已经被访问的情况
        vector<bool> visited(adj.size(), false);
    // 遍历最小生成树中的每个顶点
        for (size_t u = 0; u < mst.size(); ++u) {

        visited[u] = true;
        // 遍历当前顶点的所有相邻边
        for (const auto& neighbor : mst[u]) {
            size_t v = neighbor.first;
            float weight = neighbor.second;
            if (!visited[v])
            res[u].push_back(make_pair(v, weight));
        }
    }
        // TODO: 处理图，将 mst 转化为 res
    }

    void process_kruskal() {
        kruskal(); // 使用Prim算法得到最小生成树
        res.resize(adj.size());
    // 保存每个顶点已经被访问的情况
        vector<bool> visited(adj.size(), false);
    // 遍历最小生成树中的每个顶点
        for (size_t u = 0; u < mst.size(); ++u) {

        visited[u] = true;
        // 遍历当前顶点的所有相邻边
        for (const auto& neighbor : mst[u]) {
            size_t v = neighbor.first;
            float weight = neighbor.second;
            if (!visited[v])
            res[u].push_back(make_pair(v, weight));
        }
    }
        // TODO: 处理图，将 mst 转化为 res
    }
};

int main() {
    fstream fin("graph.txt");
    Graph g(fin);
    fin.close();
    //g.print();
    g.process_prim();
    g.saveGraph("graph_prim.html");
    g.process_kruskal();
    g.saveGraph("graph_kruscal.html");
    return 0;
}
