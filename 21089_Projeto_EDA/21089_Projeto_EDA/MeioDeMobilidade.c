#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MeioDeMobilidade.h"



MeiosDeMobilidade* CriarMeiosDeMobilidade(int id, char* tipo, int cargaBateria, float custo, char* localizacao) {


	MeiosDeMobilidade* novoMeiosDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));
	if (novoMeiosDeMobilidade == NULL) return NULL;	//pode n�o haver mem�ria!!!

	novoMeiosDeMobilidade->id = id;
	strcpy(novoMeiosDeMobilidade->tipo, tipo);
	novoMeiosDeMobilidade->cargaBateria = cargaBateria;
	novoMeiosDeMobilidade->custo = custo;
	strcpy(novoMeiosDeMobilidade->localizacao, localizacao);

	Atividade* ativ = NULL;

	novoMeiosDeMobilidade->atividade = ativ;

	novoMeiosDeMobilidade->next = NULL;

	return novoMeiosDeMobilidade;
}


MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* header, MeiosDeMobilidade* novoMeiosDeMobilidade) {
	//Verificar se o novo jogo j� existe!!!
	if (ExisteMeiosDeMobilidade(header, novoMeiosDeMobilidade->id)) return header;	//se existir n�o insere!

	if (header == NULL) {		//lista vazia
		header = novoMeiosDeMobilidade;
	}
	else
	{
		//Posicionar-se no fim da lista
		MeiosDeMobilidade* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoMeiosDeMobilidade;
	}
	return header;
}


bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* header, int idMeiosDeMobilidade) {
	if (header == NULL) return false;
	MeiosDeMobilidade* aux = header;
	while (aux != NULL) {
		if (aux->id == idMeiosDeMobilidade)
			return true;
		aux = aux->next;
	}
	return false;
}


void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* header) {
	MeiosDeMobilidade* aux = header;
	while (aux) {		//mesmo que while (aux!=NULL)
		MostraMeiosDeMobilidade(aux);
		aux = aux->next;
	}
}

void MostraMeiosDeMobilidade(MeiosDeMobilidade* meiosDeMobilidade) {
	if (meiosDeMobilidade != NULL)
	{
		printf("\nMeio De Mobilidade Dados:\nMeio De Mobilidade ID: %d\n", meiosDeMobilidade->id);
		printf("Tipo: %s\n", meiosDeMobilidade->tipo);
		printf("Carga: %d\n", meiosDeMobilidade->cargaBateria);
		printf("Custo: %d\n", meiosDeMobilidade->custo);
		printf("Localizacao: %f\n", meiosDeMobilidade->localizacao);


		printf("\n-------------\n");
	}
}

MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* header, int id) {
	if (header == NULL) return NULL;			//Lista vazia
	if (!ExisteMeiosDeMobilidade(header, id)) return header;	//se n�o existe

	if (header->id == id) {		//remove no inicio da lista
		MeiosDeMobilidade* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		MeiosDeMobilidade* aux = header;
		MeiosDeMobilidade* auxAnt = aux;
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


MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* header, int id) {
	if (header == NULL) return NULL;		//lista vazia
	else
	{
		MeiosDeMobilidade* aux = header;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);		//encontrei
			}
			aux = aux->next;
		}
		return NULL;
	}
}

void AlteraMeiosDeMobilidade(MeiosDeMobilidade** header, int id, char* tipo) {
	if (*header != NULL) {
		MeiosDeMobilidade* aux = ProcuraMeiosDeMobilidade(*header, id);
		if (aux != NULL)		//se encontrou o jogo
		{
			strcpy(aux->tipo, tipo);
		}
	}
}


int CountMeios(struct MeiosDeMobilidade* head) {
	int count = 0;
	MeiosDeMobilidade* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}


MeiosDeMobilidade* LerEArmazenarMeiosDeMobilidade(char* filename, MeiosDeMobilidade* header) {

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


		MeiosDeMobilidade* novoMeioDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));

		// parse line into variables separated by semicolons
		token = strtok(line, ";");
		novoMeioDeMobilidade->id = atoi(token); // convert string to integer
		token = strtok(NULL, ";");
		strcpy(novoMeioDeMobilidade->tipo, token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->cargaBateria = atoi(token); // convert string to integer
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->custo = atof(token); // convert string to integer
		token = strtok(NULL, ";");
		strcpy(novoMeioDeMobilidade->localizacao, token);

		Atividade* ativ = NULL;

		novoMeioDeMobilidade->atividade = ativ;
		novoMeioDeMobilidade->next = NULL;


		header = InsereMeiosDeMobilidadeNoFim(header, novoMeioDeMobilidade);

		// print stored variables for testing
	}

	return header;

	fclose(fp);
}


bool GravarMeiosDeMobilidadeBinario(char* nomeFicheiro, MeiosDeMobilidade* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	MeiosDeMobilidade* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de mem�ria
		fwrite(aux, sizeof(MeiosDeMobilidade), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

MeiosDeMobilidade* LerMeiosDeMobilidadeBinario(char* nomeFicheiro) {
	FILE* fp;
	MeiosDeMobilidade* header = NULL;
	MeiosDeMobilidade* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade))) && fread(auxAnt, sizeof(MeiosDeMobilidade), 1, fp)) {
		MeiosDeMobilidade* aux = CriarMeiosDeMobilidade(auxAnt->id, auxAnt->tipo, auxAnt->cargaBateria, auxAnt->custo, auxAnt->localizacao);
		header = InsereMeiosDeMobilidadeNoFim(header, aux);
	}
	fclose(fp);
	return header;
}