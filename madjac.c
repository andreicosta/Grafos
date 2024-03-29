//ideias para uma matriz de adjacencia e alguns algoritmos relativos a ela

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//implementação fica a gosto do cara
#include "matriz.h"
#include "pilha.h"
#include "heap.h"
#include "cdisj.h"
#include "fila.h"

struct matrizadjacencia * criamatrizadjacencia(int tamanhoinicial){
	int i, j;
	struct matrizadjacencia * novo = (struct matrizadjacencia *) malloc(sizeof(struct matrizadjacencia));
	
	if(novo == NULL || tamanhoinicial <= 0){
		return NULL;
	}
	
	novo->vetor = (char **) malloc(sizeof(char *) * tamanhoinicial);
	novo->matriz = (int **) malloc(sizeof(int *) * tamanhoinicial);

	if(novo->vetor == NULL || novo->matriz == NULL){
		return NULL;
	}

	for(i = 0 ; i < tamanhoinicial ; i++){
		novo->vetor[i] = NULL;
		novo->matriz[i] = (int *) malloc(sizeof(int) * tamanhoinicial);
		if(novo->matriz[i] == NULL){
			return NULL;
		}
		for(j = 0 ; j < tamanhoinicial ; j++){
			novo->matriz[i][j] = 0;
		}
	}
	
	novo->tamanho = tamanhoinicial;
	
	return novo;
}

int adicionavertice(struct matrizadjacencia * matriz, int id, char * nome){
	if(matriz == NULL || matriz->vetor == NULL || nome == NULL || matriz->tamanho <= id || id < 0)
		return 0;
	
	matriz->vetor[id] = (char *) malloc(sizeof(char)*50);
	strcpy(matriz->vetor[id],nome);
	return 1;
}

int delete(struct matrizadjacencia * matriz, int id){
	if(matriz->tamanho <= id || matriz->vetor[id] == NULL || id < 0){
		printf("{\"delete\":{\"ID\":%d,\"resposta\":\"falha\"}}\n", id);
		return 0;
	}
	
	matriz->vetor[id] = NULL;
	printf("{\"delete\":{\"ID\":%d,\"resposta\":\"sucesso\"}}\n", id);
	return 1;
}

int vizinhos(struct matrizadjacencia * matriz, int id, int direcionado){
	if(matriz->vetor[id] == NULL || matriz->tamanho <= id || id < 0){
		printf("{\"vizinhos\":{\"ID\":%d, \"resposta\":\"falha\", \"vizinhos\":[]}}\n", id);
		return 0;
	}
	
	int cont = 0, i, * lista = malloc(sizeof(int) * matriz->tamanho + 1), primeiro = 1;
	
	if(direcionado){
		for(i = 0 ; i < matriz->tamanho ; i++)
			if((matriz->matriz[id][i] > 0 || matriz->matriz[i][id] > 0) && matriz->vetor[i] != NULL)
				lista[cont++] = i;
	}
	else{
		for(i = 0 ; i < matriz->tamanho ; i++)
			if(matriz->matriz[id][i] && matriz->vetor[i] != NULL)
				lista[cont++] = i;
	}
	lista[cont] = -1;
	
	printf("{\"vizinhos\":{\"ID\":%d, \"resposta\":\"sucesso\", \"vizinhos\":[", id);
	for(i = 0 ; lista[i] != -1 ; i++){
		if(primeiro){
			primeiro = 0;
			printf("%d", lista[i]);
		}
		else
			printf(",%d", lista[i]);
	}
	printf("]}}\n");
	return 1;
}

