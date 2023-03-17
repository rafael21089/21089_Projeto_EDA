#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Atividade.h"

int CountHistorico(Historico* Head) {
	int Count = 0;
	Historico* Current = Head;

	while (Current != NULL) {
		Count++;
		Current = Current->next;
	}

	return Count;
}

void insertHistoricoCliente(Clientes* Cliente, Historico* Historico) {
	Historico->next = Cliente->Historico;
	Cliente->Historico = Historico;
}

void insertHistoricoMeio(MeiosDeMobilidade* Meio, Historico* Historico) {
	Historico->next = Meio->Historico;
	Meio->Historico = Historico;
}
