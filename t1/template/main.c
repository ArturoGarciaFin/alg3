#include <stdio.h>
#include <stdlib.h>

#include "redblack.h"

struct nodo SENTINELA = {.chave = LIXO, .colour = BLACK, .left = &SENTINELA, .right = &SENTINELA, .parent = &SENTINELA};

int main()
{
	struct nodo* raiz = NULL;
	
	//imprimirDadosAluno();

	char op;
	int val;
	scanf(" %c", &op);
	while(op != 'f'){
		switch (op) {
			case 'i':
				scanf("%d", &val);
				inserir(&raiz, val);
				break;
			case 'r':
				scanf("%d", &val);
				if(!excluir(&raiz, val))
					fprintf(stderr,"Falha ao remover %d.\n", val);
				break;
			case 'e':
				imprimirEmOrdem(raiz);
				printf("\n");
				break;
			case 'l':
				imprimirEmLargura(raiz);
				break;
			case 'b':
			 	scanf("%d", &val);
				struct nodo* valB = buscar(raiz, val);
				if(valB->chave != LIXO)
					printf("Encontrado %d\n", valB->chave);
				else
					printf("Nao encontrado %d.\n", val);
				break;
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	destruirArvore(raiz);

	return 0;
}