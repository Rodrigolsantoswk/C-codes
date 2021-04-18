#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

//CRIANDO STRUCT DO TIPO NÓ

struct no{
	int n;
	struct no *tr; //Aqui é definido o ponteiro para o nó  anterior    [*/n/*] <- [*/n/*]
	struct no *fr; //Aqui é definido o ponteiro para o próximo nó     [*/n/*] -> [*/n/*]
};

typedef struct no no;

no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui é onde é alocado a memória
	return p; 
}

no* inserirElementoInicio (no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo();
	novo->n = num;
	if(Lista == NULL){
		Lista = novo;
		Lista->tr = NULL;
		Lista->fr = NULL;
	}else{
		novo->fr= Lista;
		novo->tr= NULL;
		Lista->tr = novo;
		Lista = novo;
		
	}
}

no* inserirElementoFim(no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo();
	novo->n = num;
	no *aux = Lista, *atual = Lista;
	if(Lista == NULL){
		Lista = novo;
		novo->fr = NULL;
		novo->tr = NULL;
	}else{
		while(aux != NULL){
			atual = aux;
			aux= aux->fr;
		}
		aux = novo;
		atual ->fr = aux;
		aux->tr = atual;
	}
	return Lista;
}


void imprimirListaItoF(no *Lista){					//Recebe Lista como parâmetro - Imprime a lista do início para o final
	no *aux = Lista;								//Declara variável auxiliar para percorrer a lista
	printf("Imprimindo a lista do início para o fim:\n");	
	while(aux != NULL){								//Enquanto a lista for diferente de NULL
		printf("%i\n", aux->n);						//Imprime o valor de n de aux 
		aux= aux->fr;								//Diz que aux é igual ao nó que está endereçado no Elo
	}
}

void imprimirListaFtoI(no *Lista){					//Recebe Lista como parâmetro - Imprime a lista do final para o início
	no *aux = Lista;								//Declara variável auxiliar para percorrer a lista
	printf("Imprimindo a lista do fim para o início:\n");	
	while(aux->fr != NULL){								//Enquanto a lista for diferente de NULL
		//printf("%i\n", aux->n);						//Imprime o valor de n de aux 
		aux= aux->fr;								//Diz que aux é igual ao nó que está endereçado no Elo
	}
	while(aux != NULL){
		printf("%i\n", aux->n);
		aux= aux->tr;
	}
}

no *apagarInicio(no *Lista){
	no *aux = Lista;
	no *atual = NULL;
	if(Lista == NULL){
		printf("apagarInicio: Lista já está vazia\n");
		return Lista;
	}else{
		atual = aux;
		Lista= Lista->fr;
		Lista->tr = NULL;
		free(atual);		
	}
	return Lista;
}

no *apagarFinal(no *Lista){
	no *aux = Lista;
	no *anterior= Lista;
	if(Lista == NULL){
		printf("apagarFinal: Lista já está vazia\n");
	}else if(aux->fr == NULL){
		anterior = aux;
		aux = aux->fr;
		free(anterior);
	}else{
		aux= aux->fr;
		while(aux->fr != NULL){
			aux= aux->fr;
			anterior= anterior->fr;
		}
		anterior->fr = NULL;
		free(aux);
	}
	return Lista;
}

int buscaSequencial(no *Lista, int num){
	no *aux = Lista;
	int cont=0, verifExist =0, pos =0;
	if(Lista != NULL){
		while(aux != NULL){
			if(aux->n == num){		//Verifica se o elemento atual é igual ao número buscado
				pos = cont;			//Se for igual, armazena a posição
				verifExist=1;		//Coloca o valor 1 na variável de verificação
				break;				//para a repetição
			}
			cont++;					//Senão, cont++
			aux= aux->fr;			//Vai para o próximo Elo.
		}
	}
	if(verifExist==1){				//Se verifExist ==1 retorna pos, senão, retorna -1
		return pos;
	}else{
		return -1;
	}
}

//Algoritmo de ordenação Selection Sort
no* SelectionSort(no *Lista){
	no *aux = Lista;
	no *aux2= Lista;
	no *menor;							//Variável para armazenar nó com o menor valor durante a execução da repetição
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
				aux2= aux2->fr;		
			}
			aux2= Lista;
			aux= aux->fr;
		}
	}
	return Lista;
}

int elementodoMeio(no *Lista){ //retorna a posição do elemento mais ao meio
	no *aux= Lista;
	int cont= 0;
	while(aux != NULL){
		cont++;
		aux = aux->fr;
	}
	int contf = cont/2;
	return contf;
}

//Busca binária
void buscaBinaria(no *Lista, int num){
	int pos, verifExist = 0, cont=0, j, j2;;
	no *aux = Lista;
	no *aux2 = Lista;
	Lista = SelectionSort(Lista);
	imprimirListaItoF(Lista);
	j=elementodoMeio(Lista);
	j2=j;
	if(Lista != NULL){
		//percorre a lista até o elemento do meio
		for(cont=0; cont<j; cont++){
			printf("pos. elemento do meio: %i, cont: %i\n", aux->n, cont);
			aux = aux->fr;	
		}
		//pergunta se o elemento é maior ou igual ao atual em aux -> n
		if(num >= aux->n){
			printf("num >= aux->n\n");
			//se for igual retorna a posição
			if(num == aux->n){
				printf("num = aux->n\n");
				printf("pos: %i\n",j);
				verifExist = 1;
			//se for maior, percorre a lista até o elemeto ser igual ao pesquisado ou a lista ser nula.
			}else if(num> aux->n){
				printf("num > aux->n\n");
				while(aux->n != num && aux->fr != NULL){
					aux= aux->fr;
					j++;
					if(num==aux->n){
						printf("pos: %i\n",j);
						verifExist = 1;
					}
				}		
			}
		//se for menor que a posição atual, percorre do meio até o início de forma sequencial, verificando elemento por elemento.
		}else if(num<aux->n){
			printf("Condição: num < aux->n // num = %i, aux->n: %i \n", num, aux->n);
			while(aux!= NULL){
				if(aux->n == num){
					printf("pos: %i\n",j);
					verifExist =1;
				}
				j--;
				aux= aux->tr;
			}
		}
	}
	if(verifExist == 0){
		printf("buscaBinária: Elemento não encontrado \n ");
	}
	
}
//Busca Interpolada

