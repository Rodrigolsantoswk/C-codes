#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct no{
	int n;
	//Adicionado altura (nível ao contrário)
	int altura;
	//Necessário definir dois nós para a estrutura, porque cada elemento pode ter 2 nós filhos
	struct no *esquerda;
	struct no *direita;
};
typedef struct no no;

//Método retorna a altura atual do nó
int altura(no *No){
	if(No == NULL){
		return -1;
	}else{
		return No->altura;
	}
}

//método retorna o fator de balanceamento em absoluto
int Fatbal(struct no *No){
	//returna valor absoluto da subtração da altura do nó à esquerda e do nó à direita
	return labs(altura(No->esquerda) - altura(No->direita));
}

//retorna o maior valor entre dois números
int maior(int x, int y){
	if(x>y){
		return x;
	}else{
		return y;
	}
}

//Realiza a rotação simples à esquerda. Esta rotação é realizada quando há um desbalanceamento para a direita
void rotacaorr(no** No){
	no* aux = (*No)->direita;
	(*No)->direita=aux->esquerda;
	aux->esquerda = (*No);
	(*No)->altura = maior(altura((*No)->esquerda), altura((*No)->direita))+1;
	aux->altura= maior(altura(aux->direita), (*No)->altura)+1;
	(*No)=aux;
}

//Realiza a rotação simples à direita. Esta rotação é realizada quando há um desbalanceamento para a esquerda
void rotacaoll(no **No){
	no* aux = (*No)->esquerda;
	(*No)->esquerda = aux->direita;
	aux->direita = (*No);
	(*No)->altura = maior(altura((*No)->esquerda), altura((*No)->direita))+1;
	aux->altura = maior(altura((*No)->esquerda), (*No)->altura)+1;
	(*No) = aux;
}

//Rotação esquerda-direita. Utilizada quando há "joelho" para a esquerda
void rotacaolr(no** No){
	rotacaorr(&(*No)->esquerda);
	rotacaoll(No);
}

//Rotação direita-esquerda. Utilizada quando há "joelho" para a direita
void rotacaorl(no **No){
	rotacaoll(&(*No)->direita);
	rotacaorr(No);
}

int height(no* arvore){
    if (arvore == NULL)
        return 0;
    else{
        /* compute the height of each subtree */
        int eheight = height(arvore->esquerda);
        int dheight = height(arvore->direita);
 
        /* use the larger one */
        if (eheight > dheight){
            return(eheight + 1);
        }
        else{
          return(dheight + 1);
        }
    }
}


no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui é onde é alocado a memória
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
		printf("Este valor já foi inserido\n");
		return 0;
	}
	atual->altura = maior(altura(atual->esquerda), altura(atual->direita))+1;
	return res;
}

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

void imprimeNo(int num, int b, int altura){
    int i;
    for (i = 0; i < b; i++){
		printf("   "); //Mostra os espaços em branco de acordo com o nível
	}
	if(num != -1){
    	printf("%i/%i< \n", num, altura);
	}else{
		printf("NULL\n");
	}
}

void exibirNiveis(no* arvore, int b) { //Como a função é acionada recursivamente, é necessário passar o parâmetro B 
    //Quando a árvore for Nula envia -1 para imprimeNo
	if (arvore == NULL){ 
        imprimeNo(-1, b, -1);
        return;
    }
    //Exibe a árvore EM ORDEM
	exibirNiveis(arvore->direita, b+1);  //Chama recursivamente pela direita passando o parâmetro b +1 para ajustar a distância da esquerda até o elemento.
	imprimeNo(arvore->n, b, arvore->altura);  //Chama a função imprime nó que exibe o elemento
	exibirNiveis(arvore->esquerda, b+1); //Chama recursivamente pela esquerda passando o parâmetro b +1 para ajustar a distância da esquerda até o elemento.
}
//-------------------------------------------------------LISTA E BUSCA POR NÍVEL AQUI ---------------------------------------------------------------------------//

struct li{
	int n;
	int alt;
	struct li *elo; //Aqui é definido o ponteiro para o próximo nó     [n/*] -> [n/*]
};
typedef struct li li;


li* criarNoli(){
	li *p = malloc(sizeof(struct li)); //Aqui é onde é alocado a memória
	return p; 
}

void inserirElementoFim(li **Lista, int num, int alt){ //Aqui recebida a lista e o elemento a ser inserido. 
	li *novo = criarNoli(); 	 			//Novo do tipo *no recebe a alocação de memória
	novo->n = num;
	novo->alt= alt;							//Diz que o elemento n do nó novo é igual a num
	li *aux = *Lista;						//Cria uma Lista auxiliar aux do tipo no* para conseguir percorrer a Lista até o final 
	if(Lista == NULL){						//Se a lista for vazia
		*Lista = novo;						//Diz que a lista é igual ao nó novo
		novo->elo = NULL;					//Diz que o elo do novo nó é NULL porque ele é o primeiro elemento.
	}else{									
		while(aux->elo !=NULL){				//Se utilizado a variável *Lista para percorrer, os elementos da lista perderão a referência do elo.
			aux = aux ->elo;				//Passando o elemento atual para a próxima posição. Nó atual = Nó que está endereçado no Elo
		}
		aux->elo = novo;					//Após encontrar o Nó que possui como Elo -> NULL, dizer que esse novo Elo é igual a aux[num/Novo] -> Novo[num/Elo]
		novo->elo = NULL;					//NOVO[num/NULL]
	}										//Retorna lista
}

