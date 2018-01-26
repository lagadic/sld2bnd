
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

	




