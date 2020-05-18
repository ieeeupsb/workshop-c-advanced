#include <stdio.h>
#include "avl.h"

int main() {
    char nome1[50], nome2[50];
    arvore_avl *avl;

    avl = importa_lista_amizades("amizades.txt");

    avl_imprime(avl);

    return 0;
}
