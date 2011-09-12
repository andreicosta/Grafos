#include <stdio.h>
#include <stdlib.h>

typedef struct MatrizAdjacencia{
	int ** matriz;
	int * vetor;
	int nvertices;
	int tamanho;	
} MatrizAdjacencia;

MatrizAdjacencia * CriaMatrizAdjacencia(int tamanhoinicial);
int ImprimeMatrizAdjacencia(struct MatrizAdjacencia * Matriz);
int DobraMatriz(struct MatrizAdjacencia * Matriz);
int AdicionaVertice(struct MatrizAdjacencia * Matriz);
int AdicionaAresta(struct MatrizAdjacencia * Matriz, int a, int b, int direcionado);
int RetiraAresta(struct MatrizAdjacencia * Matriz, int a, int b, int direcionado);
int TestaAdjacencia(struct MatrizAdjacencia * Matriz, int a, int b);
int * ListaVizinho(struct MatrizAdjacencia * Matriz, int a);//retorna um vetor com o nome dos elementos, o final do vetor é marcado por -1

int main(){
	MatrizAdjacencia * Grafo=CriaMatrizAdjacencia(5);
	
	AdicionaVertice(Grafo);
	AdicionaVertice(Grafo);
	AdicionaVertice(Grafo);
	
	AdicionaAresta(Grafo, 0, 0, 0);
	AdicionaAresta(Grafo, 0, 1, 0);
	AdicionaAresta(Grafo, 0, 2, 0);
	AdicionaAresta(Grafo, 1, 2, 0);
	
	int i, *listavizinhos=ListaVizinho(Grafo, 0);
	
	for(i=0;listavizinhos[i]!=-1;i++)
		printf("%i ", listavizinhos[i]);
	
	ImprimeMatrizAdjacencia(Grafo);
	return 0;
}

int AdicionaVertice(struct MatrizAdjacencia * Matriz){
	if(Matriz->nvertices < Matriz->tamanho){
		Matriz->vetor[Matriz->nvertices] = 1;
		Matriz->nvertices += 1;
		return 1;
	}
	else{
		printf("AdicionaVertice: Nao ha espaco na matriz\n");
		return 0;
	}
}

int RetiraVertice(struct MatrizAdjacencia * Matriz, int posicao){
	if(Matriz->vetor[posicao] == 0){
		printf("RetiraVertice: Posicao invalida\n");
		return -1;
	}
	else{
		Matriz->vetor[posicao] = 1;
		return 1;
	}
}

int AdicionaAresta(struct MatrizAdjacencia * Matriz, int a, int b, int direcionado){
	if(Matriz==NULL || Matriz->vetor==NULL || Matriz->matriz==NULL){
		printf("AdicionaAresta: Matriz nula\n");
		return -1;
	}
	
	if(Matriz->vetor[a] == 1 && Matriz->vetor[b] == 1){
		if(direcionado == 1)
			Matriz->matriz[a][b] = 1;
		else{
			Matriz->matriz[a][b] = 1;
			Matriz->matriz[b][a] = 1;
		}
		return 1;
	}
	else
		return 0;
}

int RetiraAresta(struct MatrizAdjacencia * Matriz, int a, int b, int direcionado){
	if(Matriz==NULL || Matriz->vetor==NULL || Matriz->matriz==NULL){
		printf("RetiraAresta: Matriz nula\n");
		return -1;
	}
	if(Matriz->vetor[a] == 1 && Matriz->vetor[b] == 1){
		if(direcionado == 1)
			Matriz->matriz[a][b] = 0;
		else{
			Matriz->matriz[a][b] = 0;
			Matriz->matriz[b][a] = 0;
		}
		return 1;
	}
	else
		return 0;
}

int TestaAdjacencia(struct MatrizAdjacencia * Matriz, int a, int b){
	if(Matriz==NULL || Matriz->vetor==NULL || Matriz->matriz==NULL){
		printf("TestaAdjacencia: Matriz nula\n");
		return -1;
	}
	return Matriz->matriz[a][b] || Matriz->matriz[b][a];
}

