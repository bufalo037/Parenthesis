/* COSTEA mihai 312CB */

#include "stiva.h"
#include "coada.h"


//=============================================================================

#ifndef __Errors__
#define __Errors__

#define erram fprintf(stderr,"Eroare alocare memorie");exit(EXIT_FAILURE);
#define erraf fprintf(stderr,"Eroare alocare memorie");return NULL;
#define erraf0 fprintf(stderr,"Eroare alocare memorie");return 0;

#endif

//=============================================================================

#ifndef __Functii__
#define __Functii__

TLG AlocCelula(const void *,size_t);

#endif

//=============================================================================