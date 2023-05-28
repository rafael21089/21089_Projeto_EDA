/**
*  @file Localizacao.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 *
 * @brief Funcoes para Localizacao

*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "Localizacao.h"
#include "MeioDeMobilidade.h"


#define MAXIMO_DE_NODES_CAMINHO 100
#define DISTANCIA_MAXIMA 500
#define TERRA_RAIO 6371.0


/**
*	@brief Cria Novo Posto .
*
*
*	@param [in] id								    id do Posto
*	@param [in] cidade							    cidade do Posto
*	@param [in] latitude							latitude do Posto
*	@param [in] longitude							longitude do Posto
*	@param [in] visitado							ver se ta visitado o Posto
*	@param [in] postosAdjacentes					postos Adjacentes
*
*	@return novoPosto de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* CriarPosto(int id, char* cidade, float latitude, float longitude, bool visitado, LocalizacaoPostosAdjacentes* postosAdjacentes) {
    Postos* novoPosto = (Postos*)malloc(sizeof(Postos));
    LocalizacaoPostos* novoPostoVertice = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));
    if (novoPosto == NULL) {
        return NULL;
    }
 
    novoPosto->id = id;
    strncpy(novoPosto->cidade, cidade, LARGURAGERALSTRING);

    novoPosto->latitude = latitude;
    novoPosto->longitude = longitude;
    novoPosto->visitado = visitado;
    novoPosto->postosAdjacentes = postosAdjacentes;

    novoPostoVertice->posto = novoPosto;
    novoPostoVertice->proximo = NULL;

    return novoPostoVertice;
}


/**
*	@brief Insere Posto na lista de Postos.
*
*
*	@param [in] header								    header da Lista de Postos
*	@param [in] novoPosto							    novo Posto Para Inserir
*
*	@return header de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* InserePostoGrafo(LocalizacaoPostos* header, LocalizacaoPostos* novoPosto) {

    if (ExistePosto(header, novoPosto->posto->id)) {
        return header; // If the posto already exists, return the original header
    }

    if (header == NULL) {
        header = novoPosto; // If the list is empty, set novoPosto as the new header
        return header;
    }
    else {
        LocalizacaoPostos* aux = header;
        LocalizacaoPostos* ant = NULL; // Initialize ant to NULL
        while (aux && aux->posto->id < novoPosto->posto->id) {
            ant = aux;
            aux = aux->proximo;
        }
        if (ant == NULL) {
            header->posto = novoPosto;
        }
        else {
            ant->proximo = novoPosto;
        }
    }
    return header;
}

/**
*	@brief Ver se Posto existe na lista de Postos.
*
*
*	@param [in] header								    header da Lista de Postos
*	@param [in] idPosto							        id do Posto
*
*	@return True/False;
*
*
*/
bool ExistePosto(LocalizacaoPostos* header, int idPosto) {
    if (header == NULL) return false;
    LocalizacaoPostos* aux = header;
    while (aux != NULL) {
        if (aux->posto->id == idPosto)
            return true;
        aux = aux->proximo;
    }
    return false;
}

/**
*	@brief Remove Posto na lista de Postos.
*
*
*	@param [in] header								    header da Lista de Postos
*	@param [in] id							            id Posto Para Remover
*
*	@return header de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* RemoverPosto(LocalizacaoPostos* header, int id) {
    if (header == NULL) return NULL;			//Lista vazia

    if (!ExistePosto(header, id)) return;

    if (header->posto->id == id) {		//remove no inicio da lista
        LocalizacaoPostos* aux = header;
        header = header->proximo;
        free(aux);
    }
    else
    {
        LocalizacaoPostos* aux = header;
        LocalizacaoPostos* auxAnt = aux;
        while (aux && aux->posto->id != id) {	//procura para revover
            auxAnt = aux;
            aux = aux->proximo;
        }
        if (aux != NULL) {					//se encontrou, remove
            auxAnt->proximo = aux->proximo;
            free(aux);
        }
    }

    header = AtualizarPostosAdjacentes(header);

    return header;
}

/**
*	@brief Cria Posto Adjacente
*
*
*	@param [in] postoDestinoAdjacente						    posto que quer ficar Adjacente (Destino)
*	@param [in] postoOrigem							            posto origem (Origem)
*
*	@return postoAdjacente de LocalizacaoPostos;
*
*
*/
LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, LocalizacaoPostos* postoOrigem) {

    LocalizacaoPostosAdjacentes* postoAdjacente = (LocalizacaoPostosAdjacentes*)malloc(sizeof(LocalizacaoPostosAdjacentes));
    if (postoAdjacente == NULL) {
        return NULL;
    }

    postoAdjacente->postoDestinoAdjacente = postoDestinoAdjacente->posto;
    postoAdjacente->idDestino = postoDestinoAdjacente->posto->id;
    postoAdjacente->distancia = CalculaDistancia(postoDestinoAdjacente->posto->latitude , postoDestinoAdjacente->posto->longitude , postoOrigem->posto->latitude , postoOrigem->posto->longitude);
    postoAdjacente->proximo = NULL;

    return postoAdjacente;
}


/**
*	@brief Insere Posto Adjacente para um Posto.
*
*
*	@param [in] headLista						                head Lista Postos
*	@param [in] postoOrigem						                posto origem (Origem)
*	@param [in] postoDestino							        posto destino (Destino)
*
*	@return headLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino) {
    if (*headLista == NULL || postoOrigem == NULL || postoDestino == NULL) {
        return *headLista;
    }

    if (JaTemPostoAdjacente(postoOrigem, postoDestino)) {
        return *headLista;
    }

    LocalizacaoPostosAdjacentes* novoAdjacente = CriarPostoAdjacente(postoDestino, postoOrigem);
    if (novoAdjacente == NULL) {
        return *headLista;
    }

    LocalizacaoPostos* aux = ProcurarPorIdPostosComListaToda(*headLista, postoOrigem->posto->id);

    if (aux->posto->postosAdjacentes == NULL) {
        aux->posto->postosAdjacentes = novoAdjacente;
    }
    else {
        LocalizacaoPostosAdjacentes* aux2 = aux->posto->postosAdjacentes;
        while (aux2->proximo != NULL) {
            aux2 = aux2->proximo;
        }
        aux2->proximo = novoAdjacente;
    }

 
    *headLista = AtualizarPostosAdjacentes(*headLista);  //Atualiza a todos os Postos

    return *headLista;
}


/**
*	@brief Procura Posto Adjacente
*
*
*	@param [in] posto						                posto
*	@param [in] postoDestino						        posto destino que quer Procurar
*
*	@return adjacente de LocalizacaoPostosAdjacentes;
*
*
*/
LocalizacaoPostosAdjacentes* ProcurarPostoAdjacente(LocalizacaoPostos* posto, LocalizacaoPostos* postoDestino) {
    if (posto == NULL || postoDestino == NULL || posto->posto->postosAdjacentes == NULL) {
        return NULL;
    }

    LocalizacaoPostosAdjacentes* adjacente = posto->posto->postosAdjacentes;
    while (adjacente != NULL) {
        if (adjacente->postoDestinoAdjacente->posto->id == postoDestino->posto->id) {
            return adjacente;
        }
        adjacente = adjacente->proximo;
    }

    return NULL;
}


