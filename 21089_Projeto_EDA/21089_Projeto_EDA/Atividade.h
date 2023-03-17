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

    int id;
    int custo;
    enum Estado estadoDoAluguer;
    struct Clientes* cliente;
    struct MeiosDeMobilidade* meioUsado;

    struct Atividade* next;

} Atividade;


int CountHistorico(Atividade* head);
void insertHistoricoCliente(struct Clientes* cliente, Atividade* atividade);
void insertHistoricoMeio(struct MeiosDeMobilidade* meio, Atividade* atividade);



