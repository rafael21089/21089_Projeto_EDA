/**
*  @file Localizacao.h
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Definicao da struct Localizacao onde ira guardar o registo de postos e postos adjacentes, com as suas respectivas funcoes
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGURAGERALSTRING 100



/**
 * @brief Estrutura de Vertices (LocalizacaoPostos) para grafo orientado de Postos de Localizacao
 *
 * Um Postos contém um id (@@id), cidade (@@cidade) ,latitude (@@latitude) , longitude (@@longitude), visitado (@@visitado) e postosAdjacentes (@@postosAdjacentes).
 */
typedef struct Postos {
    int id;
    char cidade[LARGURAGERALSTRING];
    float latitude;
    float longitude;
    bool visitado;
    struct LocalizacaoPostosAdjacentes* postosAdjacentes; // Postos Adjacentes (arestas/conecçoes)

} Postos;


/**
 * @brief Estrutura de para Grafo orientado de Postos de Localizacao
 *
 * Um LocalizacaoPostos contém posto (@@posto).
 * Contém apontador para próximo LocalizacaoPostos
 */
typedef struct LocalizacaoPostos {
    struct Postos* posto;
    struct LocalizacaoPostos* proximo; // Pointer to the next adjacent node

} LocalizacaoPostos;



/**
 * @brief Estrutura de Arestas (LocalizacaoPostosAdjacentes) para Postos de Localizacao
 *
 * Um LocalizacaoPostos contém um idDestino (@@id), postoDestinoAdjacente (@@postoDestinoAdjacente) e distancia (@@distancia).
 * Contém apontador para próximo LocalizacaoPostosAdjacentes
 */

typedef struct LocalizacaoPostosAdjacentes {
    int idDestino;
    struct LocalizacaoPostos* postoDestinoAdjacente; // Posto do Destino Da Adjacencia
    float distancia;
    struct LocalizacaoPostosAdjacentes* proximo; 
} LocalizacaoPostosAdjacentes;


/**
 * @brief Estrutura de Camiao Que Recolhe Meios de Mobilidade
 *
 * Um Camiao contém um idOrigem (@@idOrigem), cargaAtual (@@cargaAtual) , cargaMaxima (@@cargaMaxima) e localizacaoAtual (@@localizacaoAtual).
 */
typedef struct Camiao {
    int idOrigem;
    float cargaAtual;
    float cargaMaxima;
    struct LocalizacaoPostos* localizacaoAtual;
} Camiao;

/**
 * @brief Estrutura Para Guardar os Pontos Que o Camiao irá Prosseguir 
 *
 * Um CaminhoCamiao contém um idPosto (@@idPosto), idMeio (@@idMeio) e pesoMeio (@@pesoMeio).
 * Contém apontador para próximo CaminhoCamiao
 */
typedef struct CaminhoCamiao {
    int idPosto;
    int idMeio;
    int pesoMeio;
    struct CaminhoCamiao* proximo;
} CaminhoCamiao;


//Criar Posto
LocalizacaoPostos* CriarPosto(int id, char* cidade, float latitude, float longitude, bool visitado, LocalizacaoPostosAdjacentes* postosAdjacentes);
//Insere Posto no Header de Postos
LocalizacaoPostos* InserePostoGrafo(LocalizacaoPostos* header, LocalizacaoPostos* novoPosto);
//Ver se Existe Posto na lista por id
bool ExistePosto(LocalizacaoPostos* header, int idPosto);
//Remove Posto no Header de Postos
LocalizacaoPostos* RemoverPosto(LocalizacaoPostos* header, int id);
//Alterna Posto
void AlteraPosto(LocalizacaoPostos* header, int id, float latitude, float longitude);

//Criar Posto Adjacente
LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, LocalizacaoPostos* postoOrigem);
//Insere Posto Adjacente no respetivo Posto
LocalizacaoPostos* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino);
//Ver se Existe Posto Adjacente na lista por id
bool ExistePostoAdjacente(LocalizacaoPostosAdjacentes* header, int idPostosAdjacentes);
//Remove Posto Adjacente no respetivo Posto
LocalizacaoPostosAdjacentes* RemoverPostoAdjacente(LocalizacaoPostos* headerPostos, LocalizacaoPostosAdjacentes* headerPostoAdjacente, int id);
//Atualiza Posto Adjacentes Para todos os Postos existentes
LocalizacaoPostos* AtualizarPostosAdjacentes(LocalizacaoPostos* headLista);

//Procura Por Id Postos e retorna a lista toda a comecar com o id
LocalizacaoPostos* ProcurarPorIdPostosComListaToda(LocalizacaoPostos* headerList, int id);
//Procura Por Id Posto e retorna o sozinho
LocalizacaoPostos* ProcurarPorIdPostos(LocalizacaoPostos* headerList, int id);

//Le e armazena txt file Posto
LocalizacaoPostos* LerEArmazenarPosto(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista);
//Le e armazena txt file Posto Adjacentes em Posto
LocalizacaoPostos* LerEArmazenarPostoAdjacente(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista);
//Grava Posto num ficheiro binario
bool GravarPostosBinario(char* nomeFicheiro, LocalizacaoPostos* header);
//Le e Guarda Posto de um ficheiro binario
LocalizacaoPostos* LerPostosBinario(char* nomeFicheiro);

