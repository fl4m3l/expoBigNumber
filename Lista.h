#ifndef _LISTA_H
#define _LISTA_H

typedef struct lista Lista;
   
Lista	*criar();
void	destruir(Lista *);

void	limpar(Lista *);
void 	inserir_pos(Lista *, int, int); 
void 	inserir_primeiro(Lista *, int);
void 	inserir_ultimo(Lista *, int);
void 	escrever_pos(Lista *, int, int);
void	remover(Lista *, int);
void    remover_todos(Lista *, int);
void    inverter(Lista *);
int	    remover_pos(Lista *, int);
int 	remover_primeiro(Lista *);
int	    remover_ultimo(Lista *);

void	imprimir(Lista *);
int	    tamanho(Lista *);
int 	esta_vazia(Lista *);
int 	ler_pos(Lista *, int);
int	    primeiro(Lista *);
int 	ultimo(Lista *);
int 	buscar(Lista *, int);

#endif /*_LISTA_H*/

