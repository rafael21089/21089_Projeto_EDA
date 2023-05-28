
#pragma once

/**
*  @file Cliente.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct Cliente onde ira guardar o registo de Clientes e as suas respectivas funcoes

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Aluguer.h"
#include "MeioDeMobilidade.h"


/**
 * @brief Estrutura para armazenar Clientes
 *
 * Um Cliente contém um id (@@id), nome (@@nome), morada (@@morada) ,nif (@@nif) , saldo (@@saldo) , latitude (@@latitude) , longitude (@@longitude) e alugueres (@@atividade).
 * Contém apontador para próximo Clientes
 */

typedef struct Clientes{

    int id;
    char nome[50];
    char morada[50];
    char nif[9];
    float saldo;
    float latitude;
    float longitude;
    struct Aluguer* aluguer;

    struct Clientes* next;

} Clientes;

//Criar Clientes

Clientes* CriarClientes(int id, char nome[50], char morada[50], char nif[9], float saldo, float latitude, float longitude);
//Insere Cliente no Header de Clientes
Clientes* InsereClienteNoFim(Clientes* header, Clientes* novoCliente);
//Ver se Existe Cliente na lista por id
bool ExisteCliente(Clientes* header, int idCliente);
//Mostra Lista de Clientes
void MostrarListaClientes(Clientes* header);
void MostraCliente(Clientes* cliente);
//Remove Clientes
Clientes* RemoverCliente(Clientes* header, int id);
//Procura Clientes
Clientes* ProcuraClientes(Clientes* header, int id);
//Altera Clientes
void AlteraCliente(Clientes** header, int id, char* nome);
//Conta Clientes no header Clientes
int CountClientes(Clientes* head);

//Le e armazena txt file
Clientes* LerEArmazenarCliente(char* filename, Clientes* header);
//Grava Clientes no ficheiro binario
bool GravarClientesBinario(char* nomeFicheiro, Clientes* header);
//Le e armazena bin file
Clientes* LerClientesBinario(char* nomeFicheiro);

//Regista um Aluguer de um Meio de Mobilidade pelo o cliente
int RegistoAluguer(struct Clientes** headerCliente, struct MeiosDeMobilidade** headerMeios, struct Aluguer** headerAluguerTotal, int idCliente, int idMeios);

//Inserir,Remover , Alterar e Registo na consola
Clientes* InserirPorEscreverCliente();
int AlterarPorEscreverCliente(Clientes* headClientes);
int RemoverPorEscreverCliente(Clientes* headClientes);
int RegistoPorEscrever(Clientes* headClientes, struct Aluguer* headAluguer, struct MeiosDeMobilidade* headMeio);
int AlterarPorEscreverClienteWindowCliente(Clientes* headClientes, int idCliente);

//Registo Para Cliente Escrever (Window Clinte)
int RegistoPorEscreverClienteWindow(Clientes* headClientes, struct Aluguer* headAluguer, struct MeiosDeMobilidade* headMeio, int idCliente);
//Procurar por um Raio Meios de um tipo
int ProcurarRaioMeioCliente(Clientes* headClientes, struct MeiosDeMobilidade* headMeio, int idCliente);

int ClienteParaMeioLocalizacao(Clientes* headClientes, struct MeiosDeMobilidade* headMeio, struct LocalizacaoPostos* headListaPostos, int idCliente);


