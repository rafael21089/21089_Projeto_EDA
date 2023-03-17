#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Atividade.h"
#include "Cliente.h"

typedef struct {
    int id;
    char tipo[50];
    int cargaBateria;
    int custo;
    float localizacao;
    struct Atividade* atividade;

    struct MeiosDeMobilidade* next;

} MeiosDeMobilidade;


MeiosDeMobilidade* CriarMeiosDeMobilidade(int id, char tipo[50], int cargaBateria, int custo, float localizacao);
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* header, MeiosDeMobilidade* novoMeiosDeMobilidade);
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* header, int idMeiosDeMobilidade);
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* meiosDeMobilidade);
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** header, int id, char* tipo);
int CountMeios(struct MeiosDeMobilidade* head);

