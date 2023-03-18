
#define _CRT_SECURE_NO_WARNINGS


/**
*  @file Gestor.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Funcoes para Gestor

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"

/**
*	@brief Cria Gestor.
*
*
*	@param [in] id								id do Gestor
*	@param [in] utilizador						utilizador do Gestor
*	@param [in] distrito						distrito Do Gestor
*	@param [in] meiosDeMobilidadeExistentes		MeioDeMobilidade para Gestor
*	@param [in] clienteExistentes				Clientes para Gestor
*	@param [in] aluguerTotal					Aluguer total para Gestor
*
*	@return novo Gestor
*
*/
Gestor* CriarNovoGestor(int id, char* utilizador, char* distrito, MeiosDeMobilidade* meiosDeMobilidadeExistentes, Clientes* clienteExistentes , Aluguer* aluguerTotal) {

	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));
	if (novoGestor == NULL) return NULL;

	novoGestor->id = id;
	strcpy(novoGestor->utilizador, utilizador);
	strcpy(novoGestor->distrito, distrito);
	novoGestor->meios = meiosDeMobilidadeExistentes;
	novoGestor->clientes = clienteExistentes;
	novoGestor->todosAlugueres = aluguerTotal;

	novoGestor->next = NULL;

	return novoGestor;
}

/**
*	@brief Insere Gestor na lista de Gestor.
*
*
*	@param [in] header								header da lista de Gestor
*	@param [in] novoGestor							novo Gestor
*
*	@return header da lista de Gestor;
*
*
*/
Gestor* InsereGestorNoFim(Gestor* header, Gestor* novoGestor) {
	//Verificar se o novo gestor já existe!!!
	if (ExisteGestor(header, novoGestor->id)) return header;	//se existir não insere!

	if (header == NULL) {		//lista vazia
		header = novoGestor;
	}
	else
	{
		//Posicionar-se no fim da lista
		Gestor* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novoGestor;
	}
	return header;
}

/**
*	@brief Ver se Gestor existe.
*
*
*	@param [in] header								header da lista de Gestor
*	@param [in] idGestor							id do Gestor da lista total
*
*	@return True/False;
*
*/
bool ExisteGestor(Gestor* header, int idGestor) {
	if (header == NULL) return false;
	Gestor* aux = header;
	while (aux != NULL) {
		if (aux->id == idGestor)
			return true;
		aux = aux->next;
	}
	return false;
}

/**
*	@brief Lista os Gestores que Existem.
*
*
*	@param [in] header				header da lista de Gestor
*
*/
void MostrarListaGestor(Gestor* header) {
	Gestor* aux = header;
	while (aux) {
		MostraGestor(aux);
		aux = aux->next;
	}
}

/**
*	@brief Lista os Gestores que Existem , e escreve.
*
*
*	@param [in] gestor					header da lista de Gestores
*
*/
void MostraGestor(Gestor* gestor) {
	if (gestor != NULL)
	{
		printf("\nGestor ID: %d\n", gestor->id);
		printf("Utilizador: %s\n", gestor->utilizador);
		printf("Distrito: %s\n", gestor->distrito);
		printf("\n-------------\n");
	}
}


/**
*	@brief Remove Gestor na lista de Gestores.
*
*
*	@param [in] header					header da lista de Gestor
*	@param [in] id						id Gestor
*
*	@return header da lista de Gestor;
*
*
*/
Gestor* RemoverGestor(Gestor* header, int id) {
	if (header == NULL) return NULL;			//Lista vazia
	if (!ExisteGestor(header, id)) return header;	//se não existe

	if (header->id == id) {		//remove no inicio da lista
		Gestor* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		Gestor* aux = header;
		Gestor* auxAnt = aux;
		while (aux && aux->id != id) {	//procura para revover
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->next = aux->next;
			free(aux);
		}
	}
	return header;
}

/**
*	@brief Procura Gestor na lista de Gestores.
*
*
*	@param [in] header					header da lista de Gestor
*	@param [in] id						id Gestor
*
*	@return header da lista de Gestor;
*
*
*/
Gestor* ProcuraGestor(Gestor* header, int id) {
	if (header == NULL) return NULL;		//lista vazia
	else
	{
		Gestor* aux = header;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);		//encontrou
			}
			aux = aux->next;
		}
		return NULL;
	}
}

/**
*	@brief Altera Gestor na lista de Gestores.
*
*
*	@param [in] header					header da lista de Gestor
*	@param [in] id						id Gestor
*	@param [in] utilizador				utilizador Gestor
*
*
*/
void AlteraGestor(Gestor** header, int id, char* utilizador) {
	if (*header != NULL) {
		Gestor* aux = ProcuraGestor(*header, id);
		if (aux != NULL)
		{
			strcpy(aux->utilizador, utilizador);
		}
	}
}