int conexao(struct matrizadjacencia * matriz, int aux1, int aux2){
	if(matriz->vetor[aux1] == NULL || matriz->tamanho <= aux1){
		printf("{\"conexao\":{\"ID1\":%d, \"ID2\":%d, \"resposta\":\"falha\", \"conexao\":\"\"}}\n", aux1, aux2);
		return 0;
	}
	
	if(matriz->vetor[aux2] == NULL || matriz->tamanho <= aux2){
		printf("{\"conexao\":{\"ID1\":%d, \"ID2\":%d, \"resposta\":\"falha\", \"conexao\":\"\"}}\n", aux1, aux2);
		return 0;
	}
	
	if(matriz->matriz[aux1][aux2] || matriz->matriz[aux2][aux1]){
		printf("{\"conexao\":{\"ID1\":%d, \"ID2\":%d, \"resposta\":\"sucesso\", \"conexao\":\"sim\"}}", aux1, aux2);
		return 1;
	}
	
	printf("{\"conexao\":{\"ID1\":%d, \"ID2\":%d, \"resposta\":\"sucesso\", \"conexao\":\"nao\"}}", aux1, aux2);	
	return 0;
}

int conexaosemprint(struct matrizadjacencia * matriz, int aux1, int aux2){
	if(matriz->vetor[aux1] == NULL || matriz->tamanho <= aux1){
		return 0;
	}
	
	if(matriz->vetor[aux2] == NULL || matriz->tamanho <= aux2){
		return 0;
	}
	
	if(matriz->matriz[aux1][aux2]){
		return 1;
	}
	
	return 0;
}

int get(struct matrizadjacencia * matriz, int id){
	if(matriz->tamanho <= id || matriz->vetor[id] == NULL){
		printf("{\"vertice\":{\"ID\":%d, \"dado\":\"\", \"resposta\":\"falha\"}}\n", id);
		return 0;
	}
	
	printf("{\"vertice\":{\"ID\":%d, \"dado\":%s, \"resposta\":\"sucesso\"}}\n", id, matriz->vetor[id]);
	return 1;
}

int adicionaaresta(struct matrizadjacencia * matriz, int v1, int v2, int peso, int direcionado){
	if(matriz == NULL || matriz->vetor == NULL || matriz->vetor[v1] == NULL || matriz->vetor[v2] == NULL || matriz->tamanho <= v1 || matriz->tamanho <= v2){
		return 0;
	}
	
	if(direcionado == 1){
		matriz->matriz[v1][v2] = peso;
	}
	if(direcionado == 0){
		matriz->matriz[v1][v2] = peso;
		matriz->matriz[v2][v1] = peso;
	}
	return 1;
}

int imprimematrizadjacencia(struct matrizadjacencia * matriz){
	int i, j;
	
	if(matriz == NULL || matriz->vetor == NULL || matriz->matriz == NULL){
		printf("Imprime: Matriz nula\n");
		return -1;
	}
	
	printf("tam: %d\n\n", matriz->tamanho);
	for(i = 0 ; i < matriz->tamanho ; i++){
		printf("%d: %s  ", i, matriz->vetor[i]);
	}
	printf("\n");
	
	for(i = 0 ; i < matriz->tamanho ; i++){
		printf("\n");
		for(j = 0 ; j < matriz->tamanho ; j++)
			printf("%d\t", matriz->matriz[i][j]);
	}
	printf("\n");
	
	return 1;
}

int verificagrau(struct matrizadjacencia * matriz, int vertice){
	if(matriz == NULL || matriz->vetor == NULL || matriz->matriz == NULL || vertice < 0 || vertice >= matriz->tamanho){
		return -1;
	}
	
	int i;
	
	for(i = 0 ; i < matriz->tamanho ; i++){
		if(matriz->matriz[i][vertice]){
			return 1;
		}
	}

	return 0;
}

