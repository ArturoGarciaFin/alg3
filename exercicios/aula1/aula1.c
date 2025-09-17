#include "dictionary.h"
#include <stdio.h>
#include <string.h>

struct pessoa *criar_pessoa(char *nome, unsigned char idade, uint64_t cpf)
{
    struct pessoa *novo = (struct pessoa*)malloc(sizeof(struct pessoa));
    if (!novo)
    {
        fprintf(stderr, "erro malloc pessoa\n");
        return NULL;
    }
    
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->cpf = cpf;

    return novo;
}

int main()
{
    struct dicionario_pessoa *dict = inicializar();
    struct pessoa *p1 = criar_pessoa("Joao", 12, 12345678900);
    struct pessoa *p2 = criar_pessoa("Pedro", 16, 00000000000);
    struct pessoa *p3 = criar_pessoa("Lucas", 20, 99999999999);
    struct pessoa *p4 = criar_pessoa("Gabriel", 7, 16285617291);
    struct pessoa *p5 = criar_pessoa("Thiago", 46, 72918375912);
    struct pessoa *p6 = criar_pessoa("Douglas", 41, 11111111111);


    //TESTE INSERCAO
    if (inserir(p1, dict))
        printf("P1 inserido com sucesso\n");
    else
        printf("Erro ao inserir p1\n");
    if (inserir(p2, dict))
        printf("P2 inserido com sucesso\n");
    else
        printf("Erro ao inserir p2\n");
    if (inserir(p3, dict))
        printf("P3 inserido com sucesso\n");
    else
        printf("Erro ao inserir p3\n");
    if (inserir(p4, dict))
        printf("P4 inserido com sucesso\n");
    else
        printf("Erro ao inserir p4\n");
    if (inserir(p5, dict))
        printf("P5 inserido com sucesso\n");
    else
        printf("Erro ao inserir p5\n\n\n");


    //TESTE BUSCA
    if (buscar(p1->cpf, dict))
        printf("P1 encontrado\n");
    else
        printf("P1 nao encontrado\n");
    if (buscar(p5->cpf, dict))
        printf("P5 encontrado\n");
    else
        printf("P5 nao encontrado\n");
    if (buscar(p6->cpf, dict))
        printf("P6 encontrado\n");
    else
        printf("P6 nao encontrado\n");

    //TESTE REMOCAO
    
}