//Implementare Add,Sub,Mult,Divi,Sqrt,Pow
// Am presupus ca PrelucrareArbore are parametru asa
// gcc fisier -lm -o output ca sa mearga pow si sqrt





#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Operatii.h"

double Add(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);

	return a+b;

}


double Sub(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a-b;

}

double Mult(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a*b;

}


double Divi(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a/b;

}


//ordin 2 
double SqrtCalc(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	//a=PrelucrareArbore(stg);
	b=PrelucrareArbore(stg);
	
	return sqrt(b);

}


//stanga este baza iar drp este puterea
double PowCalc(struct TNod *stg,struct TNod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return pow(a,b);

}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the var are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}


void ReplaceChars(struct TNod *lel, char* rep, char* with){
	
	char* a = lel->info;
	
	if(strcmp(a, rep)==0){
		memset(lel->info,0,sizeof(lel->info));
		strcpy(lel->info, with);
		return;
	}

	if(strcmp(a,"+")==0 || strcmp(a,"-")==0 || strcmp(a,"*")==0 || strcmp(a,"/")==0 || strcmp(a,"sqrt")==0 || strcmp(a,"pow")==0){
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
	if(radacina->msg != NULL)
		free(radacina->msg);
	radacina->info = NULL;

	free(radacina);
}

struct TNod* ClonareArb(struct TNod *radacina){

	if(radacina == NULL) return NULL;

	struct TNod *newNode = NULL;
	
	newNode = (TArb)malloc (sizeof(TNod));
	if(!newNode) return NULL;
	
	char* msg = (char*)malloc(sizeof(char) * 15);
	strcpy(msg,radacina->info);
	newNode->info = msg;
	
	newNode->rezultat = radacina->rezultat;
	newNode->var = radacina->var;
	newNode->start = radacina->start;
	newNode->end = radacina->end;
	
	if(radacina->st != NULL)
		(newNode->st) = ClonareArb(radacina->st);
	
	if(radacina->dr !=NULL)
		(newNode->dr) = ClonareArb(radacina->dr);

	return newNode;
}

double Sum(struct TNod *radacina){
	struct TNod* stg = radacina->st;
	struct TNod* drp = radacina->dr;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->var;
	

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double sum = 0;
	for (i=start; i<=end; i++){
		char* rep = malloc(sizeof(char));
		*rep = variab;
		char buffer[20];
		
		snprintf(buffer, 20,"%i",i);
		
		//itoa(i,buffer,10);
		
		//Clonez lel
		struct TNod* aux = NULL;
		aux = ClonareArb(radacina);
		

		//Inlcouire variabila cu valoarea lui i
		ReplaceChars(aux, rep, buffer);
		free(rep);
		sum += PrelucrareArbore(aux->dr);
	}
	return sum;
}

double Prod(struct TNod *radacina){
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
		aux = ClonareArb(radacina);
		

		//Inlcouire variabila cu valoarea lui i
		ReplaceChars(aux, rep, buffer);
		free(rep);
		prod *= PrelucrareArbore(aux->dr);
	}
	
	return prod;
}

double PrelucrareArbore(struct TNod *lel){

	char * a=lel->info;
	double rez = 0;
	if(strcmp(a,"+")==0){
		rez=Add(lel->st,lel->dr);
	}else if(strcmp(a,"-")==0){
		rez=Sub(lel->st,lel->dr);
	}else if(strcmp(a,"*")==0){
		rez=Mult(lel->st, lel->dr);
	}else if(strcmp(a,"/")==0){
		rez=Divi(lel->st, lel->dr);
	}else if(strcmp(a,"sum")==0){
		rez = Sum(lel);
	}else if(strcmp(a,"prod")==0){
		rez = Prod(lel);
	}else if(strcmp(a,"sqrt")==0){
		rez = SqrtCalc(lel->st,lel->dr);
	}else if(strcmp(a,"pow")==0){
		rez = PowCalc(lel->st, lel->dr);
	}else{
		rez=(double)atoi(a);
	}
	return rez;
}


