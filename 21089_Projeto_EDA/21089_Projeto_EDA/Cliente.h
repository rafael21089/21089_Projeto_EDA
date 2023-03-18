
#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Atividade.h"
#include "MeioDeMobilidade.h"

typedef struct Clientes{

    int id;
    char nome[50];
    char morada[50];
    char nif[9];
    float saldo;
    struct Atividade* atividade;

    struct Clientes* next;

} Clientes;


Clientes* CriarClientes(int id, char nome[50], char morada[50], char nif[9], float saldo);
Clientes* InsereClienteNoFim(Clientes* header, Clientes* novoCliente);
bool ExisteCliente(Clientes* header, int idCliente);
void MostrarListaClientes(Clientes* header);
void MostraCliente(Clientes* cliente);
Clientes* RemoverCliente(Clientes* header, int id);
Clientes* ProcuraClientes(Clientes* header, int id);
void AlteraCliente(Clientes** header, int id, char* nome);
int CountClientes(Clientes* head);

Clientes* LerEArmazenarCliente(char* filename, Clientes* header);
bool GravarClientesBinario(char* nomeFicheiro, Clientes* header);
Clientes* LerClientesBinario(char* nomeFicheiro);

void RegistoAluguer(struct Clientes** headerCliente, struct MeiosDeMobilidade** headerMeios, struct Atividade** headerAluguerTotal, int idCliente, int idMeios);


