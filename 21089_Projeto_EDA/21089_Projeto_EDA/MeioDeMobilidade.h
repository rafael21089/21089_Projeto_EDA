#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Atividade.h"
#include "Cliente.h"

typedef struct MeiosDeMobilidade{
    int id;
    char tipo[50];
    int cargaBateria;
    float custo;
    char localizacao[50];
    struct Atividade* atividade;

    struct MeiosDeMobilidade* next;

} MeiosDeMobilidade;


MeiosDeMobilidade* CriarMeiosDeMobilidade(int id, char* tipo, int cargaBateria, float custo, char* localizacao);
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* header, MeiosDeMobilidade* novoMeiosDeMobilidade);
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* header, int idMeiosDeMobilidade);
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* meiosDeMobilidade);
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* header, int id);
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** header, int id, char* tipo);
int CountMeios(struct MeiosDeMobilidade* head);


MeiosDeMobilidade* LerEArmazenarMeiosDeMobilidade(char* filename, MeiosDeMobilidade* header);
bool GravarMeiosDeMobilidadeBinario(char* nomeFicheiro, MeiosDeMobilidade* header);
MeiosDeMobilidade* LerMeiosDeMobilidadeBinario(char* nomeFicheiro);


