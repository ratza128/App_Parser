#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <mpi.h>

#include "Operatii.c"

#ifndef ARBORE_BINAR
#define ARBORE_BINAR
#define Frunza(a)(((a)->st==NULL)&&((a)->dr==NULL));
#define Interior(a) (((a)->st != NULL ) || ((a)->dr !=NULL))
#define Ordin(a) (((a)->st != NULL ) + ((a)->dr != NULL))

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(struct timeval *tv)
{
    char buffer[30];
    time_t curtime;

    printf("%ld.%06ld", tv->tv_sec, tv->tv_usec);
    curtime = tv->tv_sec;
    strftime(buffer, 30, "%m-%d-%Y  %T", localtime(&curtime));
    printf(" = %s.%06ld\n", buffer, tv->tv_usec);
}

/* Cateva functii din laboratoare */


/*-- Operatii elementare --*/
TArb InitA();           /* initializare arbore */
TArb ConstrNod(TInfo x, TArb s, TArb d); 
     /* -> adresa nod (cu info x, fiu stanga s, fiu dreapta d)
		   sau NULL daca nu exista spatiu */
TArb ConstrFr(TInfo x);
     /* -> adresa frunza cu informatia x, sau NULL daca nu exista spatiu */
void DistrArb(AArb);    /* distruge arbore */
int NrNoduri(TArb);     /* numar noduri */
int NrNiv(TArb);        /* numar niveluri (0 pentru arbore vid) */

/*-- Operatii suplimentare --*/
void AfiArb(TArb r);
	  /*- afiseaza arborele r -*/
TArb ConstrAA(int lim, int nn, int vi, int vs);
	  /*- construieste un arbore de inaltime < lim, cu cel mult
	      nn noduri cu chei in intervalul [vi,vs] -*/
#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned)time(NULL)))
#endif

static char desen[21][81], cri[] = "xxxxx";  /* zona reprezentare arbore, info */
static int limita = 21;                    /* linia limita de desenare */

void Repr(TArb r, int centru, int linie, int dif)
     /*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie+1
	 dif - distanta pe orizontala intre r si fiecare dintre cei doi descendenti
	 Exemple:  dif = 5    |        dif = 2    |
                xxxxx               xxxxx
			  ___/ \___              / \
			 |         |            |   |                               -*/
{ int k;
  if (linie > limita) return;
  if (dif <= 1)      /* spatiu de afisare insuficient -> ... */
    { memset(desen[linie]+centru, '.', 5); return; }
  desen[linie][centru] = '|';      /* legatura spre nod */
  desen[linie][0] = ':';
  if (linie+1 > limita) return;
  sprintf(cri, "%5s", r->info);   /* converteste valoare info la 5 caractere */
  k = (cri[0] == ' ') ? 2 : 1;    /* decalaj fata de centru */
  memcpy(desen[linie+1] + centru - k-2, cri, 5); /* copiaza cele 5 caractere in desen */
  desen[linie+1][0] = ':';
  if (linie+2 > limita) return;
  if (r->st)
  { desen[linie+2][centru-1] = '/';                     /* reprezinta ramura  ____/  */
    desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
    memset(desen[linie+2] + centru - dif +1, '_', dif-2);
    Repr(r->st, centru - dif, linie + 3, (dif+1)/2 );   /* si subarborele stang */
  }
  if (r->dr)
  { desen[linie + 2][centru+1] = '\\';                  /* reprezinta ramura  \____  */
    desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
    memset (desen[linie+2] + centru + 2, '_', dif-2);
    Repr(r->dr, centru + dif, linie + 3, (dif+1)/2 );   /* si subarborele drept */
  }
}

void AfiArb(TArb r) /*- afiseaza arborele r -*/
{ int j;
  for (j = 0; j <= limita; j++) memset (desen[j], ' ', 79);
  if (!r) printf ("%49s", "-=- Arbore VID -=-");
  else
  { Repr(r,40,0,19); /* preg reprezentare cu centrul in coloana 39 a primei linii */
    for (j = 0; j <= limita && desen[j][0] == ':'; j++)
     { desen[j][79] = '\0'; printf("%s\n", desen[j]+1); }
  }
  printf ("\n");
}



