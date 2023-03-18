#pragma once

/**
*  @file Gestor.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct Gestor onde ira guardar o registo de Gestores e as suas respectivas funcoes

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluguer.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"

/**
 * @brief Estrutura para armazenar Gestor
 *
 * Um Gestor contém um id (@@id), utilizador (@@utilizador), distrito (@@distrito) ,meios de mobilidade (@@meios) , clientes (@@clientes) e todos os Alugueres (@@todosAlugueres).
 * Contém apontador para próximo Gestor
 */
typedef struct Gestor{
    int id;
    char utilizador[50];
    char distrito[50];
    struct MeiosDeMobilidade* meios;
    struct Clientes* clientes;
    struct Aluguer* todosAlugueres;

    struct Gestor* next;
} Gestor;

//Criar Gestor
Gestor* CriarNovoGestor(int id, char* utilizador, char* distrito, struct MeiosDeMobilidade* meiosDeMobilidadeExistentes, struct Clientes* clienteExistentes, struct Aluguer* aluguerTotal);
//Insere Gestor no Header de Gestor
Gestor* InsereGestorNoFim(Gestor* header, Gestor* novoGestor);
//Ver se Existe Gestor na lista por id
bool ExisteGestor(Gestor* header, int idGestor);
//Mostra Lista de Gestor
void MostrarListaGestor(Gestor* header);
void MostraGestor(Gestor* gestor);

//Remove Gestor
Gestor* RemoverGestor(Gestor* header, int id);
//Procura Gestor
Gestor* ProcuraGestor(Gestor* header, int id);
//Altera Gestor
void AlteraGestor(Gestor** header, int id, char* utilizador);

//Le e armazena txt file
Gestor* LerEArmazenarGestor(char* filename, Gestor* header);
//Grava Gestor no ficheiro binario
bool GravarGestorBinario(char* nomeFicheiro, Gestor* header);
//Le e armazena bin file
Gestor* LerGestorBinario(char* nomeFicheiro);

//Grava Meios de Mobilidade e Clientes nos Gestores todos
int GravarMeiosEClientesNosGestores(Gestor* gestor, struct Aluguer* alugueresTotal, struct Clientes* clientesHeader, struct MeiosDeMobilidade* meiosHeader);

//Inserir,Remover e Alterar na consola
Gestor* InserirPorEscreverGestor();
int AlterarPorEscreverGestor(Gestor* headGestor);
int RemoverPorEscreverGestor(Gestor* headGestor);





