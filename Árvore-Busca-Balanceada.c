#include <stdio.h>
#include <stdlib.h>
#define tamEspaco 10

typedef struct TipoVar{
	int valor;		
} variavel;

typedef struct no{
	variavel chave;
	struct no *Esq;
	struct no *Dir;
	int Balancing;
	int altura;
} NO;

NO *IniciaArv(){
	return NULL;
}

void Imprime(NO *raiz, int espaco){
	if (raiz == NULL)
		return; 
    else{
		espaco += tamEspaco; 

    Imprime(raiz->Dir, espaco); 
   
    printf("\n"); 
    for (int i = tamEspaco; i < espaco; i++) {
        printf(" "); 
    }

    printf("%d\n", raiz->chave.valor); 
  
    Imprime(raiz->Esq, espaco); 
	}
}

void RemoveArv(NO *raiz){
	if (raiz != NULL){
		RemoveArv(raiz->Esq);
		RemoveArv(raiz->Dir);
		free(raiz);
		raiz = NULL;
	}
}

NO *busca(NO *raiz, int valor){
	if (raiz != NULL){
		if (raiz->chave.valor == valor)
			return raiz;
		else{
			if (valor > raiz->chave.valor)
				return busca(raiz->Dir, valor);
			else
				return busca(raiz->Esq, valor);
		}
	}
	return NULL;
}

variavel CriaValor(int valor){
	variavel chave;
	chave.valor = valor;
	return chave;
}

NO *Aloca(){
	NO *novoNoh = (NO*) malloc(sizeof(NO));
	if (novoNoh != NULL){
		return novoNoh;
	}else{
		printf("Erro ao criar novo nó\n");
		exit(1); 
	}
}


int AlturaNo(NO *raiz){ 
    if (raiz == NULL) 
        return -1;
    else
        return raiz->altura;
}

int Balancing(NO *raiz){ 
    return labs(AlturaNo(raiz->Esq)-AlturaNo(raiz->Dir));
}


int AlturaArv(NO *raiz){
	int altDir = 0;
	int altEsq = 0;

	if (raiz == NULL)	
		return -1;

	altEsq = AlturaArv(raiz->Esq);
	altDir = AlturaArv(raiz->Dir);

	if (altEsq > altDir)
		return altEsq + 1;
	else
		return altDir + 1;
}

int QtdNos(NO *raiz){
	if (raiz == NULL)
		return 0;
	else
		return QtdNos(raiz->Esq) + QtdNos(raiz->Dir) + 1; 
}

int Maior(int x, int y){
	if (x > y)
		return x;
	else
		return y;
}

void RotacaoRR(NO **raiz){
	NO *aux;

	aux  = (*raiz)->Esq;
	(*raiz)->Esq  = aux->Dir;
	aux->Dir = *raiz;

	(*raiz)->altura = Maior(AlturaNo((*raiz)->Esq), AlturaNo((*raiz)->Dir)) + 1;
	aux->altura = Maior (AlturaNo(aux->Esq), (*raiz)->altura) + 1;

	*raiz = aux;
}

void RotacaoLL(NO **raiz){
	NO *aux;

	aux  = (*raiz)->Dir;
	(*raiz)->Dir  = aux->Esq;
	aux->Esq = *raiz;

	(*raiz)->altura = Maior(AlturaNo((*raiz)->Esq), AlturaNo((*raiz)->Dir)) + 1;
	aux->altura = Maior (AlturaNo(aux->Esq), (*raiz)->altura) + 1;

	*raiz = aux;
}

void RotacaoLR(NO **raiz){
	RotacaoLL(&(*raiz)->Esq);
	RotacaoRR(raiz);
}

void RotacaoRL(NO **raiz){
	RotacaoRR(&(*raiz)->Dir);
	RotacaoLL(raiz);
}

NO* Menor(NO **raiz){
    NO *noAux1;
    NO *noAux2;

    noAux1 = (*raiz);
    noAux2 = (*raiz)->Esq;

    while(noAux2 != NULL){
        noAux1 = noAux2;
        noAux2 = noAux2->Esq;
    }
    return noAux1;
}

