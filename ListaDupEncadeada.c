#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"

typedef struct no No;

struct lista 
{
	No *ini, *fim;
	int tam;
};

struct no 
{
	No *prox;
	No *ant;
	int info;
};

Lista *
criar() 
{
	Lista *l;
	if ((l = (Lista *)malloc(sizeof(Lista))) == NULL)
	{
		printf("Erro ao alocar memoria");
		exit(1);
	}
	if ((l->ini = (No *)malloc(sizeof(No))) == NULL)
	{
		printf("Erro ao alocar memoria");
		exit(1);
	}
	if((l->fim = (No *)malloc(sizeof(No))) == NULL)
	{
		printf("Erro ao alocar memoria");
		exit(1);
	}
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->ini->ant = NULL;
	l->fim->prox = NULL;
	l->tam = 0;
	return l;
}

void 
destruir(Lista *l) 
{
	if (l != NULL) {
		limpar(l);
		free(l->ini);
		free(l->fim);
		free(l);
	}
}

void 
limpar(Lista *l) 
{
	No *aux, *aux2;
	aux = l->ini->prox;
	while (aux != l->fim) 
	{
		aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->tam = 0;	
}

void 
imprimir(Lista *l) 
{
	No *aux;
	aux = l->ini->prox;
	while (aux != l->fim) 
	{
		printf("%d", aux->info);
		aux = aux->prox;
	}	
	printf("\n");
}

int 
tamanho(Lista *l)
{
	return l->tam;	
}

int 
esta_vazia(Lista *l) 
{
	return tamanho(l) == 0;
}

int 
ler_pos(Lista *l, int p) 
{
	No *aux;	
	int i, meio;
	if (p < 0 || p >= tamanho(l))
	{
		printf("Posicao invalida!\n");
		return -1;
	}
	if (p > tamanho(l) / 2)
	{
		aux = l->fim->ant;
		for (i = tamanho(l) - 1; i > p; i--) 
		{
			aux = aux->ant;
		}
	}
	else
	{
		aux = l->ini->prox;
		for(i = 0; i < p; i++)
		{
			aux = aux->prox;
		}
	}
	return aux->info;
}

int 
primeiro(Lista *l) 
{
	return ler_pos(l, 0);
}

int 
ultimo(Lista *l) 
{
	return ler_pos(l, tamanho(l) - 1);	
}

int 
buscar(Lista *l, int v) 
{
	No *aux;	
	int p;
	p = 0;
	aux = l->ini->prox;
	while (aux != l->fim && aux->info != v) 
	{
		aux = aux->prox;
		p++;
	}		
	return aux != l->fim ? p : -1;
}

void 
escrever_pos(Lista *l, int p, int v)
{
	No *aux;	
	int i;
	if (p < 0 || p >= tamanho(l))
	{
		printf("Posicao invalida!\n");
		return;
	}
	aux = l->ini->prox;
	for (i = 0; i < p; i++) 
	{
		aux = aux->prox;
	}		
	aux->info = v;
}

void 
inserir_pos(Lista *l, int p, int v) 
{
	No *aux, *aux2;	
	int i;
	if (p < 0 || p > tamanho(l)) 
	{
		printf("Posicao invalida!\n");
		return;
	}
	aux = l->ini;
	if ((aux2 = (No *)malloc(sizeof (No))) == NULL)
	{
		printf("Erro ao alocar memoria");
		exit(1);
	}
	aux2->info = v;
	for (i = 0; i < p; i++)
	{
		aux = aux->prox;
	}		
	aux2->prox = aux->prox;
	aux->prox->ant = aux2;
	aux->prox = aux2;
	aux2->ant = aux;
	l->tam++;
} 

void 
inserir_primeiro(Lista *l, int v)
{
	inserir_pos(l, 0, v);
}

void 
inserir_ultimo(Lista *l, int v) 
{
	inserir_pos(l, tamanho(l), v);	
}

int 
remover_pos(Lista *l, int p) 
{
	No *aux, *aux2;
	int i, v;	
	
	if (p < 0 || p >= tamanho(l)) 
	{
		printf("Posicao invalida!\n");
		return -1;
	}
	aux = l->ini;
	for (i = 0; i < p; i++) 
	{
		aux = aux->prox;
	}	
	aux2 = aux->prox;
	aux->prox = aux2->prox;
	aux->prox->ant = aux;
	v = aux2->info;
	free(aux2);
	l->tam--;			
	return v;
}

int 
remover_primeiro(Lista *l) 
{
	return remover_pos(l, 0);
}

int 
remover_ultimo(Lista *l) 
{
	return remover_pos(l, tamanho(l)-1);
}

void 
remover(Lista *l, int v)
{
	No *aux2;
	aux2 = l->ini->prox;
	while (aux2 != l->fim && aux2->info != v)
	{
		aux2 = aux2->prox;
	}
	if (aux2 != l->fim) 
	{
		aux2->ant->prox = aux2->prox;
		aux2->prox->ant = aux2->ant;
		free(aux2);
		l->tam--;					
	}
}

void 
remover_todos(Lista *l, int v)
{
	No *aux, *aux2;
	aux2 = l->ini->prox;
	while (aux2 != l->fim) 
	{
		while (aux2 != NULL && aux2->info != v) 
		{
			aux2 = aux2->prox;
		}
		if (aux2 != l->fim) 
		{
			aux2->ant->prox = aux2->prox;
			aux2->prox->ant = aux2->ant;
			aux = aux2->prox;
			free(aux2);
			aux2 = aux;
			l->tam--;				
		}		
	}
}

void
inverter(Lista *l)
{
	No *i, *j;
	int tmp;
	i = l->ini->prox;
	j = l->fim->ant;
	while (i != j && i->ant != j) {
		tmp = i->info;
		i->info = j->info;
		j->info = tmp;
		i = i->prox;
		j = j->ant;
	}
}
