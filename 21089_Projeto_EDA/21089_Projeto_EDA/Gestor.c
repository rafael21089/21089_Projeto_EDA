
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"

// ----------------------------------------


Gestor* CriarNovoGestor(int id, char utilizador[50], MeiosDeMobilidade* meiosDeMobilidadeExistentes, Clientes* clienteExistentes) {

	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));
	if (novoGestor == NULL) return NULL;

	novoGestor->id = id;
	strcpy(novoGestor->utilizador, utilizador);
	novoGestor->meios = meiosDeMobilidadeExistentes;
	novoGestor->clientes = clienteExistentes;

	novoGestor->next = NULL;

	return novoGestor;
}

Gestor* InsereGestorNoFim(Gestor* header, Gestor* novoGestor) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteGestor(header, novoGestor->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoGestor;
	}
	else
	{
		//Posicionar-se no fim da lista
		Gestor* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoGestor;
	}
	return header;
}


bool ExisteGestor(Gestor* header, int idGestor) {
	if (header == NULL) return false;
	Gestor* aux = header;
	while (aux != NULL) {
		if (aux->id == idGestor)
			return true;
		aux = aux->next;
	}
	return false;
}


void MostrarListaGestor(Gestor* header) {
	Gestor* aux = header;
	while (aux) {
		MostraGestor(aux);
		aux = aux->next;
	}
}

void MostraGestor(Gestor* gestor) {
	if (gestor != NULL)
	{
		printf("\Gestor:\nMeio De Mobilidade ID: %d\n", gestor->id);
		printf("Utilizador: %s\n", gestor->utilizador);
		printf("\n-------------\n");
	}
}

Gestor* RemoverGestor(Gestor* header, int id) {
	if (header == NULL) return NULL;			//Lista vazia
	if (!ExisteGestor(header, id)) return header;	//se não existe

	if (header->id == id) {		//remove no inicio da lista
		Gestor* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		Gestor* aux = header;
		Gestor* auxAnt = aux;
		while (aux && aux->id != id) {	//procura para revover
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->next = aux->next;
			free(aux);
		}
	}
	return header;
}

Gestor* ProcuraGestor(Gestor* header, int id) {
	if (header == NULL) return NULL;		//lista vazia
	else
	{
		Gestor* aux = header;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);		//encontrei
			}
			aux = aux->next;
		}
		return NULL;
	}
}

void AlteraGestor(Gestor** header, int id, char* utilizador) {
	if (*header != NULL) {
		Gestor* aux = ProcuraGestor(*header, id);
		if (aux != NULL)		//se encontrou o jogo
		{
			strcpy(aux->utilizador, utilizador);
		}
	}
}



Gestor* LerEArmazenarGestor(char* filename, Gestor* header) {

	FILE* fp;
	char line[1024];
	char* token;

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File %s does not exist, creating empty file...\n", filename);
		fp = fopen(filename, "w");
		fclose(fp);
		return;
	}

	while (fgets(line, 1024, fp)) {
		// remove trailing newline character
		line[strcspn(line, "\n")] = '\0';


		Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

		// parse line into variables separated by semicolons
		token = strtok(line, ";");
		novoGestor->id = atoi(token); // convert string to integer
		token = strtok(NULL, ";");
		strcpy(novoGestor->utilizador, token);


		Clientes* cliente = NULL;
		MeiosDeMobilidade* meios = NULL;

		novoGestor->clientes = cliente;
		novoGestor->meios = meios;

		novoGestor->next = NULL;


		header = InsereGestorNoFim(header, novoGestor);

		// print stored variables for testing
	}

	return header;

	fclose(fp);
}


bool GravarGestorBinario(char* nomeFicheiro, Gestor* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	Gestor* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Gestor), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


Gestor* LerGestorBinario(char* nomeFicheiro) {
	FILE* fp;
	Gestor* header = NULL;
	Gestor* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Gestor*)malloc(sizeof(Gestor))) && fread(auxAnt, sizeof(Gestor), 1, fp)) {
		Gestor* aux = CriarNovoGestor(auxAnt->id, auxAnt->utilizador , NULL , NULL);
		header = InsereGestorNoFim(header, aux);
	}
	fclose(fp);
	return header;
}