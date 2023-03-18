#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Atividade.h"

int CountHistorico(Atividade* Head) {
	int count = 0;
	Atividade* current = Head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

void insertHistoricoCliente(Clientes* cliente, Atividade* atividade) {
	atividade->next = cliente->atividade;
	cliente->atividade = atividade;
}

void insertHistoricoMeio(MeiosDeMobilidade* meio, Atividade* atividade) {
	atividade->next = meio->atividade;
	meio->atividade = atividade;
}

void insertAlugerTotalGestor(Gestor* gestor, Atividade* aluguerTotal) {
	aluguerTotal->next = gestor->todosAlugueres;
	gestor->todosAlugueres = aluguerTotal;
}



Atividade* CriarAluguerListaTotal(int id, float custo , char* estadoDoAluguer , int clienteId , int meioUsadoId) {

	Atividade* novoAluguerListaTotal = (Atividade*)malloc(sizeof(Atividade));
	if (novoAluguerListaTotal == NULL) return NULL;

	novoAluguerListaTotal->id = id;
	novoAluguerListaTotal->custo = custo;
	strcpy(novoAluguerListaTotal->estadoDoAluguer, estadoDoAluguer);
	novoAluguerListaTotal->clienteId = clienteId;
	novoAluguerListaTotal->meioUsadoId = meioUsadoId;


	novoAluguerListaTotal->next = NULL;

	return novoAluguerListaTotal;
}



Atividade* InsereAluguerListaTotalNoFim(Atividade* header, Atividade* novoAluguerListaTotal) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteAluguerListaTotal(header, novoAluguerListaTotal->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoAluguerListaTotal;
	}
	else
	{
		//Posicionar-se no fim da lista
		Atividade* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoAluguerListaTotal;
	}
	return header;
}


bool ExisteAluguerListaTotal(Atividade* header, int idAluguerListaTotal) {
	if (header == NULL) return false;
	Atividade* aux = header;
	while (aux != NULL) {
		if (aux->id == idAluguerListaTotal)
			return true;
		aux = aux->next;
	}
	return false;
}


int CountAluguerListaTotal(Atividade* head) {
	int count = 0;
	Atividade* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}



Atividade* LerEArmazenarAluguerListaTotal(char* filename, Atividade* header) {

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


		Atividade* novoAluguerListaTotal = (Atividade*)malloc(sizeof(Atividade));

		// parse line into variables separated by semicolons
		token = strtok(line, ";");
		novoAluguerListaTotal->id = atoi(token); // convert string to integer
		token = strtok(NULL, ";");
		novoAluguerListaTotal->custo = atof(token);
		token = strtok(NULL, ";");
		strcpy(novoAluguerListaTotal->estadoDoAluguer, token);
		token = strtok(NULL, ";");
		novoAluguerListaTotal->clienteId = atoi(token);
		token = strtok(NULL, ";");
		novoAluguerListaTotal->meioUsadoId = atoi(token);

		novoAluguerListaTotal->next = NULL;

		header = InsereAluguerListaTotalNoFim(header, novoAluguerListaTotal);

		// print stored variables for testing
	}

	return header;

	fclose(fp);
}


bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Atividade* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	Atividade* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Atividade), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


Atividade* LerAluguerListaTotalBinario(char* nomeFicheiro) {
	FILE* fp;
	Atividade* header = NULL;
	Atividade* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Atividade*)malloc(sizeof(Atividade))) && fread(auxAnt, sizeof(Atividade), 1, fp)) {
		Atividade* aux = CriarAluguerListaTotal(auxAnt->id, auxAnt->custo, auxAnt->estadoDoAluguer , auxAnt->clienteId , auxAnt->meioUsadoId);
		header = InsereAluguerListaTotalNoFim(header, aux);
	}
	fclose(fp);
	return header;
}

void DistribuirAlugueresHistorico(Atividade* header , MeiosDeMobilidade* headerMeios , Clientes* headerClientes) {

	Atividade* auxAluguer = header;

	while (auxAluguer != NULL) {

		Clientes* auxClientes = headerClientes;
		MeiosDeMobilidade* auxMeio = headerMeios;

		while (auxClientes != NULL)
		{
			if (auxClientes->id == auxAluguer->clienteId)
			{
				auxClientes->atividade = auxAluguer;

				auxClientes->id = CountClientes(headerClientes);
			}

			auxClientes = auxClientes->next;
		}


		while (auxMeio != NULL)
		{
			if (auxMeio->id == auxAluguer->meioUsadoId)
			{
				auxMeio->atividade = auxAluguer;
				auxMeio->id = CountMeios(headerMeios);

			}

			auxMeio = auxMeio->next;
		}


		auxAluguer = auxAluguer->next;
	}


}




