#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 16

struct nodo
{
    char operacao;
    float valor;
    struct nodo *fe;
    struct nodo *fd;
};

struct nodo *cria_nodo(char op, float val)
{
    struct nodo *new = (struct nodo*)malloc(sizeof(struct nodo));
    if (!new)
        return NULL;
    new->operacao = op;
    new->valor = val;
    new->fe = NULL;
    new->fd = NULL;

    return new;
}

void preordem(struct nodo *no)
{
    if (no != NULL)
    {
        if (no->operacao != 'v')
            printf("%c\n", no->operacao);
        else
            printf("%f\n", no->valor);

        preordem(no->fe);
        preordem(no->fd);
    }
}

void emordem(struct nodo *no)
{
    if (no != NULL)
    {
        emordem(no->fe);

        if (no->operacao != 'v')
            printf("%c\n", no->operacao);
        else
            printf("%f\n", no->valor);

        emordem(no->fd);
    }
}

void posordem(struct nodo *no)
{
    if (no != NULL)
    {
        posordem(no->fe);
        posordem(no->fd);

        if (no->operacao != 'v')
            printf("%c\n", no->operacao);
        else
            printf("%f\n", no->valor);
    }
}

void ex1(struct nodo *no, char controle)
{
    if (!controle)
        return;

    char tipo, item;
    float valor;

    printf("0 para operador, 1 para valor\n");
    getchar();
    scanf("%c", &tipo);

    if (no->fe == NULL)
    {
        if (tipo == '0')
        {
            printf("operacao:\n");
            getchar();
            scanf("%c", &item);
            no->fe = cria_nodo(item, 0);
        }
        else if (tipo)
        {
            item = 'v';
            printf("numero:\n");
            getchar();
            scanf("%f", &valor);
            no->fe = cria_nodo(item, valor);
        }
    }
    else if (no->fd == NULL)
    {
        if (tipo == '0')
        {
            printf("operacao:\n");
            getchar();
            scanf("%c", &item);
            no->fd = cria_nodo(item, valor);
        }
        else
        {
            item = 'v';
            printf("numero:\n");
            getchar();
            scanf("%f", &valor);
            no->fd = cria_nodo(item, valor);
        }
    }

    if (no->fe != NULL && no->fe->operacao != 'v')
        ex1(no->fe, 1);
    else if (no->fd != NULL && no->fd->operacao != 'v')
        ex1(no->fd, 1);
    
    if (no->fe == NULL || no->fd == NULL)
        ex1(no, controle);
}

int main()
{
    char item = 'a';
    float valor = 0;
    //char tipo = 0;
    char controle;

    printf("primeira operacao\n");
    scanf("%c", &item);
    struct nodo *raiz = cria_nodo(item, valor);
    //struct nodo *atual = raiz;

    printf("quer parar?\n");
    getchar();
    scanf("%c", &controle);
    if (controle != 0)
    {
        ex1(raiz, controle);
        /*
        printf("0 para operador, 1 para valor\n");
        getchar();
        scanf("%c", &tipo);

        if (atual->fe == NULL)
        {
            if (tipo == '0')
            {
                printf("operacao:\n");
                getchar();
                scanf("%c", &item);
                atual->fe = cria_nodo(item, valor);
            }
            else if (tipo)
            {
                item = 'v';
                printf("numero:\n");
                getchar();
                scanf("%f", &valor);
                atual->fe = cria_nodo(item, valor);
            }
        }
        else if (atual->fd == NULL)
        {
            if (tipo == '0')
            {
                printf("operacao:\n");
                getchar();
                scanf("%c", &item);
                atual->fd = cria_nodo(item, valor);
            }
            else
            {
                item = 'v';
                printf("numero:\n");
                getchar();
                scanf("%f", &valor);
                atual->fd = cria_nodo(item, valor);
            }
        }

        printf("quer sair?\n");
        getchar();
        scanf("%c", &controle);
        */
    }

    printf("PRE ORDEM:\n");
    preordem(raiz);
    printf("\n\n");

    printf("EM ORDEM\n");
    emordem(raiz);
    printf("\n\n");

    printf("POS ORDEM\n");
    posordem(raiz);

    return 0;
}