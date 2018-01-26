#include <stdio.h>
#include <math.h>
#include <string.h>
#include <bound.h>

#define NBTYPE 6
#ifndef PI
#define PI              (3.14159265358979323844)
#endif /* PI */

#define true             1
#define false            0

#define PLAN             1
#define PATCH            2

#define TRI    1
#define TRIN   2
#define QUAD   3
#define QUADN  4
#define PARAL  5
#define PARALN 6


#define BUFTAILLE          80
#define eps              (float)0.0000000001
#define VecCopy(a,b)     {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VecNegate(a)     {(a)[0]=-(a)[0];(a)[1]=-(a)[1];(a)[2]=-(a)[2];}
#define VecAdd(a,b,c)    {(c)[0]=(a)[0]+(b)[0];\
			  (c)[1]=(a)[1]+(b)[1];\
			  (c)[2]=(a)[2]+(b)[2];}
#define VecDot(a,b)      ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a)        (sqrt(VecDot(a,a)))
#define VecCross(a,b,c)  {(c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1];\
			  (c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2];\
			  (c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0];}
#define VecSub(a,b,c)    {(c)[0]=(a)[0]-(b)[0];\
			  (c)[1]=(a)[1]-(b)[1];\
			  (c)[2]=(a)[2]-(b)[2];}
#define VecMul(A,a,c)    {(c)[0]=(A)*(a)[0];\
                         (c)[1]=(A)*(a)[1];\
                         (c)[2]=(A)*(a)[2];}
#define VecPrintE(v) {fprintf(stderr,"%g %g %g\n",(v)[0],(v)[1],(v)[2]);}
#define degtorad(x)      (((float)(x))*PI/180.0)

#define  COS(a)    (float)(cos((double)(a)))
#define  SIN(a)    (float)(sin((double)(a)))
#define  TAN(a)    (float)(tan((double)(a)))
#define  ACOS(a)   (float)(acos((double)(a)))
#define  ASIN(a)   (float)(asin((double)(a)))
#define  ATAN(a)   (float)(atan((double)(a)))
#define  SQRT(a)   (float)(sqrt((double)(a)))
#define  POW(a,b)  (float)(pow((double)(a),(double)(b)))
#define  EXP(a)    (float)(exp((double)(a)))
#define  LOG(a)    (float)(log((double)(a)))
#define  FABSOLUE(a)   (float)(fabs((double)(a)))

typedef float vec[3];
typedef float Vec[3];

typedef Vec SommetMaille;
typedef Vec Normale;

typedef struct t_maille
{
    int type;        /* type : PLAN ou PATCH */
    int p[4];        /* indice des points qui definissent la face */
    int n[4];        /* indice des normales aux sommets*/
    int taille;      /* nombre effectif de sommmets */
    int split;       /* vaut 1 si les 4 points ne sont pas dans le meme plan */
    vec thenormale1; /* normale du 1er triangle ou du quadrilatere */
    vec thenormale2; /* normale du 2eme triangle */
    int degenere1;   /* indique si le 1er triangle est degenere */
    int degenere2;   /* indique si le 2eme triangle est degenere */
    int commun[2];   /* arete partagee */
    int libre;       /* ??? */
    int debut;       /* indice du premier sommet de l'arete partagee */
    vec N;           /* normale au plan defini par la maille */
    int invN;        /* doit on inverser la normale ? */
    int detN;        /* le sens de N est determine */
}
Maille;

typedef Maille Patch;

typedef struct t_sommet_partage
{
    int numface;
    int posdansface;
}
SommetPartage;

typedef struct t_groupe_lissage
{
    int nbfaces;
    int valide;
    int identique_a;
    int numsommet;
    vec N;
    SommetPartage *tabsommetp;
}
GroupeLissage;

typedef struct t_voisinage
{
    int NbFaces;
    int multigroupe;
    int nbgroupes;
    vec N;
    int numsommet;
    SommetPartage *tabsommetp;
    GroupeLissage *tabgroupelissage;
}
Voisinage;

typedef struct t_connexite
{
    int nbfaces;
    vec N;
    SommetPartage *tabsommetp;
}
Connexite;

/*************************************************/
/* Comparaison de deux vecteurs (a epsilon pres) */
/*************************************************/

#define memesommet(x,y) ((fabs((x)[0]-(y)[0])<eps)\
			 &&(fabs((x)[1]-(y)[1])<eps)\
			 &&(fabs((x)[2]-(y)[2])<eps))

/*********************************************/
/* Comparaison de deux chaines de caracteres */
/*********************************************/

#define strcomp(str1,str2) (!strcmp((str1),(str2)))

typedef struct t_tri
{
    float *P[3];  
    Vec u1,v1;
}
Tri;

typedef struct t_tri_n
{
    float       *P[3]; 
    Vec       u1,v1;
    float       *N[3];
    Connexite *C[3];
}
TriN;

typedef struct t_quad
{
    float *P[4]; 
    Vec u1,v1,u2;
    float ratio;
}
Quad;

typedef struct t_quad_n
{
    float       *P[4]; 
    Vec       u1,v1,u2;
    float       ratio;
    float       *N[4];
    Connexite *C[4];
}
QuadN;

typedef struct t_paral
{
    float *P[4]; 
    Vec u1,v1;
}
Paral;

typedef struct t_paral_n
{
    float       *P[4]; 
    Vec       u1,v1;
    float       *N[4];
    Connexite *C[4];
}
ParalN;

struct t_entite;

typedef int SplePt;
typedef int TextureInfo ;


typedef struct t_primitive
{
    float             d;           /* distance origine au plan */
    int             type;        /* type de la primitive */
    void            *geometrie;  /* donnees purement geometriques */
    Vec             N;           /* normale a la facette */
    struct t_entite *entite;     /* entite courante, appelee a disparaitre */
    int             m,n;         /* nombre d'echantillons sur chaque axe */
    SplePt          *samples;    /* tableau d'echantillons */
    TextureInfo     *textinfo;   /* information texture : matrices, ... */
}
Primitive;

typedef struct t_entite
{
    int nbprimitives;    /* nombre de primitives de l'entite */
    Primitive *tabprim;  /* tableau des primitives */
    int num_layer;       /* numero de layer */
    Vec dmin;            /* volume englobant : limites inferieures */
    Vec dmax;            /* volume englobant : limites superieures */
}
Entite;

	




