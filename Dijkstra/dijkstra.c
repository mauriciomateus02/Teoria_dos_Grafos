#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct No
{
    int vertice;
    int distancia;
    struct No *prox;

} typedef No;

No *searchMinDistance(No *distancias[], bool visitados[], int numVertices)
{
    int valueMin = 99999, i;
    No *agora = NULL;

    for (i = 0; i < numVertices; i++)
    {
        if (distancias[i] != NULL && distancias[i]->distancia < valueMin && visitados[i] == false)
        {
            valueMin = distancias[i]->distancia;
            agora = distancias[i];
        }
    }
    return agora;
}

void MostrarCaminho(No *distancia[], int numVertice, bool mostrarCmd, FILE *out)
{
    int i;
    if (mostrarCmd == true)
    {
        for (i = 1; i < numVertice; i++)
        {

            if (distancia[i] == NULL || distancia[i]->distancia == 99999)
            {
                printf("%d:-1 ", i);
            }
            else
            {
                printf("%d:%d ", i, distancia[i]->distancia);
            }
        }
        printf("\n");
    }
    else
    {
        for (i = 1; i < numVertice; i++)
        {
            if(distancia[i] == NULL)
                fprintf(out, "(%d:-1) ",i);
            else
                fprintf(out, "(%d:%d) ",i, distancia[i]->distancia);
        }
        fprintf(out,"\n");
        fclose(out);
    }
}

void Dijkstra(int numVertex, int grafo[][numVertex], int inicio, bool mostrarCmd, FILE *out)
{
    int i, j;
    No *distancia[numVertex];
    bool visited[numVertex];
    for (int i = 0; i < numVertex; i++)
    {
        distancia[i] = NULL;
        visited[i] = 0;
    }
    distancia[inicio] = (No *)malloc(sizeof(No));
    distancia[inicio]->vertice = inicio;
    distancia[inicio]->distancia = 0;
    distancia[inicio]->prox = NULL;

    for (i = 0; i < numVertex - 1; i++)
    {
        No *atual = searchMinDistance(distancia, visited, numVertex);
        visited[atual->vertice] = 1;

        for (j = 0; j < numVertex; j++)
        {

            if (grafo[atual->vertice][j] != 0 && visited[j] == 0)
            {
                int newDistance = atual->distancia + grafo[atual->vertice][j];
                if (distancia[j] == NULL)
                {
                    distancia[j] = (No *)malloc(sizeof(No));
                    distancia[j]->vertice = j;
                    distancia[j]->distancia = newDistance;
                    distancia[j]->prox = NULL;
                }
                else if (newDistance < distancia[j]->distancia)
                {
                    distancia[j]->distancia = newDistance;
                }
            }
        }
    }
    MostrarCaminho(distancia,numVertex,mostrarCmd,out);
}

void help()
{
    printf("-o <arquivo> : redireciona a saida para o arquivo\n");
    printf("-f <arquivo> : indica o arquivo que contem o grafo de entrada\n");
    printf("-s : mostra a solucao (em ordem crescente)\n");
    printf("-i : vertice inicial\n");
}

int Parametro(int argc, char *argv[], bool *mostrarCmd, int *iniVertice, FILE **input, FILE **output)
{
    int i;
    if (argc < 2)
    {
        printf("precione -h para saber infromacoes\n");
        return 0;
    }

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help();
            return 0;
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            *mostrarCmd = false;
            if (i < argc - 1)
            {
                char *nome = argv[i + 1];
                *output = fopen(nome, "w");
                if (*output == NULL)
                {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                i++;
            }
            else
            {
                printf("falta o arquivo\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-f") == 0)
        {
            if (i < argc - 1)
            {
                char *nome = argv[i + 1];
                *input = fopen(nome, "r");
                if (*input == NULL)
                {
                    printf("Erro ao abrir o arquivo\n");
                    return 0;
                }
                i++;
            }
            else
            {
                printf("Falta o arquivo de entrada\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-i") == 0)
        {
            if (i < argc - 1)
            {
                *iniVertice = atoi(argv[i + 1]);
                i++;
            }
            else
            {
                printf("Falta valor inteiro\n");
                return 0;
            }
        }
    }
    return 1;
}
int main(int argc, char *argv[])
{
    int iniVertice = 1, numVertex, numArestas, x1, x2, peso, cost = 0;
    bool mostrarCmd = true;
    FILE *inputFile = NULL, *outputFile = NULL;

    if (Parametro(argc, argv, &mostrarCmd, &iniVertice, &inputFile, &outputFile) != 1)
    {
        return 0;
    }

    fscanf(inputFile, "%d %d", &numVertex, &numArestas);
    int grafo[numVertex + 1][numVertex + 1];
    memset(grafo, 0, sizeof(grafo));

    while (fscanf(inputFile, "%d %d %d", &x1, &x2, &peso) != EOF)
    {
        grafo[x1][x2] = peso;
        grafo[x2][x1] = peso;
    }

    Dijkstra(numVertex + 1, grafo, iniVertice,mostrarCmd,outputFile);

    fclose(inputFile);
    return 0;
}