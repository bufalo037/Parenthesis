/* COSTEA mihai 312CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc,char *argv[])
{

	FILE *input,*output;
	void *info;
	int N,nrS,nrQ,i,ID;
	char *command;

	input = fopen(argv[1],"r");
	output = fopen(argv[2],"w");
	fscanf(input,"%d %d %d",&N,&nrS,&nrQ);

	//=========================================================================

	command = (char *)malloc( sizeof(char) * 9);
	if(!command)
	{
		erram //macro (look functii.h)
	}

	//=========================================================================

	paranteza * braket;
	braket = (paranteza *)malloc( sizeof(paranteza));
	if (!braket)
	{
		free(command);
		erram
	}

	//=========================================================================

	coada *queue;
	queue = AlocareCozi(nrQ, sizeof(paranteza), free);
	if(!queue)
	{
		free(command);
		free(braket);
		exit(EXIT_FAILURE);
	}

	//=========================================================================

	stiva *stack;
	stack = AlocareStive(nrS, sizeof(paranteza), free);
	if(!stack)
	{
		free(command);
		free(braket);
		free(queue);
		exit(EXIT_FAILURE);
	}

	//=========================================================================
	//=========================================================================
	//incepe parsarea fisierului si apelarea functiilor necesare 


	for (i = 0;i < N;i++)
	{
		fscanf(input,"%s",command);

		//=====================================================================

		if ( strcmp(command,"intrq") == 0)
		{
			fscanf(input,"%d %d %c",&ID,&(braket->ID),&(braket->p));
			if( intrq(queue + ID,(void *)braket) == 0)
			{
				//frees
				exit(EXIT_FAILURE);
			}
			continue;
		}
		//=====================================================================

		if ( strcmp(command,"extrq") == 0)
		{
			fscanf(input,"%d",&ID);
			info = extrq(queue + ID);
			if(info != NULL)
				queue->eli(info); 
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"sortq") == 0)
		{
			fscanf(input,"%d",&ID);
			sortq(queue + ID);
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"printq") == 0)
		{
			if( printq(output, queue, nrQ) == 0)
			{
				//frees
				exit(EXIT_FAILURE);
			}
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"correctq") == 0)
		{
			fscanf(input,"%d",&ID);
			correctq(output,queue + ID);
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"push") == 0)
		{
			fscanf(input,"%d %d %c",&ID,&(braket->ID),&(braket->p));
			if( push(stack + ID,braket) == 0)
			{
				//frees
				exit(EXIT_FAILURE);
			}
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"pop") == 0)
		{

			fscanf(input,"%d",&ID);
			info = pop(stack +ID);
			if(info)
				stack->eli(info);
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"sorts") == 0)
		{
			fscanf(input,"%d",&ID);
			if(sorts(stack+ID) == 0)
			{
				//frees
			}
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"prints") == 0)
		{
			if(prints(output,stack,nrS) == 0)
			{
				//frees	
				exit(EXIT_FAILURE);
			}
			continue;
		}

		//=====================================================================

		if ( strcmp(command,"corrects") == 0)
		{
			fscanf(input,"%d",&ID);
			corrects(output,stack + ID);
		}
	}

	fclose(input);
	fclose(output);

	//=========================================================================

	free(command);
	free(braket);
	DistrugereCozi(queue,nrQ);
	DistrugereStive(stack,nrS);

	return 0;

}