//Implementare Add,Sub,Mult,Divi,Sqrt,Pow
// Am presupus ca PrelucrareArbore are parametru asa
// gcc fisier -lm -o output ca sa mearga pow si sqrt

/*

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


struct Nod{
  char* radacina;
  struct Nod *stg;
  struct Nod *drp;
  double start, end;
  char variable;
  double rez; //Optional
};




double PrelucrareArbore(struct Nod *lel){

	char * a=lel->radacina;
	double rez=(double)atoi(a);

return rez;
}

*/
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
double Sqrt_(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return sqrt(b);

}


//stanga este baza iar drp este puterea
double Pow_(struct Nod *stg,struct Nod *drp)
{
	double a,b;

	a=PrelucrareArbore(stg);
	b=PrelucrareArbore(drp);
	
	return pow(a,b);

}


/*

int main(int argc,char *argv[])
{
struct Nod a;
struct Nod b;

a.radacina=argv[1];
b.radacina=argv[2];

printf("%lf %lf %lf %lf %lf %lf \n",Add(&a,&b),Sub(&a,&b),Mult(&a,&b),Divi(&a,&b),Sqrt_(&a,&b),Pow_(&a,&b));


return 0;
}

*/
