/* COSTEA mihai 312CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

TLG AlocCelula(const void *info,size_t dime)
{
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
	{
		erraf
	}
	aux->info = malloc(dime);
	if(!aux->info)
	{
		free(aux);
		erraf
	}
	memcpy(aux->info, info, dime);
	aux->urm = NULL;
	return aux;
}