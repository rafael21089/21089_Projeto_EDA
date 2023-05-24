#pragma once

/**
*  @file MeioDeMobilidade.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct MeioDeMobilidade onde ira guardar o registo de meios e as suas respectivas funcoes

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Aluguer.h"
#include "Cliente.h"



/**
 * @brief Estrutura para armazenar Meios De Mobilidade
 *
 * Um Meios De Mobilidade contém um id (@@id), tipo (@@tipo) ,carga da Bateria (@@cargaBateria) , custo (@@custo),peso (@@peso) , cidade (@@aluguer) , latitude (@@latitude) , longitude (@@longitude), estado (@@estado) e alugueres (@@atividade).
 * Contém apontador para próximo MeiosDeMobilidade
 */
#define LARGURAGERALSTRING 100

typedef struct MeiosDeMobilidade{
    int id;
    char tipo[LARGURAGERALSTRING];
    int cargaBateria;
    float custo;
    float peso;
    char cidade[LARGURAGERALSTRING];
    float latitude;
    float longitude;
    bool estado;
    struct Aluguer* aluguer;

    struct MeiosDeMobilidade* next;

} MeiosDeMobilidade;

//Criar Meio
MeiosDeMobilidade* CriarMeiosDeMobilidade(int id, char* tipo, int cargaBateria, float custo, float peso, char* cidade, float latitude, float longitude, bool estado);
//Insere Meio no Header de Meio
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* header, MeiosDeMobilidade* novoMeiosDeMobilidade);
//Ver se Existe Meio na lista por id
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* header, int idMeiosDeMobilidade);
//Mostra Lista de Meios De Mobilidade
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* meiosDeMobilidade);
//Remove Meios De Mobilidade
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
//Procura Meios De Mobilidade
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
//Altera Meios De Mobilidade
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** header, int id, char* tipo);
//Counta Meios De Mobilidade
int CountMeios(struct MeiosDeMobilidade* head);

//Le e armazena txt file
MeiosDeMobilidade* LerEArmazenarMeiosDeMobilidade(char* filename, MeiosDeMobilidade* header);
//Grava Meios De Mobilidade no ficheiro binario
bool GravarMeiosDeMobilidadeBinario(char* nomeFicheiro, MeiosDeMobilidade* header);
//Le e armazena bin file
MeiosDeMobilidade* LerMeiosDeMobilidadeBinario(char* nomeFicheiro);

//Lista Meio Autonomia de forma Decrescente
int ListarMeioAutonomiaDecrescente(MeiosDeMobilidade* header);
//Lista Meio por Geocodigo
int ListarMeioPorGeoCodigo(MeiosDeMobilidade* header, char* geoCodigo);

//Inserir,Remover e Alterar na consola
MeiosDeMobilidade* InserirPorEscreverMeiosDeMobilidade();
int AlterarPorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios);
int RemoverPorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios);

//Lista Meio por Geocodigo
int ListarGeocodigoPorEscreverMeiosDeMobilidade(MeiosDeMobilidade* headMeios);


