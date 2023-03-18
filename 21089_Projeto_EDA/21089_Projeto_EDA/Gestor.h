#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente.h"
#include "MeioDeMobilidade.h"

typedef struct {
    int id;
    char utilizador[50];
    struct MeiosDeMobilidade* meios;
    struct Clientes* clientes;

    struct Gestor* next;
} Gestor;


Gestor* CriarNovoGestor(int id, char utilizador[50], struct MeiosDeMobilidade* meiosDeMobilidadeExistentes, struct Clientes* clienteExistentes);
Gestor* InsereGestorNoFim(Gestor* header, Gestor* novoGestor);
bool ExisteGestor(Gestor* header, int idGestor);
void MostrarListaGestor(Gestor* header);
void MostraGestor(Gestor* gestor);
Gestor* RemoverGestor(Gestor* header, int id);
Gestor* ProcuraGestor(Gestor* header, int id);
void AlteraGestor(Gestor** header, int id, char* utilizador);


Gestor* LerEArmazenarGestor(char* filename, Gestor* header);
bool GravarGestorBinario(char* nomeFicheiro, Gestor* header);
Gestor* LerGestorBinario(char* nomeFicheiro);





