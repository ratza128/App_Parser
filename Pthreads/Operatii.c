//Implementare Add,Sub,Mult,Divi,Sqrt,Pow
// Am presupus ca PrelucrareArbore are parametru asa
// gcc fisier -lm -o output ca sa mearga pow si sqrt

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#include "Operatii.h"


struct param{
	struct TNod *stg;
	struct TNod *dr;
	struct TNod *lel;
};


void Add(struct TNod *stg,struct TNod *drp, struct TNod *lel)
{
	double a,b;
	
	if(lel->st->rez == NULL){
		lel->st->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->rez == NULL){
		lel->dr->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->cost != NULL && *(lel->dr->cost) > 100 && lel->st->cost != NULL && *(lel->st->cost) > 100){


		pthread_t thread_id;
		struct param params;
		params.lel = lel->st;
		pthread_create(&(thread_id), NULL, PrelWithThread, &(params));
	

		pthread_t thread_id2;
		struct param params2;
		params2.lel = lel->dr;
		pthread_create(&(thread_id2), NULL, PrelWithThread, &(params2));
	
		pthread_join(thread_id,NULL);
	
		pthread_join(thread_id2,NULL);
	
	}else{
		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
	}
	a = *(lel->st->rez);
	b = *(lel->dr->rez);

	
	

	*(lel->rez) = a+b;
}

void *CalcAdd(void* threadArg){
	struct param *params = (struct param *)threadArg;
	
	struct TNod *stg = (struct TNod*)params->stg;
	struct TNod *dr = (struct TNod*)params->dr;
	struct TNod *lel = (struct TNod*)params->lel;
	
	Add(stg,dr,lel);
	
}


