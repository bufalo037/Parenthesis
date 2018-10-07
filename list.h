/* COSTEA mihai 312CB */

#ifndef __ListaG__
#define __ListaG__


typedef void (*eliminare)(void *);

typedef struct
{
	unsigned int ID;
	char p;
}paranteza;

typedef struct cel 
{
	void *info;
	struct cel *urm;
}TCelulaG, *TLG, **ALG;

#endif