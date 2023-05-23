#include <bits/stdc++.h>
#define PMAX 99999

using namespace std;

int weights[PMAX];
bool visited[PMAX];
vector<pair<int, int>> graph[PMAX];

int my_prim(int n){

    weights[0] = 0;
    for (int i = 1; i < n; i++) {
        weights[i] = PMAX;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;
    pQueue.push({weights[0], 0});

    while(true){
        int current = -1;

        while (!pQueue.empty()){

            int va = pQueue.top().second;
            pQueue.pop();

            if (!visited[va]){
                current = va;
                break;
            }
        }
        if(current == -1){
            break;
        }

        visited[current] = true;

        for (auto & i : graph[current]){

            int dt = i.first;

            int va = i.second;

            if (weights[va] > dt && !visited[va]){
                weights[va] = dt;
                pQueue.push({weights[va], va});
            }
        }
    }

    int result = 0;

    for (int i = 0; i < n; i++) {
        result += weights[i];
        cout << "Começando do vértice "<< i << " : "<< weights[i] << "\n";
    }

    return result;
}

int Prim()
{
    int n, m, u, v, weight;
    cin >> n >> m;

    for (int i = 0; i < m; ++i){

        cin >> u >> v >> weight;

        graph[u].emplace_back(weight, v);
        graph[v].emplace_back(weight, u);
    }
    int r = my_prim(n);
    cout << "total: "<< r << "\n";

    return 0;
}

int main(){
    Prim();
    return 0;
}