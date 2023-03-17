#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente.h"
#include "MeioDeMobilidade.h"

typedef struct {
    int Id;
    char Utilizador[50];
    struct MeiosDeMobilidade* Meios;
    struct Clientes* Clientes;

    struct Gestor* next;
} Gestor;


Gestor* CriarNovoGestor(int Id, char Utilizador[50], struct MeiosDeMobilidade* MeiosDeMobilidadeExistentes, struct Clientes* ClienteExistentes);
Gestor* InsereGestorNoFim(Gestor* Header, Gestor* NovoGestor);
bool ExisteGestor(Gestor* Header, int IdGestor);
void MostrarListaGestor(Gestor* Header);
void MostraGestor(Gestor* Gestor);
Gestor* RemoverGestor(Gestor* Header, int Id);
Gestor* ProcuraGestor(Gestor* Header, int Id);
void AlteraGestor(Gestor** Header, int Id, char* Utilizador);





