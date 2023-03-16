
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"


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


void RegistoAluguer(Clientes** HeaderCliente, MeiosDeMobilidade** HeaderMeios , int IdCliente , int IdMeios) {


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

	insertHistoricoCliente(Cliente,Historicos);
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

int CountMeios(struct MeiosDeMobilidade* head) {
	int count = 0;
	MeiosDeMobilidade* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}



// ---------------------------


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