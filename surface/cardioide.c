/************************************************************************

 TITLE		: cardioide.c 

 DESCRIPTION	: Le module "cardioide.c" contient les procedures de
		  construction de la surface de la primitive "Cardioide".
		  La primitive est obtenue par rotation d'une courbe "cardioide"
		  autour de son axe de symetrie.

 La courbe cardioide a pour equation en coordonnes polaires :

	ro = a (1 + cos(teta)),

 avec teta compris entre 0 et 2*PI, avec a = 1 pour la cardioide unite.
 Dans le plan (X,Y) on a :

	x = ro cos(teta)
	y = ro sin(teta)

 VERSION	: 1.001

 ABSTRACT	: 

 make_Cardioide_Bound	Construit la surface de la cardioide unite.
 make_Cardioide_Face	Construit les faces  de la cardioide unite.
 make_Cardioide_Point	Construit les points de la cardioide unite.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 17/11/89

 MODIFIED BY	:

 1.001 - 17/11/89 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/


#include	<errno.h>


#include <bound.h>
#include <solid.h>


static	void	make_Cardioide_Face ();
static	void	make_Cardioide_Point ();


/*
 * La procedure "make_Cardioide_Bound" construit la surface de la cardioide
 * unite dans le plan (Z,Y) avec rotation de la courbe par rapport a l'axe Z.
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition.
 */
make_Cardioide_Bound (bp, level)
register Bound	*bp;
register Index	level;
{
	register Index	row = TWO_POWER(level+1);
	register Index	col = TWO_POWER(level+2);

	malloc_Bound (bp, BND_CARDIOIDE, FALSE, row * col, (row-1) * col + 2);
	make_Cardioide_Face (bp->face.ptr, level);
	make_Cardioide_Point (bp->point.ptr, level);
}

/*
 * La procedure "make_Cardioide_Face" constuit les faces de la cardioide unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Cardioide_Face (fp, level)
register Face	*fp;
register Index	level;
{
	register Index	row = TWO_POWER(level+1) + 1;
	register Index	col = TWO_POWER(level+2);
	register Index	top;	/* point de la rangee superieure	*/
	register Index	tend;	/* borne de la rangee superieure	*/
	register Index	bot;	/* point de la rangee inferieure	*/
	register Index	bend;	/* borne de la rangee inferieure	*/

	/* construit la rangee de triangles au pole nord non duplique	*/

	top  = 0;		/* rangee 0 = nord	*/
	tend = top;		/* borne rangee 0	*/
	bot  = 1;		/* rangee 1		*/
	bend = bot + col - 1;	/* borne rangee 1	*/

	/* ferme la rangee	*/
	malloc_Face_vertex3 (fp++, FALSE, top, bend, bot);
	for (; bot < bend; bot++) {
		malloc_Face_vertex3 (fp++, FALSE, top, bot, bot + 1);
	}

	/* construit les (row - 3) rangees de trapezes	*/

	for (; 3 < row; row--) {
		top++;		/* rangee i		*/
		tend += col;	/* borne rangee i	*/
		bot++;		/* rangee i + 1		*/
		bend += col;	/* borne rangee i + 1	*/

		/* ferme la rangee	*/
		malloc_Face_vertex4 (fp++, FALSE, tend, bend, bot, top);
		for (; top < tend; top++, bot++) {
			malloc_Face_vertex4 (fp++, FALSE,
					     top, bot, bot + 1, top + 1);
		}
	}

	/* construit la rangee de triangles au pole sud non duplique	*/

	top++;			/* rangee row - 1	*/
	tend += col;		/* borne rangee row - 1	*/
	bot++;			/* rangee row		*/

	/* ferme la rangee	*/
	malloc_Face_vertex3 (fp++, FALSE, tend, bend, top);
	for (; top < tend; top++) {
		malloc_Face_vertex3 (fp++, FALSE, top, bot, top + 1);
	}
}

/*
 * La procedure "make_Cardioide_Point" construit les points de la cardioide
 * unite. On a :
 *	ro = a (1 + cos(teta)), avec a = 1, teta compris entre 0 et 2*PI.
 *	x  = - ro * sin (teta) * sin(alpha),
 *	y  =   ro * sin (teta) * cos(alpha),
 *	z  =   ro * cos (teta), avec alpha compris entre 0 et PI.
 * La cardioide a deux poles :
 * Le pole nord est obtenu pour teta = 0  : (0,0,2)
 * Le pole sud  est obtenu pour teta = PI : (0,0,0)
 *	x  = 0
 * Entree :
 * pp		Tableau de points issu de la construction.
 * level	Niveau de decomposition.
 * Remarque :
 * Les points des poles ne sont pas dupliques.
 */
static	void
make_Cardioide_Point (pp, level)
register Point3f	*pp;
register Index		level;
{
	static	 char	proc_name[] = "make_Cardioide_Point";

	register Index	row = TWO_POWER(level+1) + 1;
	register Index	col = TWO_POWER(level+2);
	register float	*cos_lut, *sin_lut;
	register float	ro;
	register Index	i, j;

	/* cree les "lookup-tables" pour les fonctions "cos" et "sin"	*/

	if ((cos_lut = (float *) malloc (col * sizeof (float))) == NULL
	||  (sin_lut = (float *) malloc (col * sizeof (float))) == NULL) {
		perror (proc_name);
		exit (1);
	}
	cosin_to_lut (level, cos_lut, sin_lut);

	SET_COORD3(*pp,0.0,0.0,2.0);	/* pole nord	*/
	pp++;
	for (i = 1; i < row - 1; i++) {		/* parallele	*/
		for (j = 0; j < col; j++) {	/* meridien	*/
			ro = 1.0 + cos_lut[i];
			if (ro < 1.3 || ro > 1.7) {
				SET_COORD3(*pp,
				-ro * sin_lut[i] * sin_lut[j],
				 ro * sin_lut[i] * cos_lut[j],
				 ro * cos_lut[i]);
			}
			else {
				SET_COORD3(*pp,
				- 0.3 * cos_lut[i] * sin_lut[i] * sin_lut[j],
				  0.3 * cos_lut[i] * sin_lut[i] * cos_lut[j],
				 ro * cos_lut[i]);
			}
			pp++;
		}
	}
	SET_COORD3(*pp,0.0,0.0,0.0);	/* pole sud	*/
	free ((char *) cos_lut);
	free ((char *) sin_lut);
}

