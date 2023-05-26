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
        // Escreve no ficheiro os dados do registo de mem�ria
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




CaminhoCamiao* CreateCaminho(LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios) {

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;

    CaminhoCamiao* caminho = NULL;

    while (auxPontos != NULL)
    {
        while (auxMeios != NULL) {
            if (auxPontos->latitude == auxMeios->latitude && auxPontos->longitude == auxMeios->longitude && auxMeios->cargaBateria >= 10) {

                CaminhoCamiao* novoCaminho = (CaminhoCamiao*)malloc(sizeof(CaminhoCamiao));

                novoCaminho->idPosto = auxPontos->id;
                novoCaminho->idMeio = auxMeios->id;
                novoCaminho->pesoMeio = auxMeios->peso;
                novoCaminho->proximo = NULL;

                if (caminho == NULL) {
                    caminho = novoCaminho;
                }
                else
                {
                    CaminhoCamiao* aux = caminho;
                    while (aux->proximo != NULL) {
                        aux = aux->proximo;
                    }

                    aux->proximo = novoCaminho;
                }
            }
            auxMeios = auxMeios->next;
        }

        auxMeios = headListMeios;
        auxPontos = auxPontos->proximo;
    }

    return caminho;

}

void camiaoRecolha(Camiao* camiao , LocalizacaoPostos* headListPontos , MeiosDeMobilidade* headListMeios) {

    LocalizacaoPostos* auxPontos = headListPontos;
    MeiosDeMobilidade* auxMeios = headListMeios;
    Camiao* auxCamiao = camiao;

    CaminhoCamiao* caminho = NULL;

    caminho = CreateCaminho(headListPontos , headListMeios);


 /*   CaminhoCamiao* caminhoAux = caminho;
   

    float min = 501;
    int id;

    while (caminhoAux != NULL)
    {
        float dist = dijkstra(headListPontos, camiao->localizacaoAtual->id, caminhoAux->idPosto);

        if (dist < min)
        {
            min = dist;
            id = caminhoAux->idPosto;
        }

        caminhoAux = caminhoAux->proximo;
    }*/

   


    // Calculate the length of the linked list
    int length = 0;

    CaminhoCamiao* current = caminho;
    while (current != NULL) {
        length++;
        current = current->proximo;
    }

    current = caminho;
    

    // Calculate the distance of the current combination

    int* arr = malloc(length * sizeof(int));

    for (int i = 0; i < length; i++)
    {
        arr[i] = current->idPosto;
        current = current->proximo;
    }

    float distancia = 501;
    float shortestDistance = distancia;  // Initialize shortestDistance with the maximum possible value
    generateVariations(arr, 0, length - 1, distancia, headListPontos, camiao->localizacaoAtual->id, caminho, &shortestDistance);
    printf("Shortest distance: %f\n", shortestDistance);

    //float yup = caminhoC(headListPontos, caminho, camiao->localizacaoAtual->id , camiao->localizacaoAtual->id);




    while (caminho != NULL)
    {
        //---

        LocalizacaoPostos* current = headListPontos;

        while (current != NULL)
        {
            current->visitado = false;

            current = current->proximo;
        }

        headListPontos = AtualizarPostosAdjacentes(headListPontos);

        //---

        if (verSeAcessivel( headListPontos, ProcurarPorIdPostos(headListPontos , camiao->localizacaoAtual->id) , ProcurarPorIdPostos(headListPontos, caminho->idPosto)) == true)
        {
           
            if (camiao->cargaAtual == camiao->cargaMaxima)
            {
                //Ir para o origemId
            }
            else
            {
                if (camiao->localizacaoAtual->id == caminho->idPosto)
                {
                    camiao->cargaAtual = camiao->cargaAtual + caminho->pesoMeio;
                    caminho = caminho->proximo;
                }
                else
                {
                    int idPostoCaminhoCamiao = 0;
                    //idPostoCaminhoCamiao = caminhoMaisPerto(headListPontos, camiao->localizacaoAtual->id , caminho);

                    //camiao->cargaAtual = recolha(caminho , camiao , idPostoCaminhoCamiao);

                    camiao->localizacaoAtual->id = idPostoCaminhoCamiao;

                    caminho = caminho->proximo;

                }
            }


           

        }
        else
        {
            printf("Caminho nao encontrado para Meio: %d  no Posto: %d", caminho->idMeio, caminho->idPosto);
            caminho = caminho->proximo;
        }

    }







}


