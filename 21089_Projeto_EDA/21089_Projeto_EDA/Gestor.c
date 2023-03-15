
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"


Clientes* CriarClientes(int Id, char Nome[50], char Morada[50], char NIF[9], float Saldo) {

	Clientes* NovoCliente = (Clientes*)malloc(sizeof(Clientes));
	if (NovoCliente == NULL) return NULL;	//pode não haver memória!!!
	
	NovoCliente->Id = Id;
	strcpy(NovoCliente->Nome, Nome);
	strcpy(NovoCliente->Morada, Morada);
	strcpy(NovoCliente->NIF, NIF);
	NovoCliente->Saldo = Saldo;
	NovoCliente->next = NULL;

	return NovoCliente;
}

Clientes* InsereClienteNoFim(Clientes* Header, Clientes* NovoCliente) {
	//Verificar se o novo jogo já existe!!!
	if (ExisteCliente(Header, NovoCliente->Id)) return Header;	//se existir não insere!

	if (Header == NULL) {		//lista vazia
		Header = NovoCliente;
	}
	else
	{
		//Posicionar-se no fim da lista
		Clientes* Aux = Header;
		while (Aux->next != NULL) {
			Aux = Aux->next;
		}
		//insere no fim da lista
		Aux->next = NovoCliente;
	}
	return Header;
}


bool ExisteCliente(Clientes* Header, int IdCliente) {
	if (Header == NULL) return false;
	Clientes* Aux = Header;
	while (Aux != NULL) {
		if (Aux->Id == IdCliente)
			return true;
		Aux = Aux->next;
	}
	return false;
}


void MostrarListaClientes(Clientes* Header) {
	Clientes* Aux = Header;
	while (Aux) {		//mesmo que while (aux!=NULL)
		MostraCliente(Aux);
		Aux = Aux->next;
	}
}


/**
*	@brief Mostra dados de um nodo
*/
void MostraCliente(Clientes* Cliente) {
	if (Cliente != NULL)
	{
		printf("\nCliente Dados:\nCliente ID: %d\n", Cliente->Id);
		printf("Nome: %s\n", Cliente->Nome);
		printf("Morada: %s\n", Cliente->Morada);
		printf("NIF: %s\n", Cliente->NIF);
		printf("\nSaldo: %f\n", Cliente->Saldo);
		printf("\n-------------\n");
	}
}





// ---------------------------


MeiosDeMobilidade* CriarMeiosDeMobilidade(int Id, char Tipo[50], int CargaBateria, int Custo, float localizacao , Clientes* ClienteAUsar) {


	MeiosDeMobilidade* NovoMeiosDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));
	if (NovoMeiosDeMobilidade == NULL) return NULL;	//pode não haver memória!!!

	NovoMeiosDeMobilidade->Id = Id;
	strcpy(NovoMeiosDeMobilidade->Tipo, Tipo);
	NovoMeiosDeMobilidade->CargaBateria = CargaBateria;
	NovoMeiosDeMobilidade->Custo = Custo;
	NovoMeiosDeMobilidade->localizacao = localizacao;

	NovoMeiosDeMobilidade->ClienteAUsar = ClienteAUsar;

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

		Clientes* c = MeiosDeMobilidade->ClienteAUsar;

		if (c != NULL)
		{
			printf("\Cliente a usar: %s\n", c->Nome);

		}
		else
		{
			printf("\Cliente a usar: Ninguem");
		}

		printf("\n-------------\n");
	}
}