/**
*	@brief Ver se Existe Posto Adjacente
*
*
*	@param [in] header						                header de postos
*	@param [in] idPostosAdjacentes						    id de postos adjacentes
*
*	@return True/False;
*
*
*/
bool ExistePostoAdjacente(LocalizacaoPostosAdjacentes* header, int idPostosAdjacentes) {
    if (header == NULL) return false;
    LocalizacaoPostosAdjacentes* aux = header;
    while (aux != NULL) {
        if (aux->postoDestinoAdjacente->posto->id == idPostosAdjacentes)
            return true;
        aux = aux->proximo;
    }
    return false;
}


/**
*	@brief Remove Posto Adjacente
*
*
*	@param [in] headerPostos						            header dos postos
*	@param [in] headerPostoAdjacente						    header de postos adjacentes
*	@param [in] id						                        id de qual quer remover
*
*	@return headerPostoAdjacente de LocalizacaoPostosAdjacentes;
*
*
*/
LocalizacaoPostosAdjacentes* RemoverPostoAdjacente(LocalizacaoPostos* headerPostos, LocalizacaoPostosAdjacentes* headerPostoAdjacente, int id) {
    if (headerPostoAdjacente == NULL) return NULL;			//Lista vazia

    if (!ExistePostoAdjacente(headerPostoAdjacente, id)) return;

    if (headerPostoAdjacente->postoDestinoAdjacente->posto->id == id) {		//remove no inicio da lista
        LocalizacaoPostosAdjacentes* aux = headerPostoAdjacente;
        headerPostoAdjacente = headerPostoAdjacente->proximo;
        headerPostos->posto->postosAdjacentes = headerPostoAdjacente;
        free(aux);
    }
    else
    {
        LocalizacaoPostosAdjacentes* aux = headerPostoAdjacente;
        LocalizacaoPostosAdjacentes* auxAnt = aux;
        while (aux && aux->postoDestinoAdjacente->posto->id != id) {	//procura para revover
            auxAnt = aux;
            aux = aux->proximo;
        }
        if (aux != NULL) {					//se encontrou, remove
            auxAnt->proximo = aux->proximo;
            free(aux);
        }
    }

    headerPostos = AtualizarPostosAdjacentes(headerPostos);

    return headerPostoAdjacente;
}


/**
*	@brief Altera Posto (Latitude e Longitude)
*
*
*	@param [in] header					header da lista de Postos
*	@param [in] id						id Posto
*	@param [in] latitude				latitude Posto
*	@param [in] longitude				longitude Posto
*
*
*/
void AlteraPosto(LocalizacaoPostos* header, int id, float latitude , float longitude) {
    if (header == NULL) {

        return NULL;
    }

        LocalizacaoPostos* aux = header;

        while (aux != NULL)
        {
            if (aux->posto->id == id)
            {
                aux->posto->latitude = latitude;
                aux->posto->longitude = longitude;
            }

            aux = aux->proximo;
        }
 
    header = AtualizarPostosAdjacentes(header);
}


/**
*	@brief Atualiza Postos Adjacentes de Postos para Todos os Postos
*
*
*	@param [in] headLista						                header dos postos
*
*	@return headLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* AtualizarPostosAdjacentes(LocalizacaoPostos* headLista) {
    if (headLista == NULL) {
        return NULL; 
    }

    LocalizacaoPostos* aux = headLista;

    while (aux != NULL) {
        LocalizacaoPostosAdjacentes* adjacente = aux->posto->postosAdjacentes;

        while (adjacente != NULL) {
            LocalizacaoPostos* destino = ProcurarPorIdPostos(headLista, adjacente->idDestino); //Procura por Id Posto
            if (destino != NULL) {
                adjacente->postoDestinoAdjacente = destino;
            }
            else
            {
                aux->posto->postosAdjacentes = adjacente->proximo;
            }

            adjacente = adjacente->proximo;
        }

        aux = aux->proximo;
    }

    return headLista;
}

/**
*	@brief Procura Por Id Postos Com a Lista Toda
*
*
*	@param [in] headLista						                header de postos
*	@param [in] id						                        id do Posto
*
*	@return headLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* ProcurarPorIdPostosComListaToda(LocalizacaoPostos* headerList, int id) {
    if (headerList == NULL) return NULL;		//lista vazia
    else
    {
        LocalizacaoPostos* aux = headerList;
        while (aux != NULL) {
            if (aux->posto->id == id) {
                return (aux);		//encontrou
            }
            aux = aux->proximo;
        }
        return NULL;
    }
}


/**
*	@brief Procura Por Id Postos Com so o Posto
*
*
*	@param [in] headerList						                header de postos
*	@param [in] id						                        id do Posto
*
*	@return headLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* ProcurarPorIdPostos(LocalizacaoPostos* headerLista, int id) {

    if (headerLista == NULL)
    {
        return NULL;
    }

    LocalizacaoPostos* aux = headerLista;

    while (aux != NULL) {
        if (aux->posto->id == id) {
            LocalizacaoPostos* novoPosto = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));
            novoPosto = CriarPosto(aux->posto->id, aux->posto->cidade, aux->posto->latitude, aux->posto->longitude , aux->posto->visitado ,aux->posto->postosAdjacentes); //Cria o encontrado e retorna
         
            return novoPosto;
        }
        aux = aux->proximo;
    }

    return NULL;
}


/**
*	@brief Ver Se Ja Tem o Posto Adjacente
*
*
*	@param [in] headerOrigem						             header do posto de origem
*	@param [in] headerDestino						             header do posto de destino
*
*	@return True/False;
*
*
*/
bool JaTemPostoAdjacente(LocalizacaoPostos* headerOrigem, LocalizacaoPostos* headerDestino) {
    if (headerOrigem == NULL) return false;
    if (headerDestino == NULL) return false;

    LocalizacaoPostos* aux = headerOrigem;
    LocalizacaoPostos* aux2 = headerDestino;

    LocalizacaoPostosAdjacentes* auxAdj = aux->posto->postosAdjacentes;

    if (auxAdj == NULL)
    {
        return false;
    }
    else
    {
        while (aux != NULL) {
           
                LocalizacaoPostos* aux3 = aux->posto->postosAdjacentes->postoDestinoAdjacente;

                while (aux3 != NULL)
                {
                    if (aux3->posto->id == aux2->posto->id)
                        return true;

                    aux3 = aux3->proximo;
                }

                aux = aux->proximo;
                aux2 = aux2->proximo;
            } 
    }

  
    return false;
}


