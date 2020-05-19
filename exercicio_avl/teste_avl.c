#include <stdio.h>
#include "avl.h"

int main() {
    arvore_avl *avl;

    avl = importa_lista_amizades("amizades.txt");

    if(avl != NULL)
        avl_imprime(avl->raiz, 0);

    return 0;
}
