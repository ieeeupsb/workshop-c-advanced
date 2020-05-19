#include <stdio.h>
#include <stdlib.h>
#include "tabdispersao.h"

int main(int argc, char *argv[]) {
	
	// Vari�veis
	FILE *fp;
	char chave[255], valor[255];
	tabela_dispersao* td;
	
	// Criar tabela
	td = tabela_nova(100, hash_djbm);
	if(td==NULL){
		printf("Unable to create table.");
		return;
	}

	// Abrir ficheiro
	fp=fopen("passwords.txt", "r");	
	if(fp==NULL){
		printf("Unable to open file.");
		return;
	}
	
	// Adicionar � tabela
	while(fscanf(fp, "%s", chave) != EOF){
		fscanf(fp, "%s", valor);
		tabela_adiciona(td, chave, valor);
	}
	
	mostraTabela(td);
	
	/*  Exerc�cio  */
	
	int novo_tamanho = 101; // Podes mudar este valor se quiseres, conv�m ser maior ou igual que o n�mero de elementos esperados, ou seja, n�mero de linhas no passwords.txt
	
	tabela_dispersao* nova = tabela_move(td, novo_tamanho); // Deves implementar esta fun��o no tabdispersao.c!
	
	mostraTabela(nova);
	
	/*   Fim Exerc�cio  */
	
	// Fechar tudo
	tabela_apaga(nova);
	fclose(fp);
}
