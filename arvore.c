#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

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

void exibirPosOrdem(no *arvore){
    if(arvore != NULL){ 
        exibirPosOrdem(arvore->esquerda); //chama a função recursivamente pela esquerda 
        exibirPosOrdem(arvore->direita);  //chama a função recursivamente pela direita
        printf("%i  ", arvore->n); 		  //exibe o elemento
    }
}

void exibirEmOrdem(no *arvore){
    if(arvore != NULL){
        exibirEmOrdem(arvore->esquerda); //chama a função recursivamente pela esquerda 
        printf("%i  ", arvore->n);		 //exibe o elemento
        exibirEmOrdem(arvore->direita);  //chama a função recursivamente pela direita
    }
}

int buscarElemento(no *arvore, int num){
	no *aux= arvore;
	//Se a árvore for nula retorna 0
	if(aux==NULL){
		return 0;
	}else{
		while(aux!= NULL){
			//printf("--%i, %i\n",aux->n, num);
			if(num == aux->n){
				return 1;
			}else if(num< aux->n){
				aux = aux->esquerda;
			}else if(num > aux->n){
				aux = aux->direita;
			}
		}
	}
	return 0;
}

void imprimeNo(int num, int b){
    int i;
    for (i = 0; i < b; i++){
		printf("   "); //Mostra os espaços em branco de acordo com o nível
	}
	
	if(num != -1){
    	printf("%i<   \n", num);
	}else{
		printf("NULL\n");
	}
	
}

void exibirNiveis(no* arvore, int b) { //Como a função é acionada recursivamente, é necessário passar o parâmetro B 
    //Quando a árvore for Nula envia -1 para imprimeNo
	if (arvore == NULL){ 
        imprimeNo(-1, b);
        return;
    }
    //Exibe a árvore EM ORDEM
	exibirNiveis(arvore->direita, b+1);  //Chama recursivamente pela direita passando o parâmetro b +1 para ajustar a distância da esquerda até o elemento.
	imprimeNo(arvore->n, b); 			 //Chama a função imprime nó que exibe o elemento
	exibirNiveis(arvore->esquerda, b+1); //Chama recursivamente pela esquerda passando o parâmetro b +1 para ajustar a distância da esquerda até o elemento.
}

// A função auxiliar imprimeNo imprime o caracter
// c precedido de 3b espaços e seguido de uma mudança
// de linha.

int main(){
	setlocale(LC_ALL, "");	
	no *arvore = NULL;
	int n, result;
	int end= 0, opc=0, elementos=0;
	do{
		printf("Elementos: %i\n", elementos);
		printf("Digite o que deseja fazer com a arvore\n1-Inserir elemento\n2-Exibir Pré-ordem\n3-Exibir Pós-ordem\n4-Exibir Em ordem\n5-Buscar elemento\n6-Imprimir em níveis\n0-SAIR\n");
		scanf("%i", &opc);
		//printf("opc: %i, end: %i\n", opc, end);
		switch(opc){
			case 1:
				printf("Digite o número a ser inserido. (Número>0)\n");
				do{
					scanf("%i", &n);	
				}while(n<1);
				arvore =inserirNoSemPonteiro(arvore, n);
				elementos++;
				exibirNiveis(arvore, 1);
				getchar();
				break;
			case 2:
				printf("Pré ordem: ");exibirPreOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 3:
				printf("Pós ordem: ");exibirPosOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 4:
				printf("Em ordem: ");exibirEmOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 5:
				printf("Digite o número que deseja buscar. (Número>0)\n");
				do{
					scanf("%i", &n);	
				}while(n<1);
				result= buscarElemento(arvore, n);
				if(result==1){
					printf("Elemento encontrado\n");
				}else{
					printf("Elemento não encontrado");
				}
				getchar();
				break;
			case 6:
				exibirNiveis(arvore, 3);
				getchar();
				break;
			case 0:
				end=1;
			default:
				printf("Opção inválida\n");
				getchar();
		}
		getchar();
		system("cls");
	}while(end==0);
	return 0;
}
