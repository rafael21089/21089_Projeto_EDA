#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {

    int Id;
    char Nome[50];
    char Morada[50];
    char NIF[9];
    float Saldo;
    struct Clientes* next;

} Clientes;


typedef struct {
    
    int Id;
    char Tipo[50];
    int CargaBateria;
    int Custo;
    float localizacao;
    struct Clientes* ClienteAUsar;

    struct MeiosDeMobilidade* next;


} MeiosDeMobilidade;



typedef struct {
    
    int Id;
    char Utilizador[50];

    struct MeiosDeMobilidade* Meios;
    struct Clientes* Cliente;

    struct Gestor* next;


} Gestor;


Clientes* CriarClientes(int Id, char Nome[50], char Morada[50], char NIF[9], float Saldo);
Clientes* InsereClienteNoFim(Clientes* Header, Clientes* NovoCliente);
bool ExisteCliente(Clientes* Header, int IdCliente);
void MostrarListaClientes(Clientes* Header);
void MostraCliente(Clientes* Cliente);


MeiosDeMobilidade* CriarMeiosDeMobilidade(int Id, char Tipo[50], int CargaBateria, int Custo, float localizacao, Clientes* ClienteAUsar);
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* Header, MeiosDeMobilidade* NovoMeiosDeMobilidade);
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* Header, int IdMeiosDeMobilidade);
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* Header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* MeiosDeMobilidade);


