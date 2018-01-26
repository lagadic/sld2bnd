/************************************************************************

 TITLE		: fractal.c

 DESCRIPTION	: Le module "fractal.c" contient les procedures de calcul
		  des fractales.

 VERSION	: 1.001

 ABSTRACT	: 
 
 open_hash		Ouvre le mode "hash".
 close_hash		Ferme le mode "hash".

 install		Cree un point d'entree dans la table de hachage.
 lookup			Recherche un point dans la table de hachage.

 open_rand3		Ouvre le mode "rand3".
 close_rand3		Ouvre le mode "rand3".

 open_rand4		Ouvre le mode "rand4".
 close_rand4		Ouvre le mode "rand4".

 edge_subdivision	Subdivise une arete d'une fractale.
 F3_subdivision		Subdivise une fractale triangulaire.
 F4_subdivision		Subdivise une fractale trapezoidale.

 make_F3_Bound		Construit une surface a partir d'une fractale F3.
 make_F4_Bound		Construit une surface a partir d'une fractale F4.
 make_Fractal_Bound	Construit une surface a partir d'une fractale.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 01/08/88

 MODIFIED BY	:

 1.001 - 01/08/88 Original.
 1.003 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/

#include <string.h>

#include <surface.h>

#define	PRIME		211
#define	HASHFUNC(I,J)	((((I) << 4) + (J)) % PRIME)


typedef	struct	hash_node {
	struct	hash_node	*next;	/* chainage noeud suivant	*/
	Index			i, j;	/* indices ligne/colonne	*/
	Index			n;	/* numero du point		*/
} Hash_node;


static	Hash_node	**hash_tbl;	/* table de hachage des points	*/
static	Hash_node	*node_tbl;	/* table des noeuds		*/
static	int		node_nbr;	/* nombre de noeuds		*/


/*
 * La procedure "open_hash" ouvre le mode "hash".
 * La procedure alloue et initialise les variables utilisees par le hachage
 * des points de la fractale.
 */
static
open_hash ()
{
	register int	i;

	hash_tbl = (Hash_node **) malloc (PRIME * sizeof (Hash_node *));
	node_tbl = (Hash_node *)  malloc (POINT_NBR * sizeof (Hash_node));
	for (i = 0; i < PRIME; hash_tbl[i++] = NULL);
}

/*
 * La procedure "close_hash" ferme le mode "hash".
 * La procedure libere les variables utilisees par le hachage
 * des points de la fractale.
 */
static
close_hash ()
{
	free ((char *) hash_tbl);
	free ((char *) node_tbl);
}

/*
 * La procedure "install" stocke un noeud dans la table de hachage.
 * Entree :
 * i, j		Indices (ligne, colonne) d'un point.
 * n		Indice du point dans la table des points.
 * Sortie :
 *		L'adresse du noeud dans la table de hachage.
 */
static	Hash_node
*install (i, j, n)
Index	i, j;
Index	n;
{
	register Hash_node	*hp	= &node_tbl[n];
		 int		bucket	= HASHFUNC(i,j);

	hp->next = hash_tbl[bucket];
	hash_tbl[bucket] = hp;

	hp->i = i;
	hp->j = j;
	hp->n = n;
	return (hp);
}

/*
 * La procedure "lookup" recherche un noeud dans la table de hachage.
 * Entree :
 * i, j		Indices (ligne, colonne) d'un point.
 * Sortie :
 *		L'adresse du noeud dans la table de hachage si present,
 * 		NULL sinon.
 */
static	Hash_node
*lookup (i, j)
Index	i, j;
{
	register Hash_node	*bucket = hash_tbl[HASHFUNC(i,j)];

	for (; bucket != NULL; bucket = bucket->next)
		if (bucket->i == i && bucket->j == j) return (bucket);
	return (NULL);
}


#define	MAX_SUB		10


/*
 * Table de 64 nombres aleatoires.
 * Voir Thierry Priol pour la generation de ces nombres.
 */
