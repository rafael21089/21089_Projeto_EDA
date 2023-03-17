
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"

// ----------------------------------------


Gestor* CriarNovoGestor(int Id, char Utilizador[50], MeiosDeMobilidade* MeiosDeMobilidadeExistentes, Clientes* ClienteExistentes) {

	Gestor* NovoGestor = (Gestor*)malloc(sizeof(Gestor));
	if (NovoGestor == NULL) return NULL;

	NovoGestor->Id = Id;
	strcpy(NovoGestor->Utilizador, Utilizador);
	NovoGestor->Meios = MeiosDeMobilidadeExistentes;
	NovoGestor->Clientes = ClienteExistentes;

	NovoGestor->next = NULL;

	return NovoGestor;
}

Gestor* InsereGestorNoFim(Gestor* Header, Gestor* NovoGestor) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteCliente(Header, NovoGestor->Id)) return Header;	//se existir não insere!

	if (Header == NULL) {		//lista vazia
		Header = NovoGestor;
	}
	else
	{
		//Posicionar-se no fim da lista
		Gestor* Aux = Header;
		while (Aux->next != NULL) {
			Aux = Aux->next;
		}
		//insere no fim da lista
		Aux->next = NovoGestor;
	}
	return Header;
}


bool ExisteGestor(Gestor* Header, int IdGestor) {
	if (Header == NULL) return false;
	Gestor* Aux = Header;
	while (Aux != NULL) {
		if (Aux->Id == IdGestor)
			return true;
		Aux = Aux->next;
	}
	return false;
}


void MostrarListaGestor(Gestor* Header) {
	Gestor* Aux = Header;
	while (Aux) {		
		MostraGestor(Aux);
		Aux = Aux->next;
	}
}

void MostraGestor(Gestor* Gestor) {
	if (Gestor != NULL)
	{
		printf("\Gestor:\nMeio De Mobilidade ID: %d\n", Gestor->Id);
		printf("Utilizador: %s\n", Gestor->Utilizador);
		printf("\n-------------\n");
	}
}

Gestor* RemoverGestor(Gestor* Header, int Id) {
	if (Header == NULL) return NULL;			//Lista vazia
	if (!ExisteGestor(Header, Id)) return Header;	//se não existe

	if (Header->Id == Id) {		//remove no inicio da lista
		Gestor* Aux = Header;
		Header = Header->next;
		free(Aux);
	}
	else
	{
		Gestor* Aux = Header;
		Gestor* AuxAnt = Aux;
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

Gestor* ProcuraGestor(Gestor* Header, int Id) {
	if (Header == NULL) return NULL;		//lista vazia
	else
	{
		Gestor* Aux = Header;
		while (Aux != NULL) {
			if (Aux->Id == Id) {
				return (Aux);		//encontrei
			}
			Aux = Aux->next;
		}
		return NULL;
	}
}

void AlteraGestor(Gestor** Header, int Id, char* Utilizador) {
	if (*Header != NULL) {
		Gestor* Aux = ProcuraGestor(*Header, Id);
		if (Aux != NULL)		//se encontrou o jogo
		{
			strcpy(Aux->Utilizador, Utilizador);
		}
	}
}