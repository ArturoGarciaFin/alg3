#ifndef _DICTIONARY_
#define _DICTIONARY_

#include <stdint.h>
#include <stdlib.h>

#define MAX_NOME 30
#define TAM_DICT 50

struct pessoa
{
    char nome [MAX_NOME];
    unsigned char idade;
    uint64_t cpf;
};

struct dicionario_pessoa
{
    struct pessoa *pessoas[TAM_DICT];
    int numItens;
};

struct dicionario_pessoa *inicializar();
struct pessoa *buscar(uint64_t chave, struct dicionario_pessoa *dict);
char inserir(struct pessoa *pessoa, struct dicionario_pessoa *dict);
struct pessoa *remover(uint64_t chave, struct dicionario_pessoa *dict);

#endif