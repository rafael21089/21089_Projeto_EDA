#define _CRT_SECURE_NO_WARNINGS



/**
*  @file Aluguer.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Funcoes para Alugueres

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Aluguer.h"



/**
*	@brief Conta quantos alugueres existem.
*
*
*	@param [in] head	Head da lista Aluguer
*	@return Quantos Alugueres Tem;
*
*/

int CountAlugueres(Aluguer* head) {
	int count = 0;
	Aluguer* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

/**
*	@brief Insere Aluguer no Cliente.
*
*
*	@param [in] cliente		Head da lista Cliente
*	@param [in] aluguer		Head da lista Aluguer
*
*/


void InsertAlugueresCliente(Clientes* cliente, Aluguer* aluguer) {
	aluguer->next = cliente->aluguer;
	cliente->aluguer = aluguer;
}

/**
*	@brief Insere Aluguer no MeiosDeMobilidade.
*
*
*	@param [in] meio		Head da lista MeiosDeMobilidade
*	@param [in] aluguer		Head da lista Aluguer
*
*/

void InsertAlugueresMeio(MeiosDeMobilidade* meio, Aluguer* aluguer) {
	aluguer->next = meio->aluguer;
	meio->aluguer = aluguer;
}

/**
*	@brief Insere Aluguer no MeiosDeMobilidade.
*
*
*	@param [in] gestor				Head da lista Gestor
*	@param [in] aluguerTotal		Head da lista Aluguer
*
*/

void InsertAlugerTotalGestor(Gestor* gestor, Aluguer* aluguerTotal) {
	aluguerTotal->next = gestor->todosAlugueres;
	gestor->todosAlugueres = aluguerTotal;
}


/**
*	@brief Cria Aluguer.
*
*
*	@param [in] id					id do Aluguer
*	@param [in] custo				custo do Aluguer
*	@param [in] estadoDoAluguer		estado Do Aluguer
*	@param [in] clienteId			id Cliente
*	@param [in] meioUsadoId			id Meio
* 
*	@return novo Aluguer;
*
*/

Aluguer* CriarAluguerListaTotal(int id, float custo, char* estadoDoAluguer, int clienteId, int meioUsadoId) {

	Aluguer* novoAluguerListaTotal = (Aluguer*)malloc(sizeof(Aluguer));
	if (novoAluguerListaTotal == NULL) return NULL;

	novoAluguerListaTotal->id = id;
	novoAluguerListaTotal->custo = custo;
	strcpy(novoAluguerListaTotal->estadoDoAluguer, estadoDoAluguer);
	novoAluguerListaTotal->clienteId = clienteId;
	novoAluguerListaTotal->meioUsadoId = meioUsadoId;


	novoAluguerListaTotal->next = NULL;

	return novoAluguerListaTotal;
}


/**
*	@brief Insere Aluguer na lista de Alugueres.
*
*
*	@param [in] header								header da lista de Alugueres
*	@param [in] novoAluguerListaTotal				novo Aluguer
*
*	@return header da lista de Alugueres;
*
*/

Aluguer* InsereAluguerListaTotalNoFim(Aluguer* header, Aluguer* novoAluguerListaTotal) {
	//Verificar se o novo aluguer já existe!!!
	if (ExisteAluguerListaTotal(header, novoAluguerListaTotal->id)) return header;	//se existir não insere!

	if (header == NULL) {
		header = novoAluguerListaTotal;
	}
	else
	{
		Aluguer* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		
		aux->next = novoAluguerListaTotal; //Insere no fim da lista
	}
	return header;
}

/**
*	@brief Ve se existe Aluguer.
*
*
*	@param [in] header								header da lista de Alugueres
*	@param [in] idAluguerListaTotal					id do Aluguer da lista total
*
*	@return True/False;
*
*/

bool ExisteAluguerListaTotal(Aluguer* header, int idAluguerListaTotal) {
	if (header == NULL) return false;
	Aluguer* aux = header;
	while (aux != NULL) {
		if (aux->id == idAluguerListaTotal)
			return true;
		aux = aux->next;
	}
	return false;
}

/**
*	@brief Conta Aluguer da lista total.
*
*
*	@param [in] header					header da lista de Alugueres
*
*	@return Quantos Alugueres Tem;
*
*/
int CountAluguerListaTotal(Aluguer* head) {
	int count = 0;
	Aluguer* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}


/**
*	@brief Le e Armazena Aluguer por txt file.
*
*
*	@param [in] filename				Path do Txt file
*	@param [in] header					header da lista de Alugueres
*
*	@return header da lista de Alugueres;
*
*/
Aluguer* LerEArmazenarAluguerListaTotal(char* filename, Aluguer* header) {

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


		Aluguer* novoAluguerListaTotal = (Aluguer*)malloc(sizeof(Aluguer));

		// Ve linha a linha separado por ";"
		token = strtok(line, ";");
		novoAluguerListaTotal->id = atoi(token);
		token = strtok(NULL, ";");
		novoAluguerListaTotal->custo = atof(token);
		token = strtok(NULL, ";");
		strcpy(novoAluguerListaTotal->estadoDoAluguer, token);
		token = strtok(NULL, ";");
		novoAluguerListaTotal->clienteId = atoi(token);
		token = strtok(NULL, ";");
		novoAluguerListaTotal->meioUsadoId = atoi(token);

		novoAluguerListaTotal->next = NULL;

		header = InsereAluguerListaTotalNoFim(header, novoAluguerListaTotal); // Insere Aluguer
	}

	return header;

	fclose(fp);
}