void ConstrArbPref (TArb *a,VctStr sir[40],int *p,int *k)   /* Functie de construire a arborului pentru ecuatii prefixate */
{      
	if ( (ispunct(sir[(*p)].str[0]) ) 
   		&& (sir[(*p)].str[0] != '<' ) 
		&& (sir[(*p)].str[0] != '>' ) ) /* Daca s-a gasit operator */
      { 
        (*a)=(TNod*)malloc(sizeof(TNod));              /* Alocam spatiu pentru un nod si il completam */

        if ( !(*a) )
           return;
	(*a)->rez = (double*)malloc(sizeof(double));
        ((*a)->info)=sir[(*p)].str;
        (*p)++;
        ConstrArbPref(&((*a))->st,sir,p,k);            /* Construim subarbore stang */
        ConstrArbPref(&((*a))->dr,sir,p,k);            /* Construim subarbore drept */
        return;
      }

    if(strcmp(sir[(*p)].str, "sqrt") == 0
		|| strcmp(sir[(*p)].str, "pow") == 0 ){
    	(*a)=(TNod*)malloc(sizeof(TNod));              /* Alocam spatiu pentru un nod si il completam */
	
	if ( !(*a) )
           return;
	(*a)->rez = (double*)malloc(sizeof(double));        
	((*a)->info)=sir[(*p)].str;
        (*p)++;
	    ConstrArbPref(&((*a))->st,sir,p,k);            /* Construim subarbore stang */
	    ConstrArbPref(&((*a))->dr,sir,p,k);
		return;
    }
    
    if(strcmp(sir[(*p)].str, "sum") == 0 
		|| strcmp(sir[(*p)].str, "prod") == 0){
    	(*a)=(TNod*)malloc(sizeof(TNod));              /* Alocam spatiu pentru un nod si il completam */
        
	if ( !(*a) )
           return;
  	(*a)->rez = (double*)malloc(sizeof(double));      
  	((*a)->info)=sir[(*p)].str;
        (*p)++;
        ((*a)->start)=atol(sir[(*p)].str);
        (*p)++;
        ((*a)->end)=atol(sir[(*p)].str);
	    (*p)++;
        ((*a)->var)=sir[(*p)].str[0];
		ConstrArbPref(&((*a))->st,sir,p,k); 

	    ConstrArbPref(&((*a))->dr,sir,p,k);
		return;
    }
    
 

    if ( isalnum(sir[(*p)].str[0]) )                   /* Daca s-a gasit nume de variabila */
      {
       (*a)=ConstrFr( (sir[(*p)].str));                /* Construim frunza */
       (*p)++;
       return;
       }
      
   if ( sir[(*p)].str[0] = '<' )                       /* Daca s-a gasit "<" se mareste doar p-ul */
      { 
        (*p)++;
        ConstrArbPref(&((*a)),sir,p,k);
      }
   if(*p == *k)                                        /* In cazul in care p devine egal cu lungimea sirului,returnam functia */
   /* Motivul pentru care am folosit acest if este faptul ca functia nu functiona cum trebuie fara ea , recunosc ca la starteput a fost
      "lucky guess", intelegand pe urma folosinta ei si anume : Functia se oprea ( din cate mi-am dat seama ) la ultimul caracter si nu 
      primea functia recursiva rezultat corect */
         return;
   if ( sir[(*p)].str[0] = '>' )                        /*In cazul in care dam peste ">" */
       { 
         (*p)++;
         return;
       }
  
}



TArb ConstrNod(TInfo x, TArb s, TArb d) /* -> adresa nod (cu informatia x, 
				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
{ TArb aux = (TArb)malloc (sizeof(TNod));  /* startearca alocare spatiu */
  if (!aux) return NULL;                   /* spatiu insuficient */
  aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */
  return aux;                              /* intoarce adresa nodului */
}

TArb ConstrFr(TInfo x)     /* -> adresa frunza cu informatia x, sau
				  NULL daca nu exista spatiu */
{ TArb aux = (TArb)malloc (sizeof(TNod));
  if (!aux) return NULL;
  
  aux->info = x; aux->st = aux->dr = NULL;
  return aux;
}