/**
*	@brief Ler txt file e Guarda Posto
*
*
*	@param [in] nomeFicheiro						             nome do Ficheiro
*	@param [in] headerPostosLista						         header da lista de postos
*
*	@return headerPostosLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* LerEArmazenarPosto(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista) {

    FILE* file = fopen(nomeFicheiro, "r");
    if (file == NULL) {
        printf("File %s does not exist, creating empty file...\n", nomeFicheiro);
        file = fopen(nomeFicheiro, "w");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        //Remove \n e \0
        line[strcspn(line, "\n")] = '\0';

        LocalizacaoPostos* novoPosto = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));

        novoPosto->posto = (Postos*)malloc(sizeof(Postos));
       
        char* token = strtok(line, ";");
        novoPosto->posto->id = atoi(token);
        token = strtok(NULL, ";");
        strncpy(novoPosto->posto->cidade, token, sizeof(novoPosto->posto->cidade));
        token = strtok(NULL, ";");
        novoPosto->posto->latitude = atof(token);
        token = strtok(NULL, ";");
        novoPosto->posto->longitude = atof(token);

        novoPosto->posto->visitado = false;
        novoPosto->posto->postosAdjacentes = NULL;
        novoPosto->proximo = NULL;

        *headerPostosLista = InserePostoGrafo(*headerPostosLista, novoPosto); // Insere Posto

    }

    fclose(file);

    return *headerPostosLista;
}


/**
*	@brief Ler txt file e Guarda Posto Adjacentes
*
*
*	@param [in] nomeFicheiro						             nome do Ficheiro
*	@param [in] headerPostosLista						         header da lista de postos
*
*	@return headerPostosLista de LocalizacaoPostos;
*
*
*/
LocalizacaoPostos* LerEArmazenarPostoAdjacente(char* nomeFicheiro, LocalizacaoPostos** headerPostosLista) {

    FILE* file = fopen(nomeFicheiro, "r");
    if (file == NULL) {
        printf("File %s does not exist, creating empty file...\n", nomeFicheiro);
        file = fopen(nomeFicheiro, "w");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        //Remove \n e \0
        line[strcspn(line, "\n")] = '\0';

    
        float distancia = 0;
        int idOrigem;
        int idDestino;

        char* token = strtok(line, ";");
        idOrigem = atoi(token);
        token = strtok(NULL, ";");
        idDestino = atoi(token);

        *headerPostosLista = InserirPostoAdjacente(headerPostosLista, ProcurarPorIdPostos(*headerPostosLista, idOrigem), ProcurarPorIdPostos(*headerPostosLista, idDestino));

    }

    fclose(file);

    return *headerPostosLista;
}



/**
*	@brief Guarda Postos em Bin file
*
*
*	@param [in] nomeFicheiro						            nome do Ficheiro
*	@param [in] header						                    header da lista de postos
*
*	@return True/False;
*
*/
bool GravarPostosBinario(char* nomeFicheiro, LocalizacaoPostos* header) {
    FILE* fp;

    if (header == NULL) return false;
    if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

    LocalizacaoPostos* aux = header;
    while (aux) {
        // Escreve no ficheiro os dados do registo de memória

        Postos* aux2 = aux->posto;

        fwrite(aux2, sizeof(Postos), 1, fp);
        aux = aux->proximo;
    }
    fclose(fp);
    return true;
}


/**
*	@brief Le Postos do Bin file
*
*
*	@param [in] nomeFicheiro						            nome do Ficheiro
*
*	@return header de LocalizacaoPostos;
*
*/
LocalizacaoPostos* LerPostosBinario(char* nomeFicheiro) {
    FILE* fp;
    LocalizacaoPostos* header = NULL;
    Postos* auxAnt;

    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

    //Ler o registos do ficheiro binario
    while ((auxAnt = (Postos*)malloc(sizeof(Postos))) && fread(auxAnt, sizeof(Postos), 1, fp)) {
        LocalizacaoPostos* aux = CriarPosto(auxAnt->id, auxAnt->cidade, auxAnt->latitude, auxAnt->longitude, auxAnt->visitado, NULL); //Cria Posto com valores recebidos
        header = InserePostoGrafo(header, aux); //Insere Posto
    }
    fclose(fp);
    return header;
}



/**
*	@brief Guarda Postos Adjacentes em Bin file
*
*
*	@param [in] nomeFicheiro						            nome do Ficheiro
*	@param [in] header						                    header da lista de postos
*
*	@return True/False;
*
*/
bool GravarPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos* header) {
    FILE* fp;

    if (header == NULL) return false;
    if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

    LocalizacaoPostos* aux = header;

    while (aux != NULL)
    {
        LocalizacaoPostosAdjacentes* adj = aux->posto->postosAdjacentes;
        while (adj != NULL) {
            fwrite(&(aux->posto->id), sizeof(int), 1, fp);  //Guarda Id
            fwrite(adj, sizeof(LocalizacaoPostosAdjacentes), 1, fp); //Guarda LocalizacaoPostosAdjacentes
            adj = adj->proximo;
        }

        aux = aux->proximo;
    }


    fclose(fp);
    return true;
}


