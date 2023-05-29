#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge
{
    int src;
    int dest;
    int weight;
} typedef Edge;

int findSet(int v, int set[])
{
    if (set[v] != v)
    {
        set[v] = findSet(set[v], set);
    }
    return set[v];
}

void joinSets(int u, int v, int set[])
{
    int source_u = findSet(u, set);
    int source_v = findSet(v, set);
    set[source_u] = source_v;
}

int compareEdgesSource(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *a2 = (Edge *)b;
    if (a1->src == a2->src)
    {
        return a1->dest - a2->dest;
    }
    return a1->src - a2->src;
}

int compareEdges(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *a2 = (Edge *)b;
    return a1->weight - a2->weight;
}

void printOut(Edge MST[], int cost, int numVertex, int inOrderAGM, int printTerminal, FILE *outputFile)
{
    if (inOrderAGM)
    {
        qsort(MST, numVertex - 1, sizeof(Edge), compareEdgesSource);
    }

    if (printTerminal)
    {
        if (inOrderAGM)
        {
            for (int i = 0; i < numVertex - 1; i++)
            {
                printf("(%d,%d) ", MST[i].src, MST[i].dest);
            }
            printf("\n");
            return;
        }
        printf("%d\n", cost);
    }
    else
    {
        if (inOrderAGM)
        {
            for (int i = 0; i < numVertex - 1; i++)
            {
                fprintf(outputFile, "(%d,%d) ", MST[i].src, MST[i].dest);
            }
            fclose(outputFile);
        }
        else
        {
            fprintf(outputFile, "%d\n", cost);
            fclose(outputFile);
        }
    }
}

void Kruskal(Edge edges[], Edge MST[], int *cost, int numVertex, int numEdges)
{
    int set[numVertex + 1];

    for (int i = 0; i <= numVertex; i++)
    {
        set[i] = i;
    }
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    int numEdgesMST = 0;
    for (int i = 0; i < numEdges; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;

        if (findSet(src, set) != findSet(dest, set))
        {
            MST[numEdgesMST++] = edges[i];
            (*cost) += edges[i].weight;
            joinSets(src, dest, set);
        }
    }
}
void help()
{
    printf("-o <arquivo> : redireciona a saida para o arquivo\n");
    printf("-f <arquivo> : indica o arquivo que contem o grafo de entrada\n");
    printf("-s : mostra a solucao (em ordem crescente)\n");
    printf("-i : vertice inicial\n");
}
int checkArguments(int argc, char *argv[], int *printTerminal, int *inOrderAGM, FILE **inputFile, FILE **outputFILE)
{
    if (argc < 2)
    {
        printf("Por favor use por exemplo: %s -f arquivo-entrada.dat\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help();
            return 1;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            *printTerminal = 0;
            if (i < argc - 1)
            {
                char *fileName = argv[i + 1];
                *outputFILE = fopen(fileName, "w");

                if (*outputFILE == NULL)
                {
                    printf("Erro ao abrir o arquivo %s.\n", fileName);
                    return 1;
                }
                i++;
            }
            else
            {
                printf("Erro: Faltando nome do arquivo de saída depois do argumento -o\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            if (i < argc - 1)
            {
                char *fileName = argv[i + 1];
                *inputFile = fopen(fileName, "r");

                if (*inputFile == NULL)
                {
                    printf("Erro ao abrir o arquivo %s.\n", fileName);
                    return 1;
                }
                i++;
            }
            else
            {
                printf("Erro: Faltando nome do arquivo de entrada depois do argumento -f\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            *inOrderAGM = 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    int numVertex, numEdges, vertex1, vertex2, edgeWeight, cost = 0;
    int inOrderAGM = 0,
        printTerminal = 1;
    FILE *inputFile = NULL, *outputFILE = NULL;

    if (checkArguments(argc, argv, &printTerminal, &inOrderAGM, &inputFile, &outputFILE) != 0)
    {
        return 1;
    }

    fscanf(inputFile, "%d %d", &numVertex, &numEdges);
    Edge edges[numEdges];
    Edge MST[numVertex - 1];

    int i = 0;
    while (fscanf(inputFile, "%d %d %d", &vertex1, &vertex2, &edgeWeight) != EOF)
    {
        edges[i++] = (Edge){vertex1, vertex2, edgeWeight};
    }

    Kruskal(edges, MST, &cost, numVertex, numEdges);
    printOut(MST, cost, numVertex, inOrderAGM, printTerminal, outputFILE);

    fclose(inputFile);
    return 0;
}