/* COSTEA mihai 312CB */

#include "list.h"


//=============================================================================

#ifndef __Coada__
#define __Coada__

#define coadavida(q) ( (q)->ic == NULL ? 1 : 0 ) 

typedef struct 
{
	size_t dime;
	size_t nrel;
	eliminare eli; 

	TLG ic,sc;
}coada;

#endif

//=============================================================================

#ifndef __FunctiiCoada__
#define __FunctiiCoada__

coada *AlocareCozi (int,size_t,eliminare);
int intrq(coada * ,void *);
void *extrq(coada *);
int printq(FILE *,coada *,int);
int sortq(coada *);
int correctq(FILE *,coada *);
void ElimElemCozi(coada *,int);
void DistrugereCozi(coada *, int);


#endif

//=============================================================================