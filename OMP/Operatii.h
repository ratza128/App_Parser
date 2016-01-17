#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef char* TInfo;

typedef struct TNod 
{ TInfo info;
  struct TNod *st, *dr;
  double *rez;
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

omp_lock_t lck;


void Add(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void Sub(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void Mult(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void Divi(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void SqrtCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void PowCalc(struct TNod *stg,struct TNod *drp,struct TNod *lel);

void Sum(struct TNod *radacina);

void PrelucrareArbore(struct TNod *lel);

void ReplaceChars(struct TNod*, char*, char*);