//Grava Posto Adjacentes num ficheiro binario
bool GravarPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos* header);
//Le e Guarda Posto Adjacentes de um ficheiro binario
LocalizacaoPostos* LerPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos** header, bool* resultado);
//Ver se ja tem Posto Adjacente no determinado Posto 
bool JaTemPostoAdjacente(LocalizacaoPostos* headerOrigem, LocalizacaoPostos* headerDestino);
//Procura Posto Adjacente
LocalizacaoPostosAdjacentes* ProcurarPostoAdjacente(LocalizacaoPostos* posto, LocalizacaoPostos* postoDestino);

//Funcao que procura o caminho pelo os Postos usando dijkstra 
float AlgoritmoDijkstra(LocalizacaoPostos* headLista, int origemId, int destinoId, bool querImprimirResultados);
//Ver se é Acessivel ir de um Posto Para Posto
bool VerSeAcessivel(LocalizacaoPostos* headLista, LocalizacaoPostos* origemPonto, LocalizacaoPostos* destinoPonto);

//Cria Camiao
Camiao* CriarCamiao(float cargaAtual, float cargaMaxima, LocalizacaoPostos* localizacaoAtual);
//Camiao Recolhe Meios com Menos de 50% De Bateria 
bool CamiaoRecolha(Camiao* camiao, LocalizacaoPostos* headListPontos, struct MeiosDeMobilidade* headListMeios);

//Cria Caminho Node
CaminhoCamiao* CriarCaminhoNodes(int idPosto, int idMeio, int pesoMeio);
//Insere Caminho Node no header
CaminhoCamiao* InserirCaminho(CaminhoCamiao* headLista, CaminhoCamiao* novoCaminho);
//Remove Node do Caminho do Camiao
CaminhoCamiao* RemoverCaminhoNode(CaminhoCamiao* header, int id);
//Cria Caminho para Camiao
CaminhoCamiao* CreateCaminho(LocalizacaoPostos* headListPontos, struct MeiosDeMobilidade* headListMeios, float* distanciaExtra);
//Ver Se Ja exite um Node Para o Caminho para Camiao
bool ExisteCaminhoNode(CaminhoCamiao* header, int idCaminhoCamiao);
//Caminho Mais Perto para os Postos no Caminho para Camiao
int CaminhoMaisPerto(LocalizacaoPostos* headLista, int origemId, CaminhoCamiao* caminhoCamiaoLista, float* distancia, int* idParaEliminar, float* pesoAtual, float capacidadeMaxima);

//Localizacao do Posto mais perto por Raio com o Cliente como centro
bool LocalizacaoRaioClientePosto(struct Clientes* cliente, LocalizacaoPostos* headListaPostos, float raio);
//Localizacao do Meio por tipo mais perto por Raio com o Cliente como centro
bool LocalizacaoRaioClienteMeio(struct Clientes* cliente, struct MeiosDeMobilidade* headListaMeio, float raio, char* tipo);
//Calcula distancia por Latitude e Longitude de dois Geocodigos
float CalculaDistancia(float latitude1, float longitude1, float latitude2, float longitude2);
//Distancia e Caminho de Cliente a Meio usando Postos
LocalizacaoPostos* DistanciaClienteAMeioTotal(struct Clientes* cliente, struct MeiosDeMobilidade* meio, LocalizacaoPostos* headListPostos);
//Distancia e Caminho de Cliente a Posto
LocalizacaoPostos* DistanciaClienteAPostoTotal(struct Clientes* cliente, LocalizacaoPostos* headListaPostos, int idPostoDestino);
//Cria Posto Escrever
int CriarPostoEscrever(LocalizacaoPostos* headPosto);
//Listar Postos
int ListarTodosPostos(LocalizacaoPostos* header);
//Remover Postos Escrever
LocalizacaoPostos* RemoverPostoEscrever(LocalizacaoPostos* headPostos);
//Alterar Posto (Latitude e Longitude)
int AlterarPorEscreverPosto(LocalizacaoPostos* headPosto);

//Cria Adjacencia
int CriarAdjacenciaPostoEscrever(LocalizacaoPostos* headPosto);
//Remover Adjacencia
int RemoverAdjacenciaPostoEscrever(LocalizacaoPostos* headPosto);

//Camiao Recolha Escrever
int CamiaoRecolhaEscrever(LocalizacaoPostos* headPosto, struct MeiosDeMobilidade* headListaMeios);
//Cliente Para Posto Escrever
int ClienteParaPostoLocalizacao(struct Clientes* headClientes, LocalizacaoPostos* headListaPostos, int idCliente);

//Cliente viaja com o Meio Alugado (tem que tar na mesma localizacao) 
LocalizacaoPostos* ViajarComMeioAteLocalizacao(struct Clientes* cliente, LocalizacaoPostos* headListaPostos, struct MeiosDeMobilidade* headListaMeio, float latitude, float longitude);