void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{ if (!r) return;
  distruge (r->st);     /* distruge subarborele stang */
  distruge (r->dr);     /* distruge subarborele drept */
  free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{ if (!(*a)) return;       /* arbore deja vid */
  distruge (*a);           /* distruge toate nodurile */
  *a = NULL;               /* arborele este vid */
}

int NrNoduri(TArb r)        /* numarul de noduri din arborele r -*/
{ if (!r) return 0;          /* arbore vid => 0 noduri */
  return 1 + NrNoduri(r->st) + NrNoduri(r->dr);
}

int NrNiv(TArb r)           /* numar niveluri (0 pentru arbore vid) */
{ int ns, nd,x;
  if (!r) return 0;
  ns = NrNiv (r->st); nd = NrNiv (r->dr);
  return 1 + (ns >= nd ? ns : nd);
}

void AfiEc(TArb a,Tabela tab[40],int *k)    /* Functie de afisare a ecuatiei */
{if (!a) 
   return;
  if ( (a->dr == NULL ) && (a->st==NULL ) )   /* Daca e frunza */
   {printf("%i",tab[(*k)].val);               /* Afisam valoarea */
    (*k)++;
    return;
   }
 printf("(");                                  /* "(" pentru delimitarea ecuatiilor */
 AfiEc(a->st,tab,k);                           
 printf(" %s ",a->info);                       /* Tiparim operant */
 AfiEc(a->dr,tab,k);                           /* "(" pentru delimitarea ecuatiilor */
 printf(")");                                    
}

/*----------------------------MAIN-----------------------------*/

int main(int argc, char*argv[])
{ TArb arb=NULL,arb2=NULL,arb3=NULL,arbaux=NULL;                  /* Declaratii */
  int p,i,in,k,k1,ind=0,j,alpha,rezultat,i2,ok,t=0,arbcon=0,dest;
  char sir[80],sir2[5],sir3[5],sir4[5],sir5[5];
  char numef[20];
  VctArb varb;
  FILE* f;
  VctStr siro[40],sirn[40];
  Tabela tab[40],tab2[40];
  char op1[20], op2[20], op3[20],op4[20];
  
  int rank = 0;
  int comm_size = 0; 
  struct timeval tvBegin, tvEnd, tvDiff;
  
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  
  int auxComm = comm_size;
  
  if(rank == 0){
  	gettimeofday(&tvBegin, NULL);
  }
  
  if(rank == 0){
	  f=fopen(argv[1],"rt");               /*Deschidere fisier si verificare */
	  if (!f)
	     {printf("\nNu s-a putut deschide fisierul!");
	      return 0;
	     }
	  else
      printf("\n\n\nFisierul %s s-a deschis cu succes !\n\n\n",argv[1]);
  }
  
  while ( 1 )
              /* Cat timp se citeste ecuatie din fisier */
        {
        if(rank == 0){
        
        	int succes = fgets(sir,80,f);
        	
	  	if(!succes){
	  		
	  		for (i=1; i<=auxComm-1; i++)
			{  	
				 MPI_Send("Done", sizeof(sir), MPI_CHAR, i, 0, MPI_COMM_WORLD);
		        }
	  		break;	
  		}
		
		for (i=1; i<=auxComm-1; i++)
	        {  	
			 MPI_Send(&sir, sizeof(sir), MPI_CHAR, i, 0, MPI_COMM_WORLD);
	        }
	}
	else{
		MPI_Recv(&sir, sizeof(sir), MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
         	if(strcmp(sir,"Done") == 0){
         		break;
         	}
	}
        if(rank == 0){
        printf("\nArborele pentru :  %s",sir);   
        }
         k=0;                      
         in=0;
         p=0;
         
         for (i=0;i<=strlen(sir);i++)      /* Separare prin spatii si construirea unui vector de strings */  
             {if (sir[i]!= ' ' )
                {sir2[in]=sir[i];
                 in++;
                 sir2[in]='\0';
                
                }
              else
                  {     
                   siro[k].str=(char*)malloc(sizeof(sir2)+1);
                   strcpy(siro[k].str,sir2);
                   sir2[0]='\0';             /* Resetare sirurui */
                   sir2[1]='\0';
                   sir2[2]='\0';
                   sir2[3]='\0';
                   sir2[4]='\0';
                   in=0;
                   k++;
                  }
             }
    
          k1=k;
          k=0;
          for(i=0;i<k1;i++)           /* Construirea unui vector de strings CORECT. Daca cel anterior putea avea pe o pozitie
          ceva de genul acesta: (a+ , acest vector va avea doar nume de variabile, operanzi sau paranteze */
            if ( ( strlen(siro[i].str) != 1 ) && (ispunct(siro[i].str[0])) )
               { 
                  sir3[0]=siro[i].str[0];
                  sir3[1]='\0';
                  sir4[0]=siro[i].str[strlen(siro[i].str)-1];
                  sir4[1]='\0';
                  sir4[2]='\0';
                  sirn[k].str=(char*)malloc(6);
                  strcpy(sirn[k].str,sir3);  
                  k++;
               
                  for ( j=1;j<strlen(siro[i].str)-1;j++)
                      {sir5[j-1]=siro[i].str[j];
                       sir5[j]='\0';
                       alpha=1;
                      }
                      
                  if (alpha == 1 )
                  {sirn[k].str=(char*)malloc(6);
                  strcpy(sirn[k].str,sir5);
                
                  k++;
                  alpha=0;
                  }
                  sirn[k].str=(char*)malloc(6);
                  strcpy(sirn[k].str,sir4);
                  
                  
                  sir3[0]='\0';        /* Resetare sirurui */
                  sir3[1]='\0';
                  sir4[0]='\0';
                  sir4[1]='\0';
                  sir5[0]='\0';
                  sir5[1]='\0';
                  sir5[2]='\0';
                  sir5[3]='\0';
                  sir5[4]='\0';
                  k++;
               }
            else
                 {sirn[k].str=(char*)malloc(6);
                  strcpy(sirn[k].str,siro[i].str);
                  k++;
                 }
            if( strlen(siro[i-1].str) == 2)
                {sir3[0]=sir[strlen(sir)-3];
                sir3[1]='\0';
                sirn[k].str=(char*)malloc(6);
                strcpy(sirn[k].str,sir3);
                k++;
                }
            sir4[0]=sir[strlen(sir)-2];
            sir4[1]='\0';
         
            sirn[k].str=(char*)malloc(6);
            strcpy(sirn[k].str,sir4);
        /* Termninare construire vector strings */
        
        
        /*-----------------------------------------------------------------*/
                        
         if ( arbcon == 0 )  /* Daca nu s-a construit arbore pentru aceasta ecuatie */
         for(i2=0;i2<k;)     /* Verificare prefixata. Varianta BONUS: verific daca sir[i] e operant */
                        if ( (ispunct(sirn[i2].str[0] )) && (sirn[i2].str[0] != '+' ) && (sirn[i2].str[0] != '-' ) && (sirn[i2].str[0] != '*' ) && (sirn[i2].str[0] != '/' )  )
                            i2++;
                        else
                                if (( sirn[i2].str[0] == '+' ) || (sirn[i2].str[0] == '-' ) || (sirn[i2].str[0] == '*' ) || (sirn[i2].str[0] == '/' ) || ( strcmp( sirn[i2].str, "sqrt") == 0 ) || ( strcmp( sirn[i2].str, "pow") == 0 ) || ( strcmp( sirn[i2].str, "sum") == 0 ) || ( strcmp( sirn[i2].str, "prod") == 0 ) )
                                  {
                                   ConstrArbPref(&(varb[t]),sirn,&p,&k);
                                   printf("\n");
                                   if(rank == 0){
                                    AfiArb(varb[t]);
				   }
				   
					   		
				   // Logica pentru 2 procese
				   if(auxComm == 2){
				   
				   	   if(rank == 0){
					   	
					   	strcpy(op1, varb[t]->info);
					   	
					   	if(strcmp(op1, "sum") == 0 || strcmp(op1, "prod") == 0){
					 		MPI_Send("Done", 5, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
					 		PrelucrareArbore(varb[t]);
							printf("%lf\n",*(varb[t]->rez));
					   	}       
					   	else{
					   		MPI_Send( "Ok", 5, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
							struct TNod* aux = NULL;
							aux = (TArb)malloc (sizeof(TNod));
			
							ClonareArb(varb[t]->dr, aux);
						
							PrelucrareArbore(aux);
							double rez;
							MPI_Recv(&rez, sizeof(double), MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
							
							double finalR;
							finalR = SimpleRezult( op1,rez,   *(aux->rez));
							printf("Final %lf\n",finalR);
					 	}
					 	
		                           }
		                           else{
		                           	char ack[10];
		                           	MPI_Recv(&ack, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		                           	
		                           	if(strcmp(ack,"Ok") == 0){
		                           	
							struct TNod* aux = NULL;
							aux = (TArb)malloc (sizeof(TNod));
			
							ClonareArb(varb[t]->st, aux);
			                   	        PrelucrareArbore(aux);
				                   	 
						        MPI_Send(&(*(aux->rez)), sizeof(double), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
				                }
		                           }
				   }
				   
				   // Logica pentru 4 procese
				     if(auxComm == 4){
				   
				   	   if(rank == 0){
					   	
					   	strcpy(op1, varb[t]->info);
						strcpy(op2, varb[t]->st->info);
					   		
					   	if(strcmp(op1, "sum") == 0 || strcmp(op1, "prod") == 0){
					 		for (i=1; i<=auxComm; i++)
							{  	 
					 			MPI_Send("Done", 5, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
							}
					 		
					 		PrelucrareArbore(varb[t]);
							printf("%lf\n",*(varb[t]->rez));
					   	}       
					   	else{
					   		MPI_Send( "Ok", 5, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
					   		if(strcmp(op2, "sum") == 0 || strcmp(op2, "prod") == 0 || varb[t]->st->st == NULL){
					   			MPI_Send( "Done", 5, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
					   			
					   			struct TNod* aux = NULL;
								aux = (TArb)malloc (sizeof(TNod));
			
								ClonareArb(varb[t]->st, aux);
						
								PrelucrareArbore(aux);
								double rez;
								MPI_Recv(&rez, sizeof(double), MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &status);
								
								double finalR;
								finalR = SimpleRezult( op1, *(aux->rez), rez);
								printf("Rezultat final = %lf\n",finalR);
								
					   		}
					   		else{
					   			MPI_Send( "Ok", 5, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
								struct TNod* aux = NULL;
								aux = (TArb)malloc (sizeof(TNod));
			
								ClonareArb(varb[t]->st->st, aux);
						
								PrelucrareArbore(aux);
								double rez;
								MPI_Recv(&rez, sizeof(double), MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
							
								double finalR;
								finalR = SimpleRezult( op1,rez,   *(aux->rez));
								
								MPI_Recv(&rez, sizeof(double), MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &status);
								
								finalR = SimpleRezult( op1,finalR, rez);
								printf("Rezultat final = %lf\n",finalR);
							}
					 	}
					 	
		                           }
		                           else{
		                           	char ack[10];
		                           	
		                           if(rank == 3 ){
		                           	MPI_Recv(&ack, 10, MPI_CHAR, 2, 0, MPI_COMM_WORLD, &status);
		                           }
		                           else{
		                           	MPI_Recv(&ack, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
	                           	   }
	                           	   
		                           	if(strcmp(ack,"Ok") == 0){
		                           		if(rank == 1){
								struct TNod* aux = NULL;
								aux = (TArb)malloc (sizeof(TNod));
			
								ClonareArb(varb[t]->st->dr, aux);
					           	        PrelucrareArbore(aux);
						           	   
								MPI_Send(&(*(aux->rez)), sizeof(double), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
						        	
						        }
						        
						        if(rank == 2){
						        
						        	strcpy(op3, varb[t]->dr->info);
						        	if(strcmp(op3, "sum") == 0 || strcmp(op3, "prod") == 0 || varb[t]->dr->st == NULL){
						        		MPI_Send( "Done", 5, MPI_CHAR, 3, 0, MPI_COMM_WORLD);
						        		struct TNod* aux = NULL;
									aux = (TArb)malloc (sizeof(TNod));
			
									ClonareArb(varb[t]->dr, aux);
							   	        PrelucrareArbore(aux);
									MPI_Send(&(*(aux->rez)), sizeof(double), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
						        	}
						        	else{
						        		MPI_Send( "Ok", 5, MPI_CHAR, 3, 0, MPI_COMM_WORLD);
									struct TNod* aux = NULL;
									aux = (TArb)malloc (sizeof(TNod));
			
									ClonareArb(varb[t]->dr->st, aux);
							   	        PrelucrareArbore(aux);
								   	double rez;
									MPI_Recv(&rez, sizeof(double), MPI_DOUBLE, 3, 0, MPI_COMM_WORLD, &status);
							
									double finalR;
									finalR = SimpleRezult( op3,rez,   *(aux->rez));
								
									MPI_Send(&finalR, sizeof(double), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
						        	}
						        }
						        
						        if(rank == 3){
								struct TNod* aux = NULL;
								aux = (TArb)malloc (sizeof(TNod));
			
								ClonareArb(varb[t]->dr->dr, aux);
					           	        PrelucrareArbore(aux);
						           	   
								MPI_Send(&(*(aux->rez)), sizeof(double), MPI_DOUBLE, 3, 0, MPI_COMM_WORLD);
						        	
						        }
				                }
		                           }
				   }
				   
                                   t++;
                                   
                                   arbcon=1;
                                   break;
                                   }    
                                 else
                                     break;
            
          sir3[0]='\0';        /* Resetare siruri */
          sir3[1]='\0';
          sir4[0]='\0';
          sir4[1]='\0';
             k=0;
             if(rank == 0){
          	printf("\n\n\n--------------------------------\n\n\n");
          }
          
          
       arbcon=0;
        }   
  
    if(rank == 0){
    	gettimeofday(&tvEnd, NULL);
	    	 
	    	 timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	   	printf("%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

  return 0;
}   
     
     
    
