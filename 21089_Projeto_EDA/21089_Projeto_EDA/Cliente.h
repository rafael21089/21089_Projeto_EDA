
#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Atividade.h"
#include "MeioDeMobilidade.h"

typedef struct {

    int Id;
    char Nome[50];
    char Morada[50];
    char NIF[9];
    float Saldo;
    struct Historico* Historico;

    struct Clientes* next;

} Clientes;


Clientes* CriarClientes(int Id, char Nome[50], char Morada[50], char NIF[9], float Saldo);
Clientes* InsereClienteNoFim(Clientes* Header, Clientes* NovoCliente);
bool ExisteCliente(Clientes* Header, int IdCliente);
void MostrarListaClientes(Clientes* Header);
void MostraCliente(Clientes* Cliente);
Clientes* RemoverCliente(Clientes* Header, int Id);
Clientes* ProcuraClientes(Clientes* Header, int Id);
void AlteraCliente(Clientes** Header, int Id, char* Nome);
int CountClientes(Clientes* head);

void RegistoAluguer(Clientes** HeaderCliente, struct MeiosDeMobilidade** HeaderMeios, int IdCliente, int IdMeios);


