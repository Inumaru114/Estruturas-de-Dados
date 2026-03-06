#include <stdio.h>
#include <stdlib.h>

typedef struct SkipList SkipList;

SkipList* CriaSL(int MAXLVL, float P);
void Libera(SkipList* sk);
int Insere(SkipList *sk, int key);
int Remove(SkipList *sk, int key);
int Busca(SkipList *sk, int key);
void Imprime(SkipList *sk);