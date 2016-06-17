#include <stdio.h>
#include <stdlib.h>

#include "Expo.h"

/* 	Exponenciação de um número absurdamente grande usando o TAD Lista
	Daniel Pinto de Oliveira
	Faculdade Farias Brito - Ciências da Computação
*/

int 
main(int argc, char **argv)
{	
	Lista *exp, *a, *b;
	a = convert_to_list(argv[1]);
	b = convert_to_list(argv[2]);
	exp = exponentiation_lists(a, b);
	imprimir(exp);
	destruir(a);
	destruir(b);
	return EXIT_SUCCESS;
};