int retornaPrimeiroElemento(no *Lista){
	no *aux = Lista;
	return aux->n;
}

int verifInterpolada(no *Lista){  //verifica se a lista é interpolada, senão, retorna 0
	no *aux = Lista;
	
	if(Lista  == NULL){
		return 0;
	}else{ 
		int primeiro = retornaPrimeiroElemento(Lista);
		aux = aux -> fr;
		int segundo = aux->n;
		int diff = segundo - primeiro;
		int anterior =aux ->n;
		
		printf("diff: %i, actual: %i\n", segundo-primeiro, aux->n);
		while(aux->fr != NULL){
			anterior = aux->n;
			aux= aux->fr;
			printf("diff: %i, actual: %i\n", aux->n - anterior, aux->n);
			if((aux->n -anterior)!= diff){
				return 0;
			}			
		}
	}
	return 1;
}

int menorElementoLista(no *Lista){    //Encontrar menor elemento na lista
	int menor, cont =0;
	no *aux = Lista;
	if(Lista == NULL){ 					//Verifica se a lista possui elementos.
		printf("Lista não possui elementos suficientes...\n");
	}else{
		while(aux !=NULL) { 				//Percorre a lista até o fim
			if(cont == 0){
				menor = aux->n;			//Para a primeira pesquisa, diz que o menor elemento é o elemento inicial da lista
			}else{
				if(aux->n < menor){		//Para as outras pesquisas, realiza a comparação do elemento atual com o menor elemento registrado até agora
					menor = aux->n;			
				}
				
			}
			cont++;
			aux = aux->fr;
		}
	}
	return menor;	
}

int maiorElementoLista(no *Lista){
	int maior, cont=0;
	no *aux = Lista;
	if(Lista == NULL){
		printf("Lista não possui elementos suficientes...\n");
	}else{
		while(aux != NULL){
			if(cont==0){
				maior = aux->n;
			}else{
				if(aux->n >maior){
					maior = aux->n;
				}
			}
			cont++;
			aux = aux->fr;
		}
	}
	return maior;
}

int quantElementos(no *Lista){
	int cont= 0;
	no *aux = Lista;
	if(Lista == NULL){
		return 0;
	}else{
		while(aux!= NULL){
			cont++;
			aux=aux->fr;
		}
	}
	return cont;
}

//Busca interpolada
//---
//---x =( 0 + (floor)(qntElementos(Lista)-1)*(valorPesquisado-valordoPrimeiroElemento)) / (valordoMaiorElemento - valorDoMenorElemento)
int buscaInterpolada(no *Lista, int num){
	int verif= verifInterpolada(Lista); 
	if(verif ==1){
		int x1 = ((quantElementos(Lista)-1)*(num - retornaPrimeiroElemento(Lista)));
		int x2 = ((maiorElementoLista(Lista) - menorElementoLista(Lista)));
		int x = (0 + floor( x1 / x2 ));
		return x;
	}else{
		printf("buscaInterpolada: Lista não atende as condições: não está interpolada\n");
	}
}

void main(){
	setlocale(LC_ALL, "");
	no *Lista = NULL;
	printf("-------------Início---------------: \n");
	printf("Inserindo no início da lista: \n");
	Lista = inserirElementoInicio(Lista, 1);
	Lista = inserirElementoInicio(Lista, 2);
	Lista = inserirElementoInicio(Lista, 3);
	Lista = inserirElementoInicio(Lista, 4);
	imprimirListaItoF(Lista);
	imprimirListaFtoI(Lista);
	printf("-----------------------------------: \n");
	printf("Inserindo no fim da lista: \n");
	no *Lista2 = NULL;
	Lista2 = inserirElementoFim(Lista2, 1);
	Lista2 = inserirElementoFim(Lista2, 2);
	Lista2 = inserirElementoFim(Lista2, 3);
	Lista2 = inserirElementoFim(Lista2, 4);
	imprimirListaItoF(Lista2);
	imprimirListaFtoI(Lista2);
	//OBS: Reutilizando a lista que estou inserindo elementos no final
	printf("----Apagando em forma de FILA----: \n");
	Lista2= apagarInicio(Lista2);
	imprimirListaItoF(Lista2);
	printf("----Apagando em forma de PILHA---: \n");
	Lista2= apagarFinal(Lista2);
	imprimirListaItoF(Lista2);
	
	printf("----Busca sequencial-Find: 3---: \n");
	int pos= buscaSequencial(Lista, 3);
	if(pos == -1){
		printf("Elemento não encontrado...\n");
	}else{
		printf("pos buscaSequencial: %i\n", pos);
	}
	Lista2 = inserirElementoFim(Lista2, 1);
	
	printf("\n-----buscaBinária-Find: 3-----: \n");
	buscaBinaria(Lista2, 3);
	
	printf("\n---buscaInterpolada-Find: 2---: \n");
	//printf("verifInterpolada: %i\n", verifInterpolada(Lista2));
	printf("pos: %i\n", buscaInterpolada(Lista2, 2));
	
}




