#define _CRT_SECURE_NO_WARNINGS

/**
*  @file Cliente.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Funcoes para Clientes
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Aluguer.h"
#include "Localizacao.h"

/**
*	@brief Cria MeioDeMobilidade.
*
*
*	@param [in] id				id do Cliente
*	@param [in] nome			nome do Cliente
*	@param [in] morada			morada do Cliente
*	@param [in] nif				nif do Cliente
*	@param [in] saldo			saldo do Cliente
*	@param [in] latitude		latitude do Cliente
*	@param [in] longitude		longitude do Cliente
*
*	@return novo Clientes
*
*/

Clientes* CriarClientes(int id, char nome[50], char morada[50], char nif[9], float saldo , float latitude , float longitude) {

	Clientes* novoCliente = (Clientes*)malloc(sizeof(Clientes));
	if (novoCliente == NULL) return NULL;

	novoCliente->id = id;
	strcpy(novoCliente->nome, nome);
	strcpy(novoCliente->morada, morada);
	strcpy(novoCliente->nif, nif);
	novoCliente->saldo = saldo;

	Aluguer* ativ = NULL;

	novoCliente->aluguer = ativ;

	novoCliente->latitude = latitude;
	novoCliente->longitude = longitude;


	novoCliente->next = NULL;

	return novoCliente;
}

/**
*	@brief Insere Cliente na lista de Clientes.
*
*
*	@param [in] header						header da lista de Clientes
*	@param [in] novoCliente					novo Cliente
*
*	@return header da lista de Clientes;
*
*
*/

Clientes* InsereClienteNoFim(Clientes* header, Clientes* novoCliente) {
	//Verificar se o novo cliente já existe
	if (ExisteCliente(header, novoCliente->id)) return header;

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

/**
*	@brief Ver se Cliente existe.
*
*
*	@param [in] header						header da lista de Clientes
*	@param [in] idCliente					id do Cliente da lista total
*
*	@return True/False;
*
*/
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

/**
*	@brief Lista os Clientes que Existem.
*
*
*	@param [in] header					header da lista de Clientes
*
*/
void MostrarListaClientes(Clientes* header) {
	Clientes* aux = header;
	while (aux) {
		MostraCliente(aux);
		aux = aux->next;
	}
}


/**
*	@brief Lista os Clientes que Existem , e escreve.
*
*
*	@param [in] cliente					header da lista de Clientes
*
*/
void MostraCliente(Clientes* cliente) {
	if (cliente != NULL)
	{
		printf("\nCliente ID: %d\n", cliente->id);
		printf("Nome: %s\n", cliente->nome);
		printf("Morada: %s\n", cliente->morada);
		printf("NIF: %s\n", cliente->nif);
		printf("Latitude: %f\n", cliente->latitude);
		printf("Longitude: %f\n", cliente->longitude);
		printf("\nSaldo: %.2f\n", cliente->saldo);

		printf("\n-------------\n");
	}
}

/**
*	@brief Remove Cliente na lista de Clientes.
*
*
*	@param [in] header					header da lista de Clientes
*	@param [in] id						id Cliente
*
*	@return header da lista de Clientes;
*
*
*/
Clientes* RemoverCliente(Clientes* header, int id) {
	if (header == NULL) return NULL;			
	if (!ExisteCliente(header, id)) return header;	//se não existe retorna

	if (header->id == id) {		//Remove no inicio da lista
		Clientes* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		Clientes* aux = header;
		Clientes* auxAnt = aux;
		while (aux && aux->id != id) {	//Procura para revover
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//Se encontrou remove
			auxAnt->next = aux->next;
			free(aux);
		}
	}
	return header;
}

/**
*	@brief Procura Cliente na lista de Clientes.
*
*
*	@param [in] header					header da lista de Clientes
*	@param [in] id						id Cliente
*
*	@return header da lista de Clientes;
*
*
*/
Clientes* ProcuraClientes(Clientes* header, int id) {
	if (header == NULL) return NULL;		
	else
	{
		Clientes* aux = header;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);	
			}
			aux = aux->next;
		}
		return NULL;
	}
}


/**
*	@brief Altera Cliente na lista de Clientes.
*
*
*	@param [in] header					header da lista de Clientes
*	@param [in] id						id Cliente
*	@param [in] nome					nome Cliente
*
*
*/
void AlteraCliente(Clientes** header, int id, char* nome) {
	if (*header != NULL) {
		Clientes* aux = ProcuraClientes(*header, id);
		if (aux != NULL)
		{
			strcpy(aux->nome, nome);
		}
	}
}


