# Exercício Heap Binário
No último exercício foi pedido que se criasse uma árvore AVL onde estão organizados os diferentes utilizadores de uma rede social bem como o seu número de amigos. O exercício foi feito por forma a procurar quem são as pessoas mais influentes nessa rede social. No entanto, de forma a encontrar mais rapidamente essa informação, pode-se reorganizar estes dados num heap em que a raiz contém o utilizador mais influente de todos.  
Completa a função `avl_para_heap()` (no ficheiro *teste_heap.c*) na qual uma árvore AVL deve ser convertida num max-heap ordenado pelo número de amigos de cada utilizador.  
O resultado esperado do programa é:  
```
                                                            Maria (3)
                                             Carlos (3)
                                                            Sofia (2)
                              Pedro (4)
                                                            Ines (2)
                                             Jessica (3)
                                                            Ricardo (3)
               Joao (4)
                                                            Rodrigo (1)
                                             Ana (2)
                                                            Vasco (2)
                              Vanessa (4)
                                                            Joaquim (3)
                                             Vitor (4)
                                                            Luisa (3)
Filipe (4)
                                             Diogo (1)
                              Luis (2)
                                             Jose (2)
               Filipa (3)
                                             Hugo (1)
                              Nuno (2)
                                             Manuel (2)
```
Mais uma vez há várias soluções possíveis, mas o resultado do programa deve ser na mesma um heap binário que respeita as propriedades estrutural e de ordem.
