#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

caminho percorre_grafo(grafo *g, caminho c);

int main()
{
    grafo *g = grafo_novo(13, DIGRAFO);

    grafo_adiciona(g, 0, 1, 3);
    grafo_adiciona(g, 0, 11, 10);
    grafo_adiciona(g, 1, 2, 5);
    grafo_adiciona(g, 2, 3, 26);
    grafo_adiciona(g, 3, 11, 7);
    grafo_adiciona(g, 4, 5, 7);
    grafo_adiciona(g, 4, 7, 23);
    grafo_adiciona(g, 5, 6, 3);
    grafo_adiciona(g, 6, 7, 1);
    grafo_adiciona(g, 7, 8, 8);
    grafo_adiciona(g, 8, 9, 9);
    grafo_adiciona(g, 9, 10, 7);
    grafo_adiciona(g, 9, 12, 35);
    grafo_adiciona(g, 10, 11, 11);
    grafo_adiciona(g, 12, 11, 8);

    caminho c = grafo_caminho_mais_longo(g);

    if (c.peso == 83 && c.vertices[0] == 4 && c.vertices[3] == 9)
    {
        printf("caminho correto!\n");
    }
    else
    {
        printf("caminho errado :(\n");
    }
    printf("caminho de origem %d com tamanho %ld:", c.vertices[0], c.peso);
    int *aux = c.vertices;
    while (*aux != -1)
    {
        printf(" %d", *aux);
        aux++;
    }
    printf("\n");

    free(c.vertices);
    grafo_apaga(g);
}
