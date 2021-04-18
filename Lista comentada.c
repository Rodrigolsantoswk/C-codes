#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

//CRIANDO STRUCT DO TIPO N�

struct no{
	int n;
	struct no *elo; //Aqui � definido o ponteiro para o pr�ximo n�     [n/*] -> [n/*]
};

typedef struct no no;

no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui � onde � alocado a mem�ria
	return p; 
}

no* inserirElementoInicio (no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo();	//Novo do tipo *no recebe a aloca��o de mem�ria
	novo->n=num; 			//Diz que o elemento n � igual a num 
	if(Lista == NULL){
		Lista = novo; 		//Se Lista for NULL, ent�o Lista recebe Novo
		Lista->elo = NULL;	//Lista->elo aponta para NULL 
	}else{
		novo->elo = Lista;  //Diz que o novo Elo aponta para lista, Novo[n/elo] -> Lista[n3/elo3] -> Lista[n2/elo2] -> Lista[n1/elo1]. Por esse motivo, o elemento � adicionado na frente dos outros. 
		Lista = novo; 		//Diz que agora a Lista � o par�metro recebido em InserirElementoInicio + o novo elo.
	}
	return Lista;           //Retorna a lista com o novo elemento.
}

no* inserirElementoFim(no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo(); 	 				//Novo do tipo *no recebe a aloca��o de mem�ria
	novo->n = num;							//Diz que o elemento n do n� novo � igual a num
	no *aux = Lista;						//Cria uma Lista auxiliar aux do tipo no* para conseguir percorrer a Lista at� o final 
	if(Lista == NULL){						//Se a lista for vazia
		Lista = novo;						//Diz que a lista � igual ao n� novo
		novo->elo = NULL;					//Diz que o elo do novo n� � NULL porque ele � o primeiro elemento.
	}else{									
		while(aux->elo !=NULL){				//Se utilizado a vari�vel *Lista para percorrer, os elementos da lista perder�o a refer�ncia do elo.
			aux = aux ->elo;				//Passando o elemento atual para a pr�xima posi��o. N� atual = N� que est� endere�ado no Elo
		}
		aux->elo = novo;					//Ap�s encontrar o N� que possui como Elo -> NULL, dizer que esse novo Elo � igual a aux[num/Novo] -> Novo[num/Elo]
		novo->elo = NULL;					//NOVO[num/NULL]
	}
	return Lista;							//Retorna lista
}

void imprimirLista(no *Lista){						//Recebe Lista como par�metro
	no *aux = Lista;								//Declara vari�vel auxiliar para percorrer a lista
	printf("Imprimindo elementos da lista\n");		
	while(aux != NULL){								//Enquanto a lista for diferente de NULL
		printf("%i\n", aux->n);						//Imprime o valor de n de aux 
		aux= aux->elo;								//Diz que aux � igual ao n� que est� endere�ado no Elo
	}
}

int menorElementoLista(no *Lista){    //Encontrar menor elemento na lista
	int menor, cont =0;
	no *aux = Lista;
	if(Lista == NULL){ 					//Verifica se a lista possui elementos.
		printf("Lista n�o possui elementos suficientes...\n");
	}else{
		while(aux !=NULL) { 				//Percorre a lista at� o fim
			if(cont == 0){
				menor = aux->n;			//Para a primeira pesquisa, diz que o menor elemento � o elemento inicial da lista
			}else{
				if(aux->n < menor){		//Para as outras pesquisas, realiza a compara��o do elemento atual com o menor elemento registrado at� agora
					menor = aux->n;			
				}
				
			}
			cont++;
			aux = aux->elo;
		}
	}
	return menor;	
}

int maiorElementoLista(no *Lista){
	int maior, cont=0;
	no *aux = Lista;
	if(Lista == NULL){
		printf("Lista n�o possui elementos suficientes...\n");
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
			aux = aux->elo;
		}
	}
	return maior;
}

