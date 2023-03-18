#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Cliente.h"


Clientes* CriarClientes(int id, char nome[50], char morada[50], char nif[9], float saldo) {

	Clientes* novoCliente = (Clientes*)malloc(sizeof(Clientes));
	if (novoCliente == NULL) return NULL;

	novoCliente->id = id;
	strcpy(novoCliente->nome, nome);
	strcpy(novoCliente->morada, morada);
	strcpy(novoCliente->nif, nif);
	novoCliente->saldo = saldo;

	Atividade* ativ = NULL;

	novoCliente->atividade = ativ;


	novoCliente->next = NULL;

	return novoCliente;
}

Clientes* InsereClienteNoFim(Clientes* header, Clientes* novoCliente) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteCliente(header, novoCliente->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoCliente;
	}
	else
	{
		//Posicionar-se no fim da lista
		Clientes* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoCliente;
	}
	return header;
}


bool ExisteCliente(Clientes* header, int idCliente) {
	if (header == NULL) return false;
	Clientes* aux = header;
	while (aux != NULL) {
		if (aux->id == idCliente)
			return true;
		aux = aux->next;
	}
	return false;
}


void MostrarListaClientes(Clientes* header) {
	Clientes* aux = header;
	while (aux) {
		MostraCliente(aux);
		aux = aux->next;
	}
}



void MostraCliente(Clientes* cliente) {
	if (cliente != NULL)
	{
		printf("\nCliente Dados:\nCliente ID: %d\n", cliente->id);
		printf("Nome: %s\n", cliente->nome);
		printf("Morada: %s\n", cliente->morada);
		printf("NIF: %s\n", cliente->nif);
		printf("\nSaldo: %f\n", cliente->saldo);
		printf("\n-------------\n");
	}
}

Clientes* RemoverCliente(Clientes* header, int id) {
	if (header == NULL) return NULL;			//Lista vazia
	if (!ExisteCliente(header, id)) return header;	//se não existe

	if (header->id == id) {		//remove no inicio da lista
		Clientes* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		Clientes* aux = header;
		Clientes* auxAnt = aux;
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


Clientes* ProcuraClientes(Clientes* header, int id) {
	if (header == NULL) return NULL;		//lista vazia
	else
	{
		Clientes* aux = header;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);		//encontrei
			}
			aux = aux->next;
		}
		return NULL;
	}
}

void AlteraCliente(Clientes** header, int id, char* nome) {
	if (*header != NULL) {
		Clientes* aux = ProcuraClientes(*header, id);
		if (aux != NULL)		//se encontrou o jogo
		{
			strcpy(aux->nome, nome);
		}
	}
}


void RegistoAluguer(Clientes** headerCliente, MeiosDeMobilidade** headerMeios , AluguerListaTotal** headerAluguerTotal, int idCliente, int idMeios) {


	Clientes* cliente = ProcuraClientes(*headerCliente, idCliente);
	MeiosDeMobilidade* meio = ProcuraMeiosDeMobilidade(*headerMeios, idMeios);

	if (cliente->saldo >= meio->custo)
	{
		cliente->saldo = cliente->saldo - meio->custo;

		Atividade* atividades = (Atividade*)malloc(sizeof(Atividade));
		Atividade* atividadesMeios = (Atividade*)malloc(sizeof(Atividade));

		int idClienteRegisto = 0;
		int idMeioRegisto = 0;

		if (cliente->atividade != NULL)
		{
			idClienteRegisto = CountHistorico(cliente->atividade);
		}


		if (meio->atividade != NULL)
		{
			idMeioRegisto = CountHistorico(meio->atividade);

		}


		atividades->id = idClienteRegisto;
		atividades->estadoDoAluguer = ATIVO;
		atividades->custo = meio->custo;
		atividades->clienteId = cliente->id;
		atividades->meioUsadoId = meio->id;
		atividades->next = NULL;

		atividadesMeios->id = idMeioRegisto;
		atividadesMeios->estadoDoAluguer = ATIVO;
		atividadesMeios->custo = meio->custo;
		atividadesMeios->clienteId = cliente->id;
		atividadesMeios->meioUsadoId = meio->id;
		atividadesMeios->next = NULL;

		insertHistoricoCliente(cliente, atividades);
		insertHistoricoMeio(meio, atividadesMeios);


		int idAluguerListaTotal = CountAluguerListaTotal(*headerAluguerTotal);

		AluguerListaTotal* aluguerNovo = CriarAluguerListaTotal(idAluguerListaTotal, atividades , atividadesMeios);
		*headerAluguerTotal = InsereAluguerListaTotalNoFim(*headerAluguerTotal, aluguerNovo);

	}
	

}

int CountClientes(Clientes* head) {
	int count = 0;
	Clientes* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}


Clientes* LerEArmazenarCliente(char* filename, Clientes* header) {

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


		Clientes* novoCliente = (Clientes*)malloc(sizeof(Clientes));

		// parse line into variables separated by semicolons
		token = strtok(line, ";");
		novoCliente->id = atoi(token); // convert string to integer
		token = strtok(NULL, ";");
		strcpy(novoCliente->nome, token);
		token = strtok(NULL, ";");
		strcpy(novoCliente->morada, token);
		token = strtok(NULL, ";");
		strcpy(novoCliente->nif, token);
		token = strtok(NULL, ";");
		novoCliente->saldo = atoi(token);

		Atividade* ativ = NULL;

		novoCliente->atividade = ativ;
		novoCliente->next = NULL;


		header = InsereClienteNoFim(header,novoCliente);

		// print stored variables for testing
	}

	return header;

	fclose(fp);
}


bool GravarClientesBinario(char* nomeFicheiro, Clientes* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	Clientes* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Clientes), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


Clientes* LerClientesBinario(char* nomeFicheiro) {
	FILE* fp;
	Clientes* header = NULL;
	Clientes* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Clientes*)malloc(sizeof(Clientes))) && fread(auxAnt, sizeof(Clientes), 1, fp)) {
		Clientes* aux = CriarClientes(auxAnt->id, auxAnt->nome, auxAnt->morada, auxAnt->nif, auxAnt->saldo);
		header = InsereClienteNoFim(header, aux);
	}
	fclose(fp);
	return header;
}


