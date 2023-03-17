#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Atividade.h"
#include "Cliente.h"

typedef struct {
    int Id;
    char Tipo[50];
    int CargaBateria;
    int Custo;
    float localizacao;
    struct Historico* Historico;

    struct MeiosDeMobilidade* next;

} MeiosDeMobilidade;


MeiosDeMobilidade* CriarMeiosDeMobilidade(int Id, char Tipo[50], int CargaBateria, int Custo, float localizacao);
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* Header, MeiosDeMobilidade* NovoMeiosDeMobilidade);
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* Header, int IdMeiosDeMobilidade);
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* Header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* MeiosDeMobilidade);
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id);
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id);
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** Header, int Id, char* Tipo);
int CountMeios(struct MeiosDeMobilidade* head);