/**
*	@brief Le Postos Adjacentes do Bin file
*
*
*	@param [in] nomeFicheiro						            nome do Ficheiro
*	@param [in] header						                    header da Lista de Postos
*	@param [in] resultado						                resultado da funcao
*
*	@return header de LocalizacaoPostos;
*
*/
LocalizacaoPostos* LerPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos** header , bool* resultado) {
    FILE* fp;

    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) {

        *resultado = false;
        return *header;
    }


    int id;

    while (!feof(fp))
    {
        int id;
        LocalizacaoPostosAdjacentes adj;

        // Le id e LocalizacaoPostosAdjacentes
        if (fread(&id, sizeof(int), 1, fp) != 1) break;
        if (fread(&adj, sizeof(LocalizacaoPostosAdjacentes), 1, fp) != 1) break;

        int idOrigem = id;
        int idDestino = adj.idDestino;

        *header = InserirPostoAdjacente(header, ProcurarPorIdPostos(*header, idOrigem), ProcurarPorIdPostos(*header, idDestino));  //Insere Posto Adjacente
     
    }

    fclose(fp);

    return *header;
}


/**
*	@brief Cria Camiao
*
*	@param [in] cargaAtual						                carga Atual do camiao
*	@param [in] cargaMaxima						                carga Maxima do Camiao
*	@param [in] localizacaoAtual						        localizacao Atual
*
*	@return novoCamiao de Camiao;
*
*/
Camiao* CriarCamiao(float cargaAtual , float cargaMaxima, LocalizacaoPostos* localizacaoAtual) {

    Camiao* novoCamiao= (Camiao*)malloc(sizeof(Camiao));
    if (novoCamiao == NULL) {
        return NULL;
    }

    novoCamiao->idOrigem = localizacaoAtual->posto->id;
    novoCamiao->cargaAtual = cargaAtual;
    novoCamiao->cargaMaxima = cargaMaxima;
    novoCamiao->localizacaoAtual = localizacaoAtual;

    return novoCamiao;
}


/**
*	@brief Cria Caminho para Camiao
*
*	@param [in] idPosto						             id do Posto
*	@param [in] idMeio						             id do Meio
*	@param [in] pesoMeio						         peso do Meio
*
*	@return novoCaminho de CaminhoCamiao;
*
*/
CaminhoCamiao* CriarCaminhoNodes(int idPosto, int idMeio, int pesoMeio) {

    CaminhoCamiao* novoCaminho = (Camiao*)malloc(sizeof(Camiao));
    if (novoCaminho == NULL) {
        return NULL;
    }

    novoCaminho->idPosto = idPosto;
    novoCaminho->idMeio = idMeio;
    novoCaminho->pesoMeio = pesoMeio;
    novoCaminho->proximo = NULL;

    return novoCaminho;
}

/**
*	@brief Insere novo Caminho para Camiao na Lista
*
*	@param [in] headLista						         head lista do caminho do camiao
*	@param [in] novoCaminho						         novo node para Caminho Camiao
*
*	@return headLista de CaminhoCamiao;
*
*/
CaminhoCamiao* InserirCaminho(CaminhoCamiao* headLista , CaminhoCamiao* novoCaminho) {

    if (headLista == NULL) {
        headLista = novoCaminho;
    }
    else
    {
        CaminhoCamiao* aux = headLista;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = novoCaminho;
    }

    return headLista;
}

/**
*	@brief Cria Caminho
*
*	@param [in] headListPontos						         head lista de pontos
*	@param [in] headListMeios						         head lista de meios
*	@param [in] distanciaExtra						         distancia extra para chegar aos pontos
*
*	@return caminho de CaminhoCamiao;
*
*/
CaminhoCamiao* CreateCaminho(LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios, float* distanciaExtra ) {

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;
    MeiosDeMobilidade* auxMeiosNaoEmPostos = headListMeios;

    CaminhoCamiao* caminho = NULL; // Começa Caminho


    // Ve quais Meios Estao na localizacao Exata Nos Postos de Recolha e Adiciona ao caminho
    while (auxPontos != NULL)
    {
        while (auxMeios != NULL) {
            if (auxPontos->posto->latitude == auxMeios->latitude && auxPontos->posto->longitude == auxMeios->longitude && auxMeios->cargaBateria <= 50 && auxMeios->estado == true) {

                CaminhoCamiao* novoCaminho = CriarCaminhoNodes(auxPontos->posto->id, auxMeios->id, auxMeios->peso);
                caminho = InserirCaminho(caminho , novoCaminho);

                printf("Caminho: Posto %d - (%.4f, %.4f) Com Meio de Mobilidade %d com peso %.2f kg \n", novoCaminho->idPosto, auxPontos->posto->latitude, auxPontos->posto->longitude, auxMeios->id , auxMeios->peso);
 
            }

            auxMeios = auxMeios->next;
        }

        auxMeios = headListMeios;
        auxPontos = auxPontos->proximo;
    }

    //Variaveis Para Guardar Valores
    LocalizacaoPostos* auxPontosProximos = headListPontos;
    float caminhoMaisPerto = DISTANCIA_MAXIMA;
    int idPostoMaisPerto = 0;
    int idMeioMaisPerto = 0;
    float latitudeMaisPerto = 0;
    float longitudeMaisPerto = 0;
    float pesoMaisPerto = 0;

    // Ve Quais Meios Na Distancia Maxima Estao Perto de os Postos de Recolha e Adiciona os mas Tambem Adiciona a Distancia Extra do Posto Mais Perto ao Meio
    while (auxPontosProximos != NULL)
    {
        while (auxMeiosNaoEmPostos != NULL)
        {
            float caminhoParaPontoExtra = CalculaDistancia(auxMeiosNaoEmPostos->latitude , auxMeiosNaoEmPostos->longitude, auxPontosProximos->posto->latitude , auxPontosProximos->posto->longitude);

            if ((caminhoParaPontoExtra <= DISTANCIA_MAXIMA && caminhoParaPontoExtra != 0) && auxMeiosNaoEmPostos->cargaBateria <= 50 && auxMeiosNaoEmPostos->estado == true && !ExisteCaminhoNode(caminho, auxMeiosNaoEmPostos->id)) { //Ve se o Meio ja ta no caminho

                if (caminhoParaPontoExtra < caminhoMaisPerto)
                {
                    caminhoMaisPerto = caminhoParaPontoExtra;
                    idPostoMaisPerto = auxPontosProximos->posto->id;
                    idMeioMaisPerto = auxMeiosNaoEmPostos->id;
                    pesoMaisPerto = auxMeiosNaoEmPostos->peso;
                    latitudeMaisPerto = auxPontosProximos->posto->latitude;
                    longitudeMaisPerto = auxPontosProximos->posto->longitude;
                }
            }

            auxMeiosNaoEmPostos = auxMeiosNaoEmPostos->next;
        }

        if (latitudeMaisPerto != 0 && longitudeMaisPerto != 0 && !ExisteCaminhoNode(caminho, idMeioMaisPerto))
        {
            printf("Caminho: Posto %d - (%.4f, %.4f) - Distancia Extra Para Chegar a Meio de Mobilidade %d : %.2f km  com peso %.2f kg \n", idPostoMaisPerto, latitudeMaisPerto, longitudeMaisPerto, idMeioMaisPerto, caminhoMaisPerto, pesoMaisPerto);

            CaminhoCamiao* novoCaminho = CriarCaminhoNodes(idPostoMaisPerto, idMeioMaisPerto, pesoMaisPerto);

            caminho = InserirCaminho(caminho, novoCaminho);

            *distanciaExtra = *distanciaExtra + caminhoMaisPerto;
        }
        
        auxMeiosNaoEmPostos = headListMeios;
        auxPontosProximos = auxPontosProximos->proximo;
    }

   

    printf("\n\n");

    return caminho;

}


