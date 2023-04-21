/*
* author: Gonçalo Malheiro
* brief: Ficheiro onde serão demonstradas todas as funcões
* descricao: Trabalho Pratico Estruturas De Dados Avançadas
* data: Abril de 2023
*/

#define _CRT_SECURE_NO_WARNINGS
#include <yvals.h>
#include <stdio.h>
#define countof(arr) (sizeof(arr) / sizeof((arr)[0])) //calcular o número de elementos de um array 
#include "Estrutura.h"
#pragma warning(disable: 4996)

#pragma region menusmartcity
int menuSmartCity() {
	int opcaoPrincipal;

	do {
		printf("\n=============================================\n");
		printf("              MENU PRINCIPAL             \n");
		printf("=============================================\n");
		printf("\nSelecione uma das seguintes opcoes:\n\n");
		printf("1. Menu do Cliente\n");
		printf("2. Menu do Gestor\n");
		printf("3. Sair\n");
		printf("\n=============================================\n");
		printf("Opcao: ");
		scanf("%d", &opcaoPrincipal);
		system("cls");

		if (opcaoPrincipal < 1 || opcaoPrincipal > 3) {
			printf("\nDesculpe, essa opcao esta indisponivel, tente novamente.\n");
		}
	} while (opcaoPrincipal < 1 || opcaoPrincipal > 3);

	return opcaoPrincipal;
}

#pragma endregion

#pragma region menuCliente
int menuCliente()
{
	int opcaoCliente;

	printf("\n\n====================ESCOLHA A OPCAO QUE PRETENDE=====================\n");
	printf("\n1: Listagem dos Meios de Mobilidade Eletrica\n");
	printf("2: Listagem por ordem decrescente de Autonomia\n");
	printf("3: Listagem Meios num Geocodigo\n");
	printf("0: Sair\n");
	printf("\n========================================================================\n");
	printf("\nOpcao:");
	scanf_s("%d", &opcaoCliente);
	printf("\n===============================================\n");
	if (opcaoCliente < 0 || opcaoCliente > 4) {
		printf("\nDesculpe, essa opcao esta indisponivel.\n");
	}

	while (opcaoCliente < 0 || opcaoCliente > 3);
	return (opcaoCliente);
	system("cls");
}
#pragma endregion 

#pragma region menugestor
int menuGestor()
{
	int opcaoGestor;

	printf("\n===============================================\n");
	printf("\n1: Inserir Meio de Mobilidade Eletrica\n");
	printf("2: Listar Os Meios de Mobilidade Eletrica\n");
	printf("3: Remover Meio\ de Mobilidade Eletrica\n");
	printf("4: Guardar Meios de Mobilidade Eletrica\n");
	printf("5: Ler Meios de Mobilidade Eletrica\n");
	printf("6: Alteracao de um dado concreto de um Meio de Mobilidade Eletrica\n");
	printf("7: Inserir Cliente\n");
	printf("8: Listar Clientes\n");
	printf("9: Remover Cliente\n");
	printf("10: Guardar Cliente\n");
	printf("11: Ler Cliente\n");
	printf("12: Alteracao de um dado concreto de um cliente \n");
	printf("13: Inserir Gestor\n");
	printf("14: Listar Gestores\n");
	printf("15: Remover Gestor\n");
	printf("16: Guardar Gestor\n");
	printf("17: Ler Gestor\n");
	printf("18: Alteracao de um dado concreto de um Gestor\n");
	printf("19: Registo Aluguer de um Meio de Mobilidade Eletrica\n");
	printf("20: Listagem por Autonomia\n");
	printf("21: Listagem Meios de Mobilidade Eletrica num dado Geocodigo\n ");
	printf("0: Sair\n");
	printf("\n===============================================\n");
	printf("\nOpcao:");
	scanf_s("%d", &opcaoGestor);
	printf("\n================================================\n");

	if (opcaoGestor < 0 || opcaoGestor > 21) {
		printf("\nDesculpe, essa opcao esta indisponivel!!!\n");
	}

	while (opcaoGestor < 0 || opcaoGestor > 21);
	return (opcaoGestor);

	system("cls");
}
#pragma endregion 

