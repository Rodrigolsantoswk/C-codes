#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct no{
	int n;
	//Necessário definir dois nós para a estrutura, porque cada elemento tem 2 nós
	struct no *esquerda;
	struct no *direita;
};
typedef struct no no;

void inserirNo(no** arvore, int num){
	//Se a arvore for nula, então insere o elemento na raiz
	if(*arvore==NULL){
		*arvore= (no *)malloc(sizeof(no)); //Aloca memória para o nó da estrutura
		//Define que o nó a esquerda e direita são NULL e que o elemento é num
		(*arvore)->esquerda = NULL; 	   
		(*arvore)->direita = NULL;
		(*arvore)->n = num;
	//Senão, verifica se o num é menor, maior ou igual que o elemento atual
	}else{
		if(num < (*arvore)->n){
			//Se for menor, chama a função recursivamente passando o elemento à esquerda
			inserirNo(&(*arvore)->esquerda, num);
		}else{
			//Se for maior, chama a função recursivamente passando o elemento à direita
			inserirNo(&(*arvore)->direita, num);
		}
	}
}

//Minha tentativa
no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui é onde é alocado a memória
	return p; 
}

no *inserirNoSemPonteiro(no* arvore, int num){
	no *aux=arvore;
	//Se a arvore for nula, então insere o elemento na raiz
	if(arvore==NULL){
		aux= criarNo(); //Aloca memória para o nó da estrutura
		//Define que o nó a esquerda e direita são NULL e que o elemento n é num
		aux->esquerda = NULL; 	   
		aux->direita = NULL;
		aux->n = num;
	//Senão, verifica se o num é menor, maior ou igual que o elemento atual
	}else{
		if(num < arvore->n){
			//Se for menor, chama a função recursivamente passando o elemento à esquerda
			inserirNo(&(arvore->esquerda), num);
		}else{
			//Se for maior, chama a função recursivamente passando o elemento à direita
			inserirNo(&(arvore->direita), num);
		}
	}
	return aux;
}
//Minha tentativa

void exibirPreOrdem(no *arvore){
	//Define variável auxiliar para percorrer a àrvore
	no *aux= arvore;
	printf("("); 							//Exibição serve para visualizar os nós e os filhos durante a recursão.
    if(arvore != NULL){ 					//Se a árvore for diferente de NULL, então:
    	printf("%i", aux->n);				//Exibe o elemento
        exibirPreOrdem(aux->esquerda);		//Chama a função recursivamente passando o nó à esquerda
        exibirPreOrdem(aux->direita);		//Chama a função recursivamente passando o nó à direita
    }
    printf(")");
}

int buscarElemento(no *arvore, int num){
	no *aux= arvore;
	//Se a árvore for nula retorna 0
	if(arvore==NULL){
		return 0;
	}else{
		//Enquanto a arvore auxiliar não for nula, então faça
		while(aux!= NULL){
			//Se o elemento for igual, então retorna 1
			if(aux->n == num){
				return 1;
			}
			//Se o elemento for maior, percorre para o nó à direita
			if(aux->n > num){
				aux= aux->direita;
			//Senão, percorre para o nó à esquerda
			}else{
				aux= aux->esquerda;
			}
		}
	}
	
	return 0;
}

int main(){
	setlocale(LC_ALL, "");	
	no *arvore = NULL;
	int n;
	int end= 0, opc=0;
	do{
		printf("Digite o que deseja fazer com a arvore\n1-Inserir elemento\n2-Exibir Pré-ordem\n0-SAIR\n");
		scanf("%i", &opc);
		printf("opc: %i, end: %i\n", opc, end);
		switch(opc){
			case 1:
				printf("Digite o número a ser inserido. (Número>0)\n");
				do{
					scanf("%i", &n);	
				}while(n<1);
				arvore =inserirNoSemPonteiro(arvore, n);
				break;
			case 2:
				exibirPreOrdem(arvore);
				getchar();
				break;
			case 0:
				end=1;
			default:
				printf("Opção inválida\n");
		}
		getchar();
		system("cls");
	}while(end==0);
	return 0;
}

