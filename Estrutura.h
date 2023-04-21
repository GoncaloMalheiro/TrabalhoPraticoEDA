/*
* author: Gon�alo Malheiro
* brief: Todas as estruturas utilizadas
* descricao: Trabalho Pratico Estruturas De Dados Avan�adas
* data: Abril de 2023
*/

#pragma once
#include <stdio.h>
#include <string.h>

typedef struct Registo {

	int codigo; //C�digo do meio de mobilidade el�trica
	char tipo[50]; //Tipo do meio de mobiidade el�trica, ex: bicicleta,carro, etc...
	float bateria; //Bateria do meio de mobilidade el�trica 
	float autonomia; //Autonomia do meio de mobilidade el�trica
	float custo; //Custo do meio de mobilidade el�trica	
	char geocodigo[50]; // Geocodigo do meio de mobilidade el�trica
	char estadoaluguer[50]; //Se o tipo de mobilidade el�trica est� dispon�vel ou indispon�vel
	struct Registo* seguinte; //Apontador "seguinte" guarda o endere�o de mem�ria da "struct Registo"
}Meio;

typedef struct registoCliente {

	char nome[50]; //Nome do cliente
	char morada[70]; //Morada do cliente
	int nif; // NIF do cliente
	float saldo; //Saldo do cliente
	struct Registo* seguinte; //Apontador "seguinte" guarda o endere�o de mem�ria da "struct Registo"
}Cliente;

typedef struct registoGestor {

	char nomegestor[30]; //Nome do Gestor
	float codigogestor; //C�digo do Gestor
	char passe[20]; // Palavra-Passe de cada Gestor
	struct Registo* seguinte; //Apontador "seguinte" guarda o endere�o de mem�ria da "struct Registo"
}Gestor;


//Funcoes Meio de Mobilidade El�trica
Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, float custo, char geocodigo[]); //Insere um novo registo
int existeMeio(Meio* inicio, int codigo); // Determina se existe o 'codigo' na lista ligada 'inicio'
void listarOrdemDecrescenteAutonomia(Meio* inicio); // Compara as autonomias das listas ligadas e poe por ordem decrescente de autonomia
void listarMeios(Meio* inicio); // Mostra o conte�do da Lista Ligada
Meio* eliminarMeio(Meio* inicio, int codigo); //Remove um Meio de Mobilidade El�trica a partir do seu c�digo
Meio* lerMeios(); // L� cada valor da lista ligada
int armazenarMeios(Meio* inicio); // Guarda cada valor da lista ligada
void trocar(Meio* a, Meio* b); //Troca os parametros de ordem
Meio* alterarMeio(Meio* inicio, int codigo, char tipo[], float bat, float aut, float custo, char geocodigo[], char estadoaluguer[]); //Compara o codigo na lista ligada, com o que pretendemos procurar, quando encontrado troca na lista ligada
int registoAluguer(Meio* inicio, int codigo); //Compara o codigo do meio de mobilidade eletrica pedido com os existentes na lista ligada. 
void listagemGeoCodigo(Meio* inicio, char geocodigo); // Verifica se o geocodigo que queremos existe na lista ligada
int salvarMeios(FILE* fp, Meio* inicio); // Salva cada parametro da struct "Meios"

//Funcoes do Cliente
Cliente* inserirCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo); //Verifica se cliente existe, caso exista adiciona
Cliente* eliminarCliente(Cliente* inicio, char nome); //Verifica se o endere�o de memoria inicial n�o � nulo e depois compara os nomes na lista ligada com o que � para eliminar da lista ligada
void listarClientes(Cliente* inicio); //Mostra o conteudo da lista ligada
int armaenarCliente(Cliente* inicio); //Guarda os valores da lista ligada
Cliente* alterarCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo); //Compara os nomes da lista ligada com o pedido realizado pelo utilizador,caso encontre altera os dados do cliente
Cliente* lerClientes(); // Le cada valor da lista ligada

//Funcoes do Gestor
Gestor* lerGestor(); //Le cada valor da lista ligada
Gestor* inserirGestor(Gestor* inicio, char nomegestor[], float codigo, char passe); //Insere um novo gestor
int armazenarGestor(Gestor* inicio); // Guarda cada valor da lista ligada
void listarGestor(Gestor* inicio); // Mostra o conteudo da lista ligada
Gestor* eliminarGestor(Gestor* inicio, char nome);//Verifica se o endere�o de memoria inicial n�o � nulo e depois compara os nomes na lista ligada com o que � para eliminar da lista ligada
Gestor* alterarGestor(Gestor* inicio, char nomegestor[], float codigogestor, char passe[]); //Compara os nomes da lista ligada com o pedido realizado pelo utilizador,caso encontre altera os dados do cliente