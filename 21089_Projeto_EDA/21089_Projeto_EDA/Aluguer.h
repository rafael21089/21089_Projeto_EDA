#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Gestor.h"



typedef struct Aluguer{

    int id;
    float custo;
    char estadoDoAluguer[10];
    int clienteId;
    int meioUsadoId;

    struct Aluguer* next;

} Aluguer;



Aluguer* CriarAluguerListaTotal(int id, float custo, char* estadoDoAluguer, int clienteId, int meioUsadoId);
Aluguer* InsereAluguerListaTotalNoFim(Aluguer* header, Aluguer* novoAluguerListaTotal);
bool ExisteAluguerListaTotal(Aluguer* header, int idAluguerListaTotal);
int CountAluguerListaTotal(Aluguer* head);


int CountHistorico(Aluguer* head);
void insertHistoricoCliente(struct Clientes* cliente, Aluguer* atividade);
void insertHistoricoMeio(struct MeiosDeMobilidade* meio, Aluguer* atividade);

void insertAlugerTotalGestor(struct Gestor* gestor, Aluguer* aluguerTotal);


Aluguer* LerEArmazenarAluguerListaTotal(char* filename, Aluguer* header);
bool GravarAluguerListaTotalBinario(char* nomeFicheiro, Aluguer* header);
Aluguer* LerAluguerListaTotalBinario(char* nomeFicheiro);

void DistribuirAlugueresHistorico(Aluguer* header, struct MeiosDeMobilidade* headerMeios, struct Clientes* headerClientes);

int ListarClienteAlugueresById(Aluguer* header, int idCliente);
int AluguerClientePorEscrever(Aluguer* headAluguer);
int ListarMeiosAlugueresById(Aluguer* header, int idMeios);
int AluguerMeiosPorEscrever(Aluguer* headAluguer);
int ListarTodosAlugueres(Aluguer* header);




