/*****************************************************************/
/*   Grafo c/ lista de adjacencias | PROG2 | MIEEC | 2017/18     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

caminho *copia_caminho(grafo *g, caminho c)
{
    caminho *nc = malloc(sizeof(caminho));
    nc->vertices = malloc(sizeof(int) * (g->tamanho + 1));
    memcpy(nc->vertices, c.vertices, sizeof(int) * (g->tamanho + 1));
    nc->peso = c.peso;
    return nc;
}

void apaga_caminho(caminho *c)
{
    free(c->vertices);
    free(c);
}

void imprime_caminho(caminho *c)
{
    int *aux = c->vertices;
    while (*aux != -1)
    {
        printf(" %d", *aux);
        aux++;
    }
    printf("\n");
}

/**
 * @brief devolve o caminho mais longo a partir do último vertice do caminho c
 * 
 * @param g grafo
 * @param c caminho até então
 * @return caminho mais longo que pode encontrar
 */
caminho percorre_grafo(grafo *g, caminho c)
{
    int *curr = c.vertices;
    int key = 0;
    while (*curr != -1)
    {
        key++; // a posição no caminho onde se deve inserir um novo vértice
        curr++;
    }
    int i = 0;
    lista_no *aux = g->adjacencias[c.vertices[key-1]].inicio;
    caminho *caminhos = malloc(sizeof(caminho) * (g->tamanho + 1));
    while (aux != NULL) /* para cada aresta deste nó */
    {
        caminho *nc = copia_caminho(g, c); // copia para o novo caminho o caminho atual
        nc->peso += aux->peso;             // incrementa o peso
        nc->vertices[key] = aux->vertice;  // adiciona um vértice ao caminho
        nc->vertices[key + 1] = -1;
        caminhos[i] = percorre_grafo(g, *nc); // chama-se recursivamente para as arestas deste nó
        i++;
        aux = aux->proximo;
        apaga_caminho(nc);
    }

    if (i == 0) // não há caminhos a sair deste vértice
    {
        free(caminhos);
        int *new_vertices = malloc(sizeof(int) * (g->tamanho + 1));
        memcpy(new_vertices, c.vertices, sizeof(int) * (g->tamanho + 1));
        c.vertices = new_vertices;
        return c; // o caminho mais longo até mim é o próprio caminho que eu recebi.
    }
    else if (i == 1) // só há 1 caminho
    {
        caminho nc;
        nc.vertices = malloc(sizeof(int) * (g->tamanho + 1));
        memcpy(nc.vertices, caminhos[0].vertices, sizeof(int) * (g->tamanho + 1));
        nc.peso = caminhos[0].peso;

        free(caminhos[0].vertices);
        free(caminhos);
        return nc;
    }

    caminhos[i].vertices = NULL;

    long max = -2;
    caminho *cMax = NULL;
    caminho *caux = caminhos;
    while (caux->vertices != NULL)
    {
        if (caux->peso >= max)
        {
            max = caux->peso;
            if (cMax != NULL)
                free(cMax->vertices);
            cMax = caux;
        }
        else
        {
            free(caux->vertices);
            caux->vertices = NULL;
        }
        caux++;
    }
    caminho cret = *cMax;
    free(caminhos);
    return cret;
}

caminho grafo_caminho_mais_longo(grafo *g)
{
    caminho *caminhos = malloc(sizeof(caminho) * (g->tamanho + 1));
    caminhos[g->tamanho].peso = -1; // marca o fim

    for (int origem = 0; origem < g->tamanho; origem++)
    {
        caminho c;
        c.peso = 0;
        c.vertices = malloc(sizeof(int) * (g->tamanho + 1));
        c.vertices[0] = origem;
        c.vertices[1] = -1;
        caminhos[origem] = percorre_grafo(g, c); // c é passado por valor, i.e., é copiado
        free(c.vertices);
    }

    long max = -2;
    caminho *cMax = NULL;
    caminho *aux2 = caminhos;
    while (aux2->peso != -1)
    {
        if (aux2->peso >= max)
        {
            max = aux2->peso;
            if (cMax != NULL)
                free(cMax->vertices);
            cMax = aux2;
        }
        else
        {
            free(aux2->vertices);
            aux2->vertices = NULL;
        }
        aux2++;
    }
    caminho cret = *cMax;
    free(caminhos);
    return cret;
}