/**
*	@brief Camiao Recolhe os Meios
*
*	@param [in] camiao						         camiao
*	@param [in] headListPontos						 head lista de Postos
*	@param [in] headListMeios						 head lista de meios
*
*	@return True/False;
*
*/
bool CamiaoRecolha(Camiao* camiao , LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios) {

    if (headListPontos == NULL || headListMeios == NULL || camiao == NULL)
    {
        return false;
    }

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;
    Camiao* auxCamiao = camiao;

    CaminhoCamiao* caminho = NULL;

    float distanciaExtra = 0;

    caminho = CreateCaminho(headListPontos , headListMeios, &distanciaExtra);  //Cria Caminho


    float distancia = 0;
    float peso = 0;


    while (caminho != NULL)
    {
       
        int length = 0;
        CaminhoCamiao* current = caminho;
        float distanciaAux = distancia;

        //Conta o numero de Nodes CaminhoCamiao Tem
        while (current != NULL) {
            length++;
            current = current->proximo;
        }

        current = caminho;

        // numero de o Caminho é acrescentado + 2 , o origem , e o destino
        int numIds = length + 2;
        int* idsCaminho = malloc((numIds) * sizeof(int));

        //Adiciona a um array o ids para o caminho
        for (int i = 0; i < numIds; i++)
        {
            if (i == 0)
            {
                idsCaminho[i] = camiao->localizacaoAtual->posto->id;
            }
            else if (i == numIds - 1)
            {
                idsCaminho[i] = camiao->localizacaoAtual->posto->id;

            }
            else
            {
                idsCaminho[i] = current->idPosto;
                current = current->proximo;
            }

        }


        //Vai Por Todos os Pontos Obrigatorios e Recolhe os Meios , metendo os inativos e com a localizacao na origem do Camiao
        for (int i = 0; i < numIds; i++)
        {
            if (i == 0) //Primeio Node
            {
                float distanciaCaminho = AlgoritmoDijkstra(headListPontos, camiao->localizacaoAtual->posto->id, camiao->idOrigem , true); //Distancia da origem ate ao primeiro dos Postos Obrigatorios

                distancia = distancia + distanciaCaminho;
                printf("%d -> ", camiao->idOrigem);
                camiao->localizacaoAtual->posto->id = camiao->idOrigem;

            }
            else if (i == numIds - 1) //Ultimo Node
            {
                float distanciaCaminho = AlgoritmoDijkstra(headListPontos, camiao->localizacaoAtual->posto->id, camiao->idOrigem , true); //Distancia do Posto que esta ate ao final
                distancia = distancia + distanciaCaminho;
                printf("%d -> ", camiao->idOrigem);
                camiao->localizacaoAtual->posto->id = camiao->idOrigem;
            }
            else
            {
                int idParaEliminar = 0;
                int distanciaCaminho = CaminhoMaisPerto(headListPontos, camiao->localizacaoAtual->posto->id, caminho, &distancia, &idParaEliminar, &peso , camiao->cargaMaxima); //Caminho Mais Perto Por os Postos Obrigatorios

                if (distanciaCaminho >= 0)
                {
                    printf("%d -> ", distanciaCaminho);

                    //Desativa Meio
                    MeiosDeMobilidade* meio = ProcuraMeiosDeMobilidade(headListMeios, idParaEliminar);
                    meio->estado = false;

                    //Poe Meio na Localizacao de Origem Do Camiao
                    LocalizacaoPostos* posto = ProcurarPorIdPostos(headListPontos, camiao->idOrigem);
                    meio->latitude = posto->posto->latitude;
                    meio->longitude = posto->posto->longitude;

                    //Remove No Caminho
                    caminho = RemoverCaminhoNode(caminho, idParaEliminar);
                    camiao->localizacaoAtual->posto->id = distanciaCaminho;
                }


            }

        }

        distanciaAux = distancia - distanciaAux;

        printf(" Distancia Por Fases Cometida: %.2f km ", distanciaAux);

        printf(" Peso Na Viagem: %.2f kg\n", peso);

        peso = 0;


    }


    printf("\n Distancia Total da Viagem: %.2f km (normal) + %.2f km (extra) = %.2f km  \n", distancia , distanciaExtra,  distancia + distanciaExtra);

    return true;
}

/**
*	@brief Ver se Existe o Node no Caminho
*
*	@param [in] header						         head do Caminho de Camiao
*	@param [in] idCaminhoCamiao						 id do node do Caminho de Camiao
*
*	@return True/False;
*
*/
bool ExisteCaminhoNode(CaminhoCamiao* header, int idCaminhoCamiao) {
    if (header == NULL) return false;
    CaminhoCamiao* aux = header;
    while (aux != NULL) {
        if (aux->idMeio == idCaminhoCamiao)
            return true;
        aux = aux->proximo;
    }
    return false;
}


