#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Gestor.h"



typedef struct {

    int id;
    float custo;
    char estadoDoAluguer[10];
    int clienteId;
    int meioUsadoId;

    struct Atividade* next;

} Atividade;


//typedef struct {
//
//    int id;
//    float custoDoAluguer;
//    int aluguerClienteRegistoId;
//    int aluguerMeioRegistoId;
//    struct AluguerListaTotal* next;
//
//} AluguerListaTotal;



Atividade* CriarAluguerListaTotal(int id, float custo, char* estadoDoAluguer, int clienteId, int meioUsadoId);
Atividade* InsereAluguerListaTotalNoFim(Atividade* header, Atividade* novoAluguerListaTotal);
bool ExisteAluguerListaTotal(Atividade* header, int idAluguerListaTotal);
int CountAluguerListaTotal(Atividade* head);


int CountHistorico(Atividade* head);
void insertHistoricoCliente(struct Clientes* cliente, Atividade* atividade);
void insertHistoricoMeio(struct MeiosDeMobilidade* meio, Atividade* atividade);

void insertAlugerTotalGestor(struct Gestor* gestor, Atividade* aluguerTotal);


Atividade* LerEArmazenarAluguerListaTotal(char* filename, Atividade* header);
bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Atividade* header);
Atividade* LerAluguerListaTotalBinario(char* nomeFicheiro);

void DistribuirAlugueresHistorico(Atividade* header, struct MeiosDeMobilidade* headerMeios, struct Clientes* headerClientes);

int ListarClienteAlugueresById(Atividade* header, int idCliente);
int AluguerClientePorEscrever(Atividade* headAluguer);
int ListarMeiosAlugueresById(Atividade* header, int idMeios);
int AluguerMeiosPorEscrever(Atividade* headAluguer);
int ListarTodosAlugueres(Atividade* header);




