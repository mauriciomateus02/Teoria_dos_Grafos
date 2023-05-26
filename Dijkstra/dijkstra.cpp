#include <bits/stdc++.h>
#include <queue>
#define MAX_DISTANCE 999999999
using namespace std;

int shortestPath(int &n, vector<vector<pair<int, int>>> &graph, vector<int> &distance,
                 vector<bool> &visited, int s, int d)
{

    for (int i = 0; i < n; i++)
    {
        distance[i] = MAX_DISTANCE;
        visited[i] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;

    distance[s] = 0;

    pQueue.push({distance[s], s});

    while (!pQueue.empty())
    {

        int v = pQueue.top().second;
        pQueue.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        for (auto const &next : graph[v])
        {
            int weight = next.first;
            int u = next.second;

            if (distance[u] > distance[v] + weight)
            {

                distance[u] = distance[v] + weight;
                pQueue.push({distance[u], u});
            }
        }
    }
    if (d != s && distance[d] == 0)
        return -1;
    return distance[d];
}

void dijkstra(vector<vector<pair<int, int>>> &graph, int m, int n, int value)
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

    for (int i = 1; i <= n; i++)
    {
        cout << i << ":" << shortestPath(n, graph, distance, visited, value, i)<<" ";
    }
    cout << "\n";
}
void help()
{
    printf(" > <arquivo> : redireciona a saida para o arquivo\n");
    printf(" < <arquivo> : indica o arquivo que contem o grafo de entrada\n");
    printf("-i : vertice inicial\n");
}

int main(int argc, char *argv[])
{

    int value = 0, i, n, m;
    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
                help();
        if (!strcmp(argv[i], "-i"))
                value = atoi(argv[i + 1]);
    }

    cin >> n >> m;
    vector<vector<pair<int, int>>> graph;
    graph.resize(n);
    if(value > 0)
        dijkstra(graph, m, n,value);
    else
        dijkstra(graph, m, n,1);
    return 0;
}
