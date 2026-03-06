#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkipList.h"

int main(){
	srand((unsigned)time(0));
    SkipList* SL = CriaSL(15, 0.5);

    int i, s[15] = {10,25,3,18,20,32,41,2,8,14,27,13,53,7,60};
    for(i = 0; i < 15; i++){
        Insere(SL, s[i]);
    }
    Imprime(SL);

    if(Busca(SL, 21)){
        printf("21 encontrado com sucesso!\n");
        Remove(SL, 21);
    } else
        printf("Não foi encontrado 21 na skip list.\n");

    if(Busca(SL, 27)){
        printf("27 eocntrado com sucesso!\n");
        Remove(SL, 27);
    } else
        printf("Não foi encontrado 27 na skip list.");

    Imprime(SL);

    Libera(SL);

    return 0;
}