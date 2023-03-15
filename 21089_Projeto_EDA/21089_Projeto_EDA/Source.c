#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Gestor.h"


int main() {


	

	Clientes* C1 = CriarClientes(1,"Manuel","Rua X", "123456789",3);
	Clientes* C2 = CriarClientes(2,"Manuela","Rua X", "123456789",3);

	MeiosDeMobilidade* M1 = CriarMeiosDeMobilidade(1,"Bicicleta",67,20,123331);
	MeiosDeMobilidade* M2 = CriarMeiosDeMobilidade(2,"Bicicleta",44,20,123331);
 
	Clientes* HeadListaClientes = NULL;		//inicio da lista
	MeiosDeMobilidade* HeadListaMeios = NULL;		//inicio da lista
	Gestor* HeadListaGestor = NULL;		//inicio da lista

	HeadListaClientes = InsereClienteNoFim(HeadListaClientes, C1);
	HeadListaClientes = InsereClienteNoFim(HeadListaClientes, C2);
	HeadListaMeios = InsereMeiosDeMobilidadeNoFim(HeadListaMeios, M1);
	HeadListaMeios = InsereMeiosDeMobilidadeNoFim(HeadListaMeios, M2);

	RemoverCliente(HeadListaClientes,2);
	//RemoverMeiosDeMobilidade(HeadListaMeios, 2);


	AlteraCliente(&HeadListaClientes,1,"Javier");
	AlteraMeiosDeMobilidade(&HeadListaMeios,1,"Carro");


	Gestor* G1 = CriarNovoGestor(1,"Jeronimo", HeadListaMeios, HeadListaClientes);
	HeadListaGestor = InsereGestorNoFim(HeadListaGestor, G1);


	RegistoAluguer(&HeadListaClientes, &HeadListaMeios,1,1,1);
	RegistoAluguer(&HeadListaClientes, &HeadListaMeios,1,1,2);

	AlteraGestor(&HeadListaGestor, 1, "Carla");

	//RemoverGestor(HeadListaGestor, 1);

	MostrarListaMeiosDeMobilidade(HeadListaMeios);
	MostrarListaClientes(HeadListaClientes);
	MostrarListaGestor(HeadListaGestor);



	return 0;
}