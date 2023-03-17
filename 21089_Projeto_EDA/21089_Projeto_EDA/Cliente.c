#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Cliente.h"


Clientes* CriarClientes(int Id, char Nome[50], char Morada[50], char NIF[9], float Saldo) {

	Clientes* NovoCliente = (Clientes*)malloc(sizeof(Clientes));
	if (NovoCliente == NULL) return NULL;

	NovoCliente->Id = Id;
	strcpy(NovoCliente->Nome, Nome);
	strcpy(NovoCliente->Morada, Morada);
	strcpy(NovoCliente->NIF, NIF);
	NovoCliente->Saldo = Saldo;

	Historico* Hist = NULL;

	NovoCliente->Historico = Hist;


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
	while (Aux) {
		MostraCliente(Aux);
		Aux = Aux->next;
	}
}



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

Clientes* RemoverCliente(Clientes* Header, int Id) {
	if (Header == NULL) return NULL;			//Lista vazia
	if (!ExisteCliente(Header, Id)) return Header;	//se não existe

	if (Header->Id == Id) {		//remove no inicio da lista
		Clientes* Aux = Header;
		Header = Header->next;
		free(Aux);
	}
	else
	{
		Clientes* Aux = Header;
		Clientes* AuxAnt = Aux;
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


Clientes* ProcuraClientes(Clientes* Header, int Id) {
	if (Header == NULL) return NULL;		//lista vazia
	else
	{
		Clientes* Aux = Header;
		while (Aux != NULL) {
			if (Aux->Id == Id) {
				return (Aux);		//encontrei
			}
			Aux = Aux->next;
		}
		return NULL;
	}
}

void AlteraCliente(Clientes** Header, int Id, char* Nome) {
	if (*Header != NULL) {
		Clientes* Aux = ProcuraClientes(*Header, Id);
		if (Aux != NULL)		//se encontrou o jogo
		{
			strcpy(Aux->Nome, Nome);
		}
	}
}


void RegistoAluguer(Clientes** HeaderCliente, MeiosDeMobilidade** HeaderMeios, int IdCliente, int IdMeios) {


	Clientes* Cliente = ProcuraClientes(*HeaderCliente, IdCliente);
	MeiosDeMobilidade* Meio = ProcuraMeiosDeMobilidade(*HeaderMeios, IdMeios);

	Historico* Historicos = (Historico*)malloc(sizeof(Historico));
	Historico* HistoricosMeios = (Historico*)malloc(sizeof(Historico));

	int IdClienteRegisto = 0;
	int IdMeioRegisto = 0;

	if (Cliente->Historico != NULL)
	{
		IdClienteRegisto = CountHistorico(Cliente->Historico);
	}


	if (Meio->Historico != NULL)
	{
		IdMeioRegisto = CountHistorico(Meio->Historico);

	}


	Historicos->Id = IdClienteRegisto;
	Historicos->EstadoDoAluguer = ATIVO;
	Historicos->Custo = Meio->Custo;
	Historicos->Cliente = Cliente;
	Historicos->MeioUsado = Meio;
	Historicos->next = NULL;

	HistoricosMeios->Id = IdMeioRegisto;
	HistoricosMeios->EstadoDoAluguer = ATIVO;
	HistoricosMeios->Custo = Meio->Custo;
	HistoricosMeios->Cliente = Cliente;
	HistoricosMeios->MeioUsado = Meio;
	HistoricosMeios->next = NULL;

	insertHistoricoCliente(Cliente, Historicos);
	insertHistoricoMeio(Meio, HistoricosMeios);

}

int CountClientes(Clientes* Head) {
	int Count = 0;
	Clientes* Current = Head;

	while (Current != NULL) {
		Count++;
		Current = Current->next;
	}

	return Count;
}



