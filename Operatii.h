#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef char* TInfo;

typedef struct TNod 
{ TInfo info;
  struct TNod *st, *dr;
  long int rezultat;
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



double Add(struct TNod *stg,struct TNod *drp);

double Sub(struct TNod *stg,struct TNod *drp);

double Mult(struct TNod *stg,struct TNod *drp);

double Divi(struct TNod *stg,struct TNod *drp);

double SqrtCalc(struct TNod *stg,struct TNod *drp);

double PowCalc(struct TNod *stg,struct TNod *drp);

double Sum(struct TNod *radacina);

double PrelucrareArbore(struct TNod *lel);

void ReplaceChars(struct TNod*, char*, char*);
