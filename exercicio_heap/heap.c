/*****************************************************************/
/*   Fila de prioridade / min-heap | PROG2 | MIEEC | 2018/19     */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

int menor_que(elemento * e1, elemento * e2);

heap* heap_nova(int capacidade)
{
	heap * h = (heap *) malloc(sizeof(heap));

	if (!h)
		return NULL;

	h->tamanho = 0;
	h->capacidade = capacidade;
	h->elementos = (elemento **) calloc(capacidade+1, sizeof(elemento *));

	if (!h->elementos) {
		free(h);
		return NULL;
	}

	return h;
}

void heap_apaga(heap *h)
{
	int i;

	if(!h)
		return;

	/* apaga todos os elementos e respetivas strings */
	for(i=RAIZ; i<=h->tamanho; i++)
	{
		free(h->elementos[i]->valor);
		free(h->elementos[i]);
		h->elementos[i]=NULL;
	}

	free(h->elementos);
	free(h);
}


elemento * elemento_novo(int prioridade, const char * valor)
{
	elemento * elem = (elemento *) malloc(sizeof(elemento));

	if (!elem)
		return NULL;

	elem->valor = (char*)calloc(strlen(valor)+1, sizeof(char));
	if (!elem->valor)
	{
		free(elem);
		return NULL;
	}

	strcpy(elem->valor, valor);
	elem->prioridade = prioridade;

	return elem;
}


int heap_insere(heap * h, const char * texto, int prioridade)
{
	elemento * aux, * elem;
	int i;

	/* se heap esta' cheia, nao insere elemento */
	if (h->tamanho >= h->capacidade)
		return 0;

	elem = elemento_novo(prioridade, texto);
	if (!elem)
		return 0;

	/* coloca elemento no fim da heap */
	h->tamanho++;
	i = h->tamanho;
	h->elementos[i] = elem;

 	/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while (i != RAIZ && menor_que(h->elementos[PAI(i)], h->elementos[i]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
	return 1;
}


char * heap_remove(heap * h)
{
	int i, filho_maior;
	elemento * aux;
	char * ret;

	/* se heap estiver vazia, nao remove elemento */
	if (!h || h->tamanho <= 0)
		return NULL;

	ret = h->elementos[RAIZ]->valor;
	free(h->elementos[RAIZ]);

	/* coloca ultimo elemento da heap na raiz */
	h->elementos[RAIZ] = h->elementos[h->tamanho];
	h->elementos[h->tamanho] = NULL;
	h->tamanho--;

 	i = RAIZ;

	/* enquanto nao chegar 'a base da heap */
	while(FILHO_ESQ(i) <= h->tamanho)
	{
		filho_maior = FILHO_ESQ(i);

		/* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
		if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_ESQ(i)], h->elementos[FILHO_DIR(i)]))
			filho_maior = FILHO_DIR(i);

		/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
		if (menor_que(h->elementos[i], h->elementos[filho_maior]))
		{
			aux = h->elementos[filho_maior];
			h->elementos[filho_maior] = h->elementos[i];
			h->elementos[i] = aux;
			i = filho_maior;
		}
		else
			break;
	}

	return ret;
}


void heap_imprime(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice <= h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    heap_imprime(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    heap_imprime(h, indice*2+1);
  }
}

int menor_que(elemento * e1, elemento * e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	return e1->prioridade < e2->prioridade;
}
