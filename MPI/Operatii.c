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
	double a,b;

	PrelucrareArbore(stg);
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);
	

	*(lel->rez) = a+b;
}


void Sub(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	PrelucrareArbore(stg);
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);
	
	*(lel->rez) = a-b;

}

void Mult(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	PrelucrareArbore(stg);
	PrelucrareArbore(drp);
	a = *(stg->rez);
	b = *(drp->rez);
	*(lel->rez) = a*b;

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
	
	//a=PrelucrareArbore(stg);
	PrelucrareArbore(stg);
printf("asdsad\n");
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
	
	char* a = lel->info;
	
	
	if(strcmp(a, rep)==0){
		memset(lel->info,0,sizeof(lel->info));
		strcpy(lel->info, with);
		
	}else if(strcmp(a,"+")==0 || strcmp(a,"-")==0 || strcmp(a,"*")==0 || strcmp(a,"/")==0 || strcmp(a,"sqrt")==0 || strcmp(a,"pow")==0){
		ReplaceChars(lel->st,rep,with);
		ReplaceChars(lel->dr,rep,with);
	}else if(strcmp(a,"sum")==0 || strcmp(a,"prod")==0){
		ReplaceChars(lel->dr,rep,with);
	}

}

void FreeArb(struct TNod *radacina){
	if(radacina == NULL) return;

	FreeArb(radacina->st);
	FreeArb(radacina->dr);
	if(radacina->info != NULL)
		free(radacina->info);
	radacina->info = NULL;

	free(radacina);
}

void ClonareArb(struct TNod *radacina, struct TNod* newNode){

	if(radacina == NULL) return;

	//printf("asdas\n");
	char* msg = (char*)malloc(sizeof(char) * 15);
	strcpy(msg,radacina->info);
	newNode->info = msg;
	
	newNode->rez = (double*)malloc(sizeof(double));
	newNode->var = radacina->var;
	newNode->start = radacina->start;
	newNode->end = radacina->end;
	
	if(radacina->st != NULL){
		newNode->st = (TArb)malloc (sizeof(TNod));
		ClonareArb(radacina->st,newNode->st);
	}
	if(radacina->dr !=NULL){
		newNode->dr = (TArb)malloc (sizeof(TNod));
		ClonareArb(radacina->dr,newNode->dr);
	}
	return;
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
	#pragma parallel for shared(start,end) private(i,sum) default(none)
	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);
		
		//itoa(i,buffer,10);
		
		//printf("33333#\n");
		//Clonez lel
		struct TNod* aux = NULL;
		aux = (TArb)malloc (sizeof(TNod));
			
		ClonareArb(radacina, aux);
		

		//Inlcouire variabila cu valoarea lui i
		
		ReplaceChars(aux, rep, buffer);
		free(rep);
		PrelucrareArbore(aux->dr);
		//printf("arb = %lf\n",*(aux->dr->rez));
		sum += *(aux->dr->rez);
	}
	//return sum;
	//printf("after\n");
	*(radacina->rez) += sum;
	//printf("before %lf\n",*(radacina->rez));
}

void Prod(struct TNod *radacina){
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->var;

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double prod = 1;
	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);

		//Clonez lel
		struct TNod* aux = NULL;
		ClonareArb(radacina,aux);
		

		//Inlcouire variabila cu valoarea lui i
//		#pragma omp parallel
		ReplaceChars(aux, rep, buffer);
		free(rep);
		PrelucrareArbore(aux->dr);
		prod *= *(aux->dr->rez);
	}
	
	//return prod;
	*(radacina->rez) = prod;
}

void PrelucrareArbore(struct TNod *lel){
	char * a=lel->info;
	
	if(strcmp(a,"+")==0){
		Add(lel->st,lel->dr,lel);
	}else if(strcmp(a,"-")==0){
		Sub(lel->st,lel->dr,lel);
	}else if(strcmp(a,"*")==0){
		Mult(lel->st, lel->dr,lel);
	}else if(strcmp(a,"/")==0){
		Divi(lel->st, lel->dr,lel);
	}else if(strcmp(a,"sum")==0){
		Sum(lel);
		//printf("PrelArb %lf\n",*(lel->rez));
	}else if(strcmp(a,"prod")==0){
		Prod(lel);
	}else if(strcmp(a,"sqrt")==0){
		SqrtCalc(lel->st,lel->dr,lel);
	}else if(strcmp(a,"pow")==0){
		PowCalc(lel->st, lel->dr,lel);
	}else{
		*(lel->rez) = (double)atoi(a);
		//printf("ATOI %lf\n",*(lel->rez));
	}
}

double SimpleRezult(char* a, double rez1, double rez2){
	if(strcmp(a,"+")==0){
		return rez1 + rez2;
	}else if(strcmp(a,"-")==0){
		return rez1 - rez2;
	}else if(strcmp(a,"*")==0){
		return rez1 * rez2;
	}else if(strcmp(a,"/")==0){
		return rez1 / rez2;
	}else if(strcmp(a,"sqrt")==0){
		return sqrt(rez1);
	}else if(strcmp(a,"pow")==0){
		return pow(rez1,rez2);
	}
}
