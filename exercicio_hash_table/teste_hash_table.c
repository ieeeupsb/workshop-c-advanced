#include <stdio.h>
#include <stdlib.h>
#include "tabdispersao.h"

int main(int argc, char *argv[]) {
	
	// Variáveis
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
	
	// Adicionar à tabela
	while(fscanf(fp, "%s", chave) != EOF){
		fscanf(fp, "%s", valor);
		tabela_adiciona(td, chave, valor);
	}
	
	mostraTabela(td);
	
	/*  Exercício  */
	
	int novo_tamanho = 101; // Podes mudar este valor se quiseres, convém ser maior ou igual que o número de elementos esperados, ou seja, número de linhas no passwords.txt
	
	tabela_dispersao* nova = tabela_move(td, novo_tamanho); // Deves implementar esta função no tabdispersao.c!
	
	mostraTabela(nova);
	
	/*   Fim Exercício  */
	
	// Fechar tudo
	tabela_apaga(nova);
	fclose(fp);
}
