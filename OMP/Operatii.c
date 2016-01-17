//Implementare Add,Sub,Mult,Divi,Sqrt,Pow
// Am presupus ca PrelucrareArbore are parametru asa
// gcc fisier -lm -o output ca sa mearga pow si sqrt





#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "Operatii.h"

void Add(struct TNod *stg,struct TNod *drp, struct TNod *lel)
{
		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
		
			*(lel->rez) = *(stg->rez)+*(drp->rez);
}


void Sub(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	PrelucrareArbore(stg);
	
	
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);

	//#pragma omp taskwait	
	*(lel->rez) = a-b;

}

void Mult(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	PrelucrareArbore(stg);
	PrelucrareArbore(drp);
	*(lel->rez) = *(stg->rez) * *(drp->rez);

}


void Divi(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;
	PrelucrareArbore(stg);
	
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);
	*(lel->rez) = a/b;

}


//ordin 2 
void SqrtCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;
	
	PrelucrareArbore(stg);

	b = *(stg->rez);
	*(lel->rez) = sqrt(b);

}


//stanga este baza iar drp este puterea
void PowCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	PrelucrareArbore(stg);
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);
	*(lel->rez) = pow(a,b);

}

void ReplaceChars(struct TNod *lel, char* rep, char* with){


 		if(strcmp(lel->info, rep)==0)
		{					
				memset(lel->info,0,sizeof(lel->info));
				strcpy(lel->info, with);
						
			
				
		}
	
		#pragma omp task firstprivate(lel)
		if(strcmp(lel->info,"sum")==0 || strcmp(lel->info,"prod")==0)
		{
		
				ReplaceChars(lel->dr,rep,with);
				
		}
		else if(strcmp(lel->info,"+")==0 || strcmp(lel->info,"-")==0 || strcmp(lel->info,"*")==0 || strcmp(lel->info,"/")==0 || strcmp(lel->info,"sqrt")==0 || strcmp(lel->info,"pow")==0)
		{ 

				ReplaceChars(lel->st,rep,with);		
				ReplaceChars(lel->dr,rep,with);
				
		}


		#pragma omp taskwait

		
		
}




void FreeArb(struct TNod *radacina){
	if(radacina == NULL) return;

	if(radacina->st!=NULL)
	FreeArb(radacina->st);
	if(radacina->dr!=NULL)
	FreeArb(radacina->dr);
	
	if(radacina->rez != NULL)
		free(radacina->rez);
	else {radacina->rez = NULL;
		free(radacina->rez);
		}
	free(radacina);

}

void ClonareArb(struct TNod *radacina, struct TNod* newNode){

	if(radacina == NULL) ; 

	
	else{

	char* msg = (char*)malloc(sizeof(char) * 15);
	strcpy(msg,radacina->info);
		
	newNode->info = msg;
	
	newNode->rez = (double*)malloc(sizeof(double));
	newNode->var = radacina->var;
	newNode->start = radacina->start;
	newNode->end = radacina->end;
	}
	
	if(radacina->st != NULL){
		
				
		newNode->st = (TArb)malloc (sizeof(TNod));		
		ClonareArb(radacina->st,newNode->st);
	}

	if(radacina->dr !=NULL){
		newNode->dr = (TArb)malloc (sizeof(TNod));			
		ClonareArb(radacina->dr,newNode->dr);
	
	
	}	
	//return;
}

void Sum(struct TNod *radacina){
	
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->var;
	

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	
	double sum = 0;
	struct TNod* aux=NULL;


	for (i=start; i<=end; i++){
		aux=(TArb)malloc(sizeof(TNod));
		char* rep ;

		rep = malloc(sizeof(char));
				
		*rep = variab;
		char buffer[20];
		
		#pragma omp parallel num_threads(8)
		#pragma omp single
		ClonareArb(radacina,aux);
		
		snprintf(buffer, 20,"%i",i);
		
		
		//Inlcouire variabila cu valoarea lui i
		//#pragma omp parallel
		//#pragma omp single nowait private(aux)
			
		ReplaceChars(aux,rep,buffer);
				
		
				
		
		
		free(rep);

		
		
		
		PrelucrareArbore(aux->dr);
			
		sum += *(aux->dr->rez);
		
	//	FreeArb(aux);
		free(aux);
		}
		
	
	*(radacina->rez) += sum;
}

void Prod(struct TNod *radacina){
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->var;
	
	struct TNod* aux = NULL;
	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double prod = 1;
	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);

		//Clonez lel
		aux= (TArb)malloc(sizeof(TNod));
		#pragma omp parallel num_threads(4)
		#pragma omp single
		ClonareArb(radacina,aux);
		

		//Inlcouire variabila cu valoarea lui i
		ReplaceChars(aux, rep, buffer);
		free(rep);
		PrelucrareArbore(aux->dr);
		prod =prod * *(aux->dr->rez);
		free(aux);
		}
	
	//return prod;
	*(radacina->rez) = prod;
}

void PrelucrareArbore(struct TNod *lel){
	char * a=lel->info;
	
	if(lel->rez==NULL)
		lel->rez=(double*)malloc(sizeof(double));

	if(strcmp(a,"+")==0){
			//#pragma omp parallel
			//#pragma omp single
			Add(lel->st,lel->dr,lel);
	}else if(strcmp(a,"-")==0){
			Sub(lel->st,lel->dr,lel);
	}else if(strcmp(a,"*")==0){
		Mult(lel->st, lel->dr,lel);
	}else if(strcmp(a,"/")==0){			
		Divi(lel->st, lel->dr,lel);
	}else if(strcmp(a,"sum")==0){
			Sum(lel);
	}else if(strcmp(a,"prod")==0){
		Prod(lel);
	}else if(strcmp(a,"sqrt")==0){
		SqrtCalc(lel->st,lel->dr,lel);
	}else if(strcmp(a,"pow")==0){
		PowCalc(lel->st, lel->dr,lel);
	}else{
		*(lel->rez) = (double)atoi(a);
	}
}


