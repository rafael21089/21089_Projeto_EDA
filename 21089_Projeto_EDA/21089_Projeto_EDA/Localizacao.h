/**
*  @file Aluguer.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct Localizacao onde ira guardar o registo de pontos e pontos adjacentes, com as suas respectivas funcoes
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGURAGERALSTRING 100

typedef struct LocalizacaoPostos{
	int id;
	char cidade[LARGURAGERALSTRING];
	char latitude[LARGURAGERALSTRING];
	char longitude[LARGURAGERALSTRING];
	char geocode[LARGURAGERALSTRING];
}LocalizacaoPostos;


typedef struct LocalizacaoPostosAdjacentes{

	LocalizacaoPostos* postoOrigem;
	LocalizacaoPostos* postoDestino;
	float distancia;

	LocalizacaoPostosAdjacentes* proximo;

}LocalizacaoPostosAdjacentes;


typedef struct LocalizacaoPostosLista {

	LocalizacaoPostos localizacaoPostos;
	LocalizacaoPostosAdjacentes* primeiraAdjacencia;

}LocalizacaoPostosLista;
