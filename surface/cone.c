/************************************************************************

 TITLE		: cone.c

 DESCRIPTION	: Le module "cone.c" contient les procedures de construction
		  de la surface de la primitive "Cone".

 VERSION	: 1.002

 ABSTRACT	:

 make_Cone_Bound	Construit la surface du cone unite.
 make_Cone_Face		Construit les faces  du cone unite.
 make_Cone_Point	Construit les points du cone unite.


 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 07/05/87

 MODIFIED BY	:

 1.001 - 07/05/87 Original.
 1.002 - 11/05/87 Ajout de "Face.is_polygonal".
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include	<errno.h>

#include <bound.h>
#include <solid.h>



static	void	make_Cone_Face ();
static	void	make_Cone_Point ();


/*
 * La procedure "make_Cone_bound" construit la surface du cone unite :
 *	- cercle base de centre (0,0,1) et de rayon 1
 *	- sommet (0,0,0)
 * Le sens de parcours du contour d'une face donne le sens de
 * la normale a la face.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition;
 */
make_Cone_Bound (bp, level)
register Bound	*bp;
register Index	level;
{
	register Index	col = TWO_POWER(level+2);

	malloc_Bound (bp, BND_CONE, FALSE, col * 2, col + 2);
	make_Cone_Face (bp->face.ptr, level);
	make_Cone_Point (bp->point.ptr, level);
}

/*
 * La procedure "make_Cone_Face" constuit les faces du cone unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale
 * a la face.
 * Numeros des faces :	|Z
 *			|
 *		       / \
 *		      /   \
 *		     /     \
 *		    0______col-1__Y
 *		  col	   2*col-1
 *		   /
 *		 X/
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Cone_Face (fp, level)
register Face	*fp;
register Index	level;
{
	register Index	col = TWO_POWER(level+2);
	register Index	top;	/* point de la rangee superieure	*/
	register Index	tend;	/* borne de la rangee superieure	*/
	register Index	bot;	/* point de la rangee inferieure	*/
	register Index	bend;	/* borne de la rangee inferieure	*/

	/* construit l'anneau du cone	*/

	top  = 0;		/* pole nord du cone	*/
	bot  = 1;		/* base du cone		*/
	bend = bot + col - 1;	/* borne de la base	*/

	/* ferme l'anneau du cone	*/
	malloc_Face_vertex3 (fp++, FALSE, top, bend, bot);
	for (; bot < bend; bot++) {
		malloc_Face_vertex3 (fp++, FALSE, top, bot, bot + 1);
	}

	/* construit la base du cone	*/

	top  = 1;		/* base du cone		*/
	tend = top + col - 1;	/* borne de la base	*/
	bot  = col + 1;		/* pole sud		*/

	/* ferme la base du cone	*/
	malloc_Face_vertex3 (fp++, TRUE, bot, top, tend);
	for (; top < tend; top++) {
		malloc_Face_vertex3 (fp++, TRUE, bot, top + 1, top);
	}
}

/*
 * La procedure "make_Cone_Point" construit les points du cone unite.
 * Numero des points	| Z
 *			|
 *		        0
 *		       / \
 *		      /   \
 *		     /     \
 *		    1______col__Y
 *		   /  col+1
 *		 X/	|
 * Entree :
 * pp		Tableau de points issu de la construction.
 * div		Niveau de decomposition
 */
static	void
make_Cone_Point (pp, level)
register Point3f	*pp;
register Index		level;
{
	static	 char	proc_name[] = "make_Cone_Point";

	register Index	col = TWO_POWER(level+2);
	register Index	i;
	register float	*cos_lut, *sin_lut;

	/* cree les "lookup-tables" pour les fonction "cos" et "sin"	*/

	if ((cos_lut = (float *) malloc (col * sizeof (float))) == NULL
	||  (sin_lut = (float *) malloc (col * sizeof (float))) == NULL) {
		perror (proc_name);
		exit (1);
	}
	cosin_to_lut (level, cos_lut, sin_lut);

	SET_COORD3(*pp,0.0,0.0,1.0);	/* point sommet	sur l'axe z	*/
	pp++;
	/* construit le cercle base et le sommet du cone		*/

	for (i = 0; i < col; i++) { 	/* cercle base de rayon 1	*/
		SET_COORD3(*pp,cos_lut[i],sin_lut[i],0.0);
		pp++;
	}
	SET_COORD3(*pp,0.0,0.0,0.0);	/* point centre de la base	*/
	free ((char *) cos_lut);
	free ((char *) sin_lut);
}

