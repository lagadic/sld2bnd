/* definition des types */
/* file : lgrc_type.h   */

/* ******************************************** */
/*						*/
/*   Module de declaration de tous les types	*/
/*	  d'objets manipules dans LGRC		*/
/*						*/
/*	    Compilateur LGRC V 1.0 C		*/
/*	- creation	25/11/86	TP	*/
/*	- modification	02/01/87	BA	*/
/*		conventions pour les types	*/
/*		MAJUSCULE pour les constantes	*/
/*		MAJUSCULE pour les macros	*/
/*		Majuscule pour les types definis*/
/*	- modification  23/12/87	TP	*/
/*		Polygone plan			*/
/*						*/
/* 	Copyright Th PRIOL et Br ARNALDI	*/
/*						*/
/* ******************************************** */






/* ************************************************************ */
/* 								*/
/*		     Definition des Macro			*/
/* 								*/
/* ************************************************************ */


/* Macro pour le calcul de carre */
/* ***************************** */

#define SQR(x) ((x) * (x))





/* ************************************************************ */
/*                                                              */
/*                 Definition des booleens                      */
/*                                                              */ 
/* ************************************************************ */



/*   constantes booleennes      */
/* **************************** */

#ifndef LIB_TYPE
#define FALSE 	0		/* faux 			*/
#define TRUE  	1		/* vrai				*/


/* types booleens */
/* ************** */

typedef unsigned char Boolean;
#endif





/* ************************************************************ */
/*								*/
/* 	    definition des constantes du systeme 		*/
/*								*/
/* ************************************************************ */


/* constante de taille maximum */
/* *************************** */

#define MAXERRLINE	5	/* nb maxi d'erreur par ligne	*/

#define MAXPRIMIT 	10000 	/* nombre de feuille maximum 	*/
#define MAXNOEUD 	20000 	/* nombre de noeud maximum   	*/
#define MAXFINAL 	20000
#define NPARAL 		5 	/* nombre maxi de parametre	*/
				/* decrivant une primitive 	*/
#define MAXIDENT 	20 	/* nb de caract max d'un ident 	*/
#define MAXASS 		10000 	/* nb objets maxi a assembler 	*/
#define MAXSOURCE 	10 	/* nb maxi de sources lumineuses*/
#define MAXID 		100 	/* nb maxi d'ident arithmetique */
#define MAXTEMPO 	100 	/* maxi prof calcul expression  */
#define MAXTABLE 	100 	/* taille maxi table des param. photo */
#define MAXTABPRIM 	50 	/* indice max tableau de primit */

/* gestion des surfaces bicubique */
/* ****************************** */

#define MAXM 		20 	/* nb de lignes maxi pour spline*/
#define MAXN 		10 	/* nb de lignes maxi pour spline*/
#define MAXSURF 	10 	/* nb surface differentes maxi  */

/* gestion des fichiers de polygones plans */
/* *************************************** */

#define MAXENS		10	/* nb de fichier polygones plans */
#define MAXSOM		10	/* nb de sommet max d'un polygone*/

/* generateur de nombre aleatoire */
/* ****************************** */

#define RND_M 		10000000/* constante generateur aleat   */
#define RND_M1 		10000 	/*   "       "        "     "   */
#define RND_B 		31415821/*   "       "        "     "   */

/* constantes numeriques	  */
/**********************************/

#define EPSILON 	1e-15 	/* epsilon pour calcul en reel 	*/
#define PI		3.141592654 /* constante mathematique	*/
#define PI180		PI/180	/* cont passage radian->degre	*/


/* ************************************************************ */
/*								*/
/* 	Definition des structures de donnees de LGRC		*/
/*								*/
/* ************************************************************ */


/* type de primitive du systeme	*/
/* **************************** */

#define SPHERE 		0	/* type primit	sphere		*/
#define PARAL 		1	/*   "    "	parallelepipede */
#define CONE 		2	/*   "    "	cone		*/
#define COIN 		3	/*   "    "	coin		*/
#define CYLINDRE 	4	/*   "    "	cylindre	*/
#define FRACTAL 	5	/*   "    "	fractale	*/
#define SURFACE 	6	/*   "    "	surface bicubi  */
#define POLYENS		7	/* numero disponible futur prim */
#define POLYGON		8	/* numero disponible futur prim */
#define P5 		9	/* numero disponible futur prim */

typedef char Primitive;		/* type enumere de primitives	*/

/* nom des primitives p3,p4,p5 servent a conserver la     	*/
/* validite des anciennes bases si on ajoute d'autres primitives*/
/* les fichiers restent donc compatibles                        */

/* type du modele photometrique	*/
/* **************************** */

#define COULEUR 	0	/* type modele couleur		*/
#define NB 		1	/* type modele Noir et Blanc	*/

typedef char Modphoto;		/* type enumere modele photo	*/

/*   genre de matrice utilise	*/
/* **************************** */

#define RXRY 		0	/* ni rotation sur x ni sur y	*/
#define RXRZ 		1	/* ni rotation sur x ni sur z   */
#define RYRZ 		2	/* ni rotation sur y ni sur z   */
#define IDEN 		3	/* matrice identite		*/
#define GEN 		4	/* matrice generale		*/

typedef char Tmt; 		/* type enumere de matrice 	*/



/* type matrice avec indicateur du genre */
/* ************************************* */

typedef struct 
     {
        double mat[4][4]; 	/* matrice de changement repere */
        Tmt tm;			/* genre de la matrice		*/
     } Newmatrice ;


/* matrice simple */
/* ************** */

typedef double Matr[4][4];



/* operateur pour l'arbre C.S.G. */
/* ***************************** */

#define UNION2 		0	/* operateur d'union		*/
#define INTER 		1	/* operateur d'intersection	*/
#define DIF 		2	/* operateur de difference	*/
#define ASS 		3	/* operateur d'assemblage	*/
#define FANT 		4	/* operateur fantome (primitive)*/

typedef char Operateur;		/* type enumere operateur	*/


/* ************************************************************ */
/*								*/
/* 	     definition des structure photometriques 		*/
/*								*/
/* ************************************************************ */


/* type pour une composante R,V ou B */
/* ********************************* */

typedef struct 
     {
        double ra, s, t, d, n, n2, f0, kat, lnkat;
     } Paramph;

/* type photometrique couleur et NB */
/* ******************************** */

typedef struct 
     {
        Modphoto nomodele;		/* Choix de NB ou Coul	*/
        union
            {
               struct {			/* modele couleur	*/
                        Paramph p[3];
                        double mf;
                        double m;
                        double nmoy;
                 } Mod_coul;
               struct {			/* modele noir et blanc	*/
                        double ks, kt, kd, n, n2, kat, lnkat;
                        short phong;
                 } Mod_nb;
            } Select_mod;
     } Tphoto;


/* structure de point */
/* ****************** */

typedef struct 
     {
        double x, y, z;
     } Point;


/* structure de facette triangulaire (fractale) */
/* ******************************************** */

typedef Point Triangle[3];


/* structure de vecteur */
/* ******************** */

typedef struct 
     {
        double dx, dy, dz;
     } Vect;


/* structure de volume englobant spherique */
/* *************************************** */

typedef struct 
     {
        double 	ray;
        double 	ray2;
        Point 	centre;
     } Tvs;


/* structure de volume englobant parallelepipedique */
/* ************************************************ */

typedef struct 
     {
        double xmax, xmin, ymax, ymin, zmax, zmin;
     } Tvc;


/* partie de la structure d'un noeud CSG */
/* ************************************* */

typedef struct 
     {
        Operateur op;			/* operateur			*/
        Tvc 	  vc;			/* volume englobant paral	*/
        Tvs 	  vs;			/*    "       "     spherique	*/
        short 	  filsd, filsg;		/* pointeur fils droit et gauche*/
     } T1;


/* structure des parametres geometriques d'une primitive */
/* ***************************************************** */

typedef struct 
     {
        Primitive nom;			/* selectionne la structure	*/
        union
            {
               struct {			/* parametre paral ou coin	*/
                        double tx, ty, tz;
                 } Cube;
               struct {			/* parametre sphere		*/
                        double r, r2;
                 } Sphe;
               struct {			/* param cone ou cylindre	*/
                        double h, h2, rc, rc2;
                 } Cyli;
               struct {			/* parametre facette fractale	*/
                        Triangle sommet;
                        Vect	 dep;
                        short 	 niv;
                        double	 dim;
                        double	 ech;
                 } Fract;
               struct {			/* param surface bicubique	*/
                        short nsurf, posi, posj;
                 } Bicub;
               struct {			/* param ensemble de polygones	*/
                        char	pename[14];
                 } Polens;
               struct {			/* param polygones		*/
                        Point	sommet[MAXSOM];
			short	nbsommet;
                 } Polygo;
            } Select_prim;
     } Tparageo;


/* structure associe a une primitive CSG */
/* ************************************* */

typedef struct 
     {
        Tparageo   p;		/* param geometriques		*/
        Tphoto 	   ph;		/*  "    photometriques		*/
        Newmatrice mls;		/* matrice passage local-scene	*/
        Newmatrice msl;		/*    "       "    scene-local	*/
        Newmatrice dgl;		/*    "    deformation		*/
        Newmatrice dlg;		/*    "    inverse deformation	*/
        Boolean    def;		/* presence ou non deformation	*/
     } T22;


/* structure de noeud pour sortie fichier */
/* ************************************** */

typedef struct 
     {
        T1 	pg;			/* partie effective du noeud	*/
        Boolean vide;			/* indique noeud vide (inutile) */
        short 	pp;			/* position primitive si feuille*/
     } Tvnoeud;


/* structure d'identificateur du langage */
/* ************************************* */

typedef char Chaine[MAXIDENT];


/* structure interne LGRC pour stocker les primitives DEBUTBLOC */
/* ************************************************************ */

typedef struct 
     {
        Chaine 	 nom;			/* identificateur de l'objet	*/
        Boolean  tab;			/* presence ou non d'un tableau */
        short 	 ind;			/* posit indice ds table 'ident'*/
        short 	 min;			/* valeur minimale indice	*/
        short 	 max;			/* valeur maximale indice	*/
        Tparageo geo;			/* param geometrique primitive  */
        Tphoto   pho;			/* param photometrique    "	*/
        Boolean  vfdef;			/* presence ou non deformation  */
        Boolean  prespho;		/*     "     "  "  param photo  */
        Matr	  deform;		/* matrice de deformation	*/
     } Sbloc;



/* pointeur vers la structure sbloc */
/* ******************************** */
typedef Sbloc *S2bloc;



/* definition du type d'un noeud */
/* ***************************** */

#define PRIMIT 		0		/* primitive			*/
#define NOEUD 		1		/* noeud defini par DEBUTCOMPO	*/
#define ASSEMBLAGE 	2		/* noeud defini par DEBUTASS	*/


/* type enumere du genre d'un noeud */
/* ******************************** */

typedef char Tobj;


/* structure pour stocker un element du CSG final */
/* ********************************************** */

typedef struct 
     {
        Chaine 	  nom;			/* nom de l'objet		*/
        Tobj 	  ty;			/* type de l'objet		*/
        short 	  ptrprimit;		/* numero primitive si feuille  */
        Operateur op;			/* operateur si noeud		*/
        Matr	   mls;			/* matrice local -> scene	*/
        Matr	   msl;			/*    "    scene -> local	*/
        Tvc 	  vc;			/* volume englobant paral	*/
        Tvs 	  vs;			/*    "       "     spherique   */
        short 	  filsg;		/* position fils gauche ds table*/
        short 	  filsd;		/*    "       "  droit  "    "  */
        short 	  pere;			/*    "     pere dans table	*/
        Boolean   prespho;		/* presence ou non param photo	*/
        Tphoto 	  pho;			/* parametres photometriques	*/
        short 	  prof;			/* profondeur du sous arbre	*/
     } Elemfin;


/* structure de pointeur vers un element du CSG final */
/* ************************************************** */

typedef Elemfin *Sobjet;


/* structure en tableau de pointeur pour la base de primitive */
/* ********************************************************** */
typedef S2bloc Tbloc[MAXPRIMIT];






/* ******************************************************************** */
/*									*/
/* 	   structure associee a la construction d'objets 		*/
/* 		  double pointeur sur structure				*/
/*									*/
/* ******************************************************************** */


/* structure d'un objet que l'on place */
/* *********************************** */

typedef struct 
     {
        Tobj 	ty;			/* type de l'objet		*/
        short 	ptpri_obj;		/* posit primitive ou objet	*/
        Matr	 mls;			/* matrice de positionnemet	*/
     } Noeup;


/* structure de l'objet que l'on construit */
/* *************************************** */

typedef struct 
     {
        short 	  posentre; 		/* position par ordre d'entree  */
        Chaine 	  nom;			/* nom de l'objet construit	*/
        Operateur op;			/* operateur liant les sous obj */
        Boolean   prespho;		/* presence ou non param photo	*/
        Tphoto    pho;			/* parametres photometriques	*/
        short 	  prof;			/* profondeur du sous arbre	*/
        Noeup     obgauche, obdroit;	/* obj places constituant 	*/
     } Noeul;


/* structure de pointeur vers un objet construit */
/* ********************************************* */

typedef Noeul *Pt_noeud;


/* structure elementaire d'acces a un noeud */
/* **************************************** */

typedef struct 
     {
        Pt_noeud trie;			/* structure acces trie par nom	*/
	Pt_noeud entre;			/*     "       "   ordre d'entre*/
     } Elemnoeu;


/* tableau de double acces objet ( trie par nom et ordre entre) */
/* ************************************************************ */

typedef Elemnoeu Toblib[MAXNOEUD];




/* ******************************************************************** */
/*									*/
/* 		structure de donnee pour l'assemblage 			*/
/*									*/
/* ******************************************************************** */


/* type d'objet assemble */
/* ********************* */

#define NOEUDLIBRE 	0		/* noeud dna 'objlibre'		*/
#define PRIMLIBRE 	1		/* primitive dans 'bloc'	*/


/* type enumere du genre tableau */
/* ***************************** */
typedef char Typetab;


/* element de stockage d'un objet a assembler */
/* ****************************************** */

typedef struct 
     {
        Chaine nom;			/* nom de l'objet		*/
        Tobj   ty;			/* type de l'objet 		*/
        short  niveau, posit;		/* niveau arbre, position table */
        double  px, py, pz, rx, ry, rz;	/* parametres de positionnement */
     } Elemass;


/* structure pointeur vers un element de stockage pour assemblage */
/* ************************************************************** */

typedef Elemass *Tblocass;


/* structure intensite pour source lumiere en couleur R,V et B */
/* *********************************************************** */

typedef double Icouleur[3];


/* type d'une source lumineuse */
/* *************************** */

#define SPOT	0		/* lumiere de type spot 	*/
#define LUMI	1		/* lumiere nornale 		*/

typedef char	Slum;		/* contient le type de la source*/


/* structure parametre d'une source lumineuse */
/* ****************************************** */

typedef struct 
     {  
        Slum	 tl;		/* type de la source		*/
	Point	 ps;		/* position de la source	*/
        Vect	 ds;		/* direction de la source 	*/
	double	 spec;		/* coef spec pour effet spot	*/
	double	 ctrl;		/* angle maxi pour controle spot*/
        Modphoto nomodele;	/* selectionne Couleur ou NB	*/
        union
            {
               Icouleur is2;	/* intensite pour la couleur	*/
               double    is;	/* intensite pour le NB		*/
            } Select_mod;
     } Lum;


/* structure contenant les parametres de visualisation 	   */
/* ******************************************************* */

typedef struct
     {
	Modphoto	nomodele;	/* type du modele photo		*/
	short		pf;		/* profondeur du ray-casting	*/
	double		ze;		/* valeur de ze: oeil-ecran	*/
	short		xp,yp;		/* definition de l'image	*/
	double		le;		/* largeur ecran		*/
	double		he;		/* hauteur ecran		*/
	union
	   {
	 	Icouleur 	ina2;	/* intensite ambiante couleur	*/
		double		ina;	/*     "	"     nb	*/
	   } Select_mod;
	short 		ns;		/* nombre de sources		*/
	Lum		so[MAXSOURCE];	/* param des sources lumineuses */
	double 		mi;		/* indice du milieu ambiant	*/
     } Visual;


/* structure element de stockage pour 1 mot cle du langage */
/* ******************************************************* */

typedef struct 
     {
        Chaine id;			/* mot cle			*/
        short  nt;			/* numero terminal associe	*/
     } Motclef;


/* structure de stockage pour 1 variable du langage */
/* ************************************************ */
typedef struct 
     {
        Chaine id;			/* nom de la variable		*/
        double  v;			/* valeur de la variable	*/
     } Tabid;


/* structure de stockage pour 1 element photometrique (librarie) */
/* ************************************************************* */

typedef struct 
     {
        Chaine   id;			/* nom de la var photometrique	*/
        Modphoto modele;		/* type du modele Couleur ou NB */
        Tphoto   param;			/* parametres photometriques	*/
     } Ficphoto;



/* structure pour un points 3D */
/* *************************** */

typedef double Pts[3];


/* structure pour une matrice de points de controles */
/* ************************************************* */

typedef Pts Matctrl[4][4];


/* structure pour un spline bicubique */
/* ********************************** */

typedef struct 
     {
        Pts val[(MAXN - 2) * 3+1][(MAXM - 2) * 3+1];
        Pts info;
     } Surf;


/* structure pour plusieur splines bicubiques */
/* ****************************************** */

typedef Surf Rangesurf[MAXSURF];




/* ******************************************************************** */
/* 									*/
/* 			Fin definition de types				*/
/*									*/
/* ******************************************************************** */