static	float	gauss_tbl[] =  {
	 -4.63425E-01,	-1.46393E+00,	-2.23872E-01,	-2.34799E-01,
	5.69318E-01,	2.42229E+00,	-9.85031E-01,	-4.83918E-01,
	1.41501E+00,	-9.72064E-01,	1.43704E+00,	6.91700E-01,
	-2.55114E+00,	2.53920E+00,	-1.74390E+00,	-2.39779E+00,
	-6.57878E-01,	-7.04764E-02,	-2.14973E-01,	-1.51571E+00,
	-2.75110E+00,	-9.52197E-01,	1.37892E+00,	-1.72372E+00,
	-4.48273E-01,	-6.20172E-01,	-1.00925E+00,	-9.04161E-01,
	-2.54129E-01,	5.70033E-01,	-3.31533E-01,	-1.45152E+00,
 	7.41130E-01,	-4.48331E-01,	-6.03121E-01,	1.32758E+00,
	-1.86655E-01,	-4.23884E-01,	1.12733E+00,	5.55160E-01,
 	3.18044E-01,	-1.17456E-01,	-8.63387E-01,	6.88276E-01,
	-1.19967E+00,	-1.12439E-01,	1.60292E-01,	1.02418E+00,
	-9.54332E-01,	5.54622E-01,	-7.12719E-01,	-6.39323E-01,
	-4.39239E-01,	-3.97148E-01,	9.67528E-01,	3.43044E-01,
	1.61815E-01,	1.34564E+00,	8.17816E-01,	-8.99379E-01,
	7.09229E-01,	-2.68985E-01,	1.18555E+00,	9.79782E-01
};

static	float	*gauss_rand;	/* tableau de nombres aleatoires	*/
static	Index	subdivision;	/* niveau  de subdivision de la fractale*/
static	Vecteur	distortion;	/* vecteur de deformation de la fractale*/

static	Face	*face_tbl;	/* tableau de faces  de la surface	*/
static	int	face_nbr;	/* nombre  de faces  de la surface	*/
static	Point3f	*point_tbl;	/* tableau de points de la surface	*/
static	int	point_nbr;	/* nombre  de points de la surface	*/


/*
 * La procedure "open_rand3" ouvre le mode "rand3".
 * La procedure alloue et initialise les nombres aleatoires utilises
 * pour la generation des fractales triangulaires.
 * Entree :
 * f3p		Geometrie de la fractale triangulaire.
 */
static	void
open_rand3 (f3p)
F3	*f3p;
{
	register int	sub;
	register float	*gauss;
	register float	average, alpha, beta;

	gauss_rand = (float *) malloc (sizeof (gauss_tbl));
	bcopy ((char *) gauss_tbl, (char *) gauss_rand, sizeof (gauss_tbl));
	/*
	 * Calcul des coefficients de la moyenne = alpha * exp (- sub * beta)
	 */	
	alpha	= f3p->scale * f3p->scale;
	beta	= f3p->dimension * (float) log (2.0);
	gauss	= gauss_rand;
	for (sub = 1; sub < MAX_SUB; sub++) {
		average = alpha * (float) exp ((double) - sub * (double) beta);
		*gauss++ *= average;	/* 3 nombres par subdivision	*/
		*gauss++ *= average;
		*gauss++ *= average;
	}
}

/*
 * La procedure "close_rand3" ferme le mode "rand3".
 */
static	void
close_rand3 ()
{
	free ((char *) gauss_rand);
}

/*
 * La procedure "open_rand4" ouvre le mode "rand4".
 * La procedure alloue et initialise les nombres aleatoires utilises
 * pour la generation des fractales trapezoidales.
 * Entree :
 * f4p		Geometrie de la fractale trapezoidale.
 */
