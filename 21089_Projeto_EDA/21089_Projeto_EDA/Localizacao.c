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


LocalizacaoPostos* CriarPosto(int id, char* cidade, char* latitude, char* longitude, char* geocode , LocalizacaoPostosAdjacentes* postosAdjacentes) {
    LocalizacaoPostos* novoPosto = (LocalizacaoPostos*)malloc(sizeof(LocalizacaoPostos));
    if (novoPosto == NULL) {
        return NULL;
    }
 
    novoPosto->id = id;
    strncpy(novoPosto->cidade, cidade, LARGURAGERALSTRING);
    strncpy(novoPosto->latitude, latitude, LARGURAGERALSTRING);
    strncpy(novoPosto->longitude, longitude, LARGURAGERALSTRING);
    strncpy(novoPosto->geocode, geocode, LARGURAGERALSTRING);
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
            result = CriarPosto(aux->id, aux->cidade, aux->latitude, aux->longitude, aux->geocode ,aux->postosAdjacentes);
         
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
        strncpy(novoPosto->latitude, token, sizeof(novoPosto->latitude));
        token = strtok(NULL, ";");
        strncpy(novoPosto->longitude, token, sizeof(novoPosto->longitude));
        token = strtok(NULL, ";");
        strncpy(novoPosto->geocode, token, sizeof(novoPosto->geocode));

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
        LocalizacaoPostos* aux = CriarPosto(auxAnt->id, auxAnt->cidade, auxAnt->latitude, auxAnt->longitude, auxAnt->geocode, NULL); //Cria Aluguer com valores recebidos
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