#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "Expo.h"

/* adiciona números entre 0 e 9 em uma lista */
Lista *
convert_to_list(char *number) 
{	
	Lista *list;
	list = criar();
	for(; *number != '\0'; number++)
		if(*number - '0' >= 0 && *number - '0' <= 9)
			inserir_ultimo(list, *number - '0');
	return list;
}

/* adiciona 0's a esquerda da menor lista */
void
add_zeros(Lista *a, Lista *b)
{
	Lista *tmp;		
	tmp = (tamanho(a) > tamanho(b)) ? b : a;
	while (tamanho(a) != tamanho(b))
		inserir_primeiro(tmp, 0);
}

/* remove 0's a esquerda */
void
remove_zeros(Lista *l)
{ 
	while (tamanho(l) > 1 && ler_pos(l, 0) == 0) 
		remover_primeiro(l);	
}

/* soma duas listas */
Lista *
sum_lists(Lista *a, Lista *b) 
{
	Lista *sum;
	unsigned char carry_out; 
	int size_l;
	sum = criar();
	add_zeros(a, b);
	carry_out = 0;
	size_l = tamanho(a);
	for(; size_l != 0; size_l--)
	{
		int hold = ler_pos(a, size_l - 1) + ler_pos(b, size_l - 1) + carry_out;
		inserir_primeiro(sum, hold % 10);
		carry_out = hold / 10;
	}
	inserir_primeiro(sum, carry_out);
	remove_zeros(sum);
	remove_zeros(a);
	remove_zeros(b);
	return sum;
}

/* multiplica duas listas */
Lista *
multiply_lists(Lista *a, Lista *b) 
{
	Lista *mp, *tmp;
	int i;
	mp = criar();
	for (i = 0; i < tamanho(b); i++)
    	{
        	int hold = ler_pos(b, i);
		inserir_ultimo(mp, 0);
       		for (; hold != 0; hold--)
       		{
			tmp = sum_lists(mp, a);
			destruir(mp);
			mp = tmp;
        	}
    	}
	return mp;
}

/* exponenciação de duas listas, sendo 'a' a base e 'b' o expoente */
Lista *
exponentiation_lists(Lista *a, Lista *b) 
{
	Lista *exp, *tmp;
	int i;
	exp = criar();
	inserir_ultimo(exp, 1);
	for(i = 0; i < tamanho(b); i++)
	{
		uint64_t hold = pow(10.0, tamanho(b) - i - 1) * ler_pos(b, i);
		for(; hold != 0; hold--)
		{
			tmp = multiply_lists(exp, a);
			destruir(exp);
			exp = tmp;
		}
	}
	return exp;
}
