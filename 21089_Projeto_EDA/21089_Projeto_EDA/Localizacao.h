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
    char geocode[LARGURAGERALSTRING];
    struct LocalizacaoPostosAdjacentes* postosAdjacentes; // Pointer to the first adjacent node
    struct LocalizacaoPostos* proximo; // Pointer to the next adjacent node

} LocalizacaoPostos;

typedef struct LocalizacaoPostosAdjacentes {
    struct LocalizacaoPostos* postoDestinoAdjacente; // Pointer to the destination node
    float distancia;
    struct LocalizacaoPostosAdjacentes* proximo; // Pointer to the next adjacent node
} LocalizacaoPostosAdjacentes;

LocalizacaoPostos* CriarPosto(int id, const char* cidade, const char* latitude, const char* longitude, const char* geocode);
LocalizacaoPostos* InserePostoGrafo(LocalizacaoPostos* header, LocalizacaoPostos* novoPosto);

LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, float distancia);
LocalizacaoPostosAdjacentes* InserirPostoAdjacente(LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino, float distancia);

LocalizacaoPostos* ProcurarPorIdPostos(LocalizacaoPostos* headerList, int id);
bool JaTemPostoAdjacente(LocalizacaoPostos* headerOrigem, LocalizacaoPostos* headerDestino);
bool ExistePosto(LocalizacaoPostos* header, int idPosto);