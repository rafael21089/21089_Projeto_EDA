#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Gestor.h"


int main() {

	Clientes* C1 = CriarClientes(1,"Manuel","Rua X", "123456789",3);
	Clientes* C2 = CriarClientes(2,"Manuela","Rua X", "123456789",3);


	MeiosDeMobilidade* M1 = CriarMeiosDeMobilidade(1,"Bicicleta",67,20,123331,C1);
	MeiosDeMobilidade* M2 = CriarMeiosDeMobilidade(2,"Bicicleta",44,20,123331,NULL);
 
	Clientes* HeadListaClientes = NULL;		//inicio da lista
	MeiosDeMobilidade* HeadListaMeios = NULL;		//inicio da lista

	HeadListaClientes = InsereClienteNoFim(HeadListaClientes, C1);
	HeadListaMeios = InsereMeiosDeMobilidadeNoFim(HeadListaMeios, M1);
	HeadListaMeios = InsereMeiosDeMobilidadeNoFim(HeadListaMeios, M2);

	MostrarListaMeiosDeMobilidade(HeadListaMeios);

	//MostrarListaClientes(HeadListaClientes);


	return 0;
}