#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct No
{
    int sai;
    int chega;
    int peso;

}typedef No;

int encontra(int index, int no[])
{
    if(index != no[index])
        no[index] = encontra(no[index],no);
    return no[index];
}

void uneEncontrado(int i, int j, int no[])
{
    int xi = encontra(i, no);
    int xj = encontra(j, no);
    no[xi] = xj;
}

int comparaPeso(const void *i, const void *j)
{
    struct No *ir = (struct No *)i;
    struct No *volta = (struct No *)j;

   return (ir->peso - volta->peso);
}

int compararRaiz(const void *i, const void *j)
{
    struct No *ir = (struct No *)i;
    struct No *volta = (struct No *)j;
    if (ir->sai == volta->sai)
    {
        return (ir->chega - volta->chega);
    }
    return (ir->sai - volta->sai);
}

void Kruskal(No vector[], No MST[], int *cont, int numVertices, int numArestas)
{
    int valor[numVertices+1],i,numArestasMst = 0;

    for ( i = 0; i < numVertices; i++)
    {
        valor[i] = i;
    }
    qsort(vector,numArestas,sizeof(No),comparaPeso);

    for(i = 0; i < numArestas; i++)
    {
        int saio = vector[i].sai;
        int chego = vector[i].chega;
        int peso = vector[i].peso;

        if(encontra(saio,valor) != encontra(chego,valor))
        {
            MST[numArestasMst++] = vector[i];
            *cont += vector[i].peso; 
            uneEncontrado(saio,chego,valor);
        }
    }
}

void MostrarCaminho(No vertices[], bool ordem, int numVert, int cost, bool mostrarTela, FILE *out)
{
    int i;
    if (ordem)
    {
        qsort(vertices, numVert - 1, sizeof(No), compararRaiz);
    }

    if (mostrarTela == true)
    {
        for (i = 0; i < numVert - 1; i++)
        {
            printf("(%d,%d) ", vertices[i].sai, vertices[i].chega);
        }

        printf("\n%d\n", cost);
    }
    else
    {
        for (i = 0; i < numVert - 1; i++)
        {
            fprintf(out, "(%d,%d) ", vertices[i].sai, vertices[i].chega);
        }
        fprintf(out, "%d\n", cost);
        fclose(out);
    }
}

void help()
{
    printf("-o <arquivo> : redireciona a saida para o arquivo\n");
    printf("-f <arquivo> : indica o arquivo que contem o grafo de entrada\n");
    printf("-s : mostra a solucao (em ordem crescente)\n");
    printf("-i : vertice inicial\n");
}

int Parametro(int argc, char *argv[], bool *mostrarCmd, bool *ordem, int *iniVertice, FILE **input, FILE **output)
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
        if (strcmp(argv[i], "-s") == 0)
        {
            *ordem = true;
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
    int iniVertice = 1, numVertex, numArestas, x1, x2, peso, cost = 0,i = 0;
    bool ordem = false, mostrarCmd = true;
    FILE *inputFile = NULL, *outputFile = NULL;

    if (Parametro(argc, argv, &mostrarCmd, &ordem, &iniVertice, &inputFile, &outputFile) != 1)
    {
        return 0;
    }

    fscanf(inputFile, "%d %d", &numVertex, &numArestas);

    No vector[numArestas];
    No MST[numVertex-1];

    while (fscanf(inputFile, "%d %d %d", &x1, &x2, &peso) != EOF)
    {
        vector[i++] = (No){x1, x2, peso};
    }
    Kruskal(vector, MST, &cost, numVertex, numArestas);
    MostrarCaminho(MST,ordem,numVertex,cost,mostrarCmd,outputFile);
}