/**
*	@brief Grava Aluguer no bin file.
*
*
*	@param [in] nomeFicheiro			Path do bin file
*	@param [in] header					header da lista de Alugueres
*
*	@return True/False;
*
*/
bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Aluguer* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	Aluguer* aux = header;
	while (aux) {
		// Escreve no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Aluguer), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


/**
*	@brief Le e Armazena Aluguer por um bin file.
*
*
*	@param [in] nomeFicheiro				header da lista de Alugueres
*
*	@return header da lista de Alugueres;
*
*/
Aluguer* LerAluguerListaTotalBinario(char* nomeFicheiro) {
	FILE* fp;
	Aluguer* header = NULL;
	Aluguer* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	//Ler o registos do ficheiro binario
	while ((auxAnt = (Aluguer*)malloc(sizeof(Aluguer))) && fread(auxAnt, sizeof(Aluguer), 1, fp)) {
		Aluguer* aux = CriarAluguerListaTotal(auxAnt->id, auxAnt->custo, auxAnt->estadoDoAluguer, auxAnt->clienteId, auxAnt->meioUsadoId); //Cria Aluguer com valores recebidos
		header = InsereAluguerListaTotalNoFim(header, aux); //Insere Aluguer
	}
	fclose(fp);
	return header;
}

/**
*	@brief Distribui o Historico de Alugueres por cada Cliente e Meio expecifico.
*
*
*	@param [in] header					header da lista de Alugueres
*	@param [in] headerMeios				header da lista de MeiosDeMobilidade
*	@param [in] headerClientes			header da lista de Clientes
*
*/

void DistribuirAlugueresHistorico(Aluguer* header, MeiosDeMobilidade* headerMeios, Clientes* headerClientes) {

	Aluguer* auxAluguer = header;
	Clientes* auxClientes = headerClientes;
	MeiosDeMobilidade* auxMeio = headerMeios;

	while (auxClientes != NULL)
	{
		Aluguer* auxClienteAluguerOriginal = (Aluguer*)malloc(sizeof(Aluguer));

		while (auxAluguer != NULL)
		{
			if (auxClientes->id == auxAluguer->clienteId)
			{

				auxClienteAluguerOriginal->id = auxAluguer->id;
				auxClienteAluguerOriginal->custo = auxAluguer->custo;
				strcpy(auxClienteAluguerOriginal->estadoDoAluguer, auxAluguer->estadoDoAluguer);
				auxClienteAluguerOriginal->clienteId = auxAluguer->clienteId;
				auxClienteAluguerOriginal->meioUsadoId = auxAluguer->meioUsadoId;
				auxClienteAluguerOriginal->next = NULL;

				auxClientes->aluguer = auxClienteAluguerOriginal;


			}
			auxAluguer = auxAluguer->next;

		}

		auxClientes = auxClientes->next;
		auxAluguer = header; 
	}

	auxAluguer = header;

	while (auxMeio != NULL)
	{
		Aluguer* auxMeioAluguer = (Aluguer*)malloc(sizeof(Aluguer));

		while (auxAluguer != NULL)
		{
			if (auxMeio->id == auxAluguer->meioUsadoId)
			{
				auxMeioAluguer->id = auxAluguer->id;
				auxMeioAluguer->custo = auxAluguer->custo;
				strcpy(auxMeioAluguer->estadoDoAluguer, auxAluguer->estadoDoAluguer);
				auxMeioAluguer->clienteId = auxAluguer->clienteId;
				auxMeioAluguer->meioUsadoId = auxAluguer->meioUsadoId;
				auxMeioAluguer->next = NULL;;

				auxMeio->aluguer = auxMeioAluguer;
			}
			auxAluguer = auxAluguer->next;
		}
		auxMeio = auxMeio->next;
		auxAluguer = header;  
	}


}


/**
*	@brief Listar Alugueres por Cliente
*
*
*	@param [in] header					header da lista de Alugueres
*	@param [in] idCliente				Id do Cliente
*
*/

int ListarClienteAlugueresById(Aluguer* header, int idCliente) {

	Aluguer* aux = header;

	system("cls");

	printf("\n\n\n ----------- Listagem ----------\n");

	while (aux != NULL)
	{
		if (aux->clienteId == idCliente)
		{
			printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);
		}

		aux = aux->next;
	}

	return 0;
}

