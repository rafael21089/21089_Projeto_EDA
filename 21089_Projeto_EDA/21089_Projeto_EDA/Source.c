#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Gestor.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Aluguer.h"


int main() {


	Clientes* headListaClientes = NULL;				//Inicio da lista Clientes
	MeiosDeMobilidade* headListaMeios = NULL;		//Inicio da lista MeiosDeMobilidade
	Gestor* headListaGestor = NULL;					//Inicio da lista Gestor
	Aluguer* headListaAluguerTotal = NULL;		//Inicio da lista


	// Armazenamento de listas , se tiver vazia vai ao ficheiro de texto para inserir valores.

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

	DistribuirAlugueresHistorico(headListaAluguerTotal, headListaMeios, headListaClientes);  // Distribui os alugueres passados (historico de alugueres) nas listas respectivas


	headListaGestor = LerGestorBinario("GestorSave.bin");
	if (headListaGestor == NULL)
	{
		headListaGestor = LerEArmazenarGestor("GestorInserir.txt", headListaGestor);
		GravarGestorBinario("GestorSave.bin", headListaGestor);
	}
	
	GravarMeiosEClientesNosGestores(headListaGestor , headListaAluguerTotal,  headListaClientes , headListaMeios);  //Grava as listas Clientes e Meios em todos os gestores


	//---------


	int escolha;

	//----------  Menu --------------

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
		printf("13. Listar Alugueres de Cliente por Id: \n");
		printf("14. Listar Alugueres de Meios por Id: \n");
		printf("15. Listar todos Alugueres: \n");

		printf("16. Sair\n");

		printf("\nEscolha: ");
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
			printf("\n\n\n ----------- Listagem ----------\n");
			ListarGeocodigoPorEscreverMeiosDeMobilidade(headListaMeios);
			break;
		case 13:
			printf("\n\n\n ----------- Listagem ----------\n");
			AluguerClientePorEscrever(headListaAluguerTotal);
			break;
		case 14:
			printf("\n\n\n ----------- Listagem ----------\n");
			AluguerMeiosPorEscrever(headListaAluguerTotal);
			break;
		case 15:
			printf("\n\n\n ----------- Listagem ----------\n");
			ListarTodosAlugueres(headListaAluguerTotal);
			break;
		case 16:
			printf("A Sair\n");
			break;
		default:
			printf("Escolha nao disponivel , inserir outra vez.\n");
		}

		
		GravarMeiosEClientesNosGestores(headListaGestor, headListaAluguerTotal, headListaClientes, headListaMeios);//Grava as listas Clientes e Meios em todos os gestores

		//Grava nos ficheiros binarios as listas:

		GravarClientesBinario("ClientesSave.bin", headListaClientes);
		GravarMeiosDeMobilidadeBinario("MeiosSave.bin", headListaMeios);
		GravarGestorBinario("GestorSave.bin", headListaGestor);
		GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin" , headListaAluguerTotal);



	} while (escolha != 16);
	

	return 0;
}