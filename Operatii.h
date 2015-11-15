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

double Add(struct Nod *stg,struct Nod *drp);

double Sub(struct Nod *stg,struct Nod *drp);

double Mult(struct Nod *stg,struct Nod *drp);

double Divi(struct Nod *stg,struct Nod *drp);

double SqrtCalc(struct Nod *stg,struct Nod *drp);

double PowCalc(struct Nod *stg,struct Nod *drp);

double Sum(struct Nod *radacina);

double PrelucrareArbore(struct Nod *lel);