/**
*	@brief Le e Armazena Gestor por txt file.
*
*
*	@param [in] filename				Path do Txt file
*	@param [in] header					header da lista de Gestor
*
*	@return header da lista de Gestor;
*
*/
Gestor* LerEArmazenarGestor(char* filename, Gestor* header) {

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


		Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

		// Ve linha a linha separado por ";"
		token = strtok(line, ";");
		novoGestor->id = atoi(token);
		token = strtok(NULL, ";");
		strcpy(novoGestor->utilizador, token);
		token = strtok(NULL, ";");
		strcpy(novoGestor->distrito, token);

		Clientes* cliente = NULL;
		MeiosDeMobilidade* meios = NULL;
		Aluguer* todosAlugueres = NULL;

		novoGestor->clientes = cliente;
		novoGestor->meios = meios;
		novoGestor->todosAlugueres = todosAlugueres;

		novoGestor->next = NULL;


		header = InsereGestorNoFim(header, novoGestor); // Insere Gestor

	}

	return header;

	fclose(fp);
}

/**
*	@brief Grava Gestor no bin file.
*
*
*	@param [in] nomeFicheiro			Path do bin file
*	@param [in] header					header da lista de Gestor
*
*	@return True/False;
*
*/
bool GravarGestorBinario(char* nomeFicheiro, Gestor* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	Gestor* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(Gestor), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
*	@brief Le e Armazena Gestor por um bin file.
*
*
*	@param [in] nomeFicheiro				header da lista de Gestor
*
*	@return header da lista de Gestor;
*
*/
Gestor* LerGestorBinario(char* nomeFicheiro) {
	FILE* fp;
	Gestor* header = NULL;
	Gestor* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (Gestor*)malloc(sizeof(Gestor))) && fread(auxAnt, sizeof(Gestor), 1, fp)) {
		Gestor* aux = CriarNovoGestor(auxAnt->id, auxAnt->utilizador, auxAnt->distrito, NULL , NULL , NULL);
		header = InsereGestorNoFim(header, aux);
	}
	fclose(fp);
	return header;
}


/**
*	@brief Grava Meios de Mobilidade e Clientes nos Gestores todos
*
*
*	@param [in] gestor				header da lista de Gestor
*	@param [in] alugueresTotal		header da lista de Aluguer
*	@param [in] clientesHeader		header da lista de Clientes
*	@param [in] meiosHeader			header da lista de MeiosDeMobilidade
*
*	@return 0;
*
*/
int GravarMeiosEClientesNosGestores(Gestor* gestor , Aluguer* alugueresTotal , Clientes* clientesHeader , MeiosDeMobilidade* meiosHeader) {


	Gestor* aux = gestor;

	while (aux != NULL)
	{
		aux->clientes = clientesHeader;
		aux->meios = meiosHeader;
		aux->todosAlugueres = alugueresTotal;
		aux = aux->next;
	}



	return 0;
}


/**
*	@brief Insere Gestor mas na consola
*
*	@return header da lista de Gestor;
*
*/
Gestor* InserirPorEscreverGestor() {


	int id; 
	char utilizador[50]; 
	char distrito[50];

	printf("\n\nDigite o id do Gestor: ");
	scanf("%d", &id);
	printf("\nDigite o nome do utilizador: ");
	scanf("%s", &utilizador);
	printf("\nDigite o distrito: ");
	scanf("%s", &distrito);


	Gestor* gestorNovo = CriarNovoGestor(id, utilizador, distrito, NULL, NULL, NULL);

	return gestorNovo;

}

/**
*	@brief Altera Gestor mas na consola
* 
*	@param [in] headGestor			header da lista de Gestor
*
*	@return 0;
*
*/
int AlterarPorEscreverGestor(Gestor* headGestor) {


	int id;
	char utilizador[50];

	printf("\n\nDigite o id do Gestor: ");
	scanf("%d", &id);
	printf("\nDigite o novo nome de utilizador: ");
	scanf("%s", &utilizador);

	AlteraGestor(&headGestor, id, utilizador);

	return 0;

}

/**
*	@brief Remove Gestor mas na consola
* 
*	@param [in] headGestor				header da lista de Gestor
* 
*	@return 0;
*
*/
int RemoverPorEscreverGestor(Gestor* headGestor) {

	int id;

	printf("\n\nDigite o id do Gestor que quer eliminar: ");
	scanf("%d", &id);

	RemoverGestor(headGestor, id);

	return 0;

}


