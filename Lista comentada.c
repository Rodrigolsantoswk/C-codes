#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

//CRIANDO STRUCT DO TIPO NÓ

struct no{
	int n;
	struct no *elo; //Aqui é definido o ponteiro para o próximo nó     [n/*] -> [n/*]
};

typedef struct no no;

no* criarNo(){
	no *p = malloc(sizeof(struct no)); //Aqui é onde é alocado a memória
	return p; 
}

no* inserirElementoInicio (no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo();	//Novo do tipo *no recebe a alocação de memória
	novo->n=num; 			//Diz que o elemento n é igual a num 
	if(Lista == NULL){
		Lista = novo; 		//Se Lista for NULL, então Lista recebe Novo
		Lista->elo = NULL;	//Lista->elo aponta para NULL 
	}else{
		novo->elo = Lista;  //Diz que o novo Elo aponta para lista, Novo[n/elo] -> Lista[n3/elo3] -> Lista[n2/elo2] -> Lista[n1/elo1]. Por esse motivo, o elemento é adicionado na frente dos outros. 
		Lista = novo; 		//Diz que agora a Lista é o parâmetro recebido em InserirElementoInicio + o novo elo.
	}
	return Lista;           //Retorna a lista com o novo elemento.
}

no* inserirElementoFim(no *Lista, int num){ //Aqui recebida a lista e o elemento a ser inserido. 
	no *novo = criarNo(); 	 				//Novo do tipo *no recebe a alocação de memória
	novo->n = num;							//Diz que o elemento n do nó novo é igual a num
	no *aux = Lista;						//Cria uma Lista auxiliar aux do tipo no* para conseguir percorrer a Lista até o final 
	if(Lista == NULL){						//Se a lista for vazia
		Lista = novo;						//Diz que a lista é igual ao nó novo
		novo->elo = NULL;					//Diz que o elo do novo nó é NULL porque ele é o primeiro elemento.
	}else{									
		while(aux->elo !=NULL){				//Se utilizado a variável *Lista para percorrer, os elementos da lista perderão a referência do elo.
			aux = aux ->elo;				//Passando o elemento atual para a próxima posição. Nó atual = Nó que está endereçado no Elo
		}
		aux->elo = novo;					//Após encontrar o Nó que possui como Elo -> NULL, dizer que esse novo Elo é igual a aux[num/Novo] -> Novo[num/Elo]
		novo->elo = NULL;					//NOVO[num/NULL]
	}
	return Lista;							//Retorna lista
}

void imprimirLista(no *Lista){						//Recebe Lista como parâmetro
	no *aux = Lista;								//Declara variável auxiliar para percorrer a lista
	printf("Imprimindo elementos da lista\n");		
	while(aux != NULL){								//Enquanto a lista for diferente de NULL
		printf("%i\n", aux->n);						//Imprime o valor de n de aux 
		aux= aux->elo;								//Diz que aux é igual ao nó que está endereçado no Elo
	}
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
			aux = aux->elo;
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
			aux = aux->elo;
		}
	}
	return maior;
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
		return pos;
	}else{
		return -1;
	}
}

int elementodoMeio(no *Lista){ //retorna a posição do elemento mais ao meio
	no *aux= Lista;
	int cont= 0;
	while(aux != NULL){
		cont++;
		aux = aux->elo;
	}
	int contf = cont/2;
	return contf;
}

//lista binária

//---Na lista binária os elementos tem que estar organizados sequencialmente
//---É necessário identificar o elemento do meio ou próximo ao meio na lista
//---Após isso, verificar se o elemento buscado é maior ou igual ao elemento do meio
//---Se for maior, então buscar do meio para frente de forma sequencial
//---Se for menor, então considerar o elemento do meio = meio anterior -1 e 
//---percorrer a lista desta maneira até encontrar o elemento desejado.

void buscaBinaria(no *Lista, int num){
	int pos, verifExist = 0, cont=0, j, j2;;
	no *aux = Lista;
	no *aux2 = Lista;
	Lista = SelectionSort(Lista);
	imprimirLista(Lista);
	j=elementodoMeio(Lista);
	j2=j;
	if(Lista != NULL){
		//percorre a lista até o elemento do meio
		for(cont=0; cont<j; cont++){
			printf("elemento do meio: %i, cont: %i\n", aux->n, cont);
			aux = aux->elo;	
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
				while(aux->n != num && aux->elo != NULL){
					aux= aux->elo;
					j++;
					if(num==aux->n){
						printf("pos: %i\n",j);
						verifExist = 1;
					}
				}		
			}
	//se for menor que a posição atual, percorre até o meio de forma sequencial, verificando elemento por elemento.
		}else if(num<aux->n){
			printf("Condição: num < aux->n // num = %i, aux->n: %i \n", num, aux->n);
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
		printf("buscaBinária: Elemento não encontrado \n ");
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
		printf("buscaInterpolada: Lista não atende as condições: não está interpolada\n");
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
		Lista= Lista->elo;
		free(atual);		
	}
	return Lista;
}

no *apagarFinal(no *Lista){
	no *aux = Lista;
	no *anterior= Lista;
	if(Lista == NULL){
		printf("apagarFinal: Lista já está vazia\n");
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
													//Teste de mesa ----------------------LISTA = POSIÇÃO:ELEMENTO
	Lista = inserirElementoInicio(Lista, 1);		//Inserindo elemento no início ------ LISTA = 1:1
	Lista = inserirElementoFim(Lista, 3);		//Inserindo elemento no fim --------- LISTA = 1:1, 2:3
	Lista = inserirElementoInicio(Lista, 4);		//Inserindo elemento no início ------ LISTA = 1:4, 2:1, 3:3
	Lista = inserirElementoInicio(Lista, 6);	//Inserindo elemento no início ------ LISTA = 1:6, 2:4, 3:1, 4:3
	Lista = inserirElementoFim(Lista, 8);	    //Inserindo elemento no início ------ LISTA = 1:6, 2:4, 3:1, 4:3, 5:3
	Lista = inserirElementoFim(Lista, 9);	    //Inserindo elemento no início ------ LISTA = 1:6, 2:4, 3:1, 4:3, 5:3, 6:4
	imprimirLista(Lista);

	printf("\n----Busca Sequêncial-find: 3---\n");
	int posElemento =0;										//Variável para a armazenar a posição do elemento
	posElemento =buscaSequencial(Lista, 3);					//Executa o método de busca sequencial
	if(posElemento == -1){									//Se o método retornar -1, então não encontrou
		printf("Elemento não está na lista\n");
	}else{
		printf("Posição do elemento 3: %i\n", posElemento); //Exibe o resultado da busca.
	}
	
	printf("\n\n----Busca binária-find: 6---\n");
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
	printf("Inserindo no INÍCIO: \n");
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


