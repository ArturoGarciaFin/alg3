#include "redblack.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct nodo *raiz = NULL;

    printf("\n--- Testando a funcao inserir e imprimirEmOrdem ---\n");
    printf("Inserindo 10...\n");
    inserir(&raiz, 10);
    printf("Arvores após a insercao de 10:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Inserindo 20...\n");
    inserir(&raiz, 20);
    printf("Arvores após a insercao de 20:\n");
    imprimirEmOrdem(raiz);
    printf("\n");
    
    printf("Inserindo 30...\n");
    inserir(&raiz, 30);
    printf("Arvores após a insercao de 30:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Inserindo 15...\n");
    inserir(&raiz, 15);
    printf("Arvores após a insercao de 15:\n");
    imprimirEmOrdem(raiz);
    printf("\n");
    
    printf("\n--- Testando a funcao buscar ---\n");
    struct nodo* busca = buscar(raiz, 20);
    if (busca != NULL && busca->chave != LIXO) {
        printf("Chave 20 encontrada: %d\n", busca->chave);
    } else {
        printf("Chave 20 nao encontrada.\n");
    }

    busca = buscar(raiz, 99);
    if (busca != NULL && busca->chave != LIXO) {
        printf("Chave 99 encontrada: %d\n", busca->chave);
    } else {
        printf("Chave 99 nao encontrada.\n");
    }

    /*
    printf("\n--- Testando a funcao imprimirEmLargura ---\n");
    printf("Funcao imprimirEmLargura nao implementada.\n");
    imprimirEmLargura(raiz);
    
    // printf("\n--- Testando a funcao excluir ---\n");
    // int excluidos = excluir(&raiz, 20);
    // printf("Excluidos: %d\n", excluidos);
    // printf("Arvores após a exclusao:\n");
    // imprimirEmOrdem(raiz);

    // Liberar a memória alocada para a árvore (simplesmente para evitar vazamentos, não é o foco do teste)
    // Isso seria um teste mais complexo, não implementado aqui.
    */

    return 0;
}