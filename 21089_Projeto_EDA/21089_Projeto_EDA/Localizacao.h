/**
*  @file Aluguer.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct Localizacao onde ira guardar o registo de pontos e pontos adjacentes, com as suas respectivas funcoes
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGURAGERALSTRING 100

typedef struct LocalizacaoPostos {
    int id;
    char cidade[LARGURAGERALSTRING];
    char latitude[LARGURAGERALSTRING];
    char longitude[LARGURAGERALSTRING];
    struct LocalizacaoPostosAdjacentes* postosAdjacentes; // Pointer to the first adjacent node
    struct LocalizacaoPostos* proximo; // Pointer to the next adjacent node

} LocalizacaoPostos;

typedef struct LocalizacaoPostosAdjacentes {
    int idDestino;
    struct LocalizacaoPostos* postoDestinoAdjacente; // Pointer to the destination node
    float distancia;
    struct LocalizacaoPostosAdjacentes* proximo; // Pointer to the next adjacent node
} LocalizacaoPostosAdjacentes;

LocalizacaoPostos* CriarPosto(int id, char* cidade, char* latitude, char* longitude, LocalizacaoPostosAdjacentes* postosAdjacentes);
LocalizacaoPostos* InserePostoGrafo(LocalizacaoPostos* header, LocalizacaoPostos* novoPosto);

LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, float distancia);
LocalizacaoPostosAdjacentes* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino, float distancia);

LocalizacaoPostos* ProcurarPorIdPostosComListaToda(LocalizacaoPostos* headerList, int id);
LocalizacaoPostos* ProcurarPorIdPostos(LocalizacaoPostos* headerList, int id);

LocalizacaoPostos* LerEArmazenarPosto(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista);
LocalizacaoPostos* LerEArmazenarPostoAdjacente(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista);

bool GravarPostosBinario(char* nomeFicheiro, LocalizacaoPostos* header);
LocalizacaoPostos* LerPostosBinario(char* nomeFicheiro);

bool GravarPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos* header);
LocalizacaoPostos* LerPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos** header, bool* resultado);

bool JaTemPostoAdjacente(LocalizacaoPostos* headerOrigem, LocalizacaoPostos* headerDestino);
bool ExistePosto(LocalizacaoPostos* header, int idPosto);

LocalizacaoPostos* AtualizarPostosAdjacentes(LocalizacaoPostos* headLista);

LocalizacaoPostosAdjacentes* ProcurarPostoAdjacente(LocalizacaoPostos* vertex, LocalizacaoPostos* postoDestino);
void dijkstra(LocalizacaoPostos* headList, int origemId, int destinationId);
int findMinDistanceNode(bool visited[], float distances[], int numNodes);