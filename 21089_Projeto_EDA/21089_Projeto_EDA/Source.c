#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Gestor.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Atividade.h"


int main() {


	//Clientes* c1 = CriarClientes(1,"Manuel","Rua X", "123456789",300);
	//Clientes* c2 = CriarClientes(2,"Manuela","Rua X", "123456789",300);

	//MeiosDeMobilidade* m1 = CriarMeiosDeMobilidade(1,"Bicicleta",33,20,"BRAGA");
	//MeiosDeMobilidade* m2 = CriarMeiosDeMobilidade(2,"Bicicleta",44,20,"BARCELOS");
 
	Clientes* headListaClientes = NULL;		//inicio da lista
	MeiosDeMobilidade* headListaMeios = NULL;		//inicio da lista
	Gestor* headListaGestor = NULL;		//inicio da lista
	Atividade* headListaAluguerTotal = NULL;		//inicio da lista


	headListaAluguerTotal = LerAluguerListaTotalBinario("ListaAluguerTotalSave.bin");
	if (headListaAluguerTotal == NULL)
	{
		headListaAluguerTotal = LerEArmazenarAluguerListaTotal("ListaAluguerTotalInserir.txt", headListaAluguerTotal);
		GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin", headListaAluguerTotal);
	}

	headListaClientes = LerClientesBinario("ClientesSave.bin");
	if (headListaClientes == NULL)
	{
		headListaClientes = LerEArmazenarCliente("ClientesInserir.txt", headListaClientes);
		GravarClientesBinario("ClientesSave.bin", headListaClientes);

	}

	headListaMeios = LerMeiosDeMobilidadeBinario("MeiosSave.bin");
	if (headListaMeios == NULL)
	{
		headListaMeios = LerEArmazenarMeiosDeMobilidade("MeiosInserir.txt", headListaMeios);
		GravarMeiosDeMobilidadeBinario("MeiosSave.bin", headListaMeios);
	}

	DistribuirAlugueresHistorico(headListaAluguerTotal, headListaMeios, headListaClientes);


	headListaGestor = LerGestorBinario("GestorSave.bin");
	if (headListaGestor == NULL)
	{
		headListaGestor = LerEArmazenarGestor("GestorInserir.txt", headListaGestor);
		GravarGestorBinario("GestorSave.bin", headListaGestor);
	}

	//Meter tudo em todos os gestores;
	
	GravarMeiosEClientesNosGestores(headListaGestor , headListaAluguerTotal,  headListaClientes , headListaMeios);


	int escolha;

	do {

		printf("\nMeio De Mobilidade Dados:\n");
		MostrarListaMeiosDeMobilidade(headListaMeios);
		printf("\nClientes Dados:\n");
		MostrarListaClientes(headListaClientes);
		printf("\nGestor Dados:\n");
		MostrarListaGestor(headListaGestor);

		printf("\n----------- Menu -----------:\n");
		printf("1. Inserir Cliente\n");
		printf("2. Alterar Cliente\n");
		printf("3. Eliminar Cliente\n");
		printf("4. Inserir Meio\n");
		printf("5. Alterar Meio\n");
		printf("6. Eliminar Meio\n");
		printf("7. Inserir Gestor\n");
		printf("8. Alterar Gestor\n");
		printf("9. Eliminar Gestor\n");

		printf("\n10. Registar Aluguer\n");
		printf("11. Listar por autonomia meios de mobilidade \n");
		printf("12. Listar meios de mobilidade existentes com geocodigo\n");

		printf("13. Sair\n");

		printf("Escolha: ");
		scanf("%d", &escolha);

		switch (escolha) {
		case 1:
			headListaClientes = InsereClienteNoFim(headListaClientes, InserirPorEscreverCliente());
			break;
		case 2:
			AlterarPorEscreverCliente(headListaClientes);
			break;
		case 3:
			RemoverPorEscreverCliente(headListaClientes);
			break;
		case 4:
			headListaMeios = InsereMeiosDeMobilidadeNoFim(headListaMeios, InserirPorEscreverMeiosDeMobilidade());
			break;
		case 5:
			AlterarPorEscreverMeiosDeMobilidade(headListaMeios);
			break;
		case 6:
			RemoverPorEscreverMeiosDeMobilidade(headListaMeios);
			break;
		case 7:
			headListaGestor = InsereGestorNoFim(headListaGestor, InserirPorEscreverGestor());
			break;
		case 8:
			AlterarPorEscreverGestor(headListaGestor);
			break;
		case 9:
			RemoverPorEscreverGestor(headListaGestor);
			break;

		case 10:
			RegistoPorEscrever(headListaClientes , headListaAluguerTotal , headListaMeios);
			break;

		case 11:
			printf("\n\n\n ----------- Listagem ----------\n");
			ListarMeioAutonomiaDecrescente(headListaMeios);
			break;
		case 12:
			ListarGeocodigoPorEscreverMeiosDeMobilidade(headListaMeios);
			break;
		case 13:
			printf("A Sair\n");
			break;
		default:
			printf("Escolha nao disponivel , inserir outra vez.\n");
		}

		GravarMeiosEClientesNosGestores(headListaGestor, headListaAluguerTotal, headListaClientes, headListaMeios);

		GravarClientesBinario("ClientesSave.bin", headListaClientes);
		GravarMeiosDeMobilidadeBinario("MeiosSave.bin", headListaMeios);
		GravarGestorBinario("GestorSave.bin", headListaGestor);
		GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin" , headListaAluguerTotal);



	} while (escolha != 13);
	

	return 0;
}