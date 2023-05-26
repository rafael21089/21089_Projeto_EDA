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
    float latitude;
    float longitude;
    bool visitado;
    struct LocalizacaoPostosAdjacentes* postosAdjacentes; // Pointer to the first adjacent node
    struct LocalizacaoPostos* proximo; // Pointer to the next adjacent node

} LocalizacaoPostos;

typedef struct LocalizacaoPostosAdjacentes {
    int idDestino;
    struct LocalizacaoPostos* postoDestinoAdjacente; // Pointer to the destination node
    float distancia;
    struct LocalizacaoPostosAdjacentes* proximo; // Pointer to the next adjacent node
} LocalizacaoPostosAdjacentes;

typedef struct Camiao {
    int idOrigem;
    float cargaAtual;
    float cargaMaxima;
    struct LocalizacaoPostos* localizacaoAtual;
} Camiao;

typedef struct CaminhoCamiao {
    int idPosto;
    int idMeio;
    int pesoMeio;
    struct CaminhoCamiao* proximo;
} CaminhoCamiao;


LocalizacaoPostos* CriarPosto(int id, char* cidade, float latitude, float longitude, bool visitado, LocalizacaoPostosAdjacentes* postosAdjacentes);
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
float dijkstra(LocalizacaoPostos* headList, int origemId, int destinationId);

bool verSeAcessivel(LocalizacaoPostos* headLista, LocalizacaoPostos* origemPonto, LocalizacaoPostos* destinoPonto);


Camiao* CriarCamiao(int idOrigem, float cargaAtual, float cargaMaxima, LocalizacaoPostos* localizacaoAtual);
void camiaoRecolha(Camiao* camiao, LocalizacaoPostos* headListPontos, struct MeiosDeMobilidade* headListMeios);


CaminhoCamiao* RemoverCaminhoNode(CaminhoCamiao* header, int id);


CaminhoCamiao* CreateCaminho(LocalizacaoPostos* headListPontos, struct MeiosDeMobilidade* headListMeios);


bool ExisteCaminhoNode(CaminhoCamiao* header, int idCaminhoCamiao);

int caminhoMaisPerto(LocalizacaoPostos* headList, int origemId, CaminhoCamiao* caminhoCamiaoList, float* distancia, int* idParaEliminar, float* pesoAtual, float capacidadeMaxima);