int Insere(NO **raiz, int valor){
    int controle;

	if (*raiz == NULL){
		NO *aux = Aloca();
		aux->chave.valor = valor;
		aux->altura = 0;
		aux->Esq  = NULL;
		aux->Dir = NULL;
        *raiz = aux;
		return 1;
	}

	NO *atual;

	atual = *raiz;

    if(valor < atual->chave.valor){
        if((controle = Insere(&(atual->Esq), valor)) == 1){
            if(Balancing(atual) >= 2){
                if(valor < (*raiz)->Esq->chave.valor)
                    RotacaoRR(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }
    else{
        if(valor > atual->chave.valor){
            if ((controle = Insere(&(atual->Dir),valor)) == 1){
                if(Balancing(atual) >= 2){
                    if(valor > (*raiz)->Dir->chave.valor)
                        RotacaoLL(raiz);
                    else
                        RotacaoRL(raiz);
                }
            }
        }
        else{
            printf("\nValor Duplicado!\n");
            return 0;
        }
    }
    atual->altura = Maior(AlturaNo(atual->Esq), AlturaNo(atual->Dir)) + 1; 
    
	return controle;
}

int Remove(NO **raiz,int valor){
    int controle;

    if(*raiz == NULL){
        printf("\nEste valor não existe\n");
        return 0;
    }
    if(valor < (*raiz)->chave.valor){
        if((controle = Remove(&((*raiz)->Esq), valor)) == 1){
            if(Balancing(*raiz) >= 2){
                if(AlturaNo((*raiz)->Dir->Esq) <= AlturaNo((*raiz)->Dir->Dir))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }
    if(valor>(*raiz)->chave.valor){
        if ((controle = Remove(&((*raiz)->Dir), valor)) == 1){

            if(Balancing(*raiz) >= 2){
                if(AlturaNo((*raiz)->Esq->Dir) <= AlturaNo((*raiz)->Esq->Esq))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }
    if((*raiz)->chave.valor == valor){
        if(((*raiz)->Esq == NULL)||((*raiz)->Dir == NULL)){ 
            NO *aux = *raiz;

            if((*raiz)->Esq != NULL)
                *raiz = (*raiz)->Esq;
            else
                *raiz = (*raiz)->Dir;
            free(aux);
            aux = NULL;
            printf("\nNó removido com sucesso!\n");
        }
        else{            
            NO *aux = Menor(&(*raiz)->Dir);
            (*raiz)->chave.valor = aux->chave.valor;
            Remove(&(*raiz)->Dir, (*raiz)->chave.valor);
            if(Balancing(*raiz) >= 2){
                if(AlturaNo((*raiz)->Esq->Dir) <= AlturaNo((*raiz)->Esq->Esq))
                    RotacaoRR(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        return 1;
    }
    return controle;
}


int main(){
	NO *raiz = IniciaArv();
	int op = -1;
	int valor = 0;

	while(op != 0){
		printf("\n - - - Impressão da Arvore Atual: - - - \n");
		Imprime(raiz, tamEspaco);

		valor = 0;
		printf("\n - - - - - - - Operações - - - - - - - \n");
		printf("1) Inserção \n");
		printf("2) Remoção \n");
		printf("3) Pesquisa \n");
		printf("0) SAIR \n");
		scanf("%d", &op);

		switch(op){
			case 1:
			printf("\n - - - - Inserindo - - - -\n");
			printf("Digite um valor:\n");
			scanf("%d",&valor);
			Insere(&raiz, valor);
			break;

			case 2:
			printf("\n - - - - Removendo - - - - \n");
			printf("Digite um valor:\n");
			scanf("%d",&valor);
			Remove(&raiz, valor);
			break;

			case 3:
			printf("\n - - - - Pesquisando - - - - \n");
			printf("Digite um valor:\n");
			scanf("%d",&valor);

			NO *aux = busca(raiz, valor);
			if (aux == NULL)
				printf("\nElemento não foi encontrado!\n");
			else
				printf("\nElemento foi encontrado! \n");
			break;

			case 0:
			printf("\nFinalizando...\n");
			break;

			default:
			printf("\nOpção inválida! \n");
			break;
		}
	}
		RemoveArv(raiz);

	return 0;
}