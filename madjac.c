//ideias para uma matriz de adjacencia e alguns algoritmos relativos a ela

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrizadjacencia * criamatrizadjacencia(int tamanhoinicial){
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
	if(matriz == NULL || matriz->vetor == NULL || nome == NULL || matriz->tamanho <= id)
		return -1;
	
	matriz->vetor[id] = (char *) malloc(sizeof(char)*50);
	strcpy(matriz->vetor[id],nome);
	return 1;
}

int delete(struct matrizadjacencia * matriz, int id){
	if(matriz->tamanho <= id || matriz->vetor[id] == NULL){
		printf("{\"delete\":{\"ID\":%d,\"resposta\":\"falha\"}}\n", id);
		return -1;
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
		for(i=0;i<matriz->tamanho;i++)
			if((matriz->matriz[id][i] > 0 || matriz->matriz[i][id] > 0) && matriz->vetor[i] != NULL)
				lista[cont++] = i;
	}
	else{
		for(i=0;i<matriz->tamanho;i++)
			if(matriz->matriz[id][i] > 0 && matriz->vetor[i] != NULL)
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
	if(matriz == NULL || matriz->vetor == NULL || matriz->vetor[v1] == NULL || matriz->vetor[v2] == NULL || matriz->tamanho <= v1 || matriz->tamanho <= v2)
		return 0;
	
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

int verificagrau(struct aresta * arestas, int vertice){
	int cont = 0, i = 0;
	
	while(arestas[i].v1 != -1){
		if(arestas[i++].v2 == vertice){
			cont++;
		}
	}
	
	return cont;
}

int ordemtopologica(struct matrizadjacencia * matriz){
	fila * s = initfila();
	aresta * arestas = pegaarestas(matriz);
	int i, aux, arestastam, l[matriz->tamanho], ltam = 0;
		
	for(i = 0 ; i < matriz->tamanho ; i++){
		if(verificagrau(arestas, i) == 0){
			filainsere(i, s);
		}
	}
	
	for(i = 0 ; arestas[i].v1 != -1 ; i++){
	}
	arestastam = i;

	while(s->tamanho > 0){
		l[ltam++] = filaretira(s);
		
		for(i = 0 ; i < arestastam ; i++){
			if(arestas[i].v1 == l[ltam-1]){
				arestas[i].v1 = -2;
				aux = arestas[i].v2;
				arestas[i].v2 = -2;
				if(verificagrau(arestas, aux) == 0){
					filainsere(aux, s);
				}
			}
		}
	}
	ltam--;

	for(i = 0 ; i < arestastam ; i++){
		if(arestas[i].v1 > -1){
			return -1;
		}
	}
	
	printf("{\"ordemtop\":[");
	for(i=0;i<ltam;i++){
		printf("%d,", l[i]);
	}
	printf("%d]}\n", l[i]);
	
	free(s);
	return 1;
}

void merge(aresta * vetor, int tamanho) {
	int i, j, k;
	aresta * temp;
 
	temp = malloc(sizeof(aresta) * tamanho);
 
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
}
 
void mergesort(aresta * vetor, int tamanho) {
	if(tamanho > 1){
		mergesort(vetor, tamanho/2);
		mergesort(vetor + tamanho/2, tamanho - tamanho/2);
		merge(vetor, tamanho);
	}
}

aresta * arestasordenadas(struct aresta * vetor){
	int tamanho;
	
	for(tamanho = 0 ; vetor[tamanho].v1 != -1 && vetor[tamanho].v2 != -1 && vetor[tamanho].peso != -1 && vetor!=NULL; tamanho++){
	}
	
	mergesort(vetor, tamanho);
	
	return vetor;
}

aresta * pegaarestas(struct matrizadjacencia * matriz){
	int i, j, tamanho = 0, cont = 0;
	
	for(i = 0 ; i < matriz->tamanho ; i++){
		for(j = 0 ; j < matriz->tamanho ; j++){
			if(matriz->matriz[i][j] > 0 && matriz->vetor[i] != NULL && matriz->vetor[j] != NULL){
				tamanho++;
			}
		}
	}
	aresta * arestas = malloc(sizeof(aresta) * tamanho + 2);
	for(i = 0 ; i < matriz->tamanho ; i++){
		for(j = 0 ; j < matriz->tamanho ; j++){
			if(matriz->matriz[i][j] > 0 && matriz->vetor[i] != NULL && matriz->vetor[j] != NULL){
				arestas[cont].v1 = i;
				arestas[cont].v2 = j;
				arestas[cont++].peso = matriz->matriz[i][j];
			}
		}
	}
	arestas[tamanho].v1 = -1;
	arestas[tamanho].v2 = -1;
	arestas[tamanho].peso = -1;
	
	return arestas;
}

int kruskal(struct matrizadjacencia * matriz, struct aresta * arestas){
	aresta * t = malloc(sizeof(aresta) * matriz->tamanho * matriz->tamanho);
	int tamt = 0, i, custo = 0;
	descpilha * pilha = initpilha();
	cdisj * cd = initcdisj(matriz->tamanho);

	for(i = 0 ; i < matriz->tamanho ; i++){
		makeset(cd, i);
	}
	
	for(i = 0; arestas[i].v1 != -1 && arestas[i].v2 != -1 && arestas[i].peso != -1 ; i++){
		if(find(cd, arestas[i].v1) != find(cd, arestas[i].v2)){
			t[tamt++] = arestas[i];
			custo += arestas[i].peso;
			unionc(cd, arestas[i].v1, arestas[i].v2);
		}
	}
	
	printf("{\"arvoreminima\":{\"arestas\":[");
	for(i = 0 ; i < tamt - 1 ; i++){
		printf("(%d,%d),", t[i].v1, t[i].v2);
	}
	printf("(%d,%d)],\"custo\":%d}}\n", t[tamt-1].v1, t[tamt-1].v2, custo);

	free(cd);
	free(pilha);
	return 1;
}

int dijkstra(struct matrizadjacencia * matriz, int source, int target){
	int infinito = 2147483647, i, dist[matriz->tamanho], previous[matriz->tamanho], u, hacaminho = 0;
	struct descheap * q = initheap(matriz->tamanho + 2);

	for(i = 0 ; i < matriz->tamanho ; i++){
		dist[i] = infinito;
		previous[i] = -1;
		insereheap(q, &dist[i], i);
	}
	dist[source] = 0;
	setvalor(q, &dist[source], source);
	
	while(q->elementos > 0 && hacaminho == 0){
		u = deleteheap(q);
		
		if(u == target){
			hacaminho = 1;
		}
		
		if(u == -1){
			return -1;
		}
		
		if(dist[u] == infinito && hacaminho == 0){
			break;
		}
		
		for(i = 0 ; i < matriz->tamanho ; i++){
			if(conexaosemprint(matriz, u, i)){
				if(dist[i] > dist[u] + matriz->matriz[u][i]){
					dist[i] = dist[u] + matriz->matriz[u][i];
					setvalor(q, &dist[i], i);
					previous[i] = u;
				}
			}
		}
	}
	
	if(hacaminho){
		descpilha * resposta = initpilha();
		i = target;
		while(i != source){
			push(i, resposta);
			i = previous[i];
		}
		push(source, resposta);
		printf("{\"menorcaminho\":{\"ID1\":%d, \"ID2\":%d,\"caminho\":[", source, target);
		while(resposta->tamanho > 1){
			printf("%d,", pop(resposta));
		}
		printf("%d],\"custo\":%d}}\n", pop(resposta), dist[target]);
		free(resposta);
	}
	else{
		printf("{\"menorcaminho\":{\"ID1\":%d, \"ID2\":%d,\"caminho\":[],\"custo\":}}\n", source, target);
	}

	free(q);
	return 1;
}

int leitor(){
	int n, i, onde, direcionado = -1, v1, v2, peso, aux1, aux2;
	char * lido = malloc(sizeof(char) * 10), * nome = malloc(sizeof(char) * 50);
	matrizadjacencia * matriz = NULL;

	scanf("%s", lido);

	if(!strcmp(lido, "*Vertices")){
		scanf("%d", &n);
		matriz = criamatrizadjacencia(n);
		for(i = 0 ; i < n ; i++){
			scanf("%d", &onde);
			scanf("%[ ]", nome);
			scanf("%[^\n]", nome);
			adicionavertice(matriz, onde, nome);
		}

		scanf("%s", lido);
		
		if(!strcmp(lido, "*Edges")){
			direcionado = 0;
		}
		if(!strcmp(lido, "*Arcs")){
			direcionado = 1;
		}
		if(direcionado == -1){
			return 0;
		}
		
		scanf("%s", lido);
		
		while(lido != NULL && lido[0] != '*'){
			v1 = atoi(lido);
			scanf("%s", lido);
			v2 = atoi(lido);
			scanf("%s", lido);
			peso = atoi(lido);
			adicionaaresta(matriz, v1, v2, peso, direcionado);
			scanf("%s", lido);
		}
	}
	
	if(!strcmp(lido, "*Queries")){
		while(scanf("%s", lido) != EOF){
			if(!strcmp(lido, "get")){
				scanf("%d", &aux1);
				get(matriz, aux1);				
			}
			if(!strcmp(lido, "delete")){
				scanf("%d", &aux1);
				delete(matriz, aux1);
			}
			if(!strcmp(lido, "vizinhos")){
				scanf("%d", &aux1);
				vizinhos(matriz, aux1, direcionado);
			}
			if(!strcmp(lido, "conexao")){
				scanf("%d", &aux1);
				scanf("%d", &aux2);	
				conexao(matriz, aux1, aux2);
			}
			if(!strcmp(lido, "ordemtopologica")){
				ordemtopologica(matriz);
			}
			if(!strcmp(lido, "arvoreminima")){
				kruskal(matriz, arestasordenadas(pegaarestas(matriz)));
			}
			if(!strcmp(lido, "menorcaminho")){
				scanf("%d", &aux1);
				scanf("%d", &aux2);
				dijkstra(matriz, aux1, aux2);
			}
		}
	}
	return 1;
}