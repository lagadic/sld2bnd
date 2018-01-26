/************************************************************************

 TITLE		: cylinder.c

 DESCRIPTION	: Le module "cylinder.c" contient les procedures de construction
		  de la surface de la primitive "Cylinder".

 VERSION	: 1.002

 ABSTRACT	: 

 make_Cylinder_Bound	Construit la surface du cylindre unite.
 make_Cylinder_Face	Construit les faces  du cylindre unite.
 make_Cylinder_Point	Construit les points du cylindre unite.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 07/05/87

 MODIFIED BY	:

 1.001 - 07/05/87 Original.
 1.002 - 13/05/87 Ajout de "Face.is_polygonal".
		  Renommage de "..._Cyln_..." en "..._Cylinder_...".
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include	<errno.h>

#include <bound.h>
#include <solid.h>


static	void	make_Cylinder_Face ();
static	void	make_Cylinder_Point ();


/*
 * La procedure "make_Cylinder_Bound" construit la surface du cylindre unite :
 *	- disque base   de centre (0,0,0) et de rayon 1
 *      - disque sommet de centre (0,0,1) et de rayon 1
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition;
 */
make_Cylinder_Bound (bp, level)
register Bound	*bp;
register Index	level;
{
	register Index	col = TWO_POWER(level+2);

	malloc_Bound (bp, BND_CYLINDER, FALSE, col * 3, col * 2 + 2);
	make_Cylinder_Face (bp->face.ptr, level);
	make_Cylinder_Point (bp->point.ptr, level);
}

/*
 * La procedure "make_Cylinder_Face" constuit les faces du cylindre unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Numero des faces	| Z
 *			|
 *		    0_______col-1
 *		    |	    |
 *		 col|       |2*col-1
 *		    |       |
 *	      2*col+1_______3*col-1___Y
 *		     /	|
 *		   X/	|
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Cylinder_Face (fp, level)
register Face	*fp;
register Index	level;
{
	register Index	col = TWO_POWER(level+2);
	register Index	top;	/* point de la rangee superieure	*/
	register Index	tend;	/* borne de la rangee superieure	*/
	register Index	bot;	/* point de la rangee inferieure	*/
	register Index	bend;	/* borne de la rangee inferieure	*/

	/* construit le disque du cylindre	*/

	top  = 0;		/* pole nord du cylindre	*/
	tend = top;		/* borne  de la rangee		*/
	bot  = 1;		/* disque du cylindre		*/
	bend = bot + col - 1;	/* borne du disque		*/
	/* ferme le sommet du cylindre	*/
	malloc_Face_vertex3 (fp++, FALSE, top, bend, bot);
	for (; bot < bend; bot++) {
		malloc_Face_vertex3 (fp++, FALSE, top, bot, bot + 1);
	}

	/* construit l'anneau du cylindre	*/

	top++;
	tend += col;
	bot++;
	bend += col;
	/* ferme le cylindre	*/
	malloc_Face_vertex4 (fp++, FALSE, tend, bend, bot, top);
	for (; top < tend; top++, bot++) {
		malloc_Face_vertex4 (fp++, FALSE, top, bot, bot + 1, top + 1);
	}

	/* construit la base du cylindre	*/

	top++;		/* base du cylindre	*/
	tend += col;	/* borne de la base	*/
	bot++;		/* pole sud		*/
	/* ferme la base du cylindre	*/
	malloc_Face_vertex3 (fp++, TRUE, bot, top, tend);
	for (; top < tend; top++) {
		malloc_Face_vertex3 (fp++, TRUE, bot, top + 1, top);
	}
}

/*
 * La procedure "make_Cylinder_Point" construit les points du cylindre unite.
 * Numero des points	| Z
 *			0
 *		    1_______col
 *		    |	    |
 *		    |       |
 *		    |       |
 *		col+1_______2*col___Y
 *		     /  |
 *		   X/2*col+1
 * Entree :
 * pp		Tableau de points issu de la construction.
 * level	Niveau de decomposition
 */
static	void
make_Cylinder_Point (pp, level)
register Point3f	*pp;
register Index		level;
{
	static	 char	proc_name[] = "make_Cylinder_Point";

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

	/* construit les disques base et sommet du cylindre		*/

	SET_COORD3(*pp,0.0,0.0,1.0);	/* pole nord	*/
	pp++;
	for (i = 0; i < col; i++) { 	/* disque sommet de rayon 1	*/
		SET_COORD3(*pp,cos_lut[i],sin_lut[i],1.0);
		pp++;
	}
	for (i = 0; i < col; i++) { 	/* disque base   de rayon 1	*/
		SET_COORD3(*pp,cos_lut[i],sin_lut[i],0.0);
		pp++;
	}
	SET_COORD3(*pp,0.0,0.0,0.0);	/* pole sud	*/
	free ((char *) cos_lut);
	free ((char *) sin_lut);
}

