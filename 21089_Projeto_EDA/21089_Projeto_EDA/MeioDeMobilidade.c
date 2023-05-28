#define _CRT_SECURE_NO_WARNINGS


/**
*  @file MeioDeMobilidade.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Funcoes para MeioDeMobilidade

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MeioDeMobilidade.h"


/**
*	@brief Cria MeioDeMobilidade.
*
*
*	@param [in] id					id do MeioDeMobilidade
*	@param [in] tipo				tipo do MeioDeMobilidade
*	@param [in] cargaBateria		carga da Bateria Do MeioDeMobilidade
*	@param [in] custo				custo Do MeioDeMobilidade
*	@param [in] cidade				cidade Do MeioDeMobilidade
*	@param [in] latitude			latitude Do MeioDeMobilidade
*	@param [in] longitude			longitude Do MeioDeMobilidade
*	@param [in] estado				estado Do MeioDeMobilidade
* 
*	@return novo MeioDeMobilidade
*
*/
MeiosDeMobilidade* CriarMeiosDeMobilidade(int id, char* tipo, int cargaBateria, float custo, float peso, char* cidade , float latitude , float longitude,bool estado) {


	MeiosDeMobilidade* novoMeiosDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));
	if (novoMeiosDeMobilidade == NULL) return NULL;	//se não haver memória

	novoMeiosDeMobilidade->id = id;
	strcpy(novoMeiosDeMobilidade->tipo, tipo);
	novoMeiosDeMobilidade->cargaBateria = cargaBateria;
	novoMeiosDeMobilidade->custo = custo;
	novoMeiosDeMobilidade->peso = peso;
	strcpy(novoMeiosDeMobilidade->cidade, cidade);
	novoMeiosDeMobilidade->latitude = latitude;
	novoMeiosDeMobilidade->longitude = longitude;
	novoMeiosDeMobilidade->estado = estado;

	Aluguer* ativ = NULL;

	novoMeiosDeMobilidade->aluguer = ativ;

	novoMeiosDeMobilidade->next = NULL;

	return novoMeiosDeMobilidade;
}

/**
*	@brief Insere MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header								header da lista de MeiosDeMobilidade
*	@param [in] novoMeiosDeMobilidade				novo MeiosDeMobilidade
*
*	@return header da lista de MeiosDeMobilidade;
* 
*
*/
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* header, MeiosDeMobilidade* novoMeiosDeMobilidade) {
	//Verificar se o novo Meio já existe
	if (ExisteMeiosDeMobilidade(header, novoMeiosDeMobilidade->id)) return header;	//se existir não insere

	if (header == NULL) {		//se for vazia
		header = novoMeiosDeMobilidade;
	}
	else
	{
		MeiosDeMobilidade* aux = header;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		
		aux->next = novoMeiosDeMobilidade; //insere no fim da lista
	}
	return header;
}

/**
*	@brief Ver se MeiosDeMobilidade existe.
*
*
*	@param [in] header								header da lista de MeiosDeMobilidade
*	@param [in] idMeiosDeMobilidade					id do MeiosDeMobilidade da lista total
*
*	@return True/False;
*
*/
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* header, int idMeiosDeMobilidade) {
	if (header == NULL) return false;
	MeiosDeMobilidade* aux = header;
	while (aux != NULL) {
		if (aux->id == idMeiosDeMobilidade)
			return true;
		aux = aux->next;
	}
	return false;
}


/**
*	@brief Lista os Meios De Mobilidade que Existem.
*
*
*	@param [in] header								header da lista de MeiosDeMobilidade
*
*/
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* header) {
	MeiosDeMobilidade* aux = header;
	while (aux) {		
		MostraMeiosDeMobilidade(aux);
		aux = aux->next;
	}
}

/**
*	@brief Lista os Meios De Mobilidade que Existem , e escreve.
*
*
*	@param [in] meiosDeMobilidade					header da lista de MeiosDeMobilidade
*
*/
void MostraMeiosDeMobilidade(MeiosDeMobilidade* meiosDeMobilidade) {
	if (meiosDeMobilidade != NULL)
	{
		printf("\nMeio De Mobilidade ID: %d\n", meiosDeMobilidade->id);
		printf("Tipo: %s\n", meiosDeMobilidade->tipo);
		printf("Carga: %d\n", meiosDeMobilidade->cargaBateria);
		printf("Custo: %.2f\n", meiosDeMobilidade->custo);
		printf("Peso: %.2f\n", meiosDeMobilidade->peso);
		printf("Cidade: %s\n", meiosDeMobilidade->cidade);
		printf("Latitude: %f\n", meiosDeMobilidade->latitude);
		printf("Longitude: %f\n", meiosDeMobilidade->longitude);
		printf("\nEstado: %s\n", meiosDeMobilidade->estado ? "Disponivel" : "Indisponivel");


		printf("\n-------------\n");
	}
}

