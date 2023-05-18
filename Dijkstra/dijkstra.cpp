#include <bits/stdc++.h>
#include <queue>
#define MAX_DISTANCE 999999999
using namespace std;


int shortestPath(int &n, vector<vector<pair<int, int>>> &graph, vector<int> &distance,
                 vector<bool> &visited, int s, int d){

    for (int i = 0; i < n; i++){
        distance[i] = MAX_DISTANCE;
        visited[i] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;

    distance[s] = 0;

    pQueue.push({distance[s], s});

    while (!pQueue.empty()){

        int v = pQueue.top().second;
        pQueue.pop();

        if (visited[v]) continue;
        visited[v] = true;

        for (auto const &next : graph[v]){
            int weight = next.first;
            int u = next.second;

            if (distance[u] > distance[v] + weight){

                distance[u] = distance[v] + weight;
                pQueue.push({distance[u], u});
            }
        }
    }

    return distance[d];
}


void dijkstra(vector<vector<pair<int, int>>> &graph, int m, int n)
{
    int u, v, weight, initial_vector, final_vector;
    vector<int> distance;
    vector<bool> visited;
    visited.resize(n);
    distance.resize(n);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> weight;
        graph[u].push_back({weight, v});
        graph[v].push_back({weight, u});
    }

    cin >> initial_vector >> final_vector;

    cout << "A menor distancia entre os vértices: " << initial_vector <<" e " << final_vector<< " é " << shortestPath(n, graph, distance, visited, initial_vector, final_vector) << "\n";

}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph;
    graph.resize(n);

    dijkstra(graph, m, n);
    return 0;
}
