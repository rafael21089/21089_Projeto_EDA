/**
*  @file Aluguer.c
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


LocalizacaoPostos* CriarPosto(int id, char* cidade, float latitude, float longitude, bool visitado, LocalizacaoPostosAdjacentes* postosAdjacentes) {
    LocalizacaoPostos* novoPosto = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));
    if (novoPosto == NULL) {
        return NULL;
    }
 
    novoPosto->id = id;
    strncpy(novoPosto->cidade, cidade, LARGURAGERALSTRING);

    novoPosto->latitude = latitude;
    novoPosto->longitude = longitude;
    novoPosto->visitado = visitado;

    novoPosto->postosAdjacentes = postosAdjacentes;
    novoPosto->proximo = NULL;

    return novoPosto;
}

LocalizacaoPostos* InserePostoGrafo(LocalizacaoPostos* header, LocalizacaoPostos* novoPosto) {

    if (ExistePosto(header, novoPosto->id)) {
        return header; // If the posto already exists, return the original header
    }

    if (header == NULL) {
        header = novoPosto; // If the list is empty, set novoPosto as the new header
        return header;
    }
    else {
        LocalizacaoPostos* aux = header;
        LocalizacaoPostos* ant = NULL; // Initialize ant to NULL
        while (aux && aux->id < novoPosto->id) {
            ant = aux;
            aux = aux->proximo;
        }
        if (ant == NULL) {
            novoPosto->proximo = header;
            header = novoPosto;
        }
        else {
            novoPosto->proximo = aux;
            ant->proximo = novoPosto;
        }
    }
    return header;
}


bool ExistePosto(LocalizacaoPostos* header, int idPosto) {
    if (header == NULL) return false;
    LocalizacaoPostos* aux = header;
    while (aux != NULL) {
        if (aux->id == idPosto)
            return true;
        aux = aux->proximo;
    }
    return false;
}
LocalizacaoPostos* RemoverPosto(LocalizacaoPostos* header, int id) {
    if (header == NULL) return NULL;			//Lista vazia

    if (!ExistePosto(header, id)) return;

    if (header->id == id) {		//remove no inicio da lista
        LocalizacaoPostos* aux = header;
        header = header->proximo;
        free(aux);
    }
    else
    {
        LocalizacaoPostos* aux = header;
        LocalizacaoPostos* auxAnt = aux;
        while (aux && aux->id != id) {	//procura para revover
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


LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, LocalizacaoPostos* postoOrigem) {

    LocalizacaoPostosAdjacentes* postoAdjacente = (LocalizacaoPostosAdjacentes*)malloc(sizeof(LocalizacaoPostosAdjacentes));
    if (postoAdjacente == NULL) {
        return NULL;
    }

    postoAdjacente->postoDestinoAdjacente = postoDestinoAdjacente;
    postoAdjacente->idDestino = postoDestinoAdjacente->id;
    postoAdjacente->distancia = calculaDistancia(postoDestinoAdjacente->latitude , postoDestinoAdjacente->longitude , postoOrigem->latitude , postoOrigem->longitude);
    postoAdjacente->proximo = NULL;

    return postoAdjacente;
}

LocalizacaoPostosAdjacentes* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino) {
    if (headLista == NULL || postoOrigem == NULL || postoDestino == NULL) {
        return *headLista;
    }

    if (JaTemPostoAdjacente(postoOrigem, postoDestino)) {
        return *headLista; // Already exists, no need to insert
    }

    LocalizacaoPostosAdjacentes* novoAdjacente = CriarPostoAdjacente(postoDestino, postoOrigem);
    if (novoAdjacente == NULL) {
        return *headLista; // Failed to create the adjacent node
    }

    LocalizacaoPostos* aux = ProcurarPorIdPostosComListaToda(*headLista, postoOrigem->id);

    if (aux->postosAdjacentes == NULL) {
        aux->postosAdjacentes = novoAdjacente;
    }
    else {
        LocalizacaoPostosAdjacentes* aux2 = aux->postosAdjacentes;
        while (aux2->proximo != NULL) {
            aux2 = aux2->proximo;
        }
        aux2->proximo = novoAdjacente;
    }

 
    *headLista = AtualizarPostosAdjacentes(*headLista);

    return *headLista;
}


LocalizacaoPostosAdjacentes* ProcurarPostoAdjacente(LocalizacaoPostos* vertex, LocalizacaoPostos* postoDestino) {
    if (vertex == NULL || postoDestino == NULL || vertex->postosAdjacentes == NULL) {
        return NULL;
    }

    LocalizacaoPostosAdjacentes* adjacente = vertex->postosAdjacentes;
    while (adjacente != NULL) {
        if (adjacente->postoDestinoAdjacente == postoDestino) {
            return adjacente;
        }
        adjacente = adjacente->proximo;
    }

    return NULL;
}


bool ExistePostoAdjacente(LocalizacaoPostosAdjacentes* header, int idPostosAdjacentes) {
    if (header == NULL) return false;
    LocalizacaoPostosAdjacentes* aux = header;
    while (aux != NULL) {
        if (aux->postoDestinoAdjacente->id == idPostosAdjacentes)
            return true;
        aux = aux->proximo;
    }
    return false;
}
LocalizacaoPostosAdjacentes* RemoverPostoAdjacente(LocalizacaoPostosAdjacentes* headerPostos, LocalizacaoPostosAdjacentes* headerPostoAdjacente, int id) {
    if (headerPostoAdjacente == NULL) return NULL;			//Lista vazia

    if (!ExistePostoAdjacente(headerPostoAdjacente, id)) return;

    if (headerPostoAdjacente->postoDestinoAdjacente->id == id) {		//remove no inicio da lista
        LocalizacaoPostosAdjacentes* aux = headerPostoAdjacente;
        headerPostoAdjacente = headerPostoAdjacente->proximo;
        free(aux);
    }
    else
    {
        LocalizacaoPostosAdjacentes* aux = headerPostoAdjacente;
        LocalizacaoPostosAdjacentes* auxAnt = aux;
        while (aux && aux->postoDestinoAdjacente->id != id) {	//procura para revover
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




LocalizacaoPostos* AtualizarPostosAdjacentes(LocalizacaoPostos* headLista) {
    if (headLista == NULL) {
        return NULL; // Empty list
    }

    LocalizacaoPostos* aux = headLista;

    while (aux != NULL) {
        LocalizacaoPostosAdjacentes* adjacente = aux->postosAdjacentes;

        while (adjacente != NULL) {
            LocalizacaoPostos* destino = ProcurarPorIdPostos(headLista, adjacente->idDestino);
            if (destino != NULL) {
                adjacente->postoDestinoAdjacente = destino;
            }

            adjacente = adjacente->proximo;
        }

        aux = aux->proximo;
    }

    return headLista;
}


LocalizacaoPostos* ProcurarPorIdPostosComListaToda(LocalizacaoPostos* headerList, int id) {
    if (headerList == NULL) return NULL;		//lista vazia
    else
    {
        LocalizacaoPostos* aux = headerList;
        while (aux != NULL) {
            if (aux->id == id) {
                return (aux);		//encontrou
            }
            aux = aux->proximo;
        }
        return NULL;
    }
}


LocalizacaoPostos* ProcurarPorIdPostos(LocalizacaoPostos* headerList, int id) {
    LocalizacaoPostos* aux = headerList;

    // Traverse the graph until the node with the matching ID is found
    while (aux != NULL) {
        if (aux->id == id) {
            LocalizacaoPostos* result = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));
            result = CriarPosto(aux->id, aux->cidade, aux->latitude, aux->longitude , aux->visitado ,aux->postosAdjacentes);
         
            return result;  // Node with the matching ID found
        }

        // Move to the next adjacent node in the graph
        aux = aux->proximo;
    }

    return NULL;  // Node with the specified ID not found
}


bool JaTemPostoAdjacente(LocalizacaoPostos* headerOrigem, LocalizacaoPostos* headerDestino) {
    if (headerOrigem == NULL) return false;
    if (headerDestino == NULL) return false;

    LocalizacaoPostos* aux = headerOrigem;
    LocalizacaoPostos* aux2 = headerDestino;

    LocalizacaoPostosAdjacentes* auxAdj = aux->postosAdjacentes;

    if (auxAdj == NULL)
    {
        return false;
    }
    else
    {
        while (aux != NULL) {
           
                LocalizacaoPostos* aux3 = aux->postosAdjacentes->postoDestinoAdjacente;

                while (aux3 != NULL)
                {
                    if (aux3->id == aux2->id)
                        return true;

                    aux3 = aux3->proximo;
                }

                aux = aux->proximo;
                aux2 = aux2->proximo;
            } 
    }

  
    return false;
}



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
       
        char* token = strtok(line, ";");
        novoPosto->id = atoi(token);
        token = strtok(NULL, ";");
        strncpy(novoPosto->cidade, token, sizeof(novoPosto->cidade));
        token = strtok(NULL, ";");
        novoPosto->latitude = atof(token);
        token = strtok(NULL, ";");
        novoPosto->longitude = atof(token);

        novoPosto->visitado = false;
        novoPosto->postosAdjacentes = NULL;
        novoPosto->proximo = NULL;

        *headerPostosLista = InserePostoGrafo(*headerPostosLista, novoPosto); // Insere Posto

    }

    fclose(file);

    return *headerPostosLista;
}



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




bool GravarPostosBinario(char* nomeFicheiro, LocalizacaoPostos* header) {
    FILE* fp;

    if (header == NULL) return false;
    if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

    LocalizacaoPostos* aux = header;
    while (aux) {
        // Escreve no ficheiro os dados do registo de memória
        fwrite(aux, sizeof(LocalizacaoPostos), 1, fp);
        aux = aux->proximo;
    }
    fclose(fp);
    return true;
}



LocalizacaoPostos* LerPostosBinario(char* nomeFicheiro) {
    FILE* fp;
    LocalizacaoPostos* header = NULL;
    LocalizacaoPostos* auxAnt;

    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

    //Ler o registos do ficheiro binario
    while ((auxAnt = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos))) && fread(auxAnt, sizeof(LocalizacaoPostos), 1, fp)) {
        LocalizacaoPostos* aux = CriarPosto(auxAnt->id, auxAnt->cidade, auxAnt->latitude, auxAnt->longitude, auxAnt->visitado, NULL); //Cria Aluguer com valores recebidos
        header = InserePostoGrafo(header, aux); //Insere Aluguer
    }
    fclose(fp);
    return header;
}




bool GravarPostosAdjacentesBinario(char* nomeFicheiro, LocalizacaoPostos* header) {
    FILE* fp;

    if (header == NULL) return false;
    if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

    // Save the current postosAdjacentes to the binary file

    LocalizacaoPostos* aux = header;

    while (aux != NULL)
    {
        LocalizacaoPostosAdjacentes* adj = aux->postosAdjacentes;
        while (adj != NULL) {
            fwrite(&(aux->id), sizeof(int), 1, fp);
            fwrite(adj, sizeof(LocalizacaoPostosAdjacentes), 1, fp);
            adj = adj->proximo;
        }

        aux = aux->proximo;
    }


    fclose(fp);
    return true;
}


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

        // Read the data from the binary file
        if (fread(&id, sizeof(int), 1, fp) != 1) break;
        if (fread(&adj, sizeof(LocalizacaoPostosAdjacentes), 1, fp) != 1) break;

        // Create a new node for the list
        LocalizacaoPostosAdjacentes* newNode = malloc(sizeof(LocalizacaoPostosAdjacentes));

        int idOrigem = id;
        int idDestino = adj.idDestino;

        *header = InserirPostoAdjacente(header, ProcurarPorIdPostos(*header, idOrigem), ProcurarPorIdPostos(*header, idDestino));
     
    }

    fclose(fp);

    return *header;
}


Camiao* CriarCamiao(int idOrigem , float cargaAtual , float cargaMaxima, LocalizacaoPostos* localizacaoAtual) {

    Camiao* novoCamiao= (Camiao*)malloc(sizeof(Camiao));
    if (novoCamiao == NULL) {
        return NULL;
    }

    novoCamiao->idOrigem = idOrigem;
    novoCamiao->cargaAtual = cargaAtual;
    novoCamiao->cargaMaxima = cargaMaxima;
    novoCamiao->localizacaoAtual = localizacaoAtual;

    return novoCamiao;
}


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


CaminhoCamiao* CreateCaminho(LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios, float* distanciaExtra ) {

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;

    MeiosDeMobilidade* auxMeiosNaoEmPostos = headListMeios;

    CaminhoCamiao* caminho = NULL;

    while (auxPontos != NULL)
    {
        while (auxMeios != NULL) {
            if (auxPontos->latitude == auxMeios->latitude && auxPontos->longitude == auxMeios->longitude && auxMeios->cargaBateria <= 50 && auxMeios->estado == true) {

                CaminhoCamiao* novoCaminho = CriarCaminhoNodes(auxPontos->id, auxMeios->id, auxMeios->peso);

                caminho = InserirCaminho(caminho , novoCaminho);

                printf("Caminho: Posto %d - (%.4f, %.4f) Com Meio de Mobilidade %d com peso %.2f kg \n", novoCaminho->idPosto, auxPontos->latitude, auxPontos->longitude, auxMeios->id , auxMeios->peso);

               
            }

            auxMeios = auxMeios->next;
        }

        auxMeios = headListMeios;
        auxPontos = auxPontos->proximo;
    }

    LocalizacaoPostos* auxPontosProximos = headListPontos;
    float caminhoMaisPerto = DISTANCIA_MAXIMA;
    int idPostoMaisPerto = 0;
    int idMeioMaisPerto = 0;

    float latitudeMaisPerto = 0;
    float longitudeMaisPerto = 0;
    float pesoMaisPerto = 0;


    while (auxPontosProximos != NULL)
    {
        while (auxMeiosNaoEmPostos != NULL)
        {
            float caminhoParaPontoExtra = calculaDistancia(auxMeiosNaoEmPostos->latitude , auxMeiosNaoEmPostos->longitude, auxPontosProximos->latitude , auxPontosProximos->longitude);

            if ((caminhoParaPontoExtra <= DISTANCIA_MAXIMA && caminhoParaPontoExtra != 0) && auxMeiosNaoEmPostos->cargaBateria <= 50 && auxMeiosNaoEmPostos->estado == true && !ExisteCaminhoNode(caminho, auxMeiosNaoEmPostos->id)) {

                if (caminhoParaPontoExtra < caminhoMaisPerto)
                {
                    caminhoMaisPerto = caminhoParaPontoExtra;
                    idPostoMaisPerto = auxPontosProximos->id;
                    idMeioMaisPerto = auxMeiosNaoEmPostos->id;
                    pesoMaisPerto = auxMeiosNaoEmPostos->peso;
                    latitudeMaisPerto = auxPontosProximos->latitude;
                    longitudeMaisPerto = auxPontosProximos->longitude;
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

bool camiaoRecolha(Camiao* camiao , LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios) {

    if (headListPontos == NULL || headListMeios == NULL || camiao == NULL)
    {
        return false;
    }

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;
    Camiao* auxCamiao = camiao;

    CaminhoCamiao* caminho = NULL;

    float distanciaExtra = 0;

    caminho = CreateCaminho(headListPontos , headListMeios, &distanciaExtra);

    

    float distancia = 0;
    float peso = 0;


    while (caminho != NULL)
    {
        // Calculate the length of the linked list
        int length = 0;
        CaminhoCamiao* current = caminho;
        float distanciaAux = distancia;

        // Count the number of nodes in the linked list
        while (current != NULL) {
            length++;
            current = current->proximo;
        }

        current = caminho;

        // Dynamically allocate memory for the ids array

        int numIds = length + 2;
        int* ids = malloc((numIds) * sizeof(int));

        for (int i = 0; i < numIds; i++)
        {
            if (i == 0)
            {
                ids[i] = camiao->localizacaoAtual->id;
            }
            else if (i == numIds - 1)
            {
                ids[i] = camiao->localizacaoAtual->id;

            }
            else
            {
                ids[i] = current->idPosto;
                current = current->proximo;
            }

        }

        for (int i = 0; i < numIds; i++)
        {
            if (i == 0)
            {
                float e = dijkstra(headListPontos, camiao->localizacaoAtual->id, camiao->idOrigem , true);

                distancia = distancia + e;
                printf("%d ", camiao->idOrigem);
                camiao->localizacaoAtual->id = camiao->idOrigem;

            }
            else if (i == numIds - 1)
            {
                float e = dijkstra(headListPontos, camiao->localizacaoAtual->id, camiao->idOrigem , true);
                distancia = distancia + e;
                printf("%d ", camiao->idOrigem);
                camiao->localizacaoAtual->id = camiao->idOrigem;
            }
            else
            {
                int idParaEliminar = 0;
                int e = caminhoMaisPerto(headListPontos, camiao->localizacaoAtual->id, caminho, &distancia, &idParaEliminar, &peso , camiao->cargaMaxima);

                if (e >= 0)
                {
                    printf("%d ", e);
                    caminho = RemoverCaminhoNode(caminho, idParaEliminar);
                    camiao->localizacaoAtual->id = e;
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


// Function to perform Dijkstra's algorithm
bool verSeAcessivel(LocalizacaoPostos* headLista, LocalizacaoPostos* origemPonto, LocalizacaoPostos* destinoPonto) {
    // Base case: If source and destination are the same, they are reachable
    if (origemPonto == destinoPonto) {
        return true;
    }

    // Mark the source as visited to avoid revisiting it
    origemPonto->visitado = true;

    // Traverse through all adjacent nodes of the source
    LocalizacaoPostosAdjacentes* adjacentNode = origemPonto->postosAdjacentes;
    while (adjacentNode != NULL) {
        // If the adjacent node has not been visited, recursively check if it is reachable
        if (!(adjacentNode->postoDestinoAdjacente->visitado)) {

            if (adjacentNode->postoDestinoAdjacente->id == destinoPonto->id)
            {
                return true;
            }
            else
            {
                bool res = verSeAcessivel(headLista, adjacentNode->postoDestinoAdjacente, destinoPonto);

                if (res == true)
                {
                    return true;
                }
            }  
            
        }
        adjacentNode = adjacentNode->proximo;
    }

    // Reset the visitado flag of the source as we backtrack
    origemPonto->visitado = false;

    // If no path is found, return false
    return false;
}


float dijkstra(LocalizacaoPostos* headList, int origemId, int destinationId , bool querImprimirResultados)
{
    if (ProcurarPorIdPostos(headList, origemId) == NULL)
    {
        printf("\n Dados Insuficientes para a realizacao da funcao Dijkstra \n");
        return 0;
    }
    if (ProcurarPorIdPostos(headList, destinationId) == NULL)
    {
        printf("\n Dados Insuficientes para a realizacao da funcao Dijkstra \n");
        return 0;
    }

    int numNodes = 0;
    LocalizacaoPostos* current = headList;

    // Count the number of nodes in the graph
    while (current != NULL) {
        numNodes++;
        current = current->proximo;
    }

    // Create arrays for storing distance and parent information
    float distance[MAXIMO_DE_NODES_CAMINHO];
    int parent[MAXIMO_DE_NODES_CAMINHO];

    // Initialize distance and parent arrays
    for (int i = 0; i < numNodes; i++) {
        distance[i] = DISTANCIA_MAXIMA;
        parent[i] = -1;
    }

    // Set the distance of the origin node to 0
    distance[origemId] = 0;

    // Dijkstra's algorithm
    for (int count = 0; count < numNodes - 1; count++) {
        float minDistance = DISTANCIA_MAXIMA;
        LocalizacaoPostos* minNode = NULL;

        //Encontra o node com menos distancia ainda nao visitado
        current = headList;
        while (current != NULL) {
            if (!current->visitado && distance[current->id] <= minDistance) {
                minDistance = distance[current->id];
                minNode = current;
            }
            current = current->proximo;
        }

        if (minNode == NULL) {
            // Se nulo sai do Loop
            break;
        }

        // Mark the selected node as visited
        minNode->visitado = true;

        // Update the distances of the adjacent nodes
        LocalizacaoPostosAdjacentes* adjacentNode = minNode->postosAdjacentes;
        while (adjacentNode != NULL) {
            int idDestino = adjacentNode->idDestino;
            float newDistance = distance[minNode->id] + adjacentNode->distancia;

            if (newDistance < distance[idDestino]) {
                distance[idDestino] = newDistance;
                parent[idDestino] = minNode->id;
            }

            if (idDestino == destinationId)
            {
                break;
            }

            adjacentNode = adjacentNode->proximo;
        }
    }


    current = headList;

    while (current != NULL)
    {
        current->visitado = false;

        current = current->proximo;
    }

    headList = AtualizarPostosAdjacentes(headList);



    if (distance[destinationId] == DISTANCIA_MAXIMA)
    {
        printf("\n Distancia Erro de Distancia Maxima Alcancada ou Nao tem Caminho \n");
        return distance[destinationId];
    }


    if (querImprimirResultados == true)
    {
        int currentNode = destinationId;

        while (parent[currentNode] != -1) {
            printf("%d ", parent[currentNode]);
            currentNode = parent[currentNode];
        }
    }




    return distance[destinationId];
}


int caminhoMaisPerto(LocalizacaoPostos* headList, int origemId, CaminhoCamiao* caminhoCamiaoList, float* distancia ,int* idParaEliminar , float* pesoAtual , float capacidadeMaxima)
{
    float minDistance = 0;
    int shortestPathIdPosto = -1;
    int idMeio;
    int idPosto = -1;

    // Traverse the CaminhoCamiao list
    CaminhoCamiao* currentCaminhoCamiao = caminhoCamiaoList;
    while (currentCaminhoCamiao != NULL) {
        int destinationId = currentCaminhoCamiao->idPosto;

        // Perform Dijkstra's algorithm to find the shortest distance
        float distance = dijkstra(headList, origemId, destinationId ,false);

        float pesoAux = *pesoAtual;

        pesoAux = pesoAux + currentCaminhoCamiao->pesoMeio;

        // Check if the distance is valid and update the minimum distance
        if (distance >= 0 && (minDistance == 0 || distance < minDistance) && pesoAux <= capacidadeMaxima) {
            minDistance = distance;
            *idParaEliminar = currentCaminhoCamiao->idMeio;
            *pesoAtual = *pesoAtual + currentCaminhoCamiao->pesoMeio;

            idPosto = currentCaminhoCamiao->idPosto;

        }

        currentCaminhoCamiao = currentCaminhoCamiao->proximo;
    }


    *distancia = *distancia + minDistance;
    return idPosto;
}



float calculaDistancia(float latitude1 , float longitude1 , float latitude2 , float longitude2) {

    float dLat = (latitude2 - latitude1) * 3.141593 / 180.0f;
    float dLon = (longitude2 - longitude1) * 3.141593 / 180.0f;

    float a = sinf(dLat / 2) * sinf(dLat / 2) + cosf(latitude1 * 3.141593 / 180.0f) * cosf(latitude2 * 3.141593 / 180.0f) * sinf(dLon / 2) * sinf(dLon / 2);

    return 2 * TERRA_RAIO * asinf(sqrtf(a));
}


bool localizacaoRaioClientePosto(Clientes* cliente, LocalizacaoPostos* headListPostos, float raio) {

    if (cliente == NULL || headListPostos == NULL)
    {
        return false;
    }

    LocalizacaoPostos* auxPostos = headListPostos;
    int numLocations = 0;

    while (auxPostos != NULL)
    {
        numLocations++;
        auxPostos = auxPostos->proximo;
    }

    auxPostos = headListPostos;

    printf("Localizacao de raio %.2f km com centro de (%.4f, %.4f) de Postos de Recolha:\n", raio, cliente->latitude, cliente->longitude);
    printf("\n");

    for (int i = 0; i < numLocations; i++) {
        float distance = calculaDistancia(cliente->latitude, cliente->longitude , auxPostos->latitude , auxPostos->longitude);

        if (distance <= raio) {
            printf("Posto %d - (%.4f, %.4f) - Distancia: %.2f km\n", auxPostos->id, auxPostos->latitude, auxPostos->longitude, distance);
        }

        auxPostos = auxPostos->proximo;
    }

    return true;

}


bool localizacaoRaioClienteMeio(Clientes* cliente, MeiosDeMobilidade* headListMeio, float raio , char* tipo) {

    if (cliente == NULL || headListMeio == NULL)
    {
        return false;
    }

    MeiosDeMobilidade* auxMeio = headListMeio;
    int numLocations = 0;

    while (auxMeio != NULL)
    {
        numLocations++;
        auxMeio = auxMeio->next;
    }

    auxMeio = headListMeio;

    printf("Localizacao de raio %.2f km com centro de (%.4f, %.4f) de Meios Nao Alugados do tipo %s:\n", raio/10, cliente->latitude, cliente->longitude , tipo);
    printf("\n");
    for (int i = 0; i < numLocations; i++) {
        float distance = calculaDistancia(cliente->latitude, cliente->longitude, auxMeio->latitude, auxMeio->longitude);

        if (distance <= raio && auxMeio->estado == true && !TemAluguerAtivo(auxMeio->aluguer) && strcmp(auxMeio->tipo, tipo) == 0) {
            printf("Meio %d - Tipo %s - (%.4f, %.4f) - Distancia: %.2f km\n", auxMeio->id, auxMeio->tipo, auxMeio->latitude, auxMeio->longitude, distance);
        }

        auxMeio = auxMeio->next;
    }

    return true;

}


LocalizacaoPostos* DistanciaClienteAMeioTotal(Clientes* cliente , MeiosDeMobilidade* meio , LocalizacaoPostos* headListPostos) {

    if (headListPostos == NULL)
    {
        return NULL;
    }

    if (cliente == NULL || meio == NULL)
    {
        return headListPostos;
    }

    LocalizacaoPostos* postoAux = headListPostos;

    float caminhoMaisPertoClientePosto = DISTANCIA_MAXIMA;

    int idOrigemPosto = -1;
    int idDestinoPosto = -1;


    while (postoAux != NULL)
    {
        float distanciaAux = calculaDistancia(cliente->latitude, cliente->longitude, postoAux->latitude, postoAux->longitude);

        if (distanciaAux < caminhoMaisPertoClientePosto)
        {
            caminhoMaisPertoClientePosto = distanciaAux;
            idOrigemPosto = postoAux->id;
        }

        postoAux = postoAux->proximo;

    }

    postoAux = headListPostos;

    float caminhoMaisPertoMeioPosto = DISTANCIA_MAXIMA;

    while (postoAux != NULL)
    {
        float distanciaAux = calculaDistancia(meio->latitude, meio->longitude, postoAux->latitude, postoAux->longitude);

        if (distanciaAux < caminhoMaisPertoMeioPosto)
        {
            caminhoMaisPertoMeioPosto = distanciaAux;
            idDestinoPosto = postoAux->id;

        }

        postoAux = postoAux->proximo;

    }

    if (idOrigemPosto != -1 && idDestinoPosto != -1)
    {
        printf("\n\Caminho de Ponto %d a Ponto %d:\n\n" , idOrigemPosto, idDestinoPosto);

        printf("%d ", idOrigemPosto);
        float distanciaCaminho = dijkstra(headListPostos, idOrigemPosto, idDestinoPosto,true);
        printf("%d ", idDestinoPosto);

        float distanciaCaminhoTotal = distanciaCaminho + caminhoMaisPertoMeioPosto + caminhoMaisPertoClientePosto;

        printf("\n\nDistancia Total: %.2f km  (Caminho Normal: %.2f km)  (Caminho Extra: %.2f km)\n", distanciaCaminhoTotal, distanciaCaminho , caminhoMaisPertoMeioPosto + caminhoMaisPertoClientePosto);

    }



    return headListPostos;


}



