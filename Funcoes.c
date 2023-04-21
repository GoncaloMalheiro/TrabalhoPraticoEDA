/*
* author: Gon�alo Malheiro
* brief: Ficheiro onde ser�o executadas todas as func�es
* descricao: Trabalho Pratico Estruturas De Dados Avan�adas
* data: Abril de 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estrutura.h"
#pragma warning(disable: 4996)
#define MEIO_FORMATO "%d;%s;%.2f;%0.2f;%.2f;%s;%s\n" // Defenir "Meio_FORMATO" para usar na funcao Meios , cada parametro da lista ligada "Meios"

int armazenarMeios(Meio* inicio) {
	FILE* fp; // Apontor "fp" para manipular ficheiros
	int result = 0;  // Inicializa a vari�vel "result" como 0, indicando que a opera��o n�o foi bem sucedida

	fp = fopen("meios.txt", "w"); // Cria e abre o ficheiro "meios.txt" em modo de escrita ("w") com o apontador "fp"

	if (fp != NULL) { // Verifica se o ficheiro foi aberto corretamente

		result = salvarMeios(fp, inicio); //Chama a funcao "salvarMeios" para guardar as informa��es da lista no ficheiro

		fclose(fp); //fecha o ficheiro
	}

	if (!result) {  // Se "result" for igual a 0, significa que ocorreu um erro durante a opera��o de guardar as informa��es no ficheiro

		printf("Erro ao salvar o ficheiro.\n");
	}

	return result; // retorna o resultado da opera��o de escrita
}

int salvarMeios(FILE* fp, Meio* inicio) {
	int result = 0; // vari�vel para armazenar o resultado da opera��o
	Meio* current = inicio; // apontador "current" aponta para o mesmo endere�o de mem�ria do in�cio da lista

	while (current != NULL) { // percorre a lista ligada

		if (fprintf(fp, MEIO_FORMATO, // escreve as informa��es do meio de transporte no ficheiro, utilizando o formato definido em MEIO_FORMATO
			current->codigo,
			current->tipo,
			current->bateria,
			current->autonomia,
			current->custo,
			current->geocodigo,
			current->estadoaluguer) < 0) {
			return 0; // a opera��o n�o foi realizada corretamente, retorna 0
		}
		current = current->seguinte; // avan�a para o pr�ximo elemento da lista
	}

	return 1; // a opera��o foi realizada corretamente
}

Meio* lerMeios()
{
	FILE* fp; //Apontador "fp" para manipular o ficheiro 
	int codigo; // Declarar variaiveis
	float bat, aut = 0, custo;
	char tipo[50], geocodigo[50], aluguer[30];
	Meio* aux = NULL;
	fp = fopen("meios.txt", "r"); // Cria e abre o ficheiro "meios.txt" em modo de leitura ("r") com o apontador "fp"
	if (fp != NULL) //Verifica se o apontador "fp" n�o � nulo
	{
		while (!feof(fp)) // Entra no "loop" de repeti��o enquanto n�o chegar ao final do ficheiro "fp"
		{

			fscanf(fp, "%d %[;] %.2f %.2f %f %[;] %[;]\n", &codigo, tipo, &bat, &aut, &custo, geocodigo, aluguer); // L� cada linha do ficheiro e armazena as informa��es nas vari�veis correspondentes
			aux = inserirMeio(aux, codigo, tipo, bat, aut, custo, geocodigo, aluguer); // Insere as informa��es lidas num novo ponto da lista ligada e atualiza o apontador "aux"
		}
		fclose(fp); // fecha o ficheiro
	}
	return(aux); // Retorna o apontador para o in�cio da lista ligada "Meios"
}


Meio* inserirMeio(Meio* inicio, int codigo, char tipo[], float bat, float aut, float custo, char geocodigo[], char estadoaluguer[])
{

	if (!existeMeio(inicio, codigo)) //Verifica se o "Meio" ja existe na lista ligada
	{
		Meio* novo = malloc(sizeof(struct Registo)); //V� se existe espcao no endere�o de memoria

		if (novo != NULL) //Se "novo" nao for nulo
		{
			novo->codigo = codigo;
			strcpy(novo->tipo, tipo); //Copia o valor do apontador "tipo" para o campo "tipo" do novo n�
			novo->bateria = bat;
			novo->autonomia = aut; // Atribui o valor "aut" ao campo "autonomia" do novo n�
			novo->custo = custo;
			strcpy(novo->geocodigo, geocodigo); // Copia o valor do apontador "geocodigo" para o campo "geocodigo" do novo n�
			strcpy(novo->estadoaluguer, estadoaluguer);
			novo->seguinte = inicio;
			return(novo); // Devolve o novo n� inserido na lista ligada 
		}
	}
	else return(inicio);  // Retorna o in�cio da lista ligada sem modificar a estrutura
}

int existeMeio(Meio* inicio, int codigo)
{
	while (inicio != NULL) //Enquanto "inicio" nao for nulo
	{
		if (inicio->codigo == codigo) //Se o apontador "inicio->codigo" for igual a "codigo"
		{
			return(1); // Se ja existir retorna 1
		}
		inicio = inicio->seguinte;// Avan�a para o proximo elemento da lista ligada
	}
	return(0); //Se nao existir retorna 0
}

void listarMeios(Meio* inicio)
{

	while (inicio != NULL) //percorre a lista ligada enquanto "inicio" nao for nulo
	{

		printf("%d, %s, %.2f, %.2f, %.2f, %s, %s ", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo, inicio->estadoaluguer); // Mostra cada parametro da lista ligada

		inicio = inicio->seguinte; // Atualiza o apontador "inicio" para apontar para o pr�ximo elemento da lista ligada
	}

}


Meio* eliminarMeio(Meio* inicio, int codigo)
{
	if (inicio == NULL) {
		return NULL; //retorna NULL se a lista estiver vazia
	}
	else if (inicio->codigo == codigo)
	{
		Meio* aux = inicio->seguinte; // Armazena o apontador, para o proximo da lista ligada
		free(inicio); // Liberta a memoria de "inicio"
		return aux; //retorna o apontador para o pr�ximo elemento da lista, que agora � o novo in�cio
	}
	else {
		inicio->seguinte = eliminarMeio(inicio->seguinte, codigo); //recursivamente percorre a lista at� encontrar o elemento a eliminar

		return inicio; //retorna o apontador para o in�cio da lista
	}
}

void listagemGeoCodigo(Meio* inicio, char geocodigo[])
{
	while (inicio != NULL) // Enquanto "inicio" nao for nulo
	{
		if (stricmp(inicio->geocodigo, geocodigo) == 0) // Compara o apontador "inicio->geocodigo"
		{
			printf("%d, %s, %.2f, %.2f, %f, %s, %s", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo, inicio->estadoaluguer); // Mostra cada parametro da lista ligada
		}
		inicio = inicio->seguinte; //Avan�a para o proximo elemento da lista ligada
	}

}


void trocar(Meio* a, Meio* b) {

	Meio aux = *a; // Cria uma c�pia de "a" em "aux"
	*a = *b; // Copia o conte�do de "b" para "a"
	*b = aux; // Copia o conte�do de "aux" para "b"
}


void listarOrdemDecrescenteAutonomia(Meio* inicio) {
	int aux = 1;
	Meio* atual = inicio; // apontador "atual" come�a apontando para o in�cio da lista
	Meio* seguinte = NULL; // apontador "seguinte" aponta para o endere�o vazio da mem�ria da lista lista


	// Verifica se a lista est� vazia
	if (atual == NULL) {
		printf("A lista esta vazia!\n");
		return;
	}

	// Enquanto houver trocas a serem feitas
	while (aux) {
		aux = 0;
		atual = inicio;
		// Percorre a lista
		while (atual->seguinte != seguinte) {
			// Se a autonomia do meio atual for menor que a autonomia do meio seguinte, troca os meios de posi��o
			if (atual->autonomia < atual->seguinte->autonomia) {
				trocar(atual, atual->seguinte); // Chama a fun��o trocar para inverter os meios
				aux = 1; // Sinaliza que houve uma troca
			}
			atual = atual->seguinte; // Avan�a para o proximo parametro da lista ligada
		}
		seguinte = atual; // Seguinte toma o valor de atual 
	}

	// Lista os meios em ordem decrescente de autonomia
	listarMeios(inicio);
}

int registoAluguer(Meio* inicio, int codigo)
{
	// Percorre a lista de meios enquanto n�o chega ao final
	while (inicio != NULL) {

		// Se o meio com o c�digo correspondente foi encontrado
		if (inicio->codigo == codigo) {

			// Se o meio ainda n�o est� alugado
			if (stricmp(inicio->estadoaluguer, "Est� alugado") != 0) {

				// Altera o estado de aluguer do meio para "Est� alugado"
				strcpy(inicio->estadoaluguer, "Est� alugado");
				return 1;
			}
			else {
				return 0; // Retorna 0 se o meio j� est� alugado
			}
		}

		inicio = inicio->seguinte; // Avan�a para o pr�ximo meio na lista
	}

	return -1; // Retorna -1 se o meio n�o foi encontrado na lista ligada
}

Meio* alterarMeio(Meio* inicio, int codigo, char tipo[], float bat, float aut, float custo, char geocodigo[], char estadoaluguer[])
{
	Meio* aux = inicio; // Apontador que recebe o inicio da lista ligada
	while (aux != NULL) // Enquanto o apontador "aux"  nao for nulo
	{
		if (aux->codigo == codigo); //Se o apontador "aux->codigo" for igual a codigo
		{
			aux->codigo = codigo;// Atribui o valor "codigo" ao campo "codigo" do novo n�
			strcpy(aux->tipo, tipo); // Copia o apontador "tipo" para o apontador "tipo"
			aux->bateria = bat;
			aux->autonomia = aut; // Atribui o valor "aut" ao campo "autonomia" do novo n�
			aux->custo = custo;
			strcpy(aux->geocodigo, geocodigo); // Copia o apontador "geocodigo" para o apontador "geocodigo"
			strcpy(aux->estadoaluguer, estadoaluguer); // Copia o apontador "estadoaluguer" para o apontador "aux->estadoaluguer"
		}
		aux = aux->seguinte; // Avan�a para o proximo parametro da lista ligada
	}
	return inicio; // Retorna o apontador para o inicio da lista
}

Cliente* inserirCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo) {

	//Verifica se existe um cliente com  o mesmo nome na lista ligada
	if (!existeCliente(inicio->nome, nome))
	{
		Cliente* novo = malloc(sizeof(struct registoCliente)); // Aloca o espa�o na memoria para o novo cliente

		// Verifica se foi poss�vel alocar mem�ria para o novo cliente
		if (novo != NULL)
		{
			strcpy(novo->nome, nome); // Copia o apontador "nome" para o apontador "nome"
			strcpy(novo->morada, morada); // Copia o apontador "morada" para o apontador "morada"
			novo->nif = nif;
			novo->saldo = saldo; // Atribui o valor "saldo" ao campo "saldo" do novo n� 
			novo->seguinte = inicio;  // Atribui o valor "inicio" ao campo "seguinte" do novo n�  
			return(novo); // Retorna o novo in�cio da lista ligada, que agora � o novo n� adicionado
		}
	}
	else return(inicio); // Se existir um cliente com o mesmo nome, retorna para o inicio da lista ligada
}

int existeCliente(Cliente* inicio, char nome[])
{

	while (inicio != NULL) // Percorre a lista ligada de clientes at� ao final
	{
		if (stricmp(inicio->nome, nome)) // Se os nomes forem iguais, retorna 1
		{
			return 1;

		}
		inicio = inicio->seguinte; // Se os nomes n�o forem iguais, avan�a para o pr�ximo cliente da lista
	}
	return 0; // Se n�o encontrar nenhum cliente com o mesmo nome, retorna 0
}

Cliente* eliminarCliente(Cliente* inicio, char nome)
{
	if (inicio == NULL) { // Verifica se a lista esta vazia
		return NULL;
	}
	else if (inicio->nome == nome)
	{
		Cliente* aux = inicio->seguinte; /// Armazena o apontador da lista ligada
		free(inicio); // Liberta a memoria de "inicio"
		return aux; // Devolve o apontador da lista ligada
	}
	else {
		inicio->seguinte = eliminarCliente(inicio->seguinte, nome); // Chama a fun��o e armazena o apontadores para o pr�ximo elemento na vari�vel "seguinte".
		return inicio; // Retorna o apontador para o in�cio da lista
	}
}

void listarClientes(Cliente* inicio)
{
	while (inicio != NULL) // Percorre a lista ligada ate ao final
	{
		printf("%s, %s, %d, %.2f \n", inicio->nome, inicio->morada, inicio->nif, inicio->saldo); //Mostra os parametros da lista ligada
		inicio = inicio->seguinte; // Avan�a para o proximo parametro da lista ligada
	}
}

int armazenarCliente(Cliente* inicio)
{
	FILE* fp; //Apontador "FILE", para manipular a leitura e escrita em ficheiros
	fp = fopen("cliente.txt", "w"); // Cria e abre o ficheiro "cliente.txt" em modo de escrita ("w") com o apontador "fp"
	if (fp != NULL) // Verifica se o ficheiro foi aberto corretamente
	{
		Cliente* aux = inicio; //Apontador "aux" para percorrer a lista ligada
		while (aux != NULL) // Enquanto o apontador "aux" n�o chegar ao fim da lista
		{
			fprintf(fp, "%s;%s;%d;%.2f;\n", aux->nome, aux->morada, aux->nif, aux->saldo); // Mostra os campos da lista ligada
			aux = aux->seguinte; // Avan�a para o proximo parametro da lista ligada
		}
		fclose(fp); //fecha o ficheiro
		return(1); // Devolve 1 indicando que foi realizado com sucesso
	}
	else return(0); // Retorna 0 indicando que ocorreu um erro ao abrir o ficheiro
}


Cliente* lerClientes()
{
	FILE* fp; //Apontador "FILE", para manipular a leitura e escrita em ficheiros
	int nif; //definir variaveis...
	float saldo;
	char nome[50], morada[50];
	Cliente* aux = NULL; //Apontador "aux" come�a por ser nulo
	fp = fopen("cliente.txt", "r"); // Cria e abre o ficheiro "cliente.txt" em modo de leitura ("r") com o apontador "fp"
	if (fp != NULL) // Verifica se o ficheiro foi aberto corretamente
	{
		while (!feof(fp)) // Entra no "loop" de repeti��o enquanto n�o chegar ao final do ficheiro "fp"
		{
			fscanf(fp, "%[^;]; %[^\n]\n%d;%f\n", nome, morada, &nif, &saldo);// Le cada parametro da lista ligada
			aux = inserirCliente(aux, nome, morada, nif, saldo); // Insere um novo cliente na lista ligada com os dados lidos do ficheiro
		}
		fclose(fp); //fecha o ficheiro
	}
	return(aux);
}

Cliente* alterarCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo)
{
	Cliente* aux = inicio; // Apontador "aux" tem o valor do inicio da lista ligada
	while (aux != NULL) //Enquanto "aux" nao for nulo
	{
		if (!existeCliente(aux->nome, nome)) // Verifica se existe cliente com o mesmo nome na lista
		{
			strcpy(aux->nome, nome); // Copia o apontador "nome" para o apontador "nome"
			strcpy(aux->morada, morada); //Copia o apontador "morada" para o apontador "morada"
			aux->nif = nif;
			aux->saldo = saldo; // Atribui o valor "nif" ao campo "nif" do novo n�
			return(inicio);
		}
		aux = aux->seguinte;
	}
	return aux; //Retorna NULL caso nenhum cliente com o nome especificado seja encontrado na lista.
}

// A fun��o l� os dados do arquivo "gestor.txt" e retorna um ponteiro para o in�cio da lista ligada de gestores.
Gestor* lerGestor()
{
	FILE* fp; // Apontador para o arquivo
	Gestor* aux = NULL; // Ponteiro para o in�cio da lista ligada de gestores
	float codigogestor; // Vari�vel para armazenar o c�digo do gestor lido do arquivo
	char nomegestor[30], passe[20]; // Vari�veis para armazenar o nome e a senha do gestor lidos do arquivo

	// Abrir o arquivo "gestor.txt" em modo de leitura
	fp = fopen("gestor.txt", "r");
	if (fp == NULL) // Verificar se o ficheiro foi aberto com sucesso
	{
		printf("Erro ao abrir o arquivo gestor.txt\n");
		return NULL; // Retorna NULL se ocorrer um erro ao abrir o ficheiro
	}

	// Loop para ler cada linha do arquivo
	while (fscanf(fp, "%[^,],%f,%s\n", nomegestor, &codigogestor, passe) == 3)
	{
		// Chama a fun��o "inserirGestor()" para inserir um novo n� na lista ligada com os dados lidos do arquivo
		aux = inserirGestor(aux, nomegestor, codigogestor, passe);
	}

	fclose(fp); // Fecha o ficheiro ap�s a leitura
	return aux; // Retorna o apontador para o in�cio da lista ligada atualizada
}


Gestor* inserirGestor(Gestor* inicio, char nomegestor[], float codigo, char passe[])
{
	if (!existeGestor(inicio->nomegestor, nomegestor)) //Verifica se n�o existe um gestor com o nome "nomegestor" na lista ligada de gestores que � apontado por "inicio".
	{
		Gestor* novo = malloc(sizeof(struct registoGestor));

		if (novo != NULL) //Se novo nao for nulo
		{
			strcpy(novo->nomegestor, nomegestor); // Copia a as strings apontadas pelos apontadores
			novo->codigogestor = codigo;
			strcpy(novo->passe, passe); // Copia as strings apontadas pelos apontadores
			novo->seguinte = inicio;
			return(novo); // Retorna o novo in�cio da lista
		}
	}
	else return(inicio); // Se j� existe um gestor com o mesmo nome, retorna o in�cio da lista original sem altera��es.
}

int existeGestor(Gestor* inicio, char nome[])
{
	int valor;
	while (inicio != NULL) //enquanto o inicio nao for nulo...
	{
		if (stricmp(inicio->nomegestor, nome)) //Compara as strings apontadas pelos apontadores
		{
			return 1;
		}
		inicio = inicio->seguinte; // Avan�a para o proximo parametro da lista ligada
	}
	return 0;
}

int armazenarGestor(Gestor* inicio)
{
	FILE* fp; // Apontador "FILE", para manipular a leitura e escrita em ficheiros
	fp = fopen("gestor.txt", "w"); //Abre o ficheiro "gestor.txt" em modo escrita

	if (fp != NULL) // se "fp" nao for nulo
	{
		Gestor* aux = inicio;
		while (aux != NULL) {
			fprintf(fp, "%s;%.2f;%s;\n", aux->nomegestor, aux->codigogestor, aux->passe); //Mostra conteudo da lista ligada
			aux = aux->seguinte;  // Avan�a para o pr�ximo elemento da lista ligada.
		}
		fclose(fp); // fecha o ficheiro
		return(1); // Retorna 1 para indicar que os dados foram armazenados com sucesso.
	}
	else return(0); // Se n�o conseguir abrir o ficheiro, retorna 0 para indicar que houve um erro no processo.
}

void listarGestor(Gestor* inicio)
{
	while (inicio != NULL) //enquanto o inicio nao for nulo...
	{
		printf("%.*s, %.2f, %s\n", 15, inicio->nomegestor, inicio->codigogestor, inicio->passe);//Mostra os campos da lista ligada
		inicio = inicio->seguinte; // Avan�a para o proximo parametro da lista ligada
	}
}

Gestor* eliminarGestor(Gestor* inicio, char nome)
{
	if (inicio == NULL) // Verifica se o apontador "inicio" � nulo
		return(NULL);
	else if (inicio->nomegestor == nome) // Verifica se o nome do gestor apontado por "inicio" � igual ao nome passado como par�metro
	{
		Cliente* aux = inicio->seguinte;
		free(inicio); // Liberta a memoria de "inicio"
		return aux;
	}
	else {
		inicio->seguinte = eliminarGestor(inicio->seguinte, nome); // Chama a fun��o e armazena o apontadores para o pr�ximo elemento na vari�vel "seguinte".
		return inicio;
	}
}

Gestor* alterarGestor(Gestor* inicio, char nomegestor[], float codigogestor, char passe[])
{
	while (inicio != NULL) //enquanto o inicio nao for nulo...
	{
		if (!existeGestor(inicio, nomegestor)) // verifica se n�o existe um determinado valor dO "nomegestor" numa lista ligad referenciada por "inicio". 
		{
			strcpy(inicio->nomegestor, nomegestor); //Copia o conte�do da vari�vel "nomegestor" para o campo "nomegestor" da lista ligada "inicio". 
			inicio->codigogestor = codigogestor; //Atribui o valor da vari�vel "codigogestor" ao campo "codigogestor" da lista ligada por "inicio".
			strcpy(inicio->passe, passe);
			return(inicio);
		}
		inicio = inicio->seguinte; // Avan�a para o proximo parametro da lista ligada
	}
	return inicio;

}