/**
*	@brief Regista um Aluguer de um Meio de Mobilidade pelo o Cliente
*
*
*	@param [in] headerCliente					header da lista de Clientes
*	@param [in] headerMeios						header da lista de MeiosDeMobilidade
*	@param [in] headerAluguerTotal				header da lista de Aluguer
*	@param [in] idCliente						id Cliente
*	@param [in] idMeios							id Meio De Mobilidade
*
*
*/
int RegistoAluguer(Clientes** headerCliente, MeiosDeMobilidade** headerMeios , Aluguer** headerAluguerTotal, int idCliente, int idMeios) {


	Clientes* cliente = ProcuraClientes(*headerCliente, idCliente);
	MeiosDeMobilidade* meio = ProcuraMeiosDeMobilidade(*headerMeios, idMeios);

	if (cliente == NULL) return 0;
	if (meio == NULL) return 0;

	if (cliente->saldo >= meio->custo)
	{
		cliente->saldo = cliente->saldo - meio->custo;

		Aluguer* atividades = (Aluguer*)malloc(sizeof(Aluguer));
		Aluguer* atividadesMeios = (Aluguer*)malloc(sizeof(Aluguer));

		int idClienteRegisto = 0;
		int idMeioRegisto = 0;

		if (cliente->aluguer != NULL)
		{
			idClienteRegisto = CountAlugueres(cliente->aluguer);
		}


		if (meio->aluguer != NULL)
		{
			idMeioRegisto = CountAlugueres(meio->aluguer);

		}


		atividades = CriarAluguerListaTotal(idClienteRegisto, meio->custo, "Ativo", cliente->id, meio->id);
		atividadesMeios = CriarAluguerListaTotal(idMeioRegisto, meio->custo, "Ativo", cliente->id, meio->id);

		InsertAlugueresCliente(cliente, atividades);
		InsertAlugueresMeio(meio, atividadesMeios);


		int idAluguerListaTotal = CountAluguerListaTotal(*headerAluguerTotal);

		Aluguer* aluguerNovo = CriarAluguerListaTotal(idAluguerListaTotal+1, atividades->custo , atividades->estadoDoAluguer , cliente->id , meio->id);
		*headerAluguerTotal = InsereAluguerListaTotalNoFim(*headerAluguerTotal, aluguerNovo);

	}
	

}

/**
*	@brief Conta Clientes da lista total.
*
*
*	@param [in] header					header da lista de Clientes
*
*	@return Quantos Clientes Tem;
*
*/
int CountClientes(Clientes* head) {
	int count = 0;
	Clientes* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}


/**
*	@brief Le e Armazena Clientes por txt file.
*
*
*	@param [in] filename				Path do Txt file
*	@param [in] header					header da lista de Clientes
*
*	@return header da lista de Clientes;
*
*/
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
		//Remove \n e \0
		line[strcspn(line, "\n")] = '\0';


		Clientes* novoCliente = (Clientes*)malloc(sizeof(Clientes));

		// Ve linha a linha separado por ";"
		token = strtok(line, ";");
		novoCliente->id = atoi(token);
		token = strtok(NULL, ";");
		strcpy(novoCliente->nome, token);
		token = strtok(NULL, ";");
		strcpy(novoCliente->morada, token);
		token = strtok(NULL, ";");
		strcpy(novoCliente->nif, token);
		token = strtok(NULL, ";");
		novoCliente->saldo = atoi(token);
		token = strtok(NULL, ";");
		novoCliente->latitude = atof(token);
		token = strtok(NULL, ";");
		novoCliente->longitude = atof(token);


		Aluguer* ativ = NULL;

		novoCliente->aluguer = ativ;
		novoCliente->next = NULL;


		header = InsereClienteNoFim(header,novoCliente); // Insere MeiosDeMobilidade

	}

	return header;

	fclose(fp);
}

/**
*	@brief Grava Clientes no bin file.
*
*
*	@param [in] nomeFicheiro			Path do bin file
*	@param [in] header					header da lista de Clientes
*
*	@return True/False;
*
*/
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

/**
*	@brief Le e Armazena Clientes por um bin file.
*
*
*	@param [in] nomeFicheiro				header da lista de Clientes
*
*	@return header da lista de Clientes;
*
*/
Clientes* LerClientesBinario(char* nomeFicheiro) {
	FILE* fp;
	Clientes* header = NULL;
	Clientes* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Clientes*)malloc(sizeof(Clientes))) && fread(auxAnt, sizeof(Clientes), 1, fp)) {
		Clientes* aux = CriarClientes(auxAnt->id, auxAnt->nome, auxAnt->morada, auxAnt->nif, auxAnt->saldo, auxAnt->latitude ,auxAnt->longitude);
		header = InsereClienteNoFim(header, aux);
	}
	fclose(fp);
	return header;
}


/**
*	@brief Insere Clientes mas na consola
*
*	@return header da lista de Clientes;
*
*/
Clientes* InserirPorEscreverCliente() {


	int id;
	char nome[50];
	char morada[50]; 
	char nif[9];
	float saldo;
	float latitude;
	float longitude;

	printf("\n\nDigite o id do cliente: ");
	scanf("%d", &id);
	printf("\nDigite o nome do cliente: ");
	scanf("%s", &nome);
	printf("\nDigite a morada do cliente: ");
	scanf("%s", &morada);
	printf("\nDigite o nif do cliente: ");
	scanf("%s", &nif);
	printf("\nDigite o saldo do cliente: ");
	scanf("%f", &saldo);
	printf("\nDigite a latitude do cliente: ");
	scanf("%f", &latitude);
	printf("\nDigite a longitude do cliente: ");
	scanf("%f", &longitude);

	Clientes* clienteNovo = CriarClientes(id,nome,morada,nif,saldo,latitude,longitude);

	return clienteNovo;

}

