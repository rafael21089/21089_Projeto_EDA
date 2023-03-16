#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Estado {
    ATIVO,
    CANCELADO,
    COMPLETADO
};


typedef struct {

    int Id;
    char Nome[50];
    char Morada[50];
    char NIF[9];
    float Saldo;
    struct Historico* Historico;

    struct Clientes* next;

} Clientes;


typedef struct {

    int Id;
    int Custo;
    enum Estado EstadoDoAluguer;
    struct Clientes* Cliente;
    struct MeiosDeMobilidade* MeioUsado;

    struct Historico* next;

} Historico;


typedef struct {
    int Id;
    char Tipo[50];
    int CargaBateria;
    int Custo;
    float localizacao;
    struct Historico* Historico;

    struct MeiosDeMobilidade* next;

} MeiosDeMobilidade;



typedef struct {
    int Id;
    char Utilizador[50];
    struct MeiosDeMobilidade* Meios;
    struct Clientes* Clientes;

    struct Gestor* next;
} Gestor;


Clientes* CriarClientes(int Id, char Nome[50], char Morada[50], char NIF[9], float Saldo);
Clientes* InsereClienteNoFim(Clientes* Header, Clientes* NovoCliente);
bool ExisteCliente(Clientes* Header, int IdCliente);
void MostrarListaClientes(Clientes* Header);
void MostraCliente(Clientes* Cliente);
Clientes* RemoverCliente(Clientes* Header, int Id);
Clientes* ProcuraClientes(Clientes* Header, int Id);
void AlteraCliente(Clientes** Header, int Id, char* Nome);
int CountClientes(Clientes* head);
void insertHistoricoCliente(Clientes* cliente, Historico* historico);

MeiosDeMobilidade* CriarMeiosDeMobilidade(int Id, char Tipo[50], int CargaBateria, int Custo, float localizacao);
MeiosDeMobilidade* InsereMeiosDeMobilidadeNoFim(MeiosDeMobilidade* Header, MeiosDeMobilidade* NovoMeiosDeMobilidade);
bool ExisteMeiosDeMobilidade(MeiosDeMobilidade* Header, int IdMeiosDeMobilidade);
void MostrarListaMeiosDeMobilidade(MeiosDeMobilidade* Header);
void MostraMeiosDeMobilidade(MeiosDeMobilidade* MeiosDeMobilidade);
MeiosDeMobilidade* RemoverMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id);
MeiosDeMobilidade* ProcuraMeiosDeMobilidade(MeiosDeMobilidade* Header, int Id);
void AlteraMeiosDeMobilidade(MeiosDeMobilidade** Header, int Id, char* Tipo);
int CountMeios(struct MeiosDeMobilidade* head);
void insertHistoricoMeio(MeiosDeMobilidade* Meio, Historico* Historico);


Gestor* CriarNovoGestor(int Id, char Utilizador[50], MeiosDeMobilidade* MeiosDeMobilidadeExistentes, Clientes* ClienteExistentes);
Gestor* InsereGestorNoFim(Gestor* Header, Gestor* NovoGestor);
bool ExisteGestor(Gestor* Header, int IdGestor);
void MostrarListaGestor(Gestor* Header);
void MostraGestor(Gestor* Gestor);
Gestor* RemoverGestor(Gestor* Header, int Id);
Gestor* ProcuraGestor(Gestor* Header, int Id);
void AlteraGestor(Gestor** Header, int Id, char* Utilizador);


void RegistoAluguer(Clientes** HeaderCliente, MeiosDeMobilidade** HeaderMeios, int IdCliente, int IdMeios);

int CountHistorico(Historico* head);


