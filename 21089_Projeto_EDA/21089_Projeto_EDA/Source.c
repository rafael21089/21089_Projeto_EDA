#define _CRT_SECURE_NO_WARNINGS


/**
*  @file Source.c
 * @author Rafael Silva
 * @email a21089@alunos.ipca.pt
 * @date 2023
 * @brief Main da Aplicacao
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Gestor.h"
#include "Cliente.h"
#include "MeioDeMobilidade.h"
#include "Aluguer.h"
#include "Localizacao.h"


int main() {

	Clientes* headListaClientes = NULL;				//Inicio da lista Clientes
	MeiosDeMobilidade* headListaMeios = NULL;		//Inicio da lista MeiosDeMobilidade
	Gestor* headListaGestor = NULL;					//Inicio da lista Gestor
	Aluguer* headListaAluguerTotal = NULL;		//Inicio da lista

	LocalizacaoPostos* headListaPostos = NULL;		//Inicio da lista

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


	//Localizacoes - Postos

	headListaPostos = LerPostosBinario("PostosSave.bin");
	if (headListaPostos == NULL)
	{
		headListaPostos = LerEArmazenarPosto("PostosInserir.txt", &headListaPostos);
		GravarPostosBinario("PostosSave.bin", headListaPostos);

	}

	bool res = true;
	headListaPostos = LerPostosAdjacentesBinario("PostosAdjacentesSave.bin", &headListaPostos, &res);
	if (res == false)
	{
		headListaPostos = LerEArmazenarPostoAdjacente("PostosAdjacentesInserir.txt", &headListaPostos);
		GravarPostosAdjacentesBinario("PostosAdjacentesSave.bin", headListaPostos);

	}



	int escolhaClienteGestor = 0;
	int idCliente =-1;
	int idGestor = -1;

	//Escolha da Area (Cliente ou Gestor) Que Quer
	do
	{
		system("cls");

		printf("\n----------- Menu -----------:\n");
		printf("1. Area de Gestor\n");
		printf("2. Area de Cliente\n");

		printf("\n3. Sair\n");

		printf("\nEscolha: ");
		scanf("%d", &escolhaClienteGestor);

		switch (escolhaClienteGestor)
		{
		case 1:
			system("cls");

			printf("\n\nDigite o id do Gestor que quer entrar: ");
			scanf("%d", &idGestor);

			if (!ExisteGestor(headListaGestor , idGestor))
			{
				system("cls");

				printf("\nNao Exite Gestor com esse Id");
				escolhaClienteGestor = 0;
			}

			break;
		case 2:
			system("cls");

			printf("\n\nDigite o id do Cliente que quer entrar: ");
			scanf("%d", &idCliente);
			if (!ExisteCliente(headListaClientes, idCliente))
			{
				system("cls");

				printf("\nNao Exite Cliente com esse Id");
				escolhaClienteGestor = 0;
			}
			break;
		case 3:
			break;
		default:
			printf("Escolha nao disponivel , inserir outra vez.\n");
		}


	} while (escolhaClienteGestor != 1 && escolhaClienteGestor != 2 && escolhaClienteGestor != 3);

	int escolha;

	//Menu Area Gestor
	if (idGestor != -1)
	{
		system("cls");

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
			printf("3. Eliminar Cliente\n\n");
			printf("4. Inserir Meio\n");
			printf("5. Alterar Meio (tipo)\n");
			printf("6. Eliminar Meio\n\n");
			printf("7. Inserir Gestor\n");
			printf("8. Alterar Gestor\n");
			printf("9. Eliminar Gestor\n\n");

			printf("10. Listar por autonomia meios de mobilidade \n");
			printf("11. Listar meios de mobilidade existentes por cidade\n\n");
			printf("12. Listar Alugueres de Cliente por Id: \n");
			printf("13. Listar Alugueres de Meios por Id: \n");
			printf("14. Listar todos Alugueres: \n\n");

			printf("15. Lista Todos os Postos\n");
			printf("16. Eliminar Posto\n");
			printf("17. Alterar Posto\n");
			printf("18. Criar Posto\n");
			printf("19. Criar Adjacencia\n");
			printf("20. Remover Adjacencia\n\n");

			printf("21. Camiao Recolher Meios abaixo de 50 percentagem de bateria\n\n");

			printf("22. Alterar Estado Meio\n");
			printf("23. Alterar Localizacao Meio\n\n");

			printf("24. Sair\n");

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
				ListarMeioAutonomiaDecrescente(headListaMeios);
				break;
			case 11:
				ListarCidadePorEscreverMeiosDeMobilidade(headListaMeios);
				break;
			case 12:
				AluguerClientePorEscrever(headListaAluguerTotal);
				break;
			case 13:
				AluguerMeiosPorEscrever(headListaAluguerTotal);
				break;
			case 14:
				ListarTodosAlugueres(headListaAluguerTotal);
				break;
			case 15:
				ListarTodosPostos(headListaPostos);
				break;
			case 16:
				headListaPostos = RemoverPostoEscrever(headListaPostos);
				break;
			case 17:
				AlterarPorEscreverPosto(headListaPostos);
				break;
			case 18:
				CriarPostoEscrever(headListaPostos);
				break;
			case 19:
				CriarAdjacenciaPostoEscrever(headListaPostos);
				break;
			case 20:
				RemoverAdjacenciaPostoEscrever(headListaPostos);
				break;
			case 21:
				CamiaoRecolhaEscrever(headListaPostos , headListaMeios);
				break;
			case 22:
				AlterarEstadoEscrever(headListaMeios);
				break;

			case 23:
				AlterarLocalizacaoEstadoEscrever(headListaMeios);
				break;

			case 24:
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
			GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin", headListaAluguerTotal);
			GravarPostosAdjacentesBinario("PostosAdjacentesSave.bin", headListaPostos);
			GravarPostosBinario("PostosSave.bin", headListaPostos);


		} while (escolha <= 24);
	}

	//Menu Area Cliente
	else if (idCliente != -1) {
	system("cls");

	do {

		printf("\nCliente Dados:\n");

		//Mostrar Dados
		MostraCliente(ProcuraClientes(headListaClientes,idCliente));
		
		printf("\n----------- Menu -----------:\n");
		printf("1. Registo Aluguer de um Meio\n");
		printf("2. Historico de Alugueres\n");
		printf("\n3. Lista todos os Postos de Recolha\n");
		printf("\n4. Lista todos os Meios\n");
		printf("5. Lista todos os Postos de Recolha em um raio de 50 km\n");
		printf("6. Lista todos os Meios em um raio de 50 km de um certo tipo\n");
		printf("\n7. Ir para Meio de Mobilidade\n");
		printf("8. Ir para Posto de Recolha\n");

		printf("\n9. Alterar Dados (nome)\n");
		printf("10. Aumentar Saldo\n");
		printf("11. Parar Aluguer Ativo\n");
		printf("12. Viajar com o Meio Alugado Ate Localizacao\n");
	
		printf("13. Sair\n");

		printf("\nEscolha: ");
		scanf("%d", &escolha);

		switch (escolha) {
		

		case 1:
			RegistoPorEscreverClienteWindow(headListaClientes, headListaAluguerTotal, headListaMeios , idCliente);
			break;
		case 2:
			ListarClienteAlugueresById(headListaAluguerTotal, idCliente);
			break;
		case 3:
			ListarTodosPostos(headListaPostos);
			break;
		case 4:
			system("cls");
			MostrarListaMeiosDeMobilidade(headListaMeios);
			break;
		case 5:
			LocalizacaoRaioClientePosto(ProcuraClientes(headListaClientes , idCliente) , headListaPostos, 500.0);
			break;
		case 6:
			ProcurarRaioMeioCliente(headListaClientes, headListaMeios, idCliente);
			break;
		case 7:
			ClienteParaMeioLocalizacao(headListaClientes, headListaMeios , headListaPostos , idCliente);
			break;
		case 8:
			ClienteParaPostoLocalizacao(headListaClientes , headListaPostos , idCliente);
			break;
		case 9:
			AlterarPorEscreverClienteWindowCliente(headListaClientes , idCliente);
			break;
		case 10:
			AumentarSaldoPorEscreverCliente(headListaClientes, idCliente);
			system("cls");
			break;

		case 11:
			ParaAluguerAtivo(headListaClientes , headListaAluguerTotal, headListaMeios, idCliente);
			system("cls");

			break;
		case 12:
			ClienteViagemEscrever(headListaClientes, headListaMeios , headListaPostos , idCliente);
			break;

		case 13:
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
		GravarAluguerListaTotalBinario("ListaAluguerTotalSave.bin", headListaAluguerTotal);
		GravarPostosAdjacentesBinario("PostosAdjacentesSave.bin", headListaPostos);
		GravarPostosBinario("PostosSave.bin", headListaPostos);


	} while (escolha <= 13);
	}


	return 0;
}