li *apagarInicio(li *Lista){
	li *aux = Lista;
	li *atual = NULL;
	if(Lista == NULL){
		printf("apagarInicio: Lista já está vazia\n");
		return Lista;
	}else{
		atual = aux;
		Lista= Lista->elo;
		free(atual);		
	}
	return Lista;
}

void imprimirLista(li *Lista){						//Recebe Lista como parâmetro
	li *aux = Lista;								//Declara variável auxiliar para percorrer a lista
	printf("\nImprimindo elementos da lista\n");
	if(aux!=NULL){
		while(aux != NULL){								//Enquanto a lista for diferente de NULL
			printf("%i/%i\n", aux->n, aux->alt); 		//Imprime o valor de n de aux 
			aux= aux->elo;								//Diz que aux é igual ao nó que está endereçado no Elo
		}
	}else{
		printf("Lista vazia\n");
	}
	
}


li* SelectionSort(li *Lista){
	li *aux = Lista;
	li *aux2= Lista;
	li *menor;							//Variável para armazenar nó com o menor valor durante a execução da repetição
	int a;								//Variável para armazenar o menor valor
	if (Lista != NULL){					
		while(aux != NULL){				
			menor = aux;				//Define que menor = elemento atual
			while(aux2 !=NULL){			//Percorre o vetor auxiliar do início ao fim
				if(aux2->n > aux->n){	//Verifica se o elemento atual de aux2 é menor que o elemento atual de aux
					menor = aux2;		//Se o elemento de aux2 for menor que o elemento atual de aux, então menor = aux2
					//Troca de elementos na lista
					a= aux->n;			
					aux->n = menor->n;
					menor->n = a;
				
				}
				aux2= aux2->elo;		
			}
			aux2= Lista;
			aux= aux->elo;
		}
	}
	return Lista;
}

//busca sequencial
int buscaSequencial(li *Lista, int num){
	li *aux = Lista;
	int cont=0, verifExist =0, pos =0;
	if(Lista != NULL){
		while(aux != NULL){
			if(aux->n == num){		//Verifica se o elemento atual é igual ao número buscado
				pos = cont;			//Se for igual, armazena a posição
				verifExist=1;		//Coloca o valor 1 na variável de verificação
				break;				//para a repetição
			}
			cont++;					//Senão, cont++
			aux= aux->elo;			//Vai para o próximo Elo.
		}
	}
	if(verifExist==1){				//Se verifExist ==1 retorna pos, senão, retorna -1
		return 1;
	}else{
		return -1;
	}
}




//-------------------------------------------------------LISTA E BUSCA POR NÍVEL AQUI ---------------------------------------------------------------------------//


//-------------------------------Exibição
#define espaco 2
//secondary function
void desenha_arvore_horiz(no *arvore, int depth, char *path, int direita){
    // stopping condition
    if (arvore== NULL){
    	return;
	}
    // increase spacing
    depth++;
    // start with direita no
    desenha_arvore_horiz(arvore->direita, depth, path, 1);
    // set | draw map
    path[depth-2] = 0;
    if(direita)
        path[depth-2] = 1;
    if(arvore->esquerda)
        path[depth-1] = 1;
    // print root after spacing
    printf("\n");
    int i;
    for(i=0; i<depth-1; i++)
    {
      if(i == depth-2)
          printf("+");
      else if(path[i])
          printf("|");
      else
          printf(" ");
	  int j;
      for(j=1; j<espaco; j++)
      if(i < depth-2)
          printf(" ");
      else
          printf("-");
    }

    printf("%d\n", arvore->n);

    // vertical espacors below
    for(i=0; i<depth; i++)
    {
		if(path[i])
		  printf("|");
		else
		  printf(" ");
		int j;
		for(j=1; j<espaco; j++)
		  printf(" ");
    }

    // go to esquerda no
    desenha_arvore_horiz(arvore->esquerda, depth, path, 0);
}

//primary fuction
void draw_arvore_hor(no *arvore)
{
    // should check if we don't exceed this somehow..
    char path[255] = {};

    //initial depth is 0
    desenha_arvore_horiz(arvore, 0, path, 0);
}

#define elem 7
void inserir1000(no **arvore){
	int i;
	for(i=0; i<elem; i++){
		inserirNoAvl(&(*arvore), i);
	}
	draw_arvore_hor(*arvore);
}


int main(){
	setlocale(LC_ALL,"");
	no *arvore= NULL;
	li *lista= NULL;
	int resinsert=0;
	int n, result;
	int end= 0, opc=0, elementos=0;
	do{
		printf("Elementos: %i\n", elementos);
		printf("Digite o que deseja fazer com a arvore\n1-Inserir elemento\n2-Exibir Pré-ordem\n3-Exibir Pós-ordem\n4-Exibir Em ordem\n5-Buscar elemento\n6-Imprimir em níveis\n7-Inserir %i elementos\n0-SAIR\n", elem);
		scanf("%i", &opc);
		//printf("opc: %i, end: %i\n", opc, end);
		switch(opc){
			case 1:
				do{
					printf("Digite o número a ser inserido. (Número>0)\n");
					do{
						scanf("%i", &n);	
					}while(n<1);
					resinsert=inserirNoAvl(&(arvore), n);
				}while(resinsert!=1);
				elementos++; 
				//exibirNiveis(arvore, 1);
				draw_arvore_hor(arvore);
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
				draw_arvore_hor(arvore);
				//lista=LevelOrderedTree(arvore, lista);
				//imprimirLista(lista);
				getchar();
				break;
			case 7:
				inserir1000(&arvore);
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
		resinsert=0;
	}while(end==0);
	return 0;
}