static	void
open_rand4 (f4p)
F4	*f4p;
{
	register int	sub;
	register float	*gauss;
	register float	average, alpha, beta;

	gauss_rand = (float *) malloc (sizeof (gauss_tbl));
	bcopy ((char *) gauss_tbl, (char *) gauss_rand, sizeof (gauss_tbl));
	/*
	 * Calcul des coefficients de la moyenne = alpha * exp (- sub * beta)
	 */
	alpha	= f4p->scale * f4p->scale;
	beta	= f4p->dimension * (float) log (2.0);
	gauss	= gauss_rand;
	for (sub = 1; sub < MAX_SUB; sub++) {
		average = alpha * (float) exp ((double) - sub * (double) beta);
		*gauss++ *= average;	/* 5 nombres par subdivision	*/
		*gauss++ *= average;
		*gauss++ *= average;
		*gauss++ *= average;
		*gauss++ *= average;
	}
}

/*
 * La procedure "close_rand4" ferme le mode "rand4".
 */
static	void
close_rand4 ()
{
	free ((char *) gauss_rand);
}

/*
 * La procedure "edge_subdivision" calcule le point obtenu par translation
 * du point milieu d'un segment.
 * milieu.
 * Entree :
 * m		Point resultat m = (p0 + p1) / 2 + v * t.
 * p0, p1	Points extremites.
 * v		Direction de translation.
 * t		Norme de la translation.
 * Sortie :
 *		Indice du point milieu.
 */
static	Index
edge_subdivision (v0, v1, vp, t)
Index	v0, v1;
Vecteur	*vp;
float	t;
{
	Hash_node	*hp;
	Index		i = (node_tbl[v0].i + node_tbl[v1].i) / 2;
	Index		j = (node_tbl[v0].j + node_tbl[v1].j) / 2;

	if ((hp = lookup (i, j)) == NULL) {
		register Point3f	*p0 = point_tbl + v0;
		register Point3f	*p1 = point_tbl + v1;
		register Point3f	*mp = point_tbl + point_nbr;

		hp = install (i, j, point_nbr++);
		SET_COORD3 (*mp,
			(p0->x + p1->x) / 2.0 + vp->x * t,
			(p0->y + p1->y) / 2.0 + vp->y * t,
			(p0->z + p1->z) / 2.0 + vp->z * t);
	}
	return (hp->n);
}

static	void
F3_subdivision (level, v0, v1, v2)
Index	level;
Index	v0, v1, v2;
{
	Index	m0, m1, m2;	/* indice des points milieux	*/
	int	i;		/* indice dans "gauss_rand"	*/

	if (level == 0) {
		malloc_Face_vertex3 (face_tbl + face_nbr++,FALSE,v0,v1,v2);
		return;
	}

	i = (subdivision - level + 1) * 3;	/* voir "open_rand3"	*/
	m0 = edge_subdivision (v0, v1, &distortion, gauss_rand[i]);
	m1 = edge_subdivision (v1, v2, &distortion, gauss_rand[i+1]);
	m2 = edge_subdivision (v2, v0, &distortion, gauss_rand[i+2]);

	level--;
	F3_subdivision (level, m0, m1, m2);
	F3_subdivision (level, v0, m0, m2);
	F3_subdivision (level, m0, v1, m1);
	F3_subdivision (level, m2, m1, v2);
}

static	void
F4_subdivision (level, v0, v1, v2, v3)
Index	level;
Index	v0, v1, v2, v3;
{
	Index	m0, m1, m2, m3, m4;	/* indice des points milieux	*/
	int	i;			/* indice dans "gauss_rand"	*/

	if (level == 0) {
		malloc_Face_vertex4 (face_tbl + face_nbr++,FALSE,v0,v1,v2,v3);
		return;
	}

	i = (subdivision - level + 1) * 5;	/* voir "open_rand4"	*/
	m0 = edge_subdivision (v0, v1, &distortion, gauss_rand[i]);
	m1 = edge_subdivision (v1, v2, &distortion, gauss_rand[i+1]);
	m2 = edge_subdivision (v2, v3, &distortion, gauss_rand[i+2]);
	m3 = edge_subdivision (v3, v0, &distortion, gauss_rand[i+3]);
	m4 = edge_subdivision (m0, m2, &distortion, gauss_rand[i+4]);

	level--;
	F4_subdivision (level, v0, m0, m4, m3);
	F4_subdivision (level, m0, v1, m1, m4);
	F4_subdivision (level, m4, m1, v2, m2);
	F4_subdivision (level, m3, m4, m2, v3);
}

