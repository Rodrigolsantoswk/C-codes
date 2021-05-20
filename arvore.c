#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct no{
	int n;
	//Necess�rio definir dois n�s para a estrutura, porque cada elemento tem 2 n�s
	struct no *esquerda;
	struct no *direita;
};
typedef struct no no;

void inserirNo(no** arvore, int num){
	//Se a arvore for nula, ent�o insere o elemento na raiz
	if(*arvore==NULL){
		*arvore= (no *)malloc(sizeof(no)); //Aloca mem�ria para o n� da estrutura
		//Define que o n� a esquerda e direita s�o NULL e que o elemento � num
		(*arvore)->esquerda = NULL; 	   
		(*arvore)->direita = NULL;
		(*arvore)->n = num;
	//Sen�o, verifica se o num � menor, maior ou igual que o elemento atual
	}else{
		if(num < (*arvore)->n){
			//Se for menor, chama a fun��o recursivamente passando o elemento � esquerda
			inserirNo(&(*arvore)->esquerda, num);
		}else{
			//Se for maior, chama a fun��o recursivamente passando o elemento � direita
			inserirNo(&(*arvore)->direita, num);
		}
	}
}

//Minha tentativa
no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui � onde � alocado a mem�ria
	return p; 
}

no *inserirNoSemPonteiro(no* arvore, int num){
	no *aux=arvore;
	//Se a arvore for nula, ent�o insere o elemento na raiz
	if(arvore==NULL){
		aux= criarNo(); //Aloca mem�ria para o n� da estrutura
		//Define que o n� a esquerda e direita s�o NULL e que o elemento n � num
		aux->esquerda = NULL; 	   
		aux->direita = NULL;
		aux->n = num;
	//Sen�o, verifica se o num � menor, maior ou igual que o elemento atual
	}else{
		if(num < arvore->n){
			//Se for menor, chama a fun��o recursivamente passando o elemento � esquerda
			inserirNo(&(arvore->esquerda), num);
		}else{
			//Se for maior, chama a fun��o recursivamente passando o elemento � direita
			inserirNo(&(arvore->direita), num);
		}
	}
	return aux;
}
//Minha tentativa

void exibirPreOrdem(no *arvore){
	//Define vari�vel auxiliar para percorrer a �rvore
	no *aux= arvore;
	printf("("); 							//Exibi��o serve para visualizar os n�s e os filhos durante a recurs�o.
    if(arvore != NULL){ 					//Se a �rvore for diferente de NULL, ent�o:
    	printf("%i", aux->n);				//Exibe o elemento
        exibirPreOrdem(aux->esquerda);		//Chama a fun��o recursivamente passando o n� � esquerda
        exibirPreOrdem(aux->direita);		//Chama a fun��o recursivamente passando o n� � direita
    }
    printf(")");
}

int buscarElemento(no *arvore, int num){
	no *aux= arvore;
	//Se a �rvore for nula retorna 0
	if(arvore==NULL){
		return 0;
	}else{
		//Enquanto a arvore auxiliar n�o for nula, ent�o fa�a
		while(aux!= NULL){
			//Se o elemento for igual, ent�o retorna 1
			if(aux->n == num){
				return 1;
			}
			//Se o elemento for maior, percorre para o n� � direita
			if(aux->n > num){
				aux= aux->direita;
			//Sen�o, percorre para o n� � esquerda
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
		printf("Digite o que deseja fazer com a arvore\n1-Inserir elemento\n2-Exibir Pr�-ordem\n0-SAIR\n");
		scanf("%i", &opc);
		printf("opc: %i, end: %i\n", opc, end);
		switch(opc){
			case 1:
				printf("Digite o n�mero a ser inserido. (N�mero>0)\n");
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
				printf("Op��o inv�lida\n");
		}
		getchar();
		system("cls");
	}while(end==0);
	return 0;
}

