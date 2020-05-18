# Exercício Árvores AVL
Tendo como objetivo encontrar quem são as pessoas mais influentes numa rede social, é necessário escrever um programa que descubra quantos amigos tem cada pessoa nessa rede social.
Este programa deve guardar informação sobre os utilizadores na forma de uma árvore AVL para que mais tarde seja relativamente rápida a sua consulta. Cada nó da árvore deverá corresponder a uma pessoa e deve armazenar o seu nome e número de amigos.
No ficheiro *amizades.txt* está guardada toda a informação sobre as amizades entre os utilizadores da seguinte forma:
```
nome1 nome2
nome3 nome4
...
```
Isto significa que a pessoa com nome `nome1` é amiga da pessoa com nome `nome2` (e vice-versa). Não há amizades repetidas no ficheiro.
Complete a função `importa_lista_amizades()` (presente no ficheiro *avl.c*). Esta função recebe como argumento o nome do ficheiro que contém a lista de amizades e deverá devolver uma árvore AVL com toda a informação pedida.