/**
*	@brief Altera Clientes mas na consola
*
*	@return 0;
*
*/
int AlterarPorEscreverCliente(Clientes* headClientes) {


	int id;
	char nome[50];

	printf("\n\nDigite o id do cliente que quer alterar: ");
	scanf("%d", &id);
	printf("\nDigite o novo nome do cliente: ");
	scanf("%s", &nome);

	AlteraCliente(&headClientes, id, nome);

	return 0;

}

/**
*	@brief Altera Clientes mas na consola
*
*	@return 0;
*
*/
int AlterarPorEscreverClienteWindowCliente(Clientes* headClientes , int idCliente) {

	char nome[50];

	printf("\nDigite o novo nome do cliente: ");
	scanf("%s", &nome);

	AlteraCliente(&headClientes, idCliente, nome);

	return 0;

}

/**
*	@brief Remove Clientes mas na consola
*
*	@return 0;
*
*/
int RemoverPorEscreverCliente(Clientes* headClientes) {


	int id;
	char nome[50];

	printf("\n\nDigite o id do cliente que quer eliminar: ");
	scanf("%d", &id);

	RemoverCliente(headClientes, id);

	return 0;

}

/**
*	@brief Registar Aluguer na consola.
*
*
*	@param [in] headClientes				header da lista de Clientes
*	@param [in] headAluguer					header da lista de Aluguer
*	@param [in] headMeio					header da lista de MeiosDeMobilidade
*
*/

int RegistoPorEscrever(Clientes* headClientes , Aluguer* headAluguer , MeiosDeMobilidade* headMeio ) {

	int idCliente;
	int idMeio;

	printf("\n\nDigite o id do cliente que quer registar um aluguer: ");
	scanf("%d", &idCliente);
	printf("\nDigite o id do meio de mobilidade : ");
	scanf("%d", &idMeio);

	RegistoAluguer(&headClientes, &headMeio, &headAluguer, idCliente, idMeio);
	return 0;

}


/**
*	@brief Registar Aluguer na consola Cliente.
*
*
*	@param [in] headClientes				header da lista de Clientes
*	@param [in] headAluguer					header da lista de Aluguer
*	@param [in] headMeio					header da lista de MeiosDeMobilidade
*
*/

int RegistoPorEscreverClienteWindow(Clientes* headClientes, Aluguer* headAluguer, MeiosDeMobilidade* headMeio, int idCliente) {

	int idMeio;

	printf("\nDigite o id do meio de mobilidade : ");
	scanf("%d", &idMeio);

	RegistoAluguer(&headClientes, &headMeio, &headAluguer, idCliente, idMeio);
	return 0;

}


/**
*	@brief Procurar por um Raio Meios de um tipo
*
*
*	@param [in] headClientes				header da lista de Clientes
*	@param [in] headAluguer					header da lista de Aluguer
*	@param [in] headMeio					header da lista de MeiosDeMobilidade
*
*/

int ProcurarRaioMeioCliente(Clientes* headClientes, MeiosDeMobilidade* headMeio, int idCliente) {

	char meioTipo[100];

	printf("\nDigite o tipo do meio de mobilidade que quer encontrar: ");
	scanf("%s", &meioTipo);

	system("cls");

	LocalizacaoRaioClienteMeio(ProcuraClientes(headClientes, idCliente), headMeio, 500.0, meioTipo);
	return 0;

}


/**
*	@brief Cliente vai a Meio
*
*
*	@param [in] headClientes				header da lista de Clientes
*	@param [in] headAluguer					header da lista de Aluguer
*	@param [in] headMeio					header da lista de MeiosDeMobilidade
*
*/

int ClienteParaMeioLocalizacao(Clientes* headClientes, MeiosDeMobilidade* headMeio , LocalizacaoPostos* headListaPostos , int idCliente) {


	int idMeio;

	printf("\nDigite o meio de mobilidade que quer ir: ");
	scanf("%d", &idMeio);

	system("cls");

	if (ExisteMeiosDeMobilidade(headMeio, idMeio))
	{
		DistanciaClienteAMeioTotal(ProcuraClientes(headClientes, idCliente), ProcuraMeiosDeMobilidade(headMeio, idMeio), headListaPostos);
	}


	return 0;

}


/**
*	@brief Cliente vai a Posto
*
*
*	@param [in] headClientes				header da lista de Clientes
*	@param [in] headAluguer					header da lista de Aluguer
*	@param [in] headMeio					header da lista de MeiosDeMobilidade
*
*/

int ClienteParaPostoLocalizacao(Clientes* headClientes, LocalizacaoPostos* headListaPostos, int idCliente) {


	int idPosto;

	printf("\nDigite o posto que quer ir: ");
	scanf("%d", &idPosto);

	system("cls");

	if (ExistePosto(headListaPostos, idPosto))
	{
		DistanciaClienteAPostoTotal(ProcuraClientes(headClientes, idCliente), headListaPostos , idPosto);
	}


	return 0;

}
