#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MeioDeMobilidade.h"



MeiosDeMobilidade* CriarMeiosDeMobilidade(int Id, char Tipo[50], int CargaBateria, int Custo, float localizacao) {


	MeiosDeMobilidade* NovoMeiosDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));
	if (NovoMeiosDeMobilidade == NULL) return NULL;	//pode não haver memória!!!

	NovoMeiosDeMobilidade->Id = Id;
	strcpy(NovoMeiosDeMobilidade->Tipo, Tipo);
	NovoMeiosDeMobilidade->CargaBateria = CargaBateria;
	NovoMeiosDeMobilidade->Custo = Custo;
	NovoMeiosDeMobilidade->localizacao = localizacao;

	Historico* Hist = NULL;

	NovoMeiosDeMobilidade->Historico = Hist;

	NovoMeiosDeMobilidade->next = NULL;

	return NovoMeiosDeMobilidade;
}


MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* Header, MeiosDeMobilidade* NovoMeiosDeMobilidade) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteMeiosDeMobilidade(Header, NovoMeiosDeMobilidade->Id)) return Header;	//se existir não insere!

	if (Header == NULL) {		//lista vazia
		Header = NovoMeiosDeMobilidade;
	}
	else
	{
		//Posicionar-se no fim da lista
		MeiosDeMobilidade* Aux = Header;
		while (Aux->next != NULL) {
			Aux = Aux->next;
		}
		//insere no fim da lista
		Aux->next = NovoMeiosDeMobilidade;
	}
	return Header;
}


bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* Header, int IdMeiosDeMobilidade) {
	if (Header == NULL) return false;
	MeiosDeMobilidade* Aux = Header;
	while (Aux != NULL) {
		if (Aux->Id == IdMeiosDeMobilidade)
			return true;
		Aux = Aux->next;
	}
	return false;
}


void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* Header) {
	MeiosDeMobilidade* Aux = Header;
	while (Aux) {		//mesmo que while (aux!=NULL)
		MostraMeiosDeMobilidade(Aux);
		Aux = Aux->next;
	}
}

void MostraMeiosDeMobilidade(MeiosDeMobilidade* MeiosDeMobilidade) {
	if (MeiosDeMobilidade != NULL)
	{
		printf("\nMeio De Mobilidade Dados:\nMeio De Mobilidade ID: %d\n", MeiosDeMobilidade->Id);
		printf("Tipo: %s\n", MeiosDeMobilidade->Tipo);
		printf("Carga: %d\n", MeiosDeMobilidade->CargaBateria);
		printf("Custo: %d\n", MeiosDeMobilidade->Custo);
		printf("Localizacao: %f\n", MeiosDeMobilidade->localizacao);


		printf("\n-------------\n");
	}
}

MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id) {
	if (Header == NULL) return NULL;			//Lista vazia
	if (!ExisteMeiosDeMobilidade(Header, Id)) return Header;	//se não existe

	if (Header->Id == Id) {		//remove no inicio da lista
		MeiosDeMobilidade* Aux = Header;
		Header = Header->next;
		free(Aux);
	}
	else
	{
		MeiosDeMobilidade* Aux = Header;
		MeiosDeMobilidade* AuxAnt = Aux;
		while (Aux && Aux->Id != Id) {	//procura para revover
			AuxAnt = Aux;
			Aux = Aux->next;
		}
		if (Aux != NULL) {					//se encontrou, remove
			AuxAnt->next = Aux->next;
			free(Aux);
		}
	}
	return Header;
}


MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id) {
	if (Header == NULL) return NULL;		//lista vazia
	else
	{
		MeiosDeMobilidade* Aux = Header;
		while (Aux != NULL) {
			if (Aux->Id == Id) {
				return (Aux);		//encontrei
			}
			Aux = Aux->next;
		}
		return NULL;
	}
}

void AlteraMeiosDeMobilidade(MeiosDeMobilidade** Header, int Id, char* Tipo) {
	if (*Header != NULL) {
		MeiosDeMobilidade* Aux = ProcuraMeiosDeMobilidade(*Header, Id);
		if (Aux != NULL)		//se encontrou o jogo
		{
			strcpy(Aux->Tipo, Tipo);
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


