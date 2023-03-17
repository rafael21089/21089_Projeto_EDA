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
