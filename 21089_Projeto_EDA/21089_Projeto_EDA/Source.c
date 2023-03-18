#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Gestor.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Atividade.h"


int main() {


	Clientes* c1 = CriarClientes(1,"Manuel","Rua X", "123456789",300);
	Clientes* c2 = CriarClientes(2,"Manuela","Rua X", "123456789",300);

	MeiosDeMobilidade* m1 = CriarMeiosDeMobilidade(1,"Bicicleta",33,20,"BRAGA");
	MeiosDeMobilidade* m2 = CriarMeiosDeMobilidade(2,"Bicicleta",44,20,"BARCELOS");
 
	Clientes* headListaClientes = NULL;		//inicio da lista
	MeiosDeMobilidade* headListaMeios = NULL;		//inicio da lista
	Gestor* headListaGestor = NULL;		//inicio da lista
	Atividade* headListaAluguerTotal = NULL;		//inicio da lista


	//headListaClientes = LerClientesBinario("ClientesSave.bin");
	//headListaClientes = LerEArmazenarCliente("ClientesInserir.txt", HeadListaClientes);
	//GravarClientesBinario("ClientesSave.bin", headListaClientes);


	//headListaGestor = LerGestorBinario("GestorSave.bin");
	//headListaGestor = LerEArmazenarGestor("GestorInserir.txt" , headListaGestor);
	//GravarGestorBinario("GestorSave.bin", headListaGestor);

	//headListaMeios = LerMeiosDeMobilidadeBinario("MeiosSave.bin");
	//headListaMeios = LerEArmazenarMeiosDeMobilidade("MeiosInserir.txt" , headListaMeios);
	//GravarMeiosDeMobilidadeBinario("MeiosSave.bin", headListaMeios);

	//headListaAluguerTotal = LerAluguerListaTotalBinario("ListaAluguerTotalSave.bin");
	//headListaAluguerTotal = LerEArmazenarAluguerListaTotal("ListaAluguerTotalInserir.txt" , headListaAluguerTotal);
	//GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin", headListaAluguerTotal);


	headListaClientes = InsereClienteNoFim(headListaClientes, c1);
	headListaClientes = InsereClienteNoFim(headListaClientes, c2);
	headListaMeios = InsereMeiosDeMobilidadeNoFim(headListaMeios, m1);
	headListaMeios = InsereMeiosDeMobilidadeNoFim(headListaMeios, m2);


	DistribuirAlugueresHistorico(headListaAluguerTotal, headListaMeios , headListaClientes);

	//RemoverCliente(headListaClientes,2);
	//RemoverMeiosDeMobilidade(headListaMeios, 2);


	AlteraCliente(&headListaClientes,1,"Javier");
	AlteraMeiosDeMobilidade(&headListaMeios,1,"Carro");



	RegistoAluguer(&headListaClientes, &headListaMeios,&headListaAluguerTotal,1,1);
	RegistoAluguer(&headListaClientes, &headListaMeios, &headListaAluguerTotal, 1,1);
	RegistoAluguer(&headListaClientes, &headListaMeios, &headListaAluguerTotal, 1,2);

	Gestor* G1 = CriarNovoGestor(1, "Jeronimo", headListaMeios, headListaClientes, headListaAluguerTotal);
	headListaGestor = InsereGestorNoFim(headListaGestor, G1);

	AlteraGestor(&headListaGestor, 1, "Carla");

	//RemoverGestor(headListaGestor, 1);

	//ListarMeioPorGeoCodigo(headListaMeios , "BRAGA");
	ListarMeioAutonomiaDecrescente(headListaMeios);

	//MostrarListaMeiosDeMobilidade(headListaMeios);
	//MostrarListaClientes(headListaClientes);
	//MostrarListaGestor(headListaGestor);



	return 0;
}