#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef char* TInfo;

typedef struct nod 
{ TInfo info;
  struct nod*st, *dr;
  int rezultat;
  char var;
  int start, end;
} TNod, *TArb, **AArb;



typedef struct VctStr             /* Structura de string-uri */
{
   char* str; 
}VctStr;

typedef TArb VctArb[50];        /* Vector de arbori */


typedef struct Tablea          /* Structura pentru tabela cu numele variabilei si valoarea acesteia */
{
  char* nume;
  int val;
} Tabela;



double Add(struct Nod *stg,struct Nod *drp);

double Sub(struct Nod *stg,struct Nod *drp);

double Mult(struct Nod *stg,struct Nod *drp);

double Divi(struct Nod *stg,struct Nod *drp);

double SqrtCalc(struct Nod *stg,struct Nod *drp);

double PowCalc(struct Nod *stg,struct Nod *drp);

double Sum(struct Nod *radacina);

double PrelucrareArbore(struct Nod *lel);
