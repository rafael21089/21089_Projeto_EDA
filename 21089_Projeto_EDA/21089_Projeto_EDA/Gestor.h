#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluguer.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"

typedef struct Gestor{
    int id;
    char utilizador[50];
    char distrito[50];
    struct MeiosDeMobilidade* meios;
    struct Clientes* clientes;
    struct Aluguer* todosAlugueres;

    struct Gestor* next;
} Gestor;


Gestor* CriarNovoGestor(int id, char* utilizador, char* distrito, struct MeiosDeMobilidade* meiosDeMobilidadeExistentes, struct Clientes* clienteExistentes, struct Aluguer* aluguerTotal);
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

int GravarMeiosEClientesNosGestores(Gestor* gestor, struct Aluguer* alugueresTotal, struct Clientes* clientesHeader, struct MeiosDeMobilidade* meiosHeader);

Gestor* InserirPorEscreverGestor();
int AlterarPorEscreverGestor(Gestor* headGestor);
int RemoverPorEscreverGestor(Gestor* headGestor);





