/*****************************************************************/
/*   Grafo c/ lista de adjacencias | PROG2 | MIEEC | 2017/18     */
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_

typedef struct {
    int* vertices; /* vetor terminado com valor -1*/
    long peso;
} caminho;

typedef enum
{
    NAODIRECIONADO = 0,
    DIGRAFO
} tipo_grafo;

/* no da lista de adjacencias */
typedef struct _lista_no
{
    int vertice;               /* indice do array de listas de adjacencias */
    unsigned short peso;       /* peso associado ao vértice */
    struct _lista_no *proximo; /* apontador para proximo no' */
} lista_no;

/* lista de adjacencias */
typedef struct
{
    int tamanho;      /* numero de nos na lista */
    lista_no *inicio; /* apontador para primeiro no' da lista */
} lista_adj;

/* grafo e' um array de listas de adjacencias.
   tamanho do array e' o numero de vertices no grafo */
typedef struct
{
    tipo_grafo tipo;        /* digrafo ou nao direcionado */
    int tamanho;            /* numero de vertices */
    lista_adj *adjacencias; /* array de listas de adjacencias */
} grafo;

/* cria grafo com n vertices */
grafo *grafo_novo(int n, tipo_grafo tipo);

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo *g);

/* adiciona uma aresta ao grafo*/
void grafo_adiciona(grafo *g, int origem, int dest, unsigned short peso);

/* remove uma aresta do grafo*/
void grafo_remove(grafo *g, int origem, int dest);

/**
 * @brief verifica se existe aresta entre origem e destino
 * 
 * @param g grafo
 * @param origem vértice de origem
 * @param dest vértice de destino
 * @return int peso da aresta se existir, -1 se não existir.
 */
int grafo_aresta(grafo *g, int origem, int dest);

/* imprime as listas de adjacencias do grafo */
void grafo_imprime(grafo *g);

/**
 * @brief devolve o caminho mais longo em g
 * 
 * @param g grafo
 */
caminho grafo_caminho_mais_longo(grafo *g);

/* retorna caminho entre origem e dest usando pesquisa em profundidade / depth-first search (DFS)
   n guarda o tamanho do caminho
   _nao garante_ caminho mais curto */
int *grafo_dfs(grafo *g, int inicio, int fim, int *n);

/* retorna caminho entre origem e dest usando pesquisa em largura / breadth-first search (BFS)
   n guarda o tamanho do caminho
   _garante_ caminho mais curto */
int *grafo_bfs(grafo *g, int inicio, int fim, int *n);

#endif
