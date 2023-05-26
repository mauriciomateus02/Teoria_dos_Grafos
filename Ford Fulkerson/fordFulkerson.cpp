#include <bits/stdc++.h>


using namespace std;

struct FFgraph
{
    int V{};
    int E{};
    vector<vector<int>> adj_list;
} typedef FFgraph;

bool bfs(const FFgraph& my_graph, vector<vector<int>> res, int start_v, int destiny_v, int par[]){

    int squeue;
    bool visited[my_graph.V];
    memset(visited, false, sizeof(bool) * my_graph.V);
    visited[start_v] = true;
    queue<int> queue;
    queue.push(start_v);

    while(!queue.empty()){
        squeue = queue.front();
        queue.pop();

        for(int i = 0; i < my_graph.V; i++){
            if(res[squeue][i] > 0 && !visited[i]){
                par[i] = squeue;
                visited[i] = true;
                queue.push(i);
            }
        }
    }

    return visited[destiny_v];
}


int fordFulkerson(FFgraph graph, int start_v, int destiny_v){
    int u, v, maxFlow = 0;
    int *par = new int[graph.V];
    vector<vector<int>> res;
    res.resize(graph.V);

    for(int i = 0; i < graph.V; i++){
        res[i].resize(graph.V);

        for(int j = 0; j < graph.V; j++){
            res[i][j] = graph.adj_list[i][j];
        }
    }

    while(bfs(graph, res, start_v, destiny_v, par)){
        int path = 99999;

        for (v = destiny_v; v != start_v; v = par[v]){
            u = par[v];
            if(res[u][v] < path){
                path = res[u][v];
            }
        }

        for(v = destiny_v; v != start_v; v = par[v]){
            u = par[v];
            res[u][v] -= path;
            res[v][u] += path;
        }
        maxFlow += path;
    }

    return maxFlow;
}
void help()
{
    printf(" > <arquivo> : redireciona a saida para o arquivo\n");
    printf(" < <arquivo> : indica o arquivo que contem o grafo de entrada\n");
}

int main(int argc, char *argv[]) {
    FFgraph myGraph;

    int u, v, weight, start_v, destiny_v,i;

     for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
                help();
    }

    cin >> myGraph.V >> myGraph.E;

    myGraph.adj_list.resize(myGraph.V);

    for (int i = 0; i < myGraph.V; i++) {
        myGraph.adj_list[i].resize(myGraph.V);
    }

    for (int i = 0; i < myGraph.E; i++) {
        cin >> u >> v >> weight;
        myGraph.adj_list[u][v] = weight;
    }
    cin >> start_v >> destiny_v;
    cout << "O fluxo máximo do vetor: "<<start_v <<" para o vetor: "<<destiny_v<< " é: " << fordFulkerson(myGraph, start_v, destiny_v) << "\n";

    return 0;
}