void Sub(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	if(lel->st->rez == NULL){
		lel->st->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->rez == NULL){
		lel->dr->rez = (double*)malloc(sizeof(double));
	}
	
	if(lel->dr->cost != NULL && *(lel->dr->cost) > 100 && lel->st->cost != NULL && *(lel->st->cost) > 100){
	
	pthread_t thread_id;
	struct param params;
	params.lel = lel->st;
	pthread_create(&(thread_id), NULL, PrelWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = lel->dr;
	pthread_create(&(thread_id2), NULL, PrelWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);

	}else{

		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
	}	
	a = *(lel->st->rez);
	b = *(lel->dr->rez);
	
	*(lel->rez) = a-b;

}

void Mult(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	if(lel->st->rez == NULL){
		lel->st->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->rez == NULL){
		lel->dr->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->cost != NULL && *(lel->dr->cost) > 100 && lel->st->cost != NULL && *(lel->st->cost) > 100){

	pthread_t thread_id;
	struct param params;
	params.lel = lel->st;
	pthread_create(&(thread_id), NULL, PrelWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = lel->dr;
	pthread_create(&(thread_id2), NULL, PrelWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);

	}else{

		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
	}	
	a = *(lel->st->rez);
	b = *(lel->dr->rez);
	*(lel->rez) = a*b;

}


void Divi(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;


	if(lel->st->rez == NULL){
		lel->st->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->rez == NULL){
		lel->dr->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->cost != NULL && *(lel->dr->cost) > 100 && lel->st->cost != NULL && *(lel->st->cost) > 100){

	pthread_t thread_id;
	struct param params;
	params.lel = lel->st;
	pthread_create(&(thread_id), NULL, PrelWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = lel->dr;
	pthread_create(&(thread_id2), NULL, PrelWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);
	}else{
		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
	}
	a = *(lel->st->rez);
	b = *(lel->dr->rez);
	*(lel->rez) = a/b;

}


//ordin 2 
void SqrtCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;
	
	//a=PrelucrareArbore(stg);
	PrelucrareArbore(stg);
//printf("asdsad\n");
	b = *(stg->rez);
	*(lel->rez) = sqrt(b);

}


//stanga este baza iar drp este puterea
void PowCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel)
{
	double a,b;

	if(lel->st->rez == NULL){
		lel->st->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->rez == NULL){
		lel->dr->rez = (double*)malloc(sizeof(double));
	}

	if(lel->dr->cost != NULL && *(lel->dr->cost) > 100 && lel->st->cost != NULL && *(lel->st->cost) > 100){

	pthread_t thread_id;
	struct param params;
	params.lel = lel->st;
	pthread_create(&(thread_id), NULL, PrelWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = lel->dr;
	pthread_create(&(thread_id2), NULL, PrelWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);
	}else{
		PrelucrareArbore(stg);
		PrelucrareArbore(drp);
	}
	a = *(lel->st->rez);
	b = *(lel->dr->rez);
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
	if(radacina == NULL){return;}
	
	if(radacina->st!=NULL){
		FreeArb(radacina->st);}
	if(radacina->dr!=NULL){
		FreeArb(radacina->dr);}
	if(radacina->info != NULL)
		free(radacina->info);
	radacina->info = NULL;
	//if(radacina->rez!=NULL)
	//	free(radacina->rez);
	radacina->rez = NULL;
	if(radacina->cost!=NULL)
		free(radacina->cost);
	radacina->cost=NULL;
	
	free(radacina);
}

void ClonareArb(struct TNod *radacina, struct TNod* newNode){

	if(radacina == NULL) return;

	//printf("asdas\n");
	char* msg = (char*)malloc(sizeof(char) * 15);
	strcpy(msg,radacina->info);
	newNode->info = msg;
	if(newNode->rez==NULL)
		newNode->rez = (double*)malloc(sizeof(double));
	*(newNode->rez) = *(radacina->rez);
	newNode->var = radacina->var;
	newNode->start = radacina->start;
	newNode->end = radacina->end;

	if(newNode->cost==NULL)
		newNode->cost = (int*)malloc(sizeof(int));
	*(newNode->cost) = *(radacina->cost);
	
	if(radacina->st != NULL){
		if(newNode->st==NULL)
			newNode->st = (TArb)malloc (sizeof(TNod));
		ClonareArb(radacina->st,newNode->st);
	}
	if(radacina->dr !=NULL){
		if(newNode->dr==NULL)
			newNode->dr = (TArb)malloc (sizeof(TNod));
		ClonareArb(radacina->dr,newNode->dr);
	}
	return;
}

void Sum(struct TNod *radacina){
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	int start = radacina->start;
	int end = radacina->end;
	
	char variab = radacina->var;
	

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double sum = 0;
	struct TNod* aux1;
	struct TNod* aux2;
	aux1 = (TArb)malloc (sizeof(TNod));
	aux2 = (TArb)malloc (sizeof(TNod));

	aux1->start = start;
	aux1->end = (end - start + 1)/2;
	aux2->start = (end - start + 1)/2 + 1;
	aux2->end = end;
	pthread_t thread_id;
	struct param params;
	params.lel = radacina;
	params.dr = aux1;
	pthread_create(&(thread_id), NULL, SumWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = radacina;
	params2.dr = aux2;
	pthread_create(&(thread_id2), NULL, SumWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);


	*(radacina->rez) += *(params2.dr->rez);
	*(radacina->rez) += *(params.dr->rez);
	//printf("before %lf\n",*(radacina->rez));
}

void *SumWithThread(void* threadArg){
	struct param *params = (struct param *)threadArg;
	
	struct TNod *stg = (struct TNod*)params->stg;
	struct TNod *dr = (struct TNod*)params->dr;
	struct TNod *lel = (struct TNod*)params->lel;

	int start = dr->start;
	int end = dr->end;
	int i;
	char variab = lel->var;
	int sum = 0;

	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);
		
		//Clonez lel
			
		ClonareArb(lel, dr);
		

		//Inlcouire variabila cu valoarea lui i
		ReplaceChars(dr, rep, buffer);
		free(rep);
		PrelucrareArbore(dr->dr);
		//printf("arb = %lf\n",*(aux->dr->rez));
		sum += *(dr->dr->rez);
		//FreeArb(aux[i-1]);
	}
	*(dr->rez) = sum;

}

void Prod(struct TNod *radacina){
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	int start = radacina->start;
	int end = radacina->end;
	
	char variab = radacina->var;
	

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double prod = 1;
	struct TNod* aux1;
	struct TNod* aux2;
	aux1 = (TArb)malloc (sizeof(TNod));
	aux2 = (TArb)malloc (sizeof(TNod));

	aux1->start = start;
	aux1->end = (end - start + 1)/2;
	aux2->start = (end - start + 1)/2 + 1;
	aux2->end = end;
	pthread_t thread_id;
	struct param params;
	params.lel = radacina;
	params.dr = aux1;
	pthread_create(&(thread_id), NULL, ProdWithThread, &(params));
	

	pthread_t thread_id2;
	struct param params2;
	params2.lel = radacina;
	params2.dr = aux2;
	pthread_create(&(thread_id2), NULL, ProdWithThread, &(params2));
	
	pthread_join(thread_id,NULL);
	
	pthread_join(thread_id2,NULL);

	*(radacina->rez) = 1;
	*(radacina->rez) *= *(params2.dr->rez);
	*(radacina->rez) *= *(params.dr->rez);
	//printf("before %lf\n",*(radacina->rez));
}

void *ProdWithThread(void* threadArg){
	struct param *params = (struct param *)threadArg;
	
	struct TNod *stg = (struct TNod*)params->stg;
	struct TNod *dr = (struct TNod*)params->dr;
	struct TNod *lel = (struct TNod*)params->lel;

	int start = dr->start;
	int end = dr->end;
	int i;
	char variab = lel->var;
	int prod = 1;

	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);
		
		//Clonez lel
			
		ClonareArb(lel, dr);
		

		//Inlcouire variabila cu valoarea lui i
		ReplaceChars(dr, rep, buffer);
		free(rep);
		PrelucrareArbore(dr->dr);
		//printf("arb = %lf\n",*(aux->dr->rez));
		prod *= *(dr->dr->rez);
		//FreeArb(aux[i-1]);
	}
	*(dr->rez) = prod;

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

void *PrelWithThread(void* threadArg){

	struct param *params = (struct param *)threadArg;
	
	struct TNod *stg = (struct TNod*)params->stg;
	struct TNod *dr = (struct TNod*)params->dr;
	struct TNod *lel = (struct TNod*)params->lel;
	
	char * a=lel->info;
	printf("%s\n",a);

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
		printf("a = %s lel->rez %i\n", a, lel->rez==NULL);
		*(lel->rez) = (double)atoi(a);
		printf("ATOI %lf\n",*(lel->rez));
	}


}

