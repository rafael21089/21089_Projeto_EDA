#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Cliente.h"
#include "MeioDeMobilidade.h"

enum Estado {
    ATIVO,
    CANCELADO,
    COMPLETADO
};

typedef struct {

    int Id;
    int Custo;
    enum Estado EstadoDoAluguer;
    struct Clientes* Cliente;
    struct MeiosDeMobilidade* MeioUsado;

    struct Historico* next;

} Historico;


int CountHistorico(Historico* head);
void insertHistoricoCliente(struct Clientes* cliente, Historico* historico);
void insertHistoricoMeio(struct MeiosDeMobilidade* Meio, Historico* Historico);



