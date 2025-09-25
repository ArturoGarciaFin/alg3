#include "redblack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("SEU_NOME"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("NOME_NAS_SERVIDORAS_DINF"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
	strcpy(retorno->nome, "SEU_NOME");
    strcpy(retorno->nomeDinf, "NOME_NAS_SERVIDORAS_DINF");
    retorno->grr = 1234;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}
*/

//IMPLEMENTE AS DEMAIS FUNÇÕES AQUI

struct nodo *node_create(int chave)
{
    struct nodo *new_node = (struct nodo*)malloc(sizeof(struct nodo));
    if (!new_node)
    {
        fprintf(stderr, "Falha ao alocar memoria\n");
        exit(1);
    }

    new_node->chave = chave;
    new_node->colour = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
}

void rotation_left(struct nodo **raiz, struct nodo *x)
{
    struct nodo *sentinela = (*raiz)->parent;
    struct nodo *y = x->right;

    x->right = y->left;
    if (y->left != sentinela)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == sentinela)
        (*raiz) = y;
    else
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rotation_right(struct nodo **raiz, struct nodo *x)
{
    struct nodo *sentinela = (*raiz)->parent;
    struct nodo *y = x->left;

    x->left = y->right;
    if (y->right != sentinela)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == sentinela)
        (*raiz) = y;
    else
    {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void imprimirEmOrdem(struct nodo* nodo)
{
    if (nodo->chave != LIXO)
    {
        imprimirEmOrdem(nodo->left);
        if (nodo->colour == BLACK)
        {
            printf("(B)%d ", nodo->chave);
            if (nodo->parent->chave == LIXO)
                printf("[QUALQUER]\n");
            else if (nodo->parent->left == nodo)
                printf("[%de]\n", nodo->parent->chave);
            else
                printf("[%dd]\n", nodo->parent->chave);
        }
        else
        {
            printf("(R)%d ", nodo->chave);
            if (nodo->parent->chave == LIXO)
                printf("[QUALQUER]\n");
            else if (nodo->parent->left == nodo)
                printf("[%de]\n", nodo->parent->chave);
            else
                printf("[%dd]\n", nodo->parent->chave);
        }
    }
}

void imprimirEmLargura(struct nodo* raiz)
{

}

struct nodo *buscar(struct nodo *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("ARVORE INEXISTENTE\n");
        return NULL;
    }

    if (raiz->chave == chave)
        return raiz;

    struct nodo *retorno = raiz;
    retorno = buscar(raiz->left, chave);
    if (retorno->chave != LIXO)
        return retorno;
    retorno = buscar(raiz->right, chave);
    if (retorno->chave != LIXO)
        return retorno;
    
    return raiz->parent;
}

void redblack_insert_fixup(struct nodo **raiz, struct nodo *z)
{
    while (z->parent->colour == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct nodo *y = z->parent->parent->right;
            if (y->colour == RED)
            {
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotation_left(raiz, z);
                }

                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                rotation_right(raiz, z->parent->parent);
            }
        }
        else
        {
            struct nodo *y = z->parent->parent->left;
            if (y->colour == RED)
            {
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotation_right(raiz, z);
                }

                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                rotation_left(raiz, z->parent->parent);
            }
        }
    }

    (*raiz)->colour = BLACK;
}

struct nodo *inserir(struct nodo **raiz, int chave)
{
    if (*raiz == NULL)
    {
        struct nodo *sentinela = node_create(LIXO);
        sentinela->colour = BLACK;

        struct nodo *new_node = node_create(chave);
        new_node->colour = BLACK;
        new_node->left = sentinela;
        new_node->right = sentinela;
        new_node->parent = sentinela;
        *raiz = new_node;

        return *raiz;
    }

    struct nodo *sentinela = (*raiz)->parent;

    if (buscar((*raiz), chave) == sentinela)
    {
        printf("Falha ao inserir\n");
        return *raiz;
    }

    struct nodo *z = node_create(chave);
    struct nodo *x = *raiz;
    struct nodo *y = sentinela;

    while (x != sentinela)
    {
        y = x;
        if (z->chave < x->chave)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == sentinela)
        (*raiz) = z;
    else
    {
        if (z->chave < y->chave)
            y->left = z;
        else
            y->right = z;
    }

    redblack_insert_fixup(raiz, z);
    return (*raiz);
}