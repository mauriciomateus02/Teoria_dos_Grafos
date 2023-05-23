#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> krk;
vector<int> par;

struct KruskalGraph
{
    int V{};
    int E{};
    vector <pair<int, pair <int,int>>> edgeList;
    vector <vector<pair <int,int>>> adjacencyList;
} typedef KruskalGraph;


int fset(int x){
    if(par[x] != x){
        par[x] = fset(par[x]);
    }
    return par[x];
}


void uset(int x, int y){
    if(krk[x] < krk[y]){
        par[x] = y;
    }
    else{
        par[y] = x;

        if(krk[x] == krk[y]){
            krk[x]++;
        }

    }
}


vector <pair<int, pair<int,int>>> kruskal(const vector <pair<int, pair<int,int>>>& edgeList, const vector <vector<pair<int,int>>>& adjacencyList){

    vector <pair<int, pair<int,int>>> sTree;

    for(int v = 0; v < adjacencyList.size(); v++){
        krk[v] = 0;
        par[v] = v;
    }
    for(auto uv : edgeList){
        if(fset(uv.second.second) != fset(uv.second.first)){
            sTree.push_back(uv);
            uset(fset(uv.second.first), fset(uv.second.second));
        }
    }
    return sTree;
}


int Kruskal(){
    int u, v, weight;

    KruskalGraph graph;
    cin >> graph.V >> graph.E;

    graph.adjacencyList.resize(graph.V);
    par.resize(graph.V);
    krk.resize(graph.V);

    for (int i = 0; i < graph.E; ++i){
        cin >> u >> v >> weight;
        graph.adjacencyList[u].push_back(pair<int,int>(v, weight) );
        graph.adjacencyList[v].push_back(pair<int,int>(u, weight) );
        graph.edgeList.emplace_back(weight, pair<int,int>(u, v));
    }

    sort(graph.edgeList.begin(), graph.edgeList.end());
    vector <pair<int, pair<int,int>>> spanningTree = kruskal(graph.edgeList, graph.adjacencyList);

    cout << "\nAs Bordas da Árvore geradora são: \n";
    for(auto & i : spanningTree){
        cout << "("<<i.second.first << ", " << i.second.second <<")\n";
    }

    return 0;
}

int main(){
    Kruskal();
    return 0;
}