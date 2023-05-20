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


LocalizacaoPostos* CriarPosto(int id, const char* cidade, const char* latitude, const char* longitude, const char* geocode , LocalizacaoPostosAdjacentes* postosAdjacentes) {
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

    if (ExistePosto(header, novoPosto->id)) return header;	//se existir não insere!

    if (header == NULL) {
        header = novoPosto;
        return header;
    }
    else {
        LocalizacaoPostos* aux = header;
        LocalizacaoPostos* ant = aux;
        while (aux && strcmp(aux->cidade, novoPosto->cidade) > 0) {
            ant = aux;
            aux = aux->proximo;
        }
        if (aux == header) {
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
    postoAdjacente->distancia = distancia;
    postoAdjacente->proximo = NULL;

    return postoAdjacente;
}

LocalizacaoPostosAdjacentes* InserirPostoAdjacente(LocalizacaoPostos** headLista, LocalizacaoPostos* postoOrigem , LocalizacaoPostos* postoDestino, float distancia) {

    if (headLista == NULL)
    {
        return headLista;

    }

    if (JaTemPostoAdjacente(postoOrigem, postoDestino)) return *headLista;	//se existir não insere!


    if (postoOrigem->postosAdjacentes == NULL) {

        LocalizacaoPostos* aux = ProcurarPorIdPostosComListaToda(*headLista, postoOrigem->id);
        if (aux != NULL)
         {
            aux->postosAdjacentes = CriarPostoAdjacente(postoDestino, distancia);
         }
    }
    else {
        LocalizacaoPostosAdjacentes* aux = postoOrigem->postosAdjacentes;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        LocalizacaoPostos* aux2 = ProcurarPorIdPostosComListaToda(*headLista, postoOrigem->id);
        if (aux2 != NULL)
        {
            aux2->postosAdjacentes = aux;
            aux2->postosAdjacentes->proximo = CriarPostoAdjacente(postoDestino, distancia);
        }
    }

    return *headLista;

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

    if (aux->postosAdjacentes == NULL)
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