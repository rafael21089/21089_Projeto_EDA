#pragma once


/**
*  @file Aluguer.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 * 
 * @brief Definicao da struct Aluguer onde ira guardar o registo de alugueres e as suas respectivas funcoes
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Gestor.h"


/**
 * @brief Estrutura para armazenar Alugueres
 *
 * Um Aluguer contém um id (@@id), custo (@@custo) ,estado Do Aluguer (@@estadoDoAluguer) , id do Cliente que fez aluguer (@@clienteId) e id do Meio que fez aluguer (@@meioUsadoId).
 * Contém apontador para próximo Aluguer
 */

typedef struct Aluguer{

    int id;
    float custo;
    char estadoDoAluguer[10];
    int clienteId;
    int meioUsadoId;

    struct Aluguer* next; /**< apontador para próximo Aluguer*/

} Aluguer;


//Cria um Aluguer
Aluguer* CriarAluguerListaTotal(int id, float custo, char* estadoDoAluguer, int clienteId, int meioUsadoId);
//Insere Aluguer no Header de Aluguer
Aluguer* InsereAluguerListaTotalNoFim(Aluguer* header, Aluguer* novoAluguerListaTotal);
//Ver se Existe Aluguer na lista por id
bool ExisteAluguerListaTotal(Aluguer* header, int idAluguerListaTotal);

//Ver se Tem Um Aluguer Ativo
bool TemAluguerAtivo(Aluguer* header);

//Conta quantos alugueres existem Total
int CountAluguerListaTotal(Aluguer* head);
//Conta quantos alugueres existem 
int CountAlugueres(Aluguer* head);

//Insere Aluguer no Cliente
void InsertAlugueresCliente(struct Clientes* cliente, Aluguer* atividade);
//Insere Aluguer no Meio
void InsertAlugueresMeio(struct MeiosDeMobilidade* meio, Aluguer* atividade);
//Insere Aluguer no Gestor
void InsertAlugerTotalGestor(struct Gestor* gestor, Aluguer* aluguerTotal);

//Le e armazena txt file
Aluguer* LerEArmazenarAluguerListaTotal(char* filename, Aluguer* header);
//Grava aluguer no ficheiro binario
bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Aluguer* header);
//Le e armazena bin file
Aluguer* LerAluguerListaTotalBinario(char* nomeFicheiro);

//Distribui os Alugueres por Clientes e Meios
void DistribuirAlugueresHistorico(Aluguer* header, struct MeiosDeMobilidade* headerMeios, struct Clientes* headerClientes);

//Listar Aluguer por Cliente Id
int ListarClienteAlugueresById(Aluguer* header, int idCliente);
int AluguerClientePorEscrever(Aluguer* headAluguer);

//Listar Aluguer por Meio Id
int ListarMeiosAlugueresById(Aluguer* header, int idMeios);
int AluguerMeiosPorEscrever(Aluguer* headAluguer);

//Listar todos alugueres
int ListarTodosAlugueres(Aluguer* header);