//se os elementos estiverem no mesmo nível topológico eles serão impressos de forma crescente pelo seu número de id
int ordemtopologica(struct matrizadjacencia * matriz){
	if(matriz == NULL || matriz->matriz == NULL || matriz->vetor == NULL){
		return 0;
	}
	
	Queue s = CreateQueue(matriz->tamanho);
	int jausado[matriz->tamanho], l[matriz->tamanho];
	register int j, i, ltam = 0;
	struct matrizadjacencia * novamatriz = criamatrizadjacencia(matriz->tamanho);
	
	if(novamatriz == NULL){
		return 0;
	}
	
	for(i = 0 ; i < novamatriz->tamanho ; i++){
		jausado[i] = 0;
		for(j = 0 ; j < novamatriz->tamanho ; j++){
			if(matriz->vetor[i] != NULL && matriz->vetor[j] != NULL){
				novamatriz->matriz[i][j] = matriz->matriz[i][j];
			}
		}
	}
	
	while(ltam <= novamatriz->tamanho){
		for(i = 0 ; i < novamatriz->tamanho ; i++){
			if(matriz->vetor[i] != NULL && verificagrau(novamatriz, i) == 0 && jausado[i] == 0){
				Enqueue(i, s);
				jausado[i] = 1;
			}
		}
		
		if(IsEmpty(s)){
			break;
		}
		
		while(!IsEmpty(s)){
			l[ltam] = FrontAndDequeue(s);
			
			for(i = 0 ; i < novamatriz->tamanho ; i++){
				novamatriz->matriz[l[ltam]][i] = 0;
			}
			ltam++;
		}
	}
	
	if(ltam > 0){
		ltam--;
		printf("{\"ordemtop\":[");
		for(i = 0 ; i < ltam ; i++){
			printf("%d,", l[i]);
		}
		printf("%d]}\n", l[i]);
	}	

	DisposeQueue(s);
	free(novamatriz);
	return 1;
}

int merge(struct aresta * vetor, int tamanho) {
	int i, j, k;
	aresta * temp = malloc(sizeof(aresta) * tamanho);

	if(temp == NULL || vetor == NULL){
		return 0;
	}

	i = 0;
	j = tamanho/2;
	k = 0;
	while(i < tamanho/2 && j < tamanho){
		if(vetor[i].peso < vetor[j].peso){
			temp[k++] = vetor[i++];
		}
		else{
			temp[k++] = vetor[j++];
		}
	}
 
	if(i == tamanho/2){
		while(j < tamanho){
			temp[k++] = vetor[j++];
		}
	}
	else{
		while(i < tamanho/2){
			temp[k++] = vetor[i++];
		}
	}
 
	for(i = 0; i < tamanho; ++i){
		vetor[i] = temp[i];
	}
	return 1;
}
 
int mergesort(struct aresta * vetor, int tamanho) {
	if(vetor == NULL){
		return 0;
	}
	
	if(tamanho > 1){
		mergesort(vetor, tamanho/2);
		mergesort(vetor + tamanho/2, tamanho - tamanho/2);
		merge(vetor, tamanho);
	}
	
	return 1;
}

struct vetoraresta * arestasordenadas(struct vetoraresta * vetor){
	if(vetor == NULL || vetor->comeco == NULL){
		return NULL;
	}

	mergesort(vetor->comeco, vetor->tamanho);
	
	return vetor;
}

struct vetoraresta * pegaarestas(struct matrizadjacencia * matriz){
	if(matriz == NULL || matriz->vetor == NULL || matriz->matriz == NULL){
		return NULL;
	}
	int i, j, tamanho = 0, cont = 0;
	int * help1 = malloc(sizeof(int) * matriz->tamanho * matriz->tamanho);
	int * help2 = malloc(sizeof(int) * matriz->tamanho * matriz->tamanho);
	
	if(help1 == NULL || help2 == NULL){
		return NULL;
	}
	
	for(i = 0 ; i < matriz->tamanho ; i++){
		for(j = 0 ; j < matriz->tamanho ; j++){
			if(matriz->matriz[i][j] && matriz->vetor[i] != NULL && matriz->vetor[j] != NULL){
				help1[tamanho] = i;
				help2[tamanho++] = j;
			}
		}
	}
	
	vetoraresta * arestas = malloc(sizeof(vetoraresta));
	arestas->tamanho = tamanho;
	arestas->comeco = malloc(sizeof(aresta) * tamanho);
	aresta * temp = arestas->comeco;
	
