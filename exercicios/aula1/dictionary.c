#include "dictionary.h"
#include <stdio.h>

struct dicionario_pessoa *inicializar()
{
    struct dicionario_pessoa *dict = (struct dicionario_pessoa*)malloc(sizeof(struct dicionario_pessoa));
    if (!dict)
    {
        fprintf(stderr, "erro malloc inicializar_dicionario");
        return NULL;
    }
    for (size_t i = 0; i <= TAM_DICT; i++)
        dict->pessoas[i] = NULL;
    dict->numItens = 0;
    return dict;
}

struct pessoa *buscar(uint64_t chave, struct dicionario_pessoa *dict)
{
    for (size_t i = 0; i < dict->numItens; i++)
    {
        if (chave == dict->pessoas[i]->cpf)
            return dict->pessoas[i];
    }

    return NULL;
}

char inserir(struct pessoa *pessoa, struct dicionario_pessoa *dict)
{
    printf("%d %d\n", dict->numItens, TAM_DICT);
    if (dict->numItens > TAM_DICT)
        return 0;
    
    dict->pessoas[dict->numItens] = pessoa;
    dict->numItens++;
    return 1;
}

struct pessoa *remover(uint64_t chave, struct dicionario_pessoa *dict)
{
    struct pessoa *rem = buscar(chave, dict);
    if (!rem)
        return NULL;
    
    dict->numItens--;
    return rem;
}