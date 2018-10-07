/* COSTEA mihai 312CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

coada *AlocareCozi (int nrQ,size_t dime,eliminare elim)
{
	coada *queue;
	int i;
	queue = (coada *)malloc(sizeof(coada) * nrQ);
	if(!queue)
	{
		erraf	
	}
	for (i = 0; i < nrQ; i++)
	{
		queue[i].dime = dime; 
		queue[i].eli = elim;
		queue[i].nrel = 0;
		queue[i].ic = queue[i].sc = NULL;
	}
	return queue;
}


int intrq(coada *queue,void *info)
{
	TLG aux;
	aux = AlocCelula(info,queue->dime);
	if(!aux)
	{
		erraf0
	}
	(queue->nrel)++;
	if(!(queue->ic))
	{
		queue->ic = queue->sc = aux;
	}
	else
	{

		queue->sc->urm = aux;
		queue->sc = aux;
	}
	return 1;
}


void *extrq(coada *queue)
{
	if(coadavida(queue))
	{
		return NULL;
	}
	(queue->nrel)--;
	TLG aux;
	void *info;
	aux = queue->ic;
	info = (void *)aux->info;
	queue->ic = aux->urm;

	if(coadavida(queue))
	{
		queue->sc = NULL;
	}

	free(aux);
	return info;
	
}


int printq(FILE *output,coada *queue,int nrQ)
{
	int i;
	paranteza *bracket;
	coada *queueaux;
	queueaux = AlocareCozi(1,queue->dime,queue->eli);
	if(!queueaux)
	{
		return 0;
	}
	for(i = 0;i < nrQ;i++)
	{
		fprintf(output,"\"");
		while ( coadavida(queue + i) == 0) 
		{
			bracket = (paranteza *)extrq(queue + i);
			fprintf(output,"%c",bracket->p);
			if(intrq(queueaux, bracket) == 0)
			{
				free(queueaux);
				return 0;
			}
			queue->eli(bracket);
		}
		(queue + i)->ic = queueaux->ic;
		(queue + i)->sc = queueaux->sc;
		queueaux->ic = NULL;
		queueaux->sc = NULL;
		fprintf(output,"\"\n");
	}
	free(queueaux);
	return 1;
}


int sortq(coada *queue) 
{
	int ok=0;
	paranteza *info;
	paranteza *info2;
	stiva *stackaux;
	stackaux = AlocareStive(1,queue->dime,queue->eli);
	while(coadavida(queue) == 0)
	{
		info = (paranteza *)extrq(queue);
		if(stivavida(stackaux))
		{
			push(stackaux,info);
			stackaux->eli(info);
		}
		else
		{	
			info2 = (paranteza *)pop(stackaux);
			while(info2->ID < info->ID) // ca sa nu mai rastorn odata stiva
			{

				intrq(queue,info2);
				if(stivavida(stackaux) == 1)
				{
					ok = 1;
					break;
				}
				stackaux->eli(info2);

				info2 = (paranteza *)pop(stackaux);
			}

			if(ok == 0)
				push(stackaux,info2);
			
			stackaux->eli(info2);
			push(stackaux,info);
			stackaux->eli(info);
			ok=0;
		}
	}

	while (stivavida(stackaux) == 0)
	{
		info = pop(stackaux);
		intrq(queue,info);
		queue->eli(info);
	}

	free(stackaux);

	return 1;
}


int correctq(FILE *output,coada *queue)
{
	paranteza *info;
	stiva *stackaux,*stackaux2;

	stackaux = AlocareStive(1,queue->dime,free);
	stackaux2 = AlocareStive(1,queue->dime,free);


	while(coadavida(queue) == 0)
	{
		info = (paranteza *)extrq(queue);
		push(stackaux,info);	
		queue->eli(info);
	}

	corrects(output,stackaux);
	rastoarna(stackaux2,stackaux);

	while(stivavida(stackaux2) == 0)
	{
		info = (paranteza *)pop(stackaux2);
		intrq(queue,info);	
		queue->eli(info);
	}


	free(stackaux2);
	free(stackaux);

	return 1;
}


/*
	Nu merge, nush dc totusi...este o copie f buna a lui corrects
int correctq(FILE *output,coada *queue)
{
	paranteza *aux, *info, *info2;
	stiva *paranteze;
	coada *queueaux;
	int i = -1, dif, max = 0, nrparanteze = 0;
	char *nr;

	aux = malloc(sizeof(paranteza)); 
	nr = calloc(queue->nrel, sizeof(char)); 
	paranteze = AlocareStive(1, sizeof(paranteza), free);
	queueaux = AlocareCozi(1, queue->dime, queue->eli);
	while(coadavida(queue) == 0)
	{
		i++;
		info = (paranteza *)extrq(queue);
		intrq(queueaux,info);
		if(strchr("([{",info->p)) // pune in paranteze info
		{
			aux->p = info->p;
			aux->ID = i; // modific ID-ul sa le am aranjate in ordine
			push(paranteze,aux);
		}
		else
		{
			if(stivavida(paranteze) == 0) 
			{
				info2 = (paranteza *)pop(paranteze);
				dif = info->p - info2->p; // dif este 1 sau 2 pt un caz corect
				if(dif > 0 && dif <= 2)
				{
					nr[i] = 1;
					nr[info2->ID] = 1;
				}
				else
				{
					ElimElemStive(paranteze,1);
				}
				paranteze->eli(info2);
			}
		}
		queue->eli(info);
	}
	queue->ic = queueaux->ic;
	queue->sc = queueaux->sc;
	queueaux->ic = NULL;
	queueaux->sc = NULL;


	for(i = 0;i < queue->nrel;i++)
	{
		if(nr[i] == 1)
		{
			nrparanteze++;
		}
		else
		{
			if(max < nrparanteze)
				max = nrparanteze;
			nrparanteze = 0;
		}
	}
	if(max < nrparanteze) // trebuie sa verifice si la iesire
		max = nrparanteze;

	fprintf(output,"%d\n",max);

	//DistrugereCozi(queueaux,1);
	free(queueaux);
	DistrugereStive(paranteze,1);
	free(nr);
	free(aux);
	return 1;
}

*/

void ElimElemCozi(coada *queue,int nrQ)
{
	int i;
	void *info;
	for(i = 0;i < nrQ;i++)
	{
		while(coadavida(queue + i) == 0)
		{
			info = extrq(queue + i);
			(queue + i)->eli(info);
		}
	}
}

void DistrugereCozi(coada *queue, int nrQ)
{
	ElimElemCozi(queue,nrQ);
	free(queue);
}