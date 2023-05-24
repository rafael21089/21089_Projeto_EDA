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

#include "Localizacao.h"
#include "MeioDeMobilidade.h"


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


LocalizacaoPostosAdjacentes* CriarPostoAdjacente(LocalizacaoPostos* postoDestinoAdjacente, float distancia) {

    LocalizacaoPostosAdjacentes* postoAdjacente = (LocalizacaoPostosAdjacentes*)malloc(sizeof(LocalizacaoPostosAdjacentes));
    if (postoAdjacente == NULL) {
        return NULL;
    }

    postoAdjacente->postoDestinoAdjacente = postoDestinoAdjacente;
    postoAdjacente->idDestino = postoDestinoAdjacente->id;
    postoAdjacente->distancia = distancia;
    postoAdjacente->proximo = NULL;

    return postoAdjacente;
}

LocalizacaoPostosAdjacentes* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem, LocalizacaoPostos* postoDestino, float distancia) {
    if (headLista == NULL || postoOrigem == NULL || postoDestino == NULL) {
        return *headLista;
    }

    if (JaTemPostoAdjacente(postoOrigem, postoDestino)) {
        return *headLista; // Already exists, no need to insert
    }

    LocalizacaoPostosAdjacentes* novoAdjacente = CriarPostoAdjacente(postoDestino, distancia);
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

    return NULL; // Adjacent node not found
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
        token = strtok(NULL, ";");
        distancia = atof(token);

        *headerPostosLista = InserirPostoAdjacente(headerPostosLista, ProcurarPorIdPostos(*headerPostosLista, idOrigem), ProcurarPorIdPostos(*headerPostosLista, idDestino), distancia);

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
        int distancia = adj.distancia;

        *header = InserirPostoAdjacente(header, ProcurarPorIdPostos(*header, idOrigem), ProcurarPorIdPostos(*header, idDestino), distancia);
     
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




// Function to find the minimum distance node in the distance array
int findMinDistanceNode(bool visited[], float distances[], int numNodes)
{
    float minDistance = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void camiaoRecolha(Camiao* camiao , LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios) {

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;
    Camiao* auxCamiao = camiao;

    int pontosComMeios[100];
    int i = 0;

    for (int i = 0; i < 100; i++) {
        pontosComMeios[i] = -1;
    }

    while (auxPontos != NULL)
    {
        while (auxMeios != NULL) {
            if (auxPontos->latitude == auxMeios->latitude && auxPontos->longitude == auxMeios->longitude&& auxMeios->cargaBateria >= 10) {
                printf("Encontrou nos Pontos: %d o Meio %d \n", auxPontos->id , auxMeios->id);
                pontosComMeios[i] = auxPontos->id;
                i++;
            }

            auxMeios = auxMeios->next;
        }

        auxMeios = headListMeios;
        auxPontos = auxPontos->proximo;

    }

    i = 0;

    while (pontosComMeios[i] != -1)
    {
        float carga = 0;

        if (verSeAcessivel(ProcurarPorIdPostos(headListPontos , camiao->localizacaoAtual->id) , ProcurarPorIdPostos(headListPontos, pontosComMeios[i])) == true)
        {
            if (camiao->localizacaoAtual->id == camiao->idOrigem)
            {
                carga = dijkstra(headListPontos, camiao->idOrigem, pontosComMeios[i]);
                i++;

            }
            else
            {
                carga = carga + dijkstra(headListPontos, camiao->localizacaoAtual->id, pontosComMeios[i]);
                i++;
            }

            if (carga + camiao->cargaAtual <= camiao->cargaMaxima)
            {
                camiao->cargaAtual = camiao->cargaAtual + carga;
                camiao->localizacaoAtual = ProcurarPorIdPostos(headListPontos, pontosComMeios[i]);

            }
            else
            {
                carga = carga + dijkstra(headListPontos, camiao->localizacaoAtual->id, camiao->idOrigem);
            }
        }
        else
        {
            i++;
        }

        



    }







}


// Function to perform Dijkstra's algorithm
bool verSeAcessivel(LocalizacaoPostos* origemPonto, LocalizacaoPostos* destinoPonto) {
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
                bool res = verSeAcessivel(adjacentNode->postoDestinoAdjacente, destinoPonto);

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



// Function to perform Dijkstra's algorithm
float dijkstra(LocalizacaoPostos* headList, int origemId, int destinationId)
{
    if (origemId == destinationId) {
        printf("\nJá se encontra no Destino\n");
        return 0;
    }
    else {
        int numNodes = 0;
        LocalizacaoPostos* current = headList;

        // Count the number of nodes in the graph
        while (current != NULL) {
            numNodes++;
            current = current->proximo;
        }

        // Create arrays to store distances and visited flags
        float* distances = (float*)malloc(numNodes * sizeof(float));
        int* previous = (int*)malloc(numNodes * sizeof(int));

        // Initialize distances and visited flags
        for (int i = 0; i < numNodes; i++) {
            distances[i] = 200;
            previous[i] = -1;
        }

        // Set the distance of the source node to 0
        distances[origemId] = 0;

        // Dijkstra's algorithm
        for (int i = 0; i < numNodes - 1; i++) {
            // Find the node with the minimum distance
            float minDistance = 200;
            int minIndex = -1;

            for (int j = 0; j < numNodes; j++) {
                if (!headList[j].visitado && distances[j] < minDistance) {
                    minDistance = distances[j];
                    minIndex = j;
                }
            }

            // Mark the selected node as visited
            headList[minIndex].visitado = true;

            // Update distances to adjacent nodes
            LocalizacaoPostos* currentNode = headList;
            while (currentNode != NULL) {
                if (currentNode->id == minIndex) {
                    LocalizacaoPostosAdjacentes* adjacentNode = currentNode->postosAdjacentes;
                    while (adjacentNode != NULL) {
                        float newDistance = distances[minIndex] + adjacentNode->distancia;
                        if (newDistance < distances[adjacentNode->idDestino]) {
                            distances[adjacentNode->idDestino] = newDistance;
                            previous[adjacentNode->idDestino] = minIndex;
                        }
                        adjacentNode = adjacentNode->proximo;
                    }
                    break;
                }
                currentNode = currentNode->proximo;
            }
        }

        if (distances[destinationId] == 200) {
            printf("\nDestino fora de alcance\n");
            return 0;
        }
        else {
            // Print the shortest distance and path
            printf("Shortest distance from Node %d to Node %d: %.2f\n", origemId, destinationId, distances[destinationId]);
            printf("Path: ");

            int currentId = destinationId;
            while (currentId != -1) {
                printf("%d ", currentId);
                currentId = previous[currentId];
            }

            return distances[destinationId];
        }
    }
   
}