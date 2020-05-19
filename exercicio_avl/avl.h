/*****************************************************************/
/*           Arvore AVL | PROG2 | MIEEC | 2017/18                */
/*****************************************************************/

#ifndef ARVOREAVL_H
#define ARVOREAVL_H

/**
 * registo para armazenar cada no'
 */
typedef struct no_avl_
{
	char *nome;
    int numAmigos;
	struct no_avl_ *esquerda;
	struct no_avl_ *direita;
	int altura;
} no_avl;

/**
 * arvore_avl contem apenas um apontador para a raiz
 */
typedef struct
{
	no_avl *raiz;
} arvore_avl;

/**
 *  cria uma nova arvore AVL vazia
 *  retorno: apontador para a arvore criada
 *  nota: se arvore nao foi criada retorna NULL
 */
arvore_avl* avl_nova();


/**
 *  elimina uma arvore, libertando toda a memoria ocupada
 *  parametro: avl apontador para arvore
 *  nota: se avl = NULL retorna sem fazer nada
 */
void avl_apaga(arvore_avl* avl);

/**
 *  devolve o no' que contem o nome especificado
 *  parametro: avl apontador para arvore
 *  parametro: nome string pretendida
 *  retorno: elemento pretendido ou NULL se ocorrer algum erro ou nao encontrar elemento
 */
no_avl* avl_pesquisa(arvore_avl* avl, const char *nome);

/**
 *  insere um novo no' com o nome especificado
 *  parametro: avl apontador para arvore
 *  parametro: nome nome da pessoa a inserir
 *  retorno: -1 se ocorrer algum erro ou 0 se bem sucedido
 *  nota: executa as rotacoes necessarias caso a arvore deixe de estar balanceada apos a insercao
 */
int avl_insere(arvore_avl* avl, const char *nome);

/**
 *  remove o no' com o nome especificado
 *  parametro: avl apontador para arvore
 *  parametro: str string a remover
 *  retorno: -1 se ocorrer algum erro ou 0 caso contrario
 *  nota: executa as rotacoes necessarias caso a arvore deixe de estar balanceada apos a remocao
 */
int avl_remove(arvore_avl* avl, const char *str);

/**
 *  devolve a string com valor mais baixo (alfabeticamente) possivel de encontrar na arvore
 *  parametro: avl apontador para arvore
 *  retorno: NULL se ocorrer algum erro ou a string pretendida caso contrario
 */
const char *avl_min(arvore_avl* avl);

/**
 *  devolve a string com valor mais alto (alfabeticamente) possivel de encontrar na arvore
 *  parametro: avl apontador para arvore
 *  retorno: NULL se ocorrer algum erro ou a string pretendida caso contrario
 */
const char *avl_max(arvore_avl* avl);

/**
 *  devolve a altura da (sub-)arvore com origem no no' especificado
 *  parametro: no raiz da (sub-)arvore
 *  retorno: -1 se no' nao existe ou a altura do no' caso contrario
 */
int avl_altura(no_avl* no);

/**
 *  imprime a arvore avl apartir do no dado
 *  parametro: no apontador para o no da arvore onde comecar
 *  parametro: profundidade profundidade do no
 */
void avl_imprime(no_avl *no, int profundidade);

/**
 *  importa a informacao de uma lista de amizades para uma arvore AVL
 *  parametro: nomeFicheiro nome do ficheiro com a lista de amizades
 *  retorno: arvore AVL com os nomes dos utilizadores e o número de amigos de cada um ou NULL em caso de erro
 */
arvore_avl *importa_lista_amizades(const char *nomeFicheiro);


#endif  /* ARVOREAVL_H */
