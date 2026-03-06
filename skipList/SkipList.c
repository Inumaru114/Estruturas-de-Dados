#include "SkipList.h"

typedef struct no{
    int chave;
    struct no **prox;
} NO;

typedef struct SkipList{
	int NivelMAX;
	float P;
	int nivel;
	NO *inicio;
} SL;

NO* novoNo(int chave, int nivel){
	NO* novo = malloc(sizeof(NO));
	if(novo != NULL){
        novo->chave = chave;
        novo->prox = malloc((nivel + 1) * sizeof(NO*));
        int i;
        for(i = 0; i < (nivel + 1); i++)
            novo->prox[i] = NULL;
	}
	return novo;
}

SkipList* CriaSL(int NivelMAX, float P){
    SkipList *sk = (SkipList*) malloc(sizeof(SkipList));
    if(sk != NULL){
        sk->NivelMAX = NivelMAX;
        sk->P = P;
        sk->nivel = 0;
        sk->inicio = novoNo(-1, NivelMAX);
    }
	return sk;
}

int SorteiaNvl(SkipList *sk){
	float r = (float)rand()/RAND_MAX;
	int nivel = 0;
	while(r < sk->P && nivel < sk->NivelMAX){
		nivel++;
		r = (float)rand()/RAND_MAX;
	}
	return nivel;
}

int Busca(SkipList *sk, int chave){
    if(sk == NULL){
        return 0;
	}
	
	NO *atual = sk->inicio;

	int i;
	for(i = sk->nivel; i >= 0; i--){
        while(atual->prox[i] != NULL && atual->prox[i]->chave < chave)
            atual = atual->prox[i];
	}

	atual = atual->prox[0];
	if(atual != NULL && atual->chave == chave)
		return 1;
    else
        return 0;
}

int Insere(SkipList *sk, int chave){
	int i;
	NO *atual = sk->inicio;
	NO **aux = malloc((sk->NivelMAX + 1) * sizeof(NO*));
	
    if(sk == NULL){
        return 0;
	}

	for(i = 0; i <= sk->NivelMAX; i++){
	    aux[i] = NULL;
	}

	for(i = sk->nivel; i >= 0; i--){
		while(atual->prox[i] != NULL && atual->prox[i]->chave < chave)
			atual = atual->prox[i];
		aux[i] = atual;
	}

	atual = atual->prox[0];

	if(atual == NULL || atual->chave != chave){
		int novo_nivel = SorteiaNvl(sk);
		NO* novo = novoNo(chave, novo_nivel);
		if(novo == NULL){
            free(aux);
            return 0;
		}

		if(novo_nivel > sk->nivel){
			for(i = sk->nivel+1; i <= novo_nivel; i++)
				aux[i] = sk->inicio;

			sk->nivel = novo_nivel;
		}

		for(i = 0; i <= novo_nivel; i++){
			novo->prox[i] = aux[i]->prox[i];
			aux[i]->prox[i] = novo;
		}

		free(aux);
		return 1;
	}

	free(aux);
	return 0;
}

int Remove(SkipList *sk, int chave){
    if(sk == NULL){
        return 0;
	}
	int i;
	printf("removendo chave %d da Skip List...\n", chave);
	NO *atual = sk->inicio;
	NO **aux;
	aux = malloc((sk->NivelMAX+1) * sizeof(NO*));
	for(i = 0; i <= sk->NivelMAX; i++)
	    aux[i] = NULL;

	for(i = sk->nivel; i >= 0; i--){
		while(atual->prox[i] != NULL && atual->prox[i]->chave < chave)
			atual = atual->prox[i];
		aux[i] = atual;
	}

	atual = atual->prox[0];

	if(atual != NULL && atual->chave == chave){
		for(i = 0; i <= sk->nivel; i++){
			if(aux[i]->prox[i] != atual)
				break;

			aux[i]->prox[i] = atual->prox[i];
		}
		while(sk->nivel > 0 && sk->inicio->prox[sk->nivel] == NULL)
			sk->nivel--;

		free(atual->prox);
		free(atual);
		free(aux);
		return 1;
	}

	free(aux);
	return 0;
}

void Imprime(SkipList *sk){
    if(sk == NULL)
        return;

	printf("imprimindo Skip List...");
	printf("\n===== Skip List =====\n");
	for(int i = 0; i <= sk->nivel; i++){
		NO *no = sk->inicio->prox[i];
		printf("Nivel %d: ",i);
		while(no != NULL){
			printf("%d ",no->chave);
			no = no->prox[i];
		}
		printf("\n");
	}
}

void Libera(SkipList* sk){
	printf("liberando Skip List...\n");
    if(sk == NULL)
        return;

    NO *no, *atual;
    atual = sk->inicio->prox[0];
    while(atual != NULL){
        no = atual;
        atual = atual->prox[0];
        free(no->prox);
        free(no);
    }

    free(sk->inicio);
    free(sk);
}