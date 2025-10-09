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

struct nodo sentinela = {.chave = LIXO, .colour = BLACK, .left = &sentinela, .right = &sentinela, .parent = &sentinela};

struct queue_node
{
    struct nodo *conteudo;
    struct queue_node *next;
};

struct queue
{
    struct queue_node *start;
    struct queue_node *end;
};

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
    new_node->left = &sentinela;
    new_node->right = &sentinela;
    new_node->parent = &sentinela;

    return new_node;
}

struct queue *queue_create()
{
    struct queue *q = malloc(sizeof(struct queue));
    if (!q)
    {
        fprintf(stderr, "Falha ao alocar memoria\n");
        exit(1);
    }

    q->start = NULL;
    q->end = NULL;

    return q;
}

void enqueue(struct queue *q, struct nodo *in)
{
    struct queue_node *novo = malloc(sizeof(struct queue_node));
    if (!novo)
    {
        fprintf(stderr, "Falha ao alocar memoria\n");
        exit(1);
    }

    novo->conteudo = in;
    novo->next = NULL;

    if (q->start == NULL)
    {
        q->start = novo;
        q->end = novo;
    }
    else
    {
        q->end->next = novo;
        q->end = novo;
    }
}

struct nodo *dequeue(struct queue *q)
{
    if (q->start == NULL)
        return NULL;

    struct queue_node *removido = q->start;
    struct nodo *valor = removido->conteudo;

    q->start = removido->next;

    if (q->start == NULL)
        q->end = NULL;

    free(removido);
    return valor;
}

void queue_destroy(struct queue *q)
{
    while (q->start != NULL)
    {
        struct queue_node *temp = q->start;
        q->start = q->start->next;
        free(temp);
    }
    free(q);
}

void rotation_left(struct nodo **raiz, struct nodo *x)
{
    struct nodo *y = x->right;

    x->right = y->left;
    if (y->left != &sentinela)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == &sentinela)
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
    struct nodo *y = x->left;

    x->left = y->right;
    if (y->right != &sentinela)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == &sentinela)
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

void transplant(struct nodo **raiz, struct nodo *u, struct nodo *v)
{
    if (u->parent == &sentinela)
        (*raiz) = v;
    else
        if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
    
    v->parent = u->parent;
}

struct nodo *minimum(struct nodo *x)
{
    while (x->left != &sentinela)
        x = x->left;

    return x;
}

void imprimirEmOrdem(struct nodo* nodo)
{
    if (nodo == &sentinela)
        return;

    imprimirEmOrdem(nodo->left);

    printf("%d ", nodo->chave);

    imprimirEmOrdem(nodo->right);
}

struct nodo *buscar(struct nodo *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("ARVORE INEXISTENTE\n");
        return NULL;
    }

    struct nodo *atual = raiz;

    while (atual != &sentinela)
    {
        if (chave == atual->chave)
            return atual;
        if (chave < atual->chave)
            atual = atual->left;
        else
            atual = atual->right;
    }

    return &sentinela;
}

void imprimirEmLargura(struct nodo* raiz)
{
    if (raiz == &sentinela)
        return;
    
    struct queue *q = queue_create();
    struct nodo *atual;
    int nivel = 0;

    enqueue(q, raiz);
    int nodos_no_nivel = 1;
    int prox_nivel = 0;

    printf("[%d] ", nivel);

    while (q->start != NULL)
    {
        atual = dequeue(q);
        nodos_no_nivel--;

        if (atual->colour == BLACK)
            printf("(B)");
        else
            printf("(R)");
        printf("%d ", atual->chave);

        if (atual->parent == &sentinela)
            printf("[QUALQUER]");
        else if (atual->parent->left == atual)
            printf("[%de]", atual->parent->chave);
        else
            printf("[%dd]", atual->parent->chave);

        printf("    ");

        if (atual->left != &sentinela)
        {
            enqueue(q, atual->left);
            prox_nivel++;
        }
        if (atual->right != &sentinela)
        {
            enqueue(q, atual->right);
            prox_nivel++;
        }

        if (nodos_no_nivel == 0 && q->start != NULL)
        {
            printf("\n");
            nivel++;
            printf("[%d] ", nivel);
            nodos_no_nivel = prox_nivel;
            prox_nivel = 0;
        }
    }

    printf("\n");
    queue_destroy(q);
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

void redblack_delete_fixup(struct nodo **raiz, struct nodo *x)
{
    while (x != (*raiz) && x->colour == BLACK)
    {
        if (x == x->parent->left)
        {
            struct nodo *w = x->parent->right;
            if (w->colour == RED)
            {
                w->colour = BLACK;
                x->parent->colour = BLACK;
                rotation_left(raiz, x->parent);
                w = x->parent->right;

            }
            if (w->left->colour == BLACK && w->right->colour == BLACK)
            {
                w->colour = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->colour == BLACK)
                {
                    w->left->colour = BLACK;
                    w->colour = RED;
                    rotation_right(raiz, w);
                    w = x->parent->right;
                }
                w->colour = x->parent->colour;
                x->parent->colour = BLACK;
                w->right->colour = BLACK;
                rotation_left(raiz, x->parent);
                x = (*raiz);
            }
        }
        else
        {
            struct nodo *w = x->parent->left;
            if (w->colour == RED)
            {
                w->colour = BLACK;
                x->parent->colour = BLACK;
                rotation_right(raiz, x->parent);
                w = x->parent->left;

            }
            if (w->right->colour == BLACK && w->left->colour == BLACK)
            {
                w->colour = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->colour == BLACK)
                {
                    w->right->colour = BLACK;
                    w->colour = RED;
                    rotation_left(raiz, w);
                    w = x->parent->left;
                }
                w->colour = x->parent->colour;
                x->parent->colour = BLACK;
                w->left->colour = BLACK;
                rotation_right(raiz, x->parent);
                x = (*raiz);
            }
        }
    }
    x->colour = BLACK;
}

struct nodo *inserir(struct nodo **raiz, int chave)
{
    if (*raiz == NULL)
    {
        struct nodo *new_node = node_create(chave);
        new_node->colour = BLACK;
        new_node->parent = &sentinela;
        *raiz = new_node;
        //printf("RAIZ CRIADA\n");

        return *raiz;
    }

    if (buscar((*raiz), chave) != &sentinela)
    {
        printf("Falha ao inserir\n");
        return &sentinela;
    }

    struct nodo *z = node_create(chave);
    struct nodo *x = *raiz;
    struct nodo *y = &sentinela;

    while (x != &sentinela)
    {
        y = x;
        if (z->chave < x->chave)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == &sentinela)
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

int excluir(struct nodo **raiz, int chave)
{
    struct nodo *z = buscar((*raiz), chave);
    if (z == &sentinela)
        return 0;

    struct nodo *y = z;
    struct nodo *x;
    bool original_colour = y->colour;

    if (z->left == &sentinela)
    {
        x = z->right;
        transplant(raiz, z, z->right);
    }
    else
    {
        if (z->right == &sentinela)
        {
            x = z->left;
            transplant(raiz, z, z->left);
        }
        else
        {
            y = minimum(z->right);
            original_colour = y->colour;
            x = y->right;
            if (y != z->right)
            {
                transplant(raiz, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            else
                x->parent = y;
            transplant(raiz, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->colour = z->colour;
        }
    }
    if (original_colour == BLACK)
        redblack_delete_fixup(raiz, x);

    free(z);
        
    return 1;
}

void destruirArvore(struct nodo *raiz)
{
    if (raiz == &sentinela)
        return;

    destruirArvore(raiz->left);
    destruirArvore(raiz->right);
    free(raiz);
}