/**
*	@brief Remove o Node no Caminho
*
*	@param [in] header				     head do Caminho de Camiao
*	@param [in] id						 id do node do Caminho de Camiao
*
*	@return header de CaminhoCamiao;
*
*/
CaminhoCamiao* RemoverCaminhoNode(CaminhoCamiao* header, int id) {
    if (header == NULL) return NULL;			//Lista vazia

    if (!ExisteCaminhoNode(header, id)) return;

    if (header->idMeio == id) {		//remove no inicio da lista
        CaminhoCamiao* aux = header;
        header = header->proximo;
        free(aux);
    }
    else
    {
        CaminhoCamiao* aux = header;
        CaminhoCamiao* auxAnt = aux;
        while (aux && aux->idMeio != id) {	//procura para revover
            auxAnt = aux;
            aux = aux->proximo;
        }
        if (aux != NULL) {					//se encontrou, remove
            auxAnt->proximo = aux->proximo;
            free(aux);
        }
    }
    return header;
}


/**
*	@brief Ver Se o Caminho de dois Postos Sao Acessiveis
*
*	@param [in] headLista				     head lista de Postos
*	@param [in] origemPonto				     posto de Origem
*	@param [in] destinoPonto			     posto de Destino
*
*	@return True/False;
*
*/
bool VerSeAcessivel(LocalizacaoPostos* headLista, LocalizacaoPostos* origemPonto, LocalizacaoPostos* destinoPonto) {

    if (origemPonto == destinoPonto) {
        return true;
    }

    // Marca o Ponto de Origem True
    origemPonto->posto->visitado = true;

    LocalizacaoPostosAdjacentes* adjacenteNode = origemPonto->posto->postosAdjacentes;
    while (adjacenteNode != NULL) {
        // Visita os adjacentes Recursivamente
        if (!(adjacenteNode->postoDestinoAdjacente->posto->visitado)) {

            if (adjacenteNode->postoDestinoAdjacente->posto->id == destinoPonto->posto->id)
            {
                return true;
            }
            else
            {
                bool res = VerSeAcessivel(headLista, adjacenteNode->postoDestinoAdjacente, destinoPonto);

                if (res == true)
                {
                    return true;
                }
            }  
            
        }
        adjacenteNode = adjacenteNode->proximo;
    }

    // Reseta
    origemPonto->posto->visitado = false;

    // Se nao encontrou retorna Falso
    return false;
}

/**
*	@brief Algoritmo Dijkstra para obter o caminho mais pequeno
*
*	@param [in] headLista				     head lista de Postos
*	@param [in] origemId				     id posto de Origem
*	@param [in] destinoId			     id posto de Destino
*	@param [in] querImprimirResultados		 ver se quer imprimir o path ou nao
*
*	@return distancia[destinoId];
*
*/
float AlgoritmoDijkstra(LocalizacaoPostos* headLista, int origemId, int destinoId , bool querImprimirResultados)
{
    if (ProcurarPorIdPostos(headLista, origemId) == NULL)
    {
        printf("\n Dados Insuficientes para a realizacao do Algoritmo Dijkstra \n");
        return 0;
    }
    if (ProcurarPorIdPostos(headLista, destinoId) == NULL)
    {
        printf("\n Dados Insuficientes para a realizacao do Algoritmo Dijkstra \n");
        return 0;
    }

    int numNodes = 0;
    LocalizacaoPostos* aux = headLista;

    // Conta o numero de Postos
    while (aux != NULL) {
        numNodes++;
        aux = aux->proximo;
    }

    // Arrays para guardar caminho e distancia
    float distancia[MAXIMO_DE_NODES_CAMINHO];
    int caminho[MAXIMO_DE_NODES_CAMINHO];

    for (int i = 0; i < numNodes; i++) {
        distancia[i] = DISTANCIA_MAXIMA;
        caminho[i] = -1;
    }

    distancia[origemId] = 0;

    // Algoritmo Dijkstra 
    for (int count = 0; count < numNodes - 1; count++) {
        float minDistance = DISTANCIA_MAXIMA;
        LocalizacaoPostos* minNode = NULL;

        //Encontra o node com menos distancia ainda nao visitado
        aux = headLista;
        while (aux != NULL) {
            if (!aux->posto->visitado && distancia[aux->posto->id] <= minDistance) {
                minDistance = distancia[aux->posto->id];
                minNode = aux;
            }
            aux = aux->proximo;
        }

        if (minNode == NULL) {
            // Se nulo sai do Loop
            break;
        }

        minNode->posto->visitado = true;

        // Atualiza e guarda a distancia e caminho
        LocalizacaoPostosAdjacentes* adjacentNode = minNode->posto->postosAdjacentes;
        while (adjacentNode != NULL) {
            int idDestino = adjacentNode->idDestino;
            float newDistance = distancia[minNode->posto->id] + adjacentNode->distancia;

            if (newDistance < distancia[idDestino]) {
                distancia[idDestino] = newDistance;
                caminho[idDestino] = minNode->posto->id;
            }

            if (idDestino == destinoId)
            {
                break;
            }

            adjacentNode = adjacentNode->proximo;
        }
    }


    //Reseta e Atualiza os visitados a todos os Postos
    aux = headLista;

    while (aux != NULL)
    {
        aux->posto->visitado = false;

        aux = aux->proximo;
    }

    headLista = AtualizarPostosAdjacentes(headLista);


    //Se Passar Pela Distancia Maxima
    if (distancia[destinoId] >= DISTANCIA_MAXIMA)
    {
        printf("\n Distancia Erro de Distancia Maxima Alcancada ou Nao tem Caminho \n");
        return distancia[destinoId];
    }

    //Se quiser Imprimir Ou Nao
    if (querImprimirResultados == true)
    {
        int auxId = destinoId;

        while (caminho[auxId] != -1) {
            printf(" || Volta: %d -> ", caminho[auxId]);
            auxId = caminho[auxId];
        }
    }




    return distancia[destinoId];
}


/**
*	@brief Caminho Mais Pequeno Para o Caminho Camiao
*
*	@param [in] headLista				     head lista de Postos
*	@param [in] origemId				     id posto de Origem
*	@param [in] caminhoCamiaoLista			 caminho do Camiao
*	@param [in] distancia		             distancia
*	@param [in] idParaEliminar		         id posto para eliminar
*	@param [in] pesoAtual		             peso atual
*	@param [in] capacidadeMaxima		     capacidade Maxima
*
*	@return idPosto;
*
*/
int CaminhoMaisPerto(LocalizacaoPostos* headLista, int origemId, CaminhoCamiao* caminhoCamiaoLista, float* distancia ,int* idParaEliminar , float* pesoAtual , float capacidadeMaxima)
{
    float minDistance = 0;
    int shortestPathIdPosto = -1;
    int idMeio;
    int idPosto = -1;

    //Caminho
    CaminhoCamiao* currentCaminhoCamiao = caminhoCamiaoLista;
    while (currentCaminhoCamiao != NULL) {
        int destinationId = currentCaminhoCamiao->idPosto;

        // Ve a distancia usando o Algoritmo Dijkstra mais pequena
        float distance = AlgoritmoDijkstra(headLista, origemId, destinationId ,false);

        float pesoAux = *pesoAtual;

        pesoAux = pesoAux + currentCaminhoCamiao->pesoMeio;

        // Ver se é valido
        if (distance >= 0 && (minDistance == 0 || distance < minDistance) && pesoAux <= capacidadeMaxima) {
            minDistance = distance;
            *idParaEliminar = currentCaminhoCamiao->idMeio;
            *pesoAtual = *pesoAtual + currentCaminhoCamiao->pesoMeio;

            idPosto = currentCaminhoCamiao->idPosto;

        }

        currentCaminhoCamiao = currentCaminhoCamiao->proximo;
    }

    //Adiciona Distancia
    *distancia = *distancia + minDistance;
    return idPosto;
}


/**
*	@brief Calcula distancia de dois geocodigos
*
*	@param [in] latitude1				     latitude do primeiro
*	@param [in] longitude1				     longitude do primeiro
*	@param [in] latitude2			         latitude do segundo
*	@param [in] longitude2		             longitude do segundo
*
*	@return float;
*
*/
float CalculaDistancia(float latitude1 , float longitude1 , float latitude2 , float longitude2) {

    float dLat = (latitude2 - latitude1) * 3.141593 / 180.0f;
    float dLon = (longitude2 - longitude1) * 3.141593 / 180.0f;

    float a = sinf(dLat / 2) * sinf(dLat / 2) + cosf(latitude1 * 3.141593 / 180.0f) * cosf(latitude2 * 3.141593 / 180.0f) * sinf(dLon / 2) * sinf(dLon / 2);

    return 2 * TERRA_RAIO * asinf(sqrtf(a));
}


/**
*	@brief Localizacao Raio no Cliente para Postos
*
*	@param [in] cliente				     cliente
*	@param [in] headListPostos		     lista Postos
*	@param [in] raio			         raio
*
*	@return True/False;
*
*/
bool LocalizacaoRaioClientePosto(Clientes* cliente, LocalizacaoPostos* headListaPostos, float raio) {

    if (cliente == NULL || headListaPostos == NULL)
    {
        return false;
    }

    LocalizacaoPostos* auxPostos = headListaPostos;
    int numLocalizacoes = 0;

    while (auxPostos != NULL)
    {
        numLocalizacoes++;
        auxPostos = auxPostos->proximo;
    }

    auxPostos = headListaPostos;

    printf("Localizacao de raio %.2f km com centro de (%.4f, %.4f) de Postos de Recolha:\n", raio, cliente->latitude, cliente->longitude);
    printf("\n");

    for (int i = 0; i < numLocalizacoes; i++) {
        float distancia = CalculaDistancia(cliente->latitude, cliente->longitude , auxPostos->posto->latitude , auxPostos->posto->longitude);

        if (distancia <= raio) {
            printf("Posto %d - (%.4f, %.4f) - Distancia: %.2f km\n", auxPostos->posto->id, auxPostos->posto->latitude, auxPostos->posto->longitude, distancia);
        }

        auxPostos = auxPostos->proximo;
    }

    return true;

}


/**
*	@brief Localizacao Raio no Cliente para Meios de um Tipo
*
*	@param [in] cliente				     cliente
*	@param [in] headListaMeio		     lista Postos
*	@param [in] raio			         raio
*	@param [in] tipo			         tipo do meio
*
*	@return True/False;
*
*/
bool LocalizacaoRaioClienteMeio(Clientes* cliente, MeiosDeMobilidade* headListaMeio, float raio , char* tipo) {

    if (cliente == NULL || headListaMeio == NULL)
    {
        return false;
    }

    MeiosDeMobilidade* auxMeio = headListaMeio;
    int numLocalizacoes = 0;

    while (auxMeio != NULL)
    {
        numLocalizacoes++;
        auxMeio = auxMeio->next;
    }

    auxMeio = headListaMeio;

    printf("Localizacao de raio %.2f km com centro de (%.4f, %.4f) de Meios Nao Alugados do tipo %s:\n", raio/10, cliente->latitude, cliente->longitude , tipo);
    printf("\n");
    for (int i = 0; i < numLocalizacoes; i++) {
        float distancia = CalculaDistancia(cliente->latitude, cliente->longitude, auxMeio->latitude, auxMeio->longitude);

        if (distancia <= raio && auxMeio->estado == true && !TemAluguerAtivo(auxMeio->aluguer) && strcmp(auxMeio->tipo, tipo) == 0) {
            printf("Meio %d - Tipo %s - (%.4f, %.4f) - Distancia: %.2f km\n", auxMeio->id, auxMeio->tipo, auxMeio->latitude, auxMeio->longitude, distancia);
        }

        auxMeio = auxMeio->next;
    }

    return true;

}

