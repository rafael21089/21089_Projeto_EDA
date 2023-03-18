#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Gestor.h"

enum Estado {
    ATIVO,
    CANCELADO,
    COMPLETADO
};

typedef struct {

    int id;
    int custo;
    enum Estado estadoDoAluguer;
    int clienteId;
    int meioUsadoId;

    struct Atividade* next;

} Atividade;


typedef struct {

    int id;
    struct Atividade* aluguerClienteRegisto;
    struct Atividade* aluguerMeioRegisto;
    struct AluguerListaTotal* next;

} AluguerListaTotal;



AluguerListaTotal* CriarAluguerListaTotal(int id, Atividade* aluguerClienteRegisto, Atividade* aluguerMeioRegisto);
AluguerListaTotal* InsereAluguerListaTotalNoFim(AluguerListaTotal* header, AluguerListaTotal* novoAluguerListaTotal);
bool ExisteAluguerListaTotal(AluguerListaTotal* header, int idAluguerListaTotal);
int CountAluguerListaTotal(AluguerListaTotal* head);


int CountHistorico(Atividade* head);
void insertHistoricoCliente(struct Clientes* cliente, Atividade* atividade);
void insertHistoricoMeio(struct MeiosDeMobilidade* meio, Atividade* atividade);

void insertAlugerTotalGestor(struct Gestor* gestor, AluguerListaTotal* aluguerTotal);




