/* COSTEA mihai 312CB */

#include "list.h"

//=============================================================================

#ifndef __Stiva__
#define __Stiva__

#define stivavida(s) ( (s)->vf == NULL ? 1 : 0 )

typedef struct
{
	size_t dime;
	size_t nrel;
	eliminare eli; // am lasat decat pointer la functie de eliminare pt ca
	// decat eliminarea se raporteaza la toata structura
	// cazuile de sortare, afisare le-am luat ca cazuri particulare
	// ale tipului de data folosit in exercitiu.
	// Deoarece afisarea, sortarea nu se face pt toate elementele din cadrul
	// structurii la difinirea unei noi structuri structura de tip stiva sau
	// coada ar fi fost invalida, avand mai putine sau mai multe campuri 
	TLG vf;
}stiva;

#endif

//=============================================================================

#ifndef __FunctiiStiva__
#define __FunctiiStiva__

stiva *AlocareStive(int ,size_t,eliminare);
int push(stiva *, void *);
void *pop(stiva *);
void rastoarna(stiva *, stiva *);
int prints(FILE *,stiva *, int);
int sorts(stiva *);
int corrects(FILE *,stiva *);
void ElimElemStive(stiva *,int);
void DistrugereStive(stiva *,int);
int set_lungmax(int nr, int lmax);
int verificare_inapoi (stiva *paranteze,int *nr,int i);
void Redimensionare_stiva_paranteze(int *NrStiveDeParanteze,int factoraditiv,
	int **nr,stiva **paranteze);

#endif

//=============================================================================