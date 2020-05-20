#include <stdio.h>
#include "avl.h"
#include "heap.h"

void subavl_para_heap(no_avl *no, heap *h) {
    // verificacao de parametros
    if(no == NULL || h == NULL)
        return;

    // insercao do no na heap
    heap_insere(h, no->nome, no->numAmigos);
    // insercao da subarvore esquerda na heap
    subavl_para_heap(no->esquerda, h);
    // insercao da subarvore direita na heap
    subavl_para_heap(no->direita, h);
}

/**
 *  converte a arvore avl dos utilizadores na heap organizada por numero de amigos
 *  parametro: avl arvore avl onde esta' guardada a informacao sobre os utilizadores
 *  parametro: capacidade tamanho maximo da heap
 *  retorno: heap com todos os utilizadores ordenados por numero de amigos
 */
heap *avl_para_heap(arvore_avl *avl, int capacidade) {
    heap *h;

    // verificacao de parametros
    if(avl == NULL)
        return NULL;

    // criacao da heap
    h = heap_nova(capacidade);
    if(h == NULL)
        return NULL;

    // insercao da raiz e dos seus descendentes na heap
    subavl_para_heap(avl->raiz, h);

    return h;
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