float recolha(CaminhoCamiao* caminhoCamiaoList , Camiao* camiao, int idPosto) {


    CaminhoCamiao* camiaoAux = caminhoCamiaoList;

    float carga = camiao->cargaAtual;
    float cargaAux = 0;

    while (camiaoAux != NULL)
    {
        if (camiaoAux->idPosto == idPosto)
        {
            cargaAux = cargaAux + camiaoAux->pesoMeio;

            if (cargaAux + carga <= camiao->cargaMaxima)
            {
                carga = carga + cargaAux;
                printf("\nRecolheu Meio %d no posto %d",camiaoAux->idMeio ,camiaoAux->idPosto);
                //caminhoCamiaoList = RemoverCaminhoNode(caminhoCamiaoList, camiaoAux->idMeio);
            }
        }

        camiaoAux = camiaoAux->proximo;
    }

    return carga;
}


CaminhoCamiao* RemoverCaminhoNode(CaminhoCamiao* header, int id) {
    if (header == NULL) return NULL;			//Lista vazia

    if (header->idMeio == id) {		//remove no inicio da lista
        Gestor* aux = header;
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


#define MAX_NODES 100

float dijkstra(LocalizacaoPostos* headList, int origemId, int destinationId)
{
    if (ProcurarPorIdPostos(headList, origemId) == NULL)
    {
        return 0;
    }
    if (ProcurarPorIdPostos(headList, destinationId) == NULL)
    {
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
    float distance[MAX_NODES];
    int parent[MAX_NODES];

    // Initialize distance and parent arrays
    for (int i = 0; i < numNodes; i++) {
        distance[i] = 500;
        parent[i] = -1;
    }

    // Set the distance of the origin node to 0
    distance[origemId] = 0;

    // Dijkstra's algorithm
    for (int count = 0; count < numNodes - 1; count++) {
        float minDistance = 500;
        LocalizacaoPostos* minNode = NULL;

        // Find the node with the minimum distance
        current = headList;
        while (current != NULL) {
            if (!current->visitado && distance[current->id] <= minDistance) {
                minDistance = distance[current->id];
                minNode = current;
            }
            current = current->proximo;
        }

        if (minNode == NULL) {
            // All remaining nodes are unreachable
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




    //// Print the shortest distance from origin to destination
    //printf("Shortest distance from Node %d to Node %d: %.2f\n", origemId, destinationId, distance[destinationId]);

    //// Print the shortest path from origin to destination
    //printf("Shortest path: ");
    //printPath(parent, destinationId);
    //printf("\n");

    return distance[destinationId];
}

void printPath(int parent[], int destinationId) {
    if (parent[destinationId] == -1) {
        printf("%d ", destinationId);
        return;
    }

    printPath(parent, parent[destinationId]);
    printf("%d ", destinationId);
}



int caminhoC(LocalizacaoPostos* headList , CaminhoCamiao* camiao , int origemId , int destinationId[]) {

    // Calculate the smallest distance among the path points
    float smallestDistance = 500;
    float alldistance = 0;
    CaminhoCamiao* currentPoint = camiao;
    int previousPointId = origemId;


    int numIds = sizeof(destinationId) / sizeof(destinationId[0]);

    for (int i = 0; i <= numIds+1; i++)
    {
        float pointDistance = dijkstra(headList, origemId, destinationId[i]);
        alldistance = pointDistance + alldistance;
    }

  

    return alldistance;
}

int caminhoMaisPerto(LocalizacaoPostos* headList, int origemId, CaminhoCamiao* caminhoCamiaoList)
{
    float minDistance = -1;
    int shortestPathIdPosto = -1;
    int id;

    // Traverse the CaminhoCamiao list
    CaminhoCamiao* currentCaminhoCamiao = caminhoCamiaoList;
    while (currentCaminhoCamiao != NULL) {
        int destinationId = currentCaminhoCamiao->idPosto;

        // Perform Dijkstra's algorithm to find the shortest distance
        float distance = dijkstra(headList, origemId, destinationId);

        // Check if the distance is valid and update the minimum distance
        if (distance >= 0 && (minDistance == -1 || distance < minDistance)) {
            minDistance = distance;
            id = destinationId;
        }

        currentCaminhoCamiao = currentCaminhoCamiao->proximo;
    }

  
    return id;
}


// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}




// Function to generate and print all variations
void generateVariations(int arr[], int start, int end, float distancia, LocalizacaoPostos* headLista, int origemId, CaminhoCamiao* caminho, float* shortestDistance) {

    if (start == end) {
        for (int i = 0; i <= end; i++) {
            printf("%d ", arr[i]);
        }

        float distanciaAux2 = 0;
        float distAux = caminhoC(headLista, caminho, arr[0], arr);
        distanciaAux2 = distAux;

        if (distanciaAux2 < *shortestDistance) {
            *shortestDistance = distanciaAux2;
        }

        printf("\n");
    }
    else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            generateVariations(arr, start + 1, end, distancia, headLista, origemId, caminho, shortestDistance);
            swap(&arr[start], &arr[i]);
        }
    }


}


float calcularDistancia(LocalizacaoPostos* origem, LocalizacaoPostos* destino) {
    // Assuming Euclidean distance between latitude and longitude coordinates
    float latDiff = origem->latitude - destino->latitude;
    float lonDiff = origem->longitude - destino->longitude;
    return sqrtf(latDiff * latDiff + lonDiff * lonDiff);
}

float encontrarMenorDistancia(LocalizacaoPostos* posto, bool* visitados) {
    float menorDistancia = 500;
    LocalizacaoPostosAdjacentes* adjacente = posto->postosAdjacentes;
    while (adjacente != NULL) {
        if (!visitados[adjacente->idDestino] && adjacente->distancia < menorDistancia) {
            menorDistancia = adjacente->distancia;
        }
        adjacente = adjacente->proximo;
    }
    return menorDistancia;
}








// Function to find the nearest unvisited location
int encontrarProximoPosto(LocalizacaoPostos* postoAtual, LocalizacaoPostos* postos, int totalPostos) {
    int proximoPosto = -1;
    float menorDistancia = 500;

    LocalizacaoPostosAdjacentes* adjacente = postoAtual->postosAdjacentes;
    while (adjacente != NULL) {
        if (!adjacente->postoDestinoAdjacente->visitado) {
            float distancia = adjacente->distancia;
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                proximoPosto = adjacente->idDestino;
            }
        }
        adjacente = adjacente->proximo;
    }

    return proximoPosto;
}

// Function to find the shortest path using the Nearest Neighbor algorithm
void encontrarMenorCaminho(LocalizacaoPostos* postos, int totalPostos, int* caminho) {
    int proximoPosto;
    int index = 0;

    // Start from the first location
    LocalizacaoPostos* postoAtual = &postos[0];
    caminho[index++] = postoAtual->id;
    postoAtual->visitado = true;

    while (index < totalPostos) {
        proximoPosto = encontrarProximoPosto(postoAtual, postos, totalPostos);
        if (proximoPosto == -1) {
            // If no unvisited location is found, go back to the starting location
            proximoPosto = 0;
        }

        postoAtual = ProcurarPorIdPostosComListaToda(postos, proximoPosto);
        caminho[index++] = postoAtual->id;
        postoAtual->visitado = true;

        postos = AtualizarPostosAdjacentes(postos);
    }
}