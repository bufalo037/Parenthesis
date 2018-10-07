/* COSTEA mihai 312CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

stiva *AlocareStive(int nrS,size_t dime,eliminare elim)
{
	stiva *stack;
	int i;
	stack = (stiva *) malloc( sizeof(stiva) * nrS );
	if(!stack)
	{
		erraf
	}
	for (i = 0; i < nrS;i++)
	{
		stack[i].dime = dime;
		stack[i].eli = elim;
		stack[i].nrel = 0;
		stack[i].vf = NULL;
	}
	return stack;
}


int push(stiva *stack,void *info)
{
	TLG aux;
	aux = AlocCelula(info,stack->dime);
	if(!aux)
	{
		erraf0;
	}
	(stack->nrel)++;
	if(!stack->vf)
	{
		stack->vf = aux;
	}
	else
	{
		aux->urm = stack->vf;
		stack->vf = aux;
	}
	return 1;
}


void *pop(stiva *stack)
{
	void *info;
	if( stivavida(stack) )
	{
		return NULL;
	}
	(stack->nrel)--;
	TLG aux;
	aux = stack->vf;
	stack->vf = stack->vf->urm;
	info = aux->info;
	free(aux);
	return info;
}



void rastoarna(stiva *d, stiva *s)
{
	TLG aux;
	while(stivavida(s) == 0)
	{
		aux = s->vf;
		s->vf = aux->urm;
		aux->urm = d->vf;
		d->vf = aux;
	}
	d->nrel += s->nrel;
	s->nrel = 0;
}	


int prints(FILE *output,stiva *stack, int nrS)
{
	int i;
	paranteza *info;
	stiva *stackaux;
	stackaux = AlocareStive(1,stack->dime,stack->eli);
	if (!stackaux)
	{
		return 0;
	}
	for(i = 0;i < nrS; i++)
	{
		fprintf(output,"\"");
		rastoarna(stackaux,stack+i);
		while(stivavida(stackaux) == 0)
		{
			info = (paranteza *)pop(stackaux);
			fprintf(output,"%c",info->p);
			if(push(stack + i,info) == 0)
			{
				free(stackaux);
				return 0;
			}
			stack->eli(info);

		}
		fprintf(output,"\"\n");
	}
	free(stackaux);
	return 1;
}


int sorts(stiva *stack)
{
	coada *queueaux;
	queueaux = AlocareCozi(1,stack->dime, stack->eli);
	if(!queueaux)
	{
		return 0;
	}

	void *info;

	while(stivavida(stack) == 0)
	{
		info = pop(stack);
		if(intrq(queueaux,info) == 0)
		{
			free(queueaux);
			queueaux->eli(info);
			return 0;
		}	

		stack->eli(info);
	}

	sortq(queueaux);

	while(coadavida(queueaux) == 0)
	{
		info = extrq(queueaux);
		if(!push(stack,info))
		{
			free(queueaux);
			stack->eli(info);
			return 0;
		}
		queueaux->eli(info);
	}
	free(queueaux);

	return 1;
}


int corrects(FILE *output,stiva *stack)
{
	paranteza *aux, *info, *info2;
	stiva *paranteze, *stackaux;
	int i=-1,dif, max = 0, nrparanteze = 0;
	char *nr;

	aux = malloc(sizeof(paranteza)); 
	nr = calloc(stack->nrel,sizeof(char)); 
	paranteze = AlocareStive(1, sizeof(paranteza), free);
	stackaux = AlocareStive(1, stack->dime, stack->eli);
	while(stivavida(stack) == 0)
	{
		i++;
		info = (paranteza *)pop(stack);
		push(stackaux,info);
		if(strchr(")}]",info->p)) // pune in paranteze info
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
				dif = info2->p - info->p; // daca se potrivesc diferenta va fi 1 sau 2
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
		stack->eli(info);
	}

	rastoarna(stack,stackaux);
	for(i = 0;i < stack->nrel;i++)
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

	DistrugereStive(paranteze,1);
	DistrugereStive(stackaux,1);
	free(nr);
	free(aux);

	fprintf(output,"%d\n",max);
	
	return 1;
}	



void ElimElemStive(stiva *stack,int nrS)
{
	int i;
	void *info;
	for(i = 0; i < nrS;i++)
	{
		while(stivavida(stack + i) == 0)
		{
			info = pop(stack + i);
			(stack +i)->eli(info);
		}
	}
}

void DistrugereStive(stiva *stack,int nrS)
{
	ElimElemStive(stack,nrS);
	free(stack);
}