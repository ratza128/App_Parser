//Implementare Add,Sub,Mult,Divi,Sqrt,Pow
// Am presupus ca PrelucrareArbore are parametru asa
// gcc fisier -lm -o output ca sa mearga pow si sqrt





#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Operatii.h"

double Add(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a+b;

}


double Sub(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a-b;

}

double Mult(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a*b;

}


double Divi(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return a/b;

}


//ordin 2 
double SqrtCalc(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	//a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return sqrt(b);

}


//stanga este baza iar drp este puterea
double PowCalc(struct Nod *stg,struct Nod *drp)
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

    // first time through the loop, all the variable are set correctly
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

double Sum(struct Nod *radacina){
	struct Nod* stg = radacina->stg;
	struct Nod* drp = radacina->drp;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->variable;

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double sum = 0;
	for (i=start; i<=end; i++){
		char* rep = &variab;
		
		//Inlcouire variabila cu valoarea lui i
		//str_replace(orig, rep, with); 
		//sum += PrelucrareArbore(stg);
	}
	
	return sum;
}

double Prod(struct Nod *radacina){
	struct Nod* stg = radacina->stg;
	struct Nod* drp = radacina->drp;
	
	double start = radacina->start;
	double end = radacina->end;
	
	char variab = radacina->variable;

	int i = 0;
	//Iteram de la start la end si prelucram expresia
	double prod = 1;
	for (i=start; i<=end; i++){
		char* rep = &variab;
		
		//Inlcouire variabila cu valoarea lui i
		//str_replace(orig, rep, with); 
		//prod *= PrelucrareArbore(stg);
	}
	
	return prod;
}

double PrelucrareArbore(struct Nod *lel){

	char * a=lel->radacina;
	double rez = 0;
	if(strcmp(a,"+")==0){
		rez=Add(lel->stg,lel->drp);
	}else if(strcmp(a,"-")==0){
		rez=Sub(lel->stg,lel->drp);
	}else if(strcmp(a,"*")==0){
		rez=Mult(lel->stg, lel->drp);
	}else if(strcmp(a,"/")==0){
		rez=Divi(lel->stg, lel->drp);
	}else if(strcmp(a,"sum")==0){
		rez = Sum(lel);
	}else if(strcmp(a,"prod")==0){
		rez = Prod(lel);
	}else if(strcmp(a,"sqrt")==0){
		rez = SqrtCalc(lel->stg,lel->drp);
	}else if(strcmp(a,"pow")==0){
		rez = PowCalc(lel->stg, lel->drp);
	}else{
		rez=(double)atoi(a);
	}
	return rez;
}




int main(int argc,char *argv[])
{
struct Nod a;
struct Nod b;

a.radacina=argv[1];
b.radacina=argv[2];

//printf("%lf %lf %lf %lf %lf %lf \n",Add(&a,&b),Sub(&a,&b),Mult(&a,&b),Divi(&a,&b),Sqrt_(&a,&b),Pow_(&a,&b));


return 0;
}


