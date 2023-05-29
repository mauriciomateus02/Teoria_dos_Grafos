#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct FFgraph
{
    int V;
    int E;
    int **adj_list;
} typedef FFgraph;

bool bfs(const FFgraph *my_graph, int **res, int start_v, int destiny_v, int *par)
{
    int squeue;
    bool visited[my_graph->V];
    memset(visited, false, sizeof(bool) * my_graph->V);
    visited[start_v] = true;
    int queue[my_graph->V];
    int front = 0, rear = 0;
    queue[rear++] = start_v;

    while (front != rear)
    {
        squeue = queue[front++];
        for (int i = 0; i < my_graph->V; i++)
        {
            if (res[squeue][i] > 0 && !visited[i])
            {
                par[i] = squeue;
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }

    return visited[destiny_v];
}

int fordFulkerson(FFgraph graph, int start_v, int destiny_v)
{
    int u, v, maxFlow = 0;
    int *par = (int *)malloc(sizeof(int) * graph.V);
    int **res = (int **)malloc(sizeof(int *) * graph.V);
    for (int i = 0; i < graph.V; i++)
    {
        res[i] = (int *)malloc(sizeof(int) * graph.V);
        memcpy(res[i], graph.adj_list[i], sizeof(int) * graph.V);
    }

    while (bfs(&graph, res, start_v, destiny_v, par))
    {
        int path = 99999;

        for (v = destiny_v; v != start_v; v = par[v])
        {
            u = par[v];
            if (res[u][v] < path)
            {
                path = res[u][v];
            }
        }

        for (v = destiny_v; v != start_v; v = par[v])
        {
            u = par[v];
            res[u][v] -= path;
            res[v][u] += path;
        }
        maxFlow += path;
    }

    for (int i = 0; i < graph.V; i++)
    {
        free(res[i]);
    }
    free(res);
    free(par);

    return maxFlow;
}

void MostrarCaminho()
{
}

void help()
{
    printf("\n É nescessario especificar o vertice inicial e o vertice final...\nExemplo de entrada: ./FordFulkerson -f arquivo_teste -i x -u y\n Sendo x e y inteiros quaisquer não colocar letras pelo amor\n");
    printf("-o <arquivo> : redireciona a saida para o arquivo\n-f <arquivo> : indica o arquivo que contem o grafo de entrada\n-i vertice inicial\n-u verticie final\n");
}

int main(int argc, char *argv[])
{
    FFgraph myGraph;

    int u, v, weight, start_v = -1, destiny_v = -1, i;

    FILE *input = NULL;
    FILE *output = NULL;

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
        {
            help();
            return 0;
        }
        else if (!strcmp(argv[i], "-f"))
        {
            if (i < argc - 1)
            {
                input = fopen(argv[i + 1], "r");
                if (input == NULL)
                {
                    printf("Erro no arquivo\n");
                    return 0;
                }
                i++;
            }
            else
            {
                printf("Não foi indicado um arquivo de entrada\n");
                return 0;
            }
        }
        else if (!strcmp(argv[i], "-o"))
        {
            if (i < argc - 1)
            {
                output = fopen(argv[i + 1], "w");
                if (output == NULL)
                {
                    printf("Erro no arquivo de saída.\n");
                    return 0;
                }
                i++;
            }
            else
            {
                printf("Não foi indicado um arquivo de saída.\n");
                return 0;
            }
        }
        else if (!strcmp(argv[i], "-i"))
        {
            i++;
            start_v = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-u"))
        {
            i++;
            destiny_v = atoi(argv[i]);
        }
    }
    if (input != NULL)
        freopen(argv[2], "r", stdin);

    if (output != NULL)
        freopen(argv[4], "w", stdout);

    fscanf(input, "%d %d", &myGraph.V, &myGraph.E);
    myGraph.V = myGraph.V + 1;
    myGraph.adj_list = (int **)malloc(sizeof(int *) * myGraph.V);
    for (int i = 0; i < myGraph.V; i++)
    {
        myGraph.adj_list[i] = (int *)malloc(sizeof(int) * myGraph.V);
        memset(myGraph.adj_list[i], 0, sizeof(int) * myGraph.V);
    }

    for (int i = 0; i < myGraph.E; i++)
    {
        fscanf(input, "%d %d %d", &u, &v, &weight);
        myGraph.adj_list[u][v] = weight;
    }

    if(destiny_v == -1 || start_v == -1)
        fscanf(input, "%d %d", &start_v, &destiny_v);

    if (output != NULL)
        fprintf(output, "O fluxo máximo do vetor: %d para o vetor: %d é: %d\n", start_v, destiny_v, fordFulkerson(myGraph, start_v, destiny_v));
    else
        printf("O fluxo máximo do vetor: %d para o vetor: %d é: %d\n", start_v, destiny_v, fordFulkerson(myGraph, start_v, destiny_v));

    for (int i = 0; i < myGraph.V; i++)
    {
        free(myGraph.adj_list[i]);
    }
    free(myGraph.adj_list);

    if (input != NULL)
        fclose(input);

    if (output != NULL)
        fclose(output);

    return 0;
}