/**
*	@brief Localizacao Raio no Cliente para Meios de um Tipo
*
*	@param [in] cliente				     cliente
*	@param [in] meio		             meio
*	@param [in] headListPostos			 head lista Postos
*
*	@return headListPostos de LocalizacaoPostos;
*
*/
LocalizacaoPostos* DistanciaClienteAMeioTotal(Clientes* cliente , MeiosDeMobilidade* meio , LocalizacaoPostos* headListaPostos) {

    if (headListaPostos == NULL)
    {
        return NULL;
    }

    if (cliente == NULL || meio == NULL)
    {
        return headListaPostos;
    }

    LocalizacaoPostos* postoAux = headListaPostos;

    float caminhoMaisPertoClientePosto = DISTANCIA_MAXIMA;

    int idOrigemPosto = -1;
    int idDestinoPosto = -1;

    //Ve Qual Posto mais perto de o Cliente
    while (postoAux != NULL)
    {
        float distanciaAux = CalculaDistancia(cliente->latitude, cliente->longitude, postoAux->posto->latitude, postoAux->posto->longitude);

        if (distanciaAux < caminhoMaisPertoClientePosto)
        {
            caminhoMaisPertoClientePosto = distanciaAux;
            idOrigemPosto = postoAux->posto->id;
        }

        postoAux = postoAux->proximo;

    }

    postoAux = headListaPostos;

    float caminhoMaisPertoMeioPosto = DISTANCIA_MAXIMA;

    //Ve Qual Posto mais perto de o Meio
    while (postoAux != NULL)
    {
        float distanciaAux = CalculaDistancia(meio->latitude, meio->longitude, postoAux->posto->latitude, postoAux->posto->longitude);

        if (distanciaAux < caminhoMaisPertoMeioPosto)
        {
            caminhoMaisPertoMeioPosto = distanciaAux;
            idDestinoPosto = postoAux->posto->id;

        }

        postoAux = postoAux->proximo;

    }

    //Se encontrar
    if (idOrigemPosto != -1 && idDestinoPosto != -1)
    {
        printf("\n\Caminho de Ponto %d a Ponto %d:\n\n" , idOrigemPosto, idDestinoPosto);

        printf("%d -> ", idOrigemPosto);
        float distanciaCaminho = AlgoritmoDijkstra(headListaPostos, idOrigemPosto, idDestinoPosto,true);  //Calcula Distancia
        printf("%d ", idDestinoPosto);

        float distanciaCaminhoTotal = distanciaCaminho + caminhoMaisPertoMeioPosto + caminhoMaisPertoClientePosto;

        printf("\n\nDistancia Total: %.2f km  (Caminho Normal: %.2f km)  (Caminho Extra: %.2f km)\n", distanciaCaminhoTotal, distanciaCaminho , caminhoMaisPertoMeioPosto + caminhoMaisPertoClientePosto);

    }



    return headListaPostos;


}


/**
*	@brief Lista todos os Postos
*
*
*	@param [in] header					header de LocalizacaoPostos
*
*/
int ListarTodosPostos(LocalizacaoPostos* header) {

    system("cls");

    printf("\n\n\n ----------- Listagem ----------\n");

    LocalizacaoPostos* aux = header;

    while (aux != NULL)
    {

        printf(" ID Posto: %d , Cidade: %s, Latitude: %f , Longitude: %f \n", aux->posto->id  , aux->posto->cidade , aux->posto->latitude , aux->posto->longitude);

        aux = aux->proximo;
    }


    return 0;
}



/**
*	@brief Remove Postos mas na consola
* 
*	@param [in] headPostos					header de LocalizacaoPostos
*	@return headPostos;
*
*/
LocalizacaoPostos* RemoverPostoEscrever(LocalizacaoPostos* headPostos) {


    int id;

    printf("\n\nDigite o id do posto que quer eliminar: ");
    scanf("%d", &id);

    headPostos = RemoverPosto(headPostos, id);

    return headPostos;

}



/**
*	@brief Altera Postos mas na consola
*	@param [in] headPostos					header de LocalizacaoPostos
*	@return 0;
*
*/
int AlterarPorEscreverPosto(LocalizacaoPostos* headPosto) {


    int id;
    float latitude;
    float longitude;

    printf("\n\nDigite o id do posto que quer alterar: ");
    scanf("%d", &id);
    printf("\nDigite a nova Latitude: ");
    scanf("%f", &latitude);
    printf("\nDigite a nova Longitude: ");
    scanf("%f", &longitude);

    AlteraPosto(headPosto, id, latitude , longitude);

    return 0;

}



/**
*	@brief Criar Postos mas a escrever
*	@param [in] headPostos					header de LocalizacaoPostos
*	@return 0;
*
*/
int CriarPostoEscrever(LocalizacaoPostos* headPosto) {


    int id;
    float latitude;
    float longitude;
    char cidade[100];

    printf("\n\nDigite o id do novo Posto: ");
    scanf("%d", &id);
    printf("\n\nDigite a cidade do novo Posto: ");
    scanf("%s", &cidade);
    printf("\nDigite a Latitude do novo Posto: ");
    scanf("%f", &latitude);
    printf("\nDigite a Longitude do novo Posto: ");
    scanf("%f", &longitude);

    LocalizacaoPostos* novoPosto = CriarPosto(id,cidade,latitude,longitude,false,NULL);
    headPosto = InserePostoGrafo(headPosto, novoPosto);

    return 0;

}


/**
*	@brief Criar Adjacencia de Postos
*	@param [in] headPostos					header de LocalizacaoPostos
*	@return 0;
*
*/
int CriarAdjacenciaPostoEscrever(LocalizacaoPostos* headPosto) {


    int idOrigem;
    int idDestino;


    printf("\n\nDigite o id do Posto Origem: ");
    scanf("%d", &idOrigem);
    printf("\n\nDigite o id do Posto Destino: ");
    scanf("%d", &idDestino);

    headPosto = InserirPostoAdjacente(&headPosto, ProcurarPorIdPostos(headPosto, idOrigem), ProcurarPorIdPostos(headPosto, idDestino));


    return 0;

}


/**
*	@brief Remover Adjacencia de Postos
*	@param [in] headPostos					header de LocalizacaoPostos
*	@return 0;
*
*/
int RemoverAdjacenciaPostoEscrever(LocalizacaoPostos* headPosto) {


    int idOrigem;
    int idDestino;


    printf("\n\nDigite o id do Posto Origem onde quer remover: ");
    scanf("%d", &idOrigem);
    printf("\n\nDigite o id do Posto Destino que quer remover: ");
    scanf("%d", &idDestino);

    if (ProcurarPorIdPostos(headPosto, idOrigem) == NULL)
    {
        return 1;
    }

    RemoverPostoAdjacente(headPosto , ProcurarPorIdPostos(headPosto, idOrigem)->posto->postosAdjacentes, idDestino);



    return 0;

}


/**
*	@brief Camiao Recolha
*	@param [in] headPostos					header de LocalizacaoPostos
*	@param [in] headListaMeios				header de MeiosDeMobilidade
*	@return 0;
*
*/
int CamiaoRecolhaEscrever(LocalizacaoPostos* headPosto , MeiosDeMobilidade* headListaMeios) {


    int idOrigem;
    float pesoMaximo;
    Camiao* camiao = NULL;		//Inicio da lista

    printf("\n\nDigite o id do Posto Origem onde quer comecar: ");
    scanf("%d", &idOrigem);
    printf("\n\nDigite a Capacidade Maxima do Camiao (kg): ");
    scanf("%f", &pesoMaximo);

    camiao = CriarCamiao(idOrigem, pesoMaximo, ProcurarPorIdPostos(headPosto, idOrigem));
    CamiaoRecolha(camiao, headPosto, headListaMeios);

    return 0;

}