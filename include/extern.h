extern char buffer[];       /* tampon contenant la ligne courante */
extern char outfilename[];  /* nom du fichier de sortie */
extern char message[];      /* contient les instructions a stocker */
extern int nbmaille;        /* nombre de mailles de l'entite POLYLINE */
extern int nbvertex;        /* nombre de sommets de l'entite POLYLINE */
extern int NBmaille;        /* nombre presume de mailles de l'entite POLYLINE */
extern int NBvertex;        /* nombre presume de sommets de l'entite POLYLINE */
extern int nopatch;         /* numero du patch courant */
extern int nbpatch;         /* nombre de patchs a sortir */
extern int nosommet;        /* numero du sommet courant */
extern int nomaille;        /* numero de la maille courante */
extern int nbconnexite;     /* nombre de normales */

/* informations sur la nature des mailles */
extern int tri_ok;          /* maille 3 non degeneree */
extern int tri_ok0,tri_ok1; /* maille 4 non degeneree */
extern int tri_ok2,tri_ok3;
extern int non_plan ;       /* maille 4 a decouper */
extern int concavite;       /* localisation de la concavite */
extern vec NS[];            /* normales aux sommets d'une maille */
extern int degenere;        /* il y a au moins 2 sommets confondus */
extern int inconsistent;    /* quadrilatere en "noeud papillon" */ 

extern int totmaille;   /* nombre total de mailles DXF traitees */
extern int totpatch;    /* nombre total de patchs en sortie */

extern int nbconcat;      /* nombre de concatenations effectuees */
extern int nbsplit;       /* nombre de decoupages effectues */

extern FILE *f_in;          /* fichier d'entree */

extern int code;            /* code DXF, a decoder bit a bit */

extern Maille       *tabmaille;     /* tableau de mailles = donnes brutes */
extern Patch        *tabpatch;      /* tableau de patchs = donnes traitees */
extern SommetMaille *tabsommet;     /* tableau de sommets */
extern Normale      *tabnormale;    /* tableau de normales */
extern Voisinage    *tabvoisinage;  /* tableau de l'info de voisinage (brute)  */
extern Connexite    *tabconnexite;  /* tableau de l'info de voisinage (traitee)*/

extern char etiq[];              /* etiquette DXF */
extern char e[];                 /* etiquette DXF */
extern char nom_objet[];         /* nom de l'objet courant */
extern char nom_vertex[];        /* nom du vertex courant */

extern int polymaille, surfmaillee; /* type de l'objet POLYLINE DXF */
extern int polyligne3d;
extern int fermeM, fermeN;          /* indique si surface fermee sur U et/ou V */
extern int M,N;                     /* taille de la surface maillee */

extern int DO_SMOOTH;         /* code lissage */
extern float cosanglimite;   /* angle au dessus duquel on ne lisse pas */
extern int selected;          /* pour une sortie partielle */
extern char *layer;           /* nom du layer selectionne */
extern int noquad;            /* pas de quadrilatere */

/* sert au decodage bit a bit */
extern unsigned char masks[];

/* informations VPORT */
extern vec cible;
extern vec visee;
extern vec oeil;
extern float focale;

/* informations sur bound */
extern	Bound	bound;
extern	Point3f	*pp;
extern	Face	*fp;

#include "3dface.h"
#include "bddgin.h"
#include "chrono.h"
#include "geom.h"
#include "liredxf.h"
#include "lissage.h"
#include "solidxf.h"
#include "sortir.h"
#include "polyline.h"
#include "vport.h"
#include "unifier_normales.h"