//Algoritmo de ordena��o Selection Sort
no* SelectionSort(no *Lista){
	no *aux = Lista;
	no *aux2= Lista;
	no *menor;							//Vari�vel para armazenar n� com o menor valor durante a execu��o da repeti��o
	int a;								//Vari�vel para armazenar o menor valor
	if (Lista != NULL){					
		while(aux != NULL){				
			menor = aux;				//Define que menor = elemento atual
			while(aux2 !=NULL){			//Percorre o vetor auxiliar do in�cio ao fim
				if(aux2->n > aux->n){	//Verifica se o elemento atual de aux2 � menor que o elemento atual de aux
					menor = aux2;		//Se o elemento de aux2 for menor que o elemento atual de aux, ent�o menor = aux2
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
int buscaSequencial(no *Lista, int num){
	no *aux = Lista;
	int cont=0, verifExist =0, pos =0;
	if(Lista != NULL){
		while(aux != NULL){
			if(aux->n == num){		//Verifica se o elemento atual � igual ao n�mero buscado
				pos = cont;			//Se for igual, armazena a posi��o
				verifExist=1;		//Coloca o valor 1 na vari�vel de verifica��o
				break;				//para a repeti��o
			}
			cont++;					//Sen�o, cont++
			aux= aux->elo;			//Vai para o pr�ximo Elo.
		}
	}
	if(verifExist==1){				//Se verifExist ==1 retorna pos, sen�o, retorna -1
		return pos;
	}else{
		return -1;
	}
}

int elementodoMeio(no *Lista){ //retorna a posi��o do elemento mais ao meio
	no *aux= Lista;
	int cont= 0;
	while(aux != NULL){
		cont++;
		aux = aux->elo;
	}
	int contf = cont/2;
	return contf;
}

//lista bin�ria

//---Na lista bin�ria os elementos tem que estar organizados sequencialmente
//---� necess�rio identificar o elemento do meio ou pr�ximo ao meio na lista
//---Ap�s isso, verificar se o elemento buscado � maior ou igual ao elemento do meio
//---Se for maior, ent�o buscar do meio para frente de forma sequencial
//---Se for menor, ent�o considerar o elemento do meio = meio anterior -1 e 
//---percorrer a lista desta maneira at� encontrar o elemento desejado.

void buscaBinaria(no *Lista, int num){
	int pos, verifExist = 0, cont=0, j, j2;;
	no *aux = Lista;
	no *aux2 = Lista;
	Lista = SelectionSort(Lista);
	imprimirLista(Lista);
	j=elementodoMeio(Lista);
	j2=j;
	if(Lista != NULL){
		//percorre a lista at� o elemento do meio
		for(cont=0; cont<j; cont++){
			printf("elemento do meio: %i, cont: %i\n", aux->n, cont);
			aux = aux->elo;	
		}
		//pergunta se o elemento � maior ou igual ao atual em aux -> n
		if(num >= aux->n){
			printf("num >= aux->n\n");
			//se for igual retorna a posi��o
			if(num == aux->n){
				printf("num = aux->n\n");
				printf("pos: %i\n",j);
				verifExist = 1;
			//se for maior, percorre a lista at� o elemeto ser igual ao pesquisado ou a lista ser nula.
			}else if(num> aux->n){
				printf("num > aux->n\n");
				while(aux->n != num && aux->elo != NULL){
					aux= aux->elo;
					j++;
					if(num==aux->n){
						printf("pos: %i\n",j);
						verifExist = 1;
					}
				}		
			}
	//se for menor que a posi��o atual, percorre at� o meio de forma sequencial, verificando elemento por elemento.
		}else if(num<aux->n){
			printf("Condi��o: num < aux->n // num = %i, aux->n: %i \n", num, aux->n);
			cont =0;
			aux = Lista;
			for(cont =0; cont<j2; cont++){
				if(aux->n == num){
					printf("pos: %i\n", cont);
					verifExist = 1;
				}
				aux = aux->elo;
			}
		}
	}
	if(verifExist == 0){
		printf("buscaBin�ria: Elemento n�o encontrado \n ");
	}
	
}

int retornaPrimeiroElemento(no *Lista){
	no *aux = Lista;
	return aux->n;
}

int quantElementos(no *Lista){
	int cont= 0;
	no *aux = Lista;
	if(Lista == NULL){
		return 0;
	}else{
		while(aux!= NULL){
			cont++;
			aux=aux->elo;
		}
	}
	return cont;
}

int verifInterpolada(no *Lista){
	no *aux = Lista;
	
	if(Lista  == NULL){
		return 0;
	}else{ 
		int primeiro = retornaPrimeiroElemento(Lista);
		aux = aux -> elo;
		int segundo = aux->n;
		int diff = segundo - primeiro;
		int anterior =aux ->n;
		
		printf("diff: %i, actual: %i\n", segundo-primeiro, aux->n);
		while(aux->elo != NULL){
			anterior = aux->n;
			aux= aux->elo;
			printf("diff: %i, actual: %i\n", aux->n - anterior, aux->n);
			if((aux->n -anterior)!= diff){
				return 0;
			}			
		}
	}
	return 1;
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
		printf("buscaInterpolada: Lista n�o atende as condi��es: n�o est� interpolada\n");
	}
	
}

no *apagarInicio(no *Lista){
	no *aux = Lista;
	no *atual = NULL;
	if(Lista == NULL){
		printf("apagarInicio: Lista j� est� vazia\n");
		return Lista;
	}else{
		atual = aux;
		Lista= Lista->elo;
		free(atual);		
	}
	return Lista;
}

no *apagarFinal(no *Lista){
	no *aux = Lista;
	no *anterior= Lista;
	if(Lista == NULL){
		printf("apagarFinal: Lista j� est� vazia\n");
	}else if(aux->elo == NULL){
		anterior = aux;
		aux = aux->elo;
		free(anterior);
	}else{
		aux= aux->elo;
		while(aux->elo != NULL){
			aux= aux->elo;
			anterior= anterior->elo;
		}
		anterior->elo = NULL;
		free(aux);
	}
	return Lista;
}

void main(){
	setlocale(LC_ALL, "");
	printf("----------LISTA ENCADEADA----------\n\n");
	no *Lista = NULL;								//Declara uma nova lista com o valor NULL
													//Teste de mesa ----------------------LISTA = POSI��O:ELEMENTO
	Lista = inserirElementoInicio(Lista, 1);		//Inserindo elemento no in�cio ------ LISTA = 1:1
	Lista = inserirElementoFim(Lista, 3);		//Inserindo elemento no fim --------- LISTA = 1:1, 2:3
	Lista = inserirElementoInicio(Lista, 4);		//Inserindo elemento no in�cio ------ LISTA = 1:4, 2:1, 3:3
	Lista = inserirElementoInicio(Lista, 6);	//Inserindo elemento no in�cio ------ LISTA = 1:6, 2:4, 3:1, 4:3
	Lista = inserirElementoFim(Lista, 8);	    //Inserindo elemento no in�cio ------ LISTA = 1:6, 2:4, 3:1, 4:3, 5:3
	Lista = inserirElementoFim(Lista, 9);	    //Inserindo elemento no in�cio ------ LISTA = 1:6, 2:4, 3:1, 4:3, 5:3, 6:4
	imprimirLista(Lista);

	printf("\n----Busca Sequ�ncial-find: 3---\n");
	int posElemento =0;										//Vari�vel para a armazenar a posi��o do elemento
	posElemento =buscaSequencial(Lista, 3);					//Executa o m�todo de busca sequencial
	if(posElemento == -1){									//Se o m�todo retornar -1, ent�o n�o encontrou
		printf("Elemento n�o est� na lista\n");
	}else{
		printf("Posi��o do elemento 3: %i\n", posElemento); //Exibe o resultado da busca.
	}
	
	printf("\n\n----Busca bin�ria-find: 6---\n");
	int elementomeio = elementodoMeio(Lista);
	//printf("Elento do meio: %i \n", elementomeio);
	buscaBinaria(Lista, 8);
	
	printf("..............................\n");
	printf("Inserindo no FIM: \n");
	no *Lista2 = NULL;
	Lista2 = inserirElementoFim(Lista2, 1);
	Lista2 = inserirElementoFim(Lista2, 2);
	Lista2 = inserirElementoFim(Lista2, 3);
	Lista2 = inserirElementoFim(Lista2, 4);
	Lista2 = inserirElementoFim(Lista2, 5);
	Lista2 = inserirElementoFim(Lista2, 6);
	imprimirLista(Lista2);
	printf("apagando em forma de PILHA: \n");
	Lista2 = apagarFinal(Lista2);
	Lista2 = apagarFinal(Lista2);
	imprimirLista(Lista2);
	printf("..............................\n");
	no *Lista3 = NULL;
	printf("Inserindo no IN�CIO: \n");
	Lista3 = inserirElementoInicio(Lista3, 1);
	Lista3 = inserirElementoInicio(Lista3, 2);
	Lista3 = inserirElementoInicio(Lista3, 3);
	Lista3 = inserirElementoInicio(Lista3, 4);
	Lista3 = inserirElementoInicio(Lista3, 5);
	Lista3 = inserirElementoInicio(Lista3, 6);
	imprimirLista(Lista3);
	printf("apagando em forma de FILA: \n");
	Lista2 = apagarFinal(Lista3);
	Lista2 = apagarFinal(Lista3);
	imprimirLista(Lista3);
	printf("..............................\n");
	printf("Busca Interpolada: \n");
	no *Lista4= NULL;
	Lista4 = inserirElementoFim(Lista4, 1);
	Lista4 = inserirElementoFim(Lista4, 2);
	Lista4 = inserirElementoFim(Lista4, 3);
	Lista4 = inserirElementoFim(Lista4, 4);
	Lista4 = inserirElementoFim(Lista4, 5);
	Lista4 = inserirElementoFim(Lista4, 6);
	imprimirLista(Lista4);
	int pos = buscaInterpolada(Lista4, 5);
	printf("pos: %i", pos);
	printf("\n----------END----------\n");
}