/* 
 * La procedure "make_F3_Bound" construit la surface de la fractale F3.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque : 
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * f3p		Fractale triangulaire.
 * bp		Surface issue de la construction.
 * level	Niveau de subdivision de la fractale.
 */
make_F3_Bound (f3p, bp, level)
F3	*f3p;
Bound	*bp;
Index	level;
{
	open_hash ();
	open_rand3 (f3p);
	malloc_Bound (bp, BND_F3, FALSE,
		TWO_POWER(level * 2),
		(TWO_POWER(level) + 1) * (TWO_POWER(level) + 2) / 2);
	face_tbl    = bp->face.ptr;
	face_nbr    = 0;
	point_tbl   = bp->point.ptr;
	point_nbr   = 3;
	distortion  = f3p->distortion;
	subdivision = level;
	norm_vector (&distortion);
	bcopy ((char *) f3p->point, (char *) point_tbl, sizeof (f3p->point));
	install (0,		0,		0);
	install (1 << level,	0,		1);
	install (0,		1 << level,	2);
	F3_subdivision (level, 0, 1, 2);
	close_rand3 ();
	close_hash ();
}

/* 
 * La procedure "make_F4_Bound" construit la surface de la fractale.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque : 
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * f4p		Fractale trapezoidale.
 * bp		Surface issue de la construction.
 * level	Niveau de subdivision de la fractale.
 */
make_F4_Bound (f4p, bp, level)
F4	*f4p;
Bound	*bp;
Index	level;
{
	open_hash ();
	open_rand4 (f4p);
	malloc_Bound (bp, BND_F4, FALSE,
		TWO_POWER(level * 2),
		(TWO_POWER(level) + 1) * (TWO_POWER(level) + 1));
	face_tbl    = bp->face.ptr;
	face_nbr    = 0;
	point_tbl   = bp->point.ptr;
	point_nbr   = 4;
	distortion  = f4p->distortion;
	subdivision = level;
	norm_vector (&distortion);
	bcopy ((char *) f4p->point, (char *) point_tbl, sizeof (f4p->point));
	install (0,		0,		0);
	install (1 << level,	0,		1);
	install (1 << level,	1 << level,	2);
	install (0,		1 << level,	3);
	F4_subdivision (level, 0, 1, 2, 3);
	close_rand4 ();
	close_hash ();
}

/*
 * La procedure "make_Fractal_Bound" construit une surface a partir 
 * d'une fractale surfacique.
 * Entree :
 * fp		Fractale surfacique source.
 * bp		Surface polyedrique a construire.
 * Sortie :
 *		TRUE si la fractale surfacique "fp" est valide, FALSE sinon.
 */
make_Fractal_Bound (fp, bp)
Fractal	*fp;
Bound	*bp;
{
	switch (fp->type) {
	case FRAC_F3	:
		make_F3_Bound (&fp->geometry.f3, bp, fp->subdivision);
		break;
	case FRAC_F4	:
		make_F4_Bound (&fp->geometry.f4, bp, fp->subdivision);
		break;
	default	:
		fprintf (stderr, "make_Fractal_Bound: fractal unknown\n");
		return (FALSE);
	}
	Position_to_Matrice (&fp->position, fp->lsm);
	point_3D_3D (bp->point.ptr,(int) bp->point.nbr, fp->lsm, bp->point.ptr);
#ifdef	face_normal
	set_Bound_face_normal (bp);
	set_Bound_normal (bp);
#endif	face_normal
	return (TRUE);
}