/**
*	@brief Remove MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id MeiosDeMobilidade
*
*	@return header da lista de MeiosDeMobilidade;
*
*
*/
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* header, int id) {
	if (header == NULL) return NULL;			
	if (!ExisteMeiosDeMobilidade(header, id)) return header;	//se não existe retorna

	if (header->id == id) {		//Remove no inicio da lista
		MeiosDeMobilidade* aux = header;
		header = header->next;
		free(aux);
	}
	else
	{
		MeiosDeMobilidade* aux = header;
		MeiosDeMobilidade* auxAnt = aux;
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
*	@brief Procura MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id MeiosDeMobilidade
*
*	@return header da lista de MeiosDeMobilidade;
*
*
*/
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* header, int id) {
	if (header == NULL) return NULL;
	else
	{
		MeiosDeMobilidade* aux = header;
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
*	@brief Altera MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id MeiosDeMobilidade
*	@param [in] tipo						tipo MeiosDeMobilidade
*
*
*/
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** header, int id, char* tipo) {
	if (*header != NULL) {
		MeiosDeMobilidade* aux = ProcuraMeiosDeMobilidade(*header, id);
		if (aux != NULL)	
		{
			strcpy(aux->tipo, tipo);
		}
	}
}


/**
*	@brief Conta MeiosDeMobilidade da lista total.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*
*	@return Quantos Alugueres Tem;
*
*/

int CountMeios(MeiosDeMobilidade* head) {
	int count = 0;
	MeiosDeMobilidade* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

/**
*	@brief Le e Armazena MeiosDeMobilidade por txt file.
*
*
*	@param [in] filename				Path do Txt file
*	@param [in] header					header da lista de MeiosDeMobilidade
*
*	@return header da lista de MeiosDeMobilidade;
*
*/
MeiosDeMobilidade* LerEArmazenarMeiosDeMobilidade(char* filename, MeiosDeMobilidade* header) {

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


		MeiosDeMobilidade* novoMeioDeMobilidade = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade));

		// Ve linha a linha separado por ";"
		token = strtok(line, ";");
		novoMeioDeMobilidade->id = atoi(token); 
		token = strtok(NULL, ";");
		strcpy(novoMeioDeMobilidade->tipo, token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->cargaBateria = atoi(token); 
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->custo = atof(token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->peso = atof(token);
		token = strtok(NULL, ";");
		strcpy(novoMeioDeMobilidade->cidade, token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->latitude = atof(token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->longitude = atof(token);
		token = strtok(NULL, ";");
		novoMeioDeMobilidade->estado = (strcmp(token, "true") == 0);

		Aluguer* ativ = NULL;

		novoMeioDeMobilidade->aluguer = ativ;
		novoMeioDeMobilidade->next = NULL;


		header = InsereMeiosDeMobilidadeNoFim(header, novoMeioDeMobilidade); // Insere MeiosDeMobilidade
	}

	return header;

	fclose(fp);
}

/**
*	@brief Grava MeiosDeMobilidade no bin file.
*
*
*	@param [in] nomeFicheiro			Path do bin file
*	@param [in] header					header da lista de MeiosDeMobilidade
*
*	@return True/False;
*
*/
bool GravarMeiosDeMobilidadeBinario(char* nomeFicheiro, MeiosDeMobilidade* header) {
	FILE* fp;

	if (header == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	// Grava n registos no ficheiro
	MeiosDeMobilidade* aux = header;
	while (aux) {
		// Escrever no ficheiro os dados do registo de memória
		fwrite(aux, sizeof(MeiosDeMobilidade), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
*	@brief Le e Armazena MeiosDeMobilidade por um bin file.
*
*
*	@param [in] nomeFicheiro				header da lista de MeiosDeMobilidade
*
*	@return header da lista de MeiosDeMobilidade;
*
*/
MeiosDeMobilidade* LerMeiosDeMobilidadeBinario(char* nomeFicheiro) {
	FILE* fp;
	MeiosDeMobilidade* header = NULL;
	MeiosDeMobilidade* auxAnt;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	// Ler n registos do ficheiro
	while ((auxAnt = (MeiosDeMobilidade*)malloc(sizeof(MeiosDeMobilidade))) && fread(auxAnt, sizeof(MeiosDeMobilidade), 1, fp)) {
		MeiosDeMobilidade* aux = CriarMeiosDeMobilidade(auxAnt->id, auxAnt->tipo, auxAnt->cargaBateria, auxAnt->custo, auxAnt->peso, auxAnt->cidade , auxAnt->latitude , auxAnt->longitude , auxAnt->estado);
		header = InsereMeiosDeMobilidadeNoFim(header, aux);
	}
	fclose(fp);
	return header;
}

/**
*	@brief Listar MeiosDeMobilidade por Autonomia de forma decrescente
*
*
*	@param [in] header				header da lista de MeiosDeMobilidade
*
*	@return 0;
*
*/
int ListarMeioAutonomiaDecrescente(MeiosDeMobilidade* header) {

	int contador = 0;
	MeiosDeMobilidade* aux = header;

	system("cls");

	printf("\n\n\n ----------- Listagem ----------\n");

	// Conta o numero de nodes
	while (aux != NULL) {
		contador++;
		aux = aux->next;
	}

	// Cria um array de pointers
	MeiosDeMobilidade** nodeArray = (MeiosDeMobilidade**)malloc(sizeof(MeiosDeMobilidade*) * contador);
	if (nodeArray == NULL) {
		printf("Error: Failed to allocate memory for node array\n");
		return;
	}

	// Inicializa
	for (int i = 0; i < contador; i++) {
		nodeArray[i] = NULL;
	}

	// Insere os valores
	aux = header;
	for (int i = 0; i < contador; i++) {
		nodeArray[i] = aux;
		aux = aux->next;
	}

	// Poe os por ordem da Carga da Bateria
	for (int i = 0; i < contador - 1; i++) {
		for (int j = 0; j < contador - i - 1; j++) {
			if (nodeArray[j]->cargaBateria > nodeArray[j + 1]->cargaBateria) {
				MeiosDeMobilidade* temp = nodeArray[j];
				nodeArray[j] = nodeArray[j + 1];
				nodeArray[j + 1] = temp;
			}
		}
	}

	// Da Print de forma reversa para mostrar de forma decrescente
	for (int i = contador - 1; i >= 0; i--) {
		printf("id: %d, tipo: %s, cargaBateria: %d, custo: %.2f, Cidade: %s\n",
			nodeArray[i]->id, nodeArray[i]->tipo, nodeArray[i]->cargaBateria,
			nodeArray[i]->custo, nodeArray[i]->cidade);
	}

	free(nodeArray);

	return 0;

}

/**
*	@brief Listar MeiosDeMobilidade por geo Codigo
*
*
*	@param [in] header				header da lista de MeiosDeMobilidade
*	@param [in] geoCodigo			geoCodigo
*
*	@return header da lista de MeiosDeMobilidade;
*
*/
int ListarCidadePorGeoCodigo(MeiosDeMobilidade* header , char* geoCodigo) {

	MeiosDeMobilidade* aux = header;

	system("cls");

	printf("\n\n\n ----------- Listagem ----------\n");

	while (aux != NULL)
	{

		if (strcmp(aux->cidade, geoCodigo) == 0)
		{
			printf("id: %d, tipo: %s, cargaBateria: %d, custo: %.2f, Cidade: %s\n",
				aux->id, aux->tipo, aux->cargaBateria,
				aux->custo, aux->cidade);
		}

		aux = aux->next;

	}

	

	return 0;

}


/**
*	@brief Insere MeiosDeMobilidade mas na consola
*
*	@return header da lista de MeiosDeMobilidade;
*
*/
MeiosDeMobilidade* InserirPorEscreverMeiosDeMobilidade() {


	int id;
	char tipo[50];
	int cargaBateria;
	float custo;
	char cidade[50];
	float latitude;
	float longitude;
	float peco;

	printf("\n\nDigite o id do meio de mobilidade: ");
	scanf("%d", &id);
	printf("\nDigite o tipo: ");
	scanf("%s", &tipo);
	printf("\nDigite a carga de bateria: ");
	scanf("%d", &cargaBateria);
	printf("\nDigite o custo: ");
	scanf("%f", &custo);
	printf("\nDigite o peso: ");
	scanf("%f", &peco);
	printf("\nDigite a Cidade: ");
	scanf("%s", &cidade);
	printf("\nDigite a latitude: ");
	scanf("%f", &latitude);
	printf("\nDigite a longitude: ");
	scanf("%f", &longitude);

	MeiosDeMobilidade* meioNovo = CriarMeiosDeMobilidade(id, tipo, cargaBateria, custo, peco, cidade , latitude , longitude,true);

	return meioNovo;

}

/**
*	@brief Altera MeiosDeMobilidade mas na consola
*
*	@return 0;
*
*/
int AlterarPorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios) {


	int id;
	char tipo[50];

	printf("\n\nDigite o id do meio de mobilidade: ");
	scanf("%d", &id);
	printf("\nDigite o tipo: ");
	scanf("%s", &tipo);

	AlteraMeiosDeMobilidade(&headMeios, id, tipo);

	return 0;

}

/**
*	@brief Remove MeiosDeMobilidade mas na consola
*
*	@return 0;
*
*/
int RemoverPorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios) {

	int id;

	printf("\n\nDigite o id do meio de mobilidade que quer eliminar: ");
	scanf("%d", &id);

	RemoverMeiosDeMobilidade(headMeios, id);

	return 0;

}

/**
*	@brief Lista geocodigo MeiosDeMobilidade mas na consola
*
*	@return 0;
*
*/
int ListarCidadePorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios) {

	char cidade[50];

	printf("\n\nDigite a Cidade para encontrar os meios disponiveis: ");
	scanf("%s", &cidade);

	ListarCidadePorGeoCodigo(headMeios, cidade);

	return 0;

}


/**
*	@brief Altera Estado MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id MeiosDeMobilidade
*	@param [in] estado					estado MeiosDeMobilidade
*
*
*/
void AlteraEstadoMeiosDeMobilidade(MeiosDeMobilidade** header, int id, bool estado) {
	if (*header != NULL) {
		MeiosDeMobilidade* aux = ProcuraMeiosDeMobilidade(*header, id);
		if (aux != NULL)
		{
			aux->estado = estado;
		}
	}
}


/**
*	@brief Altera Localizacao MeiosDeMobilidade na lista de MeiosDeMobilidade.
*
*
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id MeiosDeMobilidade
*	@param [in] latitude				latitude MeiosDeMobilidade
*	@param [in] longitude				longitude MeiosDeMobilidade
*
*
*/
void AlteraLocalizacaoMeiosDeMobilidade(MeiosDeMobilidade** header, int id, float latitude, float longitude) {
	if (*header != NULL) {
		MeiosDeMobilidade* aux = ProcuraMeiosDeMobilidade(*header, id);
		if (aux != NULL)
		{
			aux->longitude = longitude;
			aux->latitude = latitude;
		}
	}
}


/**
*	@brief Alterar Estado Meio 
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id de Meio
*	@param [in] estado					estado de Meio

*	@return 0;
*
*/
int AtivarDesativarMeio(MeiosDeMobilidade* header , int id , bool estado) {

	if (header == NULL)
	{
		return 1;
	}

	MeiosDeMobilidade* aux = header;

	while (aux != NULL)
	{
		if (aux->id == id)
		{
			aux->estado = estado;
		}

		aux = aux->next;
	}

	return 0;

}


/**
*	@brief Alterar Estado Meio Escrever
*	@param [in] header					header da lista de MeiosDeMobilidade

*	@return 0;
*
*/
int AlterarEstadoEscrever(MeiosDeMobilidade* headMeios) {

	int id;

	char estado[100];

	bool estadoBool;

	printf("\n\nId do Meio quer alterar o estado:");
	scanf("%d", &id);

	printf("\nEstado (Ativo/Desativo): ");
	scanf("%s", &estado);

	if (strcmp(estado, "Ativo") == 0 || strcmp(estado, "ativo") == 0)
	{
		estadoBool = true;
		AtivarDesativarMeio(headMeios, id, estadoBool);

	}
	else if (strcmp(estado, "Desativo") == 0 || strcmp(estado, "desativo") == 0)
	{
		estadoBool = false;
		AtivarDesativarMeio(headMeios, id, estadoBool);

	}

	return 0;

}



/**
*	@brief Alterar Localizacao Meio
*	@param [in] header					header da lista de MeiosDeMobilidade
*	@param [in] id						id de Meio
*	@param [in] latitude				latitude nova de Meio
*	@param [in] longitude				longitude nova de Meio

*	@return 0;
*
*/
int AlterarLocalizacao(MeiosDeMobilidade* header,int id ,float latitude, float longitude) {

	if (header == NULL)
	{
		return 1;
	}

	MeiosDeMobilidade* aux = header;

	while (aux != NULL)
	{
		if (aux->id == id)
		{
			aux->latitude = latitude;
			aux->longitude = longitude;
		}

		aux = aux->next;
	}

	return 0;

}



/**
*	@brief Alterar Localizacao Meio Escrever
*	@param [in] header					header da lista de MeiosDeMobilidade

*	@return 0;
*
*/
int AlterarLocalizacaoEstadoEscrever(MeiosDeMobilidade* headMeios) {

	int id;
	float latitude;
	float longitude;


	printf("\n\nId do Meio quer alterar a localizacao:");
	scanf("%d", &id);
	printf("\n\nLatitude: ");
	scanf("%f", &latitude);
	printf("\n\nLongitude: ");
	scanf("%f", &longitude);

	AlterarLocalizacao(headMeios , id , latitude ,longitude);

	return 0;

}