int * ListaVizinho(struct MatrizAdjacencia * Matriz, int a){
	if(Matriz == NULL || Matriz->vetor == NULL || Matriz->matriz == NULL){
		printf("ListaVizinho: Matriz nula\n");
		return NULL;
	}
	int i, nvizinhos = 0, *listavizinhos;
	
	listavizinhos = (int *)malloc(sizeof(int));
	
	for(i = 0;i < Matriz->nvertices;i++){
		if(Matriz->vetor[i] == 1 && (Matriz->matriz[a][i] == 1 || Matriz->matriz[i][a] == 1)){
			listavizinhos[nvizinhos++] = i;
			listavizinhos=(int *)realloc(listavizinhos, sizeof(int) * nvizinhos + 1);
		}
	}
	
	listavizinhos[nvizinhos] = -1;
	
	printf("\n");
	return listavizinhos;
}

MatrizAdjacencia * CriaMatrizAdjacencia(int tamanhoinicial){
	int i, j;
	struct MatrizAdjacencia * novo = (struct MatrizAdjacencia *) malloc(sizeof(struct MatrizAdjacencia));
	
	if(novo==NULL){
		printf("Cria: Erro ao alocar memoria\n");
		return NULL;
	}
	
	if(tamanhoinicial==0){
		printf("Cria: Tamanho inicial = 0 não da tche\n");
		return NULL;
	}
	
	if(tamanhoinicial<0){
		printf("Cria: Tamanho negativo?\n");
		return NULL;
	}
	
	novo->vetor = (int *) malloc(sizeof(int) * tamanhoinicial);
	
    novo->matriz = (int **) malloc(sizeof(int *) * tamanhoinicial);

	if(novo->vetor==NULL || novo->matriz==NULL){
		printf("Cria: Erro ao alocar memoria, sorry\n");
		return NULL;
	}

    for(i=0;i<tamanhoinicial;i++){
		novo->vetor[i]=0;
		novo->matriz[i] = (int *) malloc(sizeof(int) * tamanhoinicial);
		if(novo->matriz[i]==NULL){
			printf("Cria: Erro ao alocar memoria, desculpa\n");
			return NULL;
		}
		for(j=0;j<tamanhoinicial;j++)
			novo->matriz[i][j] = 0;
	}
	
	novo->tamanho=tamanhoinicial;
	novo->nvertices=0;

	return novo;
}

int ImprimeMatrizAdjacencia(struct MatrizAdjacencia * Matriz){
	int i, j;
	
	if(Matriz==NULL || Matriz->vetor==NULL || Matriz->matriz==NULL){
		printf("Imprime: Matriz nula\n");
		return -1;
	}
	
	printf("nvert: %i, tam: %i\n\n", Matriz->nvertices, Matriz->tamanho);
	
	for(i=0;i<Matriz->tamanho;i++)
		printf("%i\t", Matriz->vetor[i]);
	
	printf("\n");
	for(i=0;i<Matriz->tamanho;i++){
		printf("\n");
		for(j=0;j<Matriz->tamanho;j++)
			printf("%i\t", Matriz->matriz[i][j]);
	}
	printf("\n");
	
	return 1;
}

int DobraMatriz(struct MatrizAdjacencia * Matriz){
	int i, j;
	
	if(Matriz == NULL || Matriz->vetor == NULL || Matriz->matriz == NULL){
		printf("DobraMatriz: Matriz nula\n");
		return -1;
	}
	
	//Realoca Vetor
	Matriz->vetor = (int *)realloc(Matriz->vetor, sizeof(int) * Matriz->tamanho * 2);
	
	//Realoca Matriz
	Matriz->matriz = (int **)realloc(Matriz->matriz, sizeof(int *) * Matriz->tamanho * 2);
	for(i = 0;i < Matriz->tamanho;i++)
		Matriz->matriz[i] = (int *)realloc(Matriz->matriz[i], sizeof(int) * Matriz->tamanho * 2);
	for(i = Matriz->tamanho;i < Matriz->tamanho * 2;i++)
		Matriz->matriz[i] = (int *)malloc(sizeof(int) * Matriz->tamanho * 2);
	
	//Preenche de zeros
	for(i = Matriz->tamanho;i < Matriz->tamanho * 2;i++){
		Matriz->vetor[i] = 0;
		for(j = 0;j < Matriz->tamanho * 2;j++){
			Matriz->matriz[i][j] = 0;
			Matriz->matriz[j][i] = 0;
		}
	}
	
	//Atualiza tamanho
	Matriz->tamanho += Matriz->tamanho;
	
	printf("expandindo...novo tamanho = %i\n", Matriz->tamanho);

	return 1;
}
