
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"

// ----------------------------------------


Gestor* CriarNovoGestor(int id, char* utilizador, char* distrito, MeiosDeMobilidade* meiosDeMobilidadeExistentes, Clientes* clienteExistentes , Aluguer* aluguerTotal) {

	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));
	if (novoGestor == NULL) return NULL;

	novoGestor->id = id;
	strcpy(novoGestor->utilizador, utilizador);
	strcpy(novoGestor->distrito, distrito);
	novoGestor->meios = meiosDeMobilidadeExistentes;
	novoGestor->clientes = clienteExistentes;
	novoGestor->todosAlugueres = aluguerTotal;

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
		printf("\nGestor ID: %d\n", gestor->id);
		printf("Utilizador: %s\n", gestor->utilizador);
		printf("Distrito: %s\n", gestor->distrito);
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
		token = strtok(NULL, ";");
		strcpy(novoGestor->distrito, token);

		Clientes* cliente = NULL;
		MeiosDeMobilidade* meios = NULL;
		Aluguer* todosAlugueres = NULL;

		novoGestor->clientes = cliente;
		novoGestor->meios = meios;
		novoGestor->todosAlugueres = todosAlugueres;

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
		Gestor* aux = CriarNovoGestor(auxAnt->id, auxAnt->utilizador, auxAnt->distrito, NULL , NULL , NULL);
		header = InsereGestorNoFim(header, aux);
	}
	fclose(fp);
	return header;
}


int GravarMeiosEClientesNosGestores(Gestor* gestor , Aluguer* alugueresTotal , Clientes* clientesHeader , MeiosDeMobilidade* meiosHeader) {


	Gestor* aux = gestor;

	while (aux != NULL)
	{
		aux->clientes = clientesHeader;
		aux->meios = meiosHeader;
		aux->todosAlugueres = alugueresTotal;
		aux = aux->next;
	}



	return 0;
}



Gestor* InserirPorEscreverGestor() {


	int id; 
	char utilizador[50]; 
	char distrito[50];

	printf("\n\nDigite o id do Gestor: ");
	scanf("%d", &id);
	printf("\nDigite o nome do utilizador: ");
	scanf("%s", &utilizador);
	printf("\nDigite o distrito: ");
	scanf("%s", &distrito);


	Gestor* gestorNovo = CriarNovoGestor(id, utilizador, distrito, NULL, NULL, NULL);

	return gestorNovo;

}

int AlterarPorEscreverGestor(Gestor* headGestor) {


	int id;
	char utilizador[50];

	printf("\n\nDigite o id do Gestor: ");
	scanf("%d", &id);
	printf("\nDigite o novo nome de utilizador: ");
	scanf("%s", &utilizador);

	AlteraGestor(&headGestor, id, utilizador);

	return 0;

}

int RemoverPorEscreverGestor(Gestor* headGestor) {

	int id;

	printf("\n\nDigite o id do Gestor que quer eliminar: ");
	scanf("%d", &id);

	RemoverGestor(headGestor, id);

	return 0;

}