	if(temp == NULL || arestas == NULL){
		return NULL;
	}
	
	for(i = 0 ; i < tamanho ; i++){
		temp[cont].v1 = help1[cont];
		temp[cont].v2 = help2[cont];
		temp[cont].peso = matriz->matriz[help1[cont]][help2[cont]];
		cont++;
	}
	
	free(help1);
	free(help2);
	return arestas;
}

int kruskal(struct matrizadjacencia * matriz, struct vetoraresta * arestas){	
	if(matriz == NULL || matriz->matriz == NULL || matriz->vetor == NULL || arestas == NULL){
		return 0;
	}
	
	int * ta = malloc(sizeof(int) * matriz->tamanho * matriz->tamanho);
	int * tb = malloc(sizeof(int) * matriz->tamanho * matriz->tamanho);
	int tamt = 0, i, custo = 0;
	struct cdisj * cd = initcdisj(matriz->tamanho);
	struct aresta * lista = arestas->comeco;
	
	for(i = 0 ; i < matriz->tamanho ; i++){
		makeset(cd, i);
	}
	
	for(i = 0; i < arestas->tamanho ; i++){
		if(find(cd, lista[i].v1) != find(cd, lista[i].v2)){
			ta[tamt] = lista[i].v1;
			tb[tamt++] = lista[i].v2;
			custo += lista[i].peso;
			unionc(cd, lista[i].v1, lista[i].v2);
		}
	}
	
	printf("{\"arvoreminima\":{\"arestas\":[");
	for(i = 0 ; i < tamt - 1 ; i++){
		printf("(%d,%d),", ta[i], tb[i]);
	}
	printf("(%d,%d)], \"custo\":%d}}\n", ta[tamt-1], tb[tamt-1], custo);

	free(lista);
	free(cd);
	return 1;
}

int dijkstra(struct matrizadjacencia * matriz, int source, int target){
	if(matriz == NULL || matriz->matriz == NULL || matriz->vetor == NULL || source < 0 || target < 0 || source >= matriz->tamanho || target >= matriz->tamanho){
		return 0;
	}
	register int infinito = 2147483647, i, u;
	int dist[matriz->tamanho], previous[matriz->tamanho];
	struct descheap * q = initheap(matriz->tamanho + 2);

	for(i = 0 ; i < matriz->tamanho ; i++){
		if(matriz->vetor[i] != NULL){
			dist[i] = infinito;
			previous[i] = -1;
			insereheap(q, &dist[i], i);
		}
	}
	dist[source] = 0;
	heapando(q, 1);
	
	while(q->elementos){
		heapando(q, 1);
		u = deleteheap(q);
		
		if(u <= -1 || u >= matriz->tamanho || dist[u] == infinito || dist[u] < 0 ){
			break;
		}
		
		for(i = 0 ; i < matriz->tamanho ; i++){
			if(conexaosemprint(matriz, u, i)){
				if(dist[i] > dist[u] + matriz->matriz[u][i]){
					dist[i] = dist[u] + matriz->matriz[u][i];
					previous[i] = u;
				}
			}
		}
		
		if(u == target){
			break;
		}
	}

	if(dist[target] != infinito){
		descpilha * resposta = initpilha();
		i = target;
		while(i != source){
			push(i, resposta);
			i = previous[i];
		}
		push(source, resposta);
		printf("{\"menorcaminho\":{\"ID1\":%d, \"ID2\":%d, \"caminho\":[", source, target);
		while(resposta->tamanho > 1){
			printf("%d,", pop(resposta));
		}
		printf("%d],\"custo\":%d}}\n", pop(resposta), dist[target]);
		free(resposta);
	}
	else{
		printf("{\"menorcaminho\":{\"ID1\":%d, \"ID2\":%d, \"caminho\":[],\"custo\":}}\n", source, target);
	}
	
	free(q);
	return 1;
}