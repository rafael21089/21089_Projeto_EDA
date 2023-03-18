#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Aluguer.h"

int CountHistorico(Aluguer* Head) {
	int count = 0;
	Aluguer* current = Head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

void insertHistoricoCliente(Clientes* cliente, Aluguer* atividade) {
	atividade->next = cliente->atividade;
	cliente->atividade = atividade;
}

void insertHistoricoMeio(MeiosDeMobilidade* meio, Aluguer* atividade) {
	atividade->next = meio->atividade;
	meio->atividade = atividade;
}

void insertAlugerTotalGestor(Gestor* gestor, Aluguer* aluguerTotal) {
	aluguerTotal->next = gestor->todosAlugueres;
	gestor->todosAlugueres = aluguerTotal;
}



Aluguer* CriarAluguerListaTotal(int id, float custo, char* estadoDoAluguer, int clienteId, int meioUsadoId) {

	Aluguer* novoAluguerListaTotal = (Aluguer*)malloc(sizeof(Aluguer));
	if (novoAluguerListaTotal == NULL) return NULL;

	novoAluguerListaTotal->id = id;
	novoAluguerListaTotal->custo = custo;
	strcpy(novoAluguerListaTotal->estadoDoAluguer, estadoDoAluguer);
	novoAluguerListaTotal->clienteId = clienteId;
	novoAluguerListaTotal->meioUsadoId = meioUsadoId;


	novoAluguerListaTotal->next = NULL;

	return novoAluguerListaTotal;
}



Aluguer* InsereAluguerListaTotalNoFim(Aluguer* header, Aluguer* novoAluguerListaTotal) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteAluguerListaTotal(header, novoAluguerListaTotal->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoAluguerListaTotal;
	}
	else
	{
		//Posicionar-se no fim da lista
		Aluguer* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoAluguerListaTotal;
	}
	return header;
}


bool ExisteAluguerListaTotal(Aluguer* header, int idAluguerListaTotal) {
	if (header == NULL) return false;
	Aluguer* aux = header;
	while (aux != NULL) {
		if (aux->id == idAluguerListaTotal)
			return true;
		aux = aux->next;
	}
	return false;
}


int CountAluguerListaTotal(Aluguer* head) {
	int count = 0;
	Aluguer* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}



Aluguer* LerEArmazenarAluguerListaTotal(char* filename, Aluguer* header) {

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


		Aluguer* novoAluguerListaTotal = (Aluguer*)malloc(sizeof(Aluguer));

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


bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Aluguer* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	Aluguer* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Aluguer), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


Aluguer* LerAluguerListaTotalBinario(char* nomeFicheiro) {
	FILE* fp;
	Aluguer* header = NULL;
	Aluguer* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Aluguer*)malloc(sizeof(Aluguer))) && fread(auxAnt, sizeof(Aluguer), 1, fp)) {
		Aluguer* aux = CriarAluguerListaTotal(auxAnt->id, auxAnt->custo, auxAnt->estadoDoAluguer, auxAnt->clienteId, auxAnt->meioUsadoId);
		header = InsereAluguerListaTotalNoFim(header, aux);
	}
	fclose(fp);
	return header;
}

void DistribuirAlugueresHistorico(Aluguer* header, MeiosDeMobilidade* headerMeios, Clientes* headerClientes) {

	Aluguer* auxAluguer = header;

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



int ListarClienteAlugueresById(Aluguer* header, int idCliente) {

	Aluguer* aux = header;

	system("cls");

	while (aux != NULL)
	{
		if (aux->clienteId == idCliente)
		{
			printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);
		}

		aux = aux->next;
	}

	return 0;
}

int AluguerClientePorEscrever(Aluguer* headAluguer) {

	int idCliente;

	printf("\n\nDigite o id do cliente que quer ver os alugueres: ");
	scanf("%d", &idCliente);


	ListarClienteAlugueresById(headAluguer, idCliente);

	return 0;

}


int ListarMeiosAlugueresById(Aluguer* header, int idMeios) {

	Aluguer* aux = header;

	system("cls");

	while (aux != NULL)
	{
		if (aux->meioUsadoId == idMeios)
		{
			printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);
		}

		aux = aux->next;
	}

	return 0;
}

int AluguerMeiosPorEscrever(Aluguer* headAluguer) {

	int idMeios;


	printf("\n\nDigite o id do meio de mobilidade que quer ver os alugueres: ");
	scanf("%d", &idMeios);


	ListarMeiosAlugueresById(headAluguer, idMeios);

	return 0;

}


int ListarTodosAlugueres(Aluguer* header) {

	system("cls");


	Aluguer* aux = header;

	while (aux != NULL)
	{

		printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);

		aux = aux->next;
	}

	return 0;
}




