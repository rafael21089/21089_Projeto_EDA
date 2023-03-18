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

void insertAlugerTotalGestor(Gestor* gestor, AluguerListaTotal* aluguerTotal) {
	aluguerTotal->next = gestor->todosAlugueres;
	gestor->todosAlugueres = aluguerTotal;
}



AluguerListaTotal* CriarAluguerListaTotal(int id, Atividade* aluguerClienteRegisto , Atividade* aluguerMeioRegisto) {

	AluguerListaTotal* novoAluguerListaTotal = (AluguerListaTotal*)malloc(sizeof(AluguerListaTotal));
	if (novoAluguerListaTotal == NULL) return NULL;

	novoAluguerListaTotal->id = id;
	novoAluguerListaTotal->aluguerClienteRegisto = aluguerClienteRegisto;
	novoAluguerListaTotal->aluguerMeioRegisto = aluguerMeioRegisto;

	novoAluguerListaTotal->next = NULL;

	return novoAluguerListaTotal;
}



AluguerListaTotal* InsereAluguerListaTotalNoFim(AluguerListaTotal* header, AluguerListaTotal* novoAluguerListaTotal) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteAluguerListaTotal(header, novoAluguerListaTotal->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoAluguerListaTotal;
	}
	else
	{
		//Posicionar-se no fim da lista
		AluguerListaTotal* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoAluguerListaTotal;
	}
	return header;
}


bool ExisteAluguerListaTotal(AluguerListaTotal* header, int idAluguerListaTotal) {
	if (header == NULL) return false;
	AluguerListaTotal* aux = header;
	while (aux != NULL) {
		if (aux->id == idAluguerListaTotal)
			return true;
		aux = aux->next;
	}
	return false;
}


int CountAluguerListaTotal(AluguerListaTotal* head) {
	int count = 0;
	AluguerListaTotal* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