/* cria no da lista de adjacencias */
lista_no *cria_no(int v)
{
    lista_no *novo = (lista_no *)malloc(sizeof(lista_no));
    if (!novo)
        return NULL;

    novo->vertice = v;
    novo->proximo = NULL;

    return novo;
}

/* cria grafo com n vertices */
grafo *grafo_novo(int n, tipo_grafo tipo)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    if (g == NULL)
        return NULL;

    g->tamanho = n;
    g->tipo = tipo;

    /* cria array de listas de adjacencias */
    g->adjacencias = (lista_adj *)calloc(n, sizeof(lista_adj));
    if (g->adjacencias == NULL)
    {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->tamanho; i++)
        g->adjacencias[i].inicio = NULL;

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo *g)
{
    if (g == NULL)
        return;

    if (g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
        {
            while (g->adjacencias[v].inicio)
            {
                lista_no *aux = g->adjacencias[v].inicio;
                g->adjacencias[v].inicio = g->adjacencias[v].inicio->proximo;
                free(aux);
            }
        }
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona uma aresta ao grafo*/
void grafo_adiciona(grafo *g, int origem, int dest, unsigned short peso)
{
    lista_no *novo;

    if (g == NULL || grafo_aresta(g, origem, dest) > -1)
        return;

    /* adiciona uma aresta de origem para dest na lista de adjacencias */
    novo = cria_no(dest);
    novo->peso = peso;
    novo->proximo = g->adjacencias[origem].inicio;
    g->adjacencias[origem].inicio = novo;
    g->adjacencias[origem].tamanho++;
    if (g->tipo == NAODIRECIONADO)
    {
        /* adiciona tambem aresta de dest para origem */
        novo = cria_no(origem);
        novo->proximo = g->adjacencias[dest].inicio;
        g->adjacencias[dest].inicio = novo;
        g->adjacencias[dest].tamanho++;
    }
}

/* remove uma aresta do grafo*/
void grafo_remove(grafo *g, int origem, int dest)
{
    lista_no *aux, *prev;

    if (g == NULL || g->adjacencias[origem].inicio == NULL)
        return;

    aux = g->adjacencias[origem].inicio;
    /* caso especial: primeiro no' da lista */
    if (aux->vertice == dest)
    {
        g->adjacencias[origem].inicio = aux->proximo;
        free(aux);
    }
    else
    {
        prev = aux;
        aux = aux->proximo;
        while (aux != NULL)
        {
            if (aux->vertice == dest)
            {
                prev->proximo = aux->proximo;
                free(aux);
                break;
            }
            prev = aux;
            aux = aux->proximo;
        }
    }

    if (g->tipo == NAODIRECIONADO)
    {
        /* remove tambem aresta de dest para origem */
        /* caso especial: primeiro no' da lista */
        aux = g->adjacencias[dest].inicio;
        if (aux->vertice == origem)
        {
            g->adjacencias[dest].inicio = aux->proximo;
            free(aux);
        }
        else
        {
            prev = aux;
            aux = aux->proximo;
            while (aux != NULL)
            {
                if (aux->vertice == origem)
                {
                    prev->proximo = aux->proximo;
                    free(aux);
                    break;
                }
                prev = aux;
                aux = aux->proximo;
            }
        }
    }
}

/* verifica se existe uma aresta entre os vertices origem e dest */
int grafo_aresta(grafo *g, int origem, int dest)
{
    if (g == NULL)
        return -1;

    lista_no *aux = g->adjacencias[origem].inicio;
    while (aux)
    {
        if (aux->vertice == dest)
            return aux->peso;
        aux = aux->proximo;
    }
    return -1;
}

/* imprime as listas de adjacencias do grafo */
void grafo_imprime(grafo *g)
{
    int i;
    for (i = 0; i < g->tamanho; i++)
    {
        lista_no *aux = g->adjacencias[i].inicio;
        printf("%d: ", i);
        if (aux)
        {
            printf("(%d)->%d", aux->peso, aux->vertice);
            aux = aux->proximo;

            while (aux)
            {
                printf("-(%d)->%d", aux->peso, aux->vertice);
                aux = aux->proximo;
            }
        }
        printf("\n");
    }
}

int dfs_helper(grafo *g, int inicio, int fim, int profundidade, int *visitados)
{
    int i, d;

    if (visitados[inicio])
        return 0;

    visitados[inicio] = profundidade;

    if (inicio == fim)
        return profundidade;

    for (i = 0; i < g->tamanho; i++)
    {
        if (grafo_aresta(g, inicio, i))
        {
            d = dfs_helper(g, i, fim, profundidade + 1, visitados);
            if (d)
                return d;
        }
    }
    visitados[inicio] = 0;
    return 0;
}

/* retorna caminho entre origem e dest usando depth-first search (DFS)
   n guarda o tamanho do caminho
   nao garante caminho mais curto */
int *grafo_dfs(grafo *g, int inicio, int fim, int *n)
{
    int *visitados, *caminho;
    int profundidade, i, ret_i;

    if (g == NULL)
        return 0;

    visitados = calloc(g->tamanho, sizeof(int));
    profundidade = dfs_helper(g, inicio, fim, 1, visitados);

    if (profundidade == 0)
    {
        free(visitados);
        *n = 0;
        return NULL;
    }

    /* reconstrucao do caminho */
    caminho = calloc(profundidade, sizeof(int));
    for (ret_i = 0; ret_i < profundidade; ret_i++)
        for (i = 0; i < g->tamanho; i++)
            if (visitados[i] == ret_i + 1)
            {
                caminho[ret_i] = i;
                break;
            }
    *n = profundidade;
    free(visitados);
    return caminho;
}

/* retorna caminho entre origem e dest usando breadth-first search (BFS)
   n guarda o tamanho do caminho
   garante caminho mais curto */
int *grafo_bfs(grafo *g, int inicio, int fim, int *n)
{
    int *caminho = NULL, *visitados, *fila;
    int profundidade, i, j, fila_inicio = 0, fila_fim = 0;

    if (g == NULL)
        return 0;

    visitados = calloc(g->tamanho, sizeof(int));
    fila = calloc(g->tamanho, sizeof(int));

    for (i = 0; i < g->tamanho; i++)
        visitados[i] = -1;

    visitados[inicio] = inicio;
    fila[fila_fim++] = inicio;

    while (fila_inicio != fila_fim)
    {
        i = fila[fila_inicio];
        fila_inicio = (fila_inicio + 1) % g->tamanho;
        for (j = 0; j < g->tamanho; j++)
            if (grafo_aresta(g, i, j) && visitados[j] == -1)
            {
                visitados[j] = i;
                fila[fila_fim] = j;
                fila_fim = (fila_fim + 1) % g->tamanho;
            }
    }

    /* reconstrucao do caminho */
    profundidade = 0;
    if (visitados[fim] >= 0)
    {
        int tmp = fim;
        profundidade = 1;
        while (visitados[tmp] != tmp)
        {
            profundidade++;
            tmp = visitados[tmp];
        }

        caminho = malloc(profundidade * sizeof(int));
        tmp = fim;
        i = 0;
        while (i++ < profundidade)
        {
            caminho[profundidade - i] = tmp;
            tmp = visitados[tmp];
        }
    }

    free(fila);
    free(visitados);

    *n = profundidade;
    return caminho;
}