#pragma region menucliente
int cliente1()
{
	int opcaoCliente;
	Meio* mobilidade = NULL; // Lista ligada "Meios" vazia
	char procurargeocodigo[50];

	do
	{
		opcaoCliente = menuCliente();
		switch (opcaoCliente)
		{

		case 1: listarMeios(mobilidade);
			break;

		case 2: listarOrdemDecrescenteAutonomia(mobilidade);
			break;

		case 3:
			printf("Geocodigo onde sera procurado os meios: \n");
			scanf_s("%s", procurargeocodigo, sizeof(procurargeocodigo));
			listagemGeoCodigo(mobilidade, procurargeocodigo);
			break;
		}

	} while (opcaoCliente != 0);

	return(0);
	system("cls");
}

#pragma endregion

#pragma region menugestor1
int gestor1()
{
	int opcaoGestor;
	Meio* mobilidade = NULL; //Lista ligada de "Meios" de mobilidade vazia
	Gestor* gestor = NULL; //Lista ligada de "Gestor" vazia
	Cliente* cliente = NULL; //Lista ligada de dados do cliente vazia

	int codigo, nif, codre, posicao, opção;
	float bat, aut, custo, saldo, codigogestor;
	char tipo[50], geocodigo[50], estadoaluguer[50], nome[50], morada[70], removernome[50], nomegestor[50], passe[50], procurargeocodigo[50], removernomegestor[50];

	do
	{
		opcaoGestor = menuGestor();
		switch (opcaoGestor)
		{

		case 1:
			printf("Codigo?\n");
			scanf_s("%d", &codigo);
			printf("Tipo?\n");
			getchar();
			scanf_s("%10s", tipo, 11);
			printf("Nivel da bateria?\n");
			scanf_s("%f", &bat);
			printf("Autonomia?\n");
			scanf_s("%f", &aut);
			printf("Custo?\n");
			scanf_s("%f", &custo);
			printf("Geocodigo?\n");
			getchar();
			fgets(geocodigo, 11, stdin);
			printf("Estado Aluguer\n");
			fgets(estadoaluguer, 10, stdin);

			if (strcmp(estadoaluguer, "disponivel\n") == 0) {
				// Estado do aluguel é disponível
			}
			else if (strcmp(estadoaluguer, "indisponivel\n") == 0) {
				// Estado do aluguel é indisponível
			}
			else {
				// Entrada inválida
			}

			mobilidade = inserirMeio(mobilidade, codigo, tipo, bat, aut, custo, geocodigo, estadoaluguer);
			break;
		case 2: listarMeios(mobilidade);
			printf("\n");
			break;
		case 3:
			printf("Codigo do Meio de Mobilidade Eletrica a remover?\n");
			scanf("%d", &codigo);
			mobilidade = eliminarMeio(mobilidade, codigo);
			if (mobilidade != NULL) {
				printf("Nao foi possivel encontrar o Meio de Mobilidade Eletrica com o codigo %d.\n", codigo);
			}
			else {
				printf("O Codigo do Meio de Mobilidade Eletrica %d foi removido.\n", codigo);
			}
			break;
		case 4:
			if (armazenarMeios(mobilidade)) {
				printf("Ficheiro salvo com sucesso!\n");
			}
			else {
				printf("Erro ao salvar o ficheiro.\n");
			}
			break;

		case 5: if (lerMeios(mobilidade)) {
			printf("O ficheiro foi lido com sucesso!\n");
		}
			  else {
			printf("Erro ao ler o ficheiro.\n");
		}
			  break;
		case 6:
			printf("Digite o codigo do Meio de Mobilidade Eletrica no qual iremos altera os seus dados\n");
			scanf_s("%d", &codigo);
			printf("Digite o tipo de Meio de Mobilidade Eletrica no qual iremos altera os seus dados \n");
			getchar();
			scanf_s("%10s", tipo, 11);
			printf("Digite o nivel de bateria do Meio de Mobilidade Eletrica no qual iremos altera os seus dados\n");
			scanf_s("%f", &bat);
			printf("Digite a autonomia do Meio de Mobilidade Eletrica no qual iremos altera os seus dados\n");
			scanf_s("%f", &aut);
			printf("Digite o custo\n");
			scanf_s("%f", &custo);
			printf("Digite o geocodigo do Meio de Mobilidade Eletrica no qual iremos altera os seus dados\n");
			getchar();
			fgets(geocodigo, 11, stdin);
			printf("Digite o estado de aluguer\n");
			fgets(estadoaluguer, 10, stdin);

			mobilidade = alterarMeio(mobilidade, codigo, tipo, bat, aut, custo, geocodigo, estadoaluguer);
			break;

		case 7: printf("Nome?\n");
			scanf_s("%s", nome, sizeof(nome));
			printf("Morada?\n");
			scanf_s("%s", morada, sizeof(morada));
			printf("Nif?\n");
			scanf_s("%d", &nif, sizeof(nif));
			printf("Saldo?\n");
			scanf_s("%f", &saldo, sizeof(saldo));

			cliente = inserirCliente(cliente, nome, morada, nif, saldo);
			break;

		case 8: listarClientes(cliente);
			printf("---------------------------------------\n");
			break;

		case 9:
			printf("Digite o nome do cliente a ser removido: ");
			scanf("%49s", removernome);
			fflush(stdin);
			if (strcmp(nome, removernome) == 0) {
				printf("O nome do cliente %s foi removido.\n", removernome);
			}
			else {
				printf("Nao foi possivel encontrar o cliente com o nome %s.\n", removernome);
			}

			break;

		case 10:
			if (armazenarCliente(cliente)) {
				printf("Ficheiro salvo com sucesso!\n");
			}
			else {
				printf("Erro ao salvar o ficheiro.\n");
			}
			break;

		case 11:
			if (lerClientes(cliente)) {
				printf("Ficheiro lido com sucesso!\n");
			}
			else {
				printf("Erro ao ler o ficheiro.\n");
			}
			break;

		case 12:

			printf("Digite o nome do Cliente a alterar os dados\n");
			scanf_s("%s", nome, sizeof(nome));
			printf("Digite a morada do Cliente a alterar os dados\n");
			scanf_s("%s", morada, sizeof(morada));
			printf("Digite o nif do cliente a alterar os dados\n");
			scanf_s("%d", &nif, sizeof(nif));
			printf_s("Digite o saldo do cliente a alterar os dados\n");
			scanf_s("%f", &saldo, sizeof(saldo));
			cliente = alterarCliente(cliente, nome, morada, nif, saldo);

			break;

		case 13: printf("Nome Gestor?\n");
			getchar();
			fgets(nomegestor, 11, stdin);
			printf("Codigo do Gestor?\n");
			scanf_s("%f", &codigogestor);
			printf("Palavra Passe?\n");
			scanf("%10s", passe);
			gestor = inserirGestor(gestor, nomegestor, codigogestor, passe);
			break;

		case 14: listarGestor(gestor);
			printf("-------------------------");
			break;

			
		case 15:
			printf("Digite o nome do gestor a ser removido: ");
			scanf("%49s", removernomegestor);
			if (strcmp(nomegestor, removernomegestor) == 0) {
				printf("O gestor com o nome %s foi removido.\n", removernomegestor);
				
			}
			else {
				printf("Nao foi possivel encontrar o gestor com o nome %s.\n", removernomegestor);
			}
			break;

		case 16: armazenarGestor(gestor);
			break;

		case 17: gestor = lerGestor(gestor);
			if (lerGestor(gestor)) {
				printf("Ficheiro lido com sucesso!\n");
			}
			else {
				printf("Erro ao ler o ficheiro.\n");
			}
			break;
		case 18:
			printf("Digite o nome do Gestor a alterar os dados\n");
			scanf("%10s", &nomegestor);
			printf("Digite o codigo de Gestor\n");
			scanf_s("%f", &codigogestor);
			printf("Digite a palavra passe\n");
			scanf("%10s", passe);
			gestor = alterarGestor(gestor, nomegestor, codigogestor, passe);
			break;

		case 19: printf("Codigo do Meio de Mobilidade Eletrica a Alugar:\n");
			scanf("%d", &codre);
			registoAluguer(mobilidade, codre);
			break;

		case 20: listarOrdemDecrescenteAutonomia(mobilidade);
			printf("-------------------------------------------\n");
			break;

		case 21:
			printf("O Geocodigo onde sera procurado os Meios de Mobilidade Eletrica: \n");
			scanf_s("%s", procurargeocodigo, sizeof(procurargeocodigo));
			listagemGeoCodigo(mobilidade, procurargeocodigo);
			printf("---------------------------------------------------\n");
			break;
		}
	} while (opcaoGestor != 0);

	return(0);
	system("cls");
}
#pragma endregion

int main()
{
	Meio* mobilidade = NULL; // Lista ligada dos "Meios" vazia
	Gestor* gestor = NULL; //Lista ligada do "Gestor" vazia
	Cliente* cliente = NULL; //Lista ligada vazia do "Cliente" vazia

	int opcaoPrincipal = menuSmartCity();
	switch (opcaoPrincipal)
	{
	case 1: cliente1();
		break;
	case 2: gestor1();
		break;
	default: printf("Desculpe, essa opcao esta indisponivel!!!\n");

		system("cls");
	}
}
