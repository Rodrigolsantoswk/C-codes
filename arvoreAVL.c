
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct no{
	int n;
	//Adicionado altura (n�vel ao contr�rio)
	int altura;
	//Necess�rio definir dois n�s para a estrutura, porque cada elemento pode ter 2 n�s filhos
	struct no *esquerda;
	struct no *direita;
};
typedef struct no no;

//M�todo retorna a altura atual do n�
int altura(no *No){
	if(No == NULL){
		return -1;
	}else{
		return No->altura;
	}
}

//m�todo retorna o fator de balanceamento em absoluto
int Fatbal(struct no *No){
	//returna valor absoluto da subtra��o da altura do n� � esquerda e do n� � direita
	return labs(altura(No->esquerda) - altura(No->direita));
}

//retorna o maior valor entre dois n�meros
int maior(int x, int y){
	if(x>y){
		return x;
	}else{
		return y;
	}
}

//Realiza a rota��o simples � esquerda. Esta rota��o � realizada quando
//necess�rio realocar os n�s na sub-�rvore � direita. 
void rotacaorr(no** No){
	no* aux = (*No)->direita;
	(*No)->direita=aux->esquerda;
	aux->esquerda = (*No);
	(*No)->altura = maior(altura((*No)->esquerda), altura((*No)->direita))+1;
	aux->altura= maior(altura(aux->direita), (*No)->altura)+1;
	(*No)=aux;
}

//Realiza a rota��o simples � esquerda. Esta rota��o � realizada quando
//necess�rio realocar os n�s na sub-�rvore � esquerda.
void rotacaoll(no **No){
	no* aux = (*No)->esquerda;
	(*No)->esquerda = aux->direita;
	aux->direita = (*No);
	(*No)->altura = maior(altura((*No)->esquerda), altura((*No)->direita))+1;
	aux->altura = maior(altura((*No)->esquerda), (*No)->altura)+1;
	(*No) = aux;
}

void rotacaolr(no** No){
	rotacaorr(&(*No)->esquerda);
	rotacaoll(No);
}

void rotacaorl(no **No){
	rotacaoll(&(*No)->direita);
	rotacaorr(No);
}

no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui � onde � alocado a mem�ria
	return p; 
}

int inserirNoAvl(no **arvore, int num){
	int res;
	if((*arvore)== NULL){
		no* novo = criarNo();
		novo->n= num ;
		novo->altura =0;
		novo->esquerda= NULL;
		novo->direita = NULL;
		(*arvore) = novo;
		return 1;
	}
	no *atual= (*arvore);
	
	if(num < atual->n){
		if((res=inserirNoAvl(&(atual->esquerda), num))==1){
			if(Fatbal(*arvore) >= 2){
				if(num < ((*arvore)->esquerda->n)){
					rotacaoll(arvore);
				}else{
					rotacaolr(arvore);
				}
			}
		}
	}else if(num > atual->n){
		if((res=inserirNoAvl(&(atual->direita), num))==1){
			if(Fatbal(*arvore)>=2){
				if(((*arvore)->direita->n) < num){
					rotacaorr(arvore);
				}else{
					rotacaorl(arvore);
				}
			}
		}
	}else{
		printf("Este valor j� foi inserido\n");
		return 0;
	}
	atual->altura = maior(altura(atual->esquerda), altura(atual->direita))+1;
	return res;
}

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

void exibirPosOrdem(no *arvore){
    if(arvore != NULL){ 
        exibirPosOrdem(arvore->esquerda); //chama a fun��o recursivamente pela esquerda 
        exibirPosOrdem(arvore->direita);  //chama a fun��o recursivamente pela direita
        printf("%i  ", arvore->n); 		  //exibe o elemento
    }
}

void exibirEmOrdem(no *arvore){
    if(arvore != NULL){
        exibirEmOrdem(arvore->esquerda); //chama a fun��o recursivamente pela esquerda 
        printf("%i  ", arvore->n);		 //exibe o elemento
        exibirEmOrdem(arvore->direita);  //chama a fun��o recursivamente pela direita
    }
}

int buscarElemento(no *arvore, int num){
	no *aux= arvore;
	//Se a �rvore for nula retorna 0
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

void imprimeNo(int num, int b, int altura){
    int i;
    for (i = 0; i < b; i++){
		printf("   "); //Mostra os espa�os em branco de acordo com o n�vel
	}
	if(num != -1){
    	printf("%i/%i< \n", num, altura);
	}else{
		printf("NULL\n");
	}
}

void exibirNiveis(no* arvore, int b) { //Como a fun��o � acionada recursivamente, � necess�rio passar o par�metro B 
    //Quando a �rvore for Nula envia -1 para imprimeNo
	if (arvore == NULL){ 
        imprimeNo(-1, b, -1);
        return;
    }
    //Exibe a �rvore EM ORDEM
	exibirNiveis(arvore->direita, b+1);  //Chama recursivamente pela direita passando o par�metro b +1 para ajustar a dist�ncia da esquerda at� o elemento.
	imprimeNo(arvore->n, b, arvore->altura);  //Chama a fun��o imprime n� que exibe o elemento
	exibirNiveis(arvore->esquerda, b+1); //Chama recursivamente pela esquerda passando o par�metro b +1 para ajustar a dist�ncia da esquerda at� o elemento.
}



int main(){
	setlocale(LC_ALL,"");
	no *arvore= NULL;
	int resinsert=0;
	int n, result;
	int end= 0, opc=0, elementos=0;
	do{
		printf("Elementos: %i\n", elementos);
		printf("Digite o que deseja fazer com a arvore\n1-Inserir elemento\n2-Exibir Pr�-ordem\n3-Exibir P�s-ordem\n4-Exibir Em ordem\n5-Buscar elemento\n6-Imprimir em n�veis\n0-SAIR\n");
		scanf("%i", &opc);
		//printf("opc: %i, end: %i\n", opc, end);
		switch(opc){
			case 1:
				do{
					printf("Digite o n�mero a ser inserido. (N�mero>0)\n");
					do{
						scanf("%i", &n);	
					}while(n<1);
					resinsert=inserirNoAvl(&(arvore), n);
				}while(resinsert!=1);
				elementos++; 
				exibirNiveis(arvore, 1);
				getchar();
				break;
			case 2:
				printf("Pr� ordem: ");exibirPreOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 3:
				printf("P�s ordem: ");exibirPosOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 4:
				printf("Em ordem: ");exibirEmOrdem(arvore); printf("\n");
				exibirNiveis(arvore, 1); 
				getchar();
				break;
			case 5:
				printf("Digite o n�mero que deseja buscar. (N�mero>0)\n");
				do{
					scanf("%i", &n);	
				}while(n<1);
				result= buscarElemento(arvore, n);
				if(result==1){
					printf("Elemento encontrado\n");
				}else{
					printf("Elemento n�o encontrado");
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
				printf("Op��o inv�lida\n");
				getchar();
		}
		getchar();
		system("cls");
		resinsert=0;
	}while(end==0);
	return 0;
}

