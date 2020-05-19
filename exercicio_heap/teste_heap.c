#include <stdio.h>
#include "avl.h"
#include "heap.h"

/**
 *  converte a arvore avl dos utilizadores na heap organizada por numero de amigos
 *  parametro: avl arvore avl onde esta' guardada a informacao sobre os utilizadores
 *  parametro: capacidade tamanho maximo da heap
 *  retorno: heap com todos os utilizadores ordenados por numero de amigos
 */
heap *avl_para_heap(arvore_avl *avl, int capacidade) {
    // Exercicio Heap

    return NULL;
}

int main() {
    arvore_avl *avl;
    heap *h;

    avl = importa_lista_amizades("amizades.txt");

    h = avl_para_heap(avl, 100);

    if(h != NULL)
        heap_imprime(h, 1);

    return 0;
}