/**
*	@brief Funcao para insercao de valores para listagem por cliente id
*
*
*	@param [in] header					header da lista de Alugueres
*
*/
int AluguerClientePorEscrever(Aluguer* headAluguer) {

	int idCliente;

	printf("\n\nDigite o id do cliente que quer ver os alugueres: ");
	scanf("%d", &idCliente);


	ListarClienteAlugueresById(headAluguer, idCliente);

	return 0;

}

/**
*	@brief Listar Alugueres por Meio
*
*
*	@param [in] header					header da lista de Alugueres
*	@param [in] idMeios					Id do Meio
*
*/
int ListarMeiosAlugueresById(Aluguer* header, int idMeios) {

	Aluguer* aux = header;

	system("cls");

	printf("\n\n\n ----------- Listagem ----------\n");


	while (aux != NULL)
	{
		if (aux->meioUsadoId == idMeios)
		{
			printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);
		}

		aux = aux->next;
	}

	return 0;
}

/**
*	@brief Funcao para insercao de valores para listagem por meio id
*
*
*	@param [in] headAluguer					header da lista de Alugueres
*
*/
int AluguerMeiosPorEscrever(Aluguer* headAluguer) {

	int idMeios;


	printf("\n\nDigite o id do meio de mobilidade que quer ver os alugueres: ");
	scanf("%d", &idMeios);


	ListarMeiosAlugueresById(headAluguer, idMeios);

	return 0;

}


/**
*	@brief Lista todos os Alugueres Existentes
*
*
*	@param [in] header					header da lista de Alugueres
*
*/

int ListarTodosAlugueres(Aluguer* header) {

	system("cls");

	printf("\n\n\n ----------- Listagem ----------\n");

	Aluguer* aux = header;

	while (aux != NULL)
	{

		printf(" ID Aluguer: %d , Custo: %f, Estado: %s , Cliente Id: %d, Meio Usado Id: %d \n", aux->id, aux->custo, aux->estadoDoAluguer, aux->clienteId, aux->meioUsadoId);

		aux = aux->next;
	}

	return 0;
}




