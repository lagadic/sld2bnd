/************************************************************************

 TITLE		: pipe.c

 DESCRIPTION	: Le module "pipe.c" contient les procedures de construction
		  de la surface de la primitive "Pipe".

 VERSION	: 1.001

 ABSTRACT	: 

 make_Pipe_Bound	Construit la surface du tuyau unite.
 make_Pipe_Face		Construit les faces  du tuyau unite.
 make_Pipe_Point	Construit les points du tuyau unite.

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3.
			sun4		Machines SUN 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 05/08/88

 MODIFIED BY	:

 1.001 - 05/08/88 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include <bound.h>


static	void	make_Pipe_Face ();
static	void	make_Pipe_Point ();


/*
 * La procedure "make_Pipe_Bound" construit la surface du tuyau unite :
 *	- disque base   de centre (0,0,0) et de rayon 1
 *      - disque sommet de centre (0,0,1) et de rayon 1
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition;
 */
make_Pipe_Bound (bp, level)
Bound	*bp;
Index	level;
{
	Index	col = TWO_POWER(level+2);

	malloc_Bound (bp, BND_PIPE, FALSE, col, col * 2);
	make_Pipe_Face (bp->face.ptr, level);
	make_Pipe_Point (bp->point.ptr, level);
}

/*
 * La procedure "make_Pipe_Face" constuit les faces du tuyau unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Numero des faces	| Z
 *			|
 *		     ___|___
 *		    |	    |
 *		   0|       |col-1
 *		    |       |
 *		    |_______|
 *		     /	|
 *		   X/	|
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Pipe_Face (fp, level)
register Face	*fp;
Index		level;
{
	Index		col = TWO_POWER(level+2);
	register Index	top;	/* point de la rangee superieure	*/
	register Index	tend;	/* borne de la rangee superieure	*/
	register Index	bot;	/* point de la rangee inferieure	*/
	register Index	bend;	/* borne de la rangee inferieure	*/

	/* construit l'anneau du tuyau	*/

	top  = 0;		/* pole nord du tuyau	*/
	tend = top + col - 1;	/* borne  de la rangee	*/
	bot  = col;		/* disque du tuyau	*/
	bend = bot + col - 1;	/* borne du disque	*/

	/* ferme le tuyau	*/

	malloc_Face_vertex4 (fp++, FALSE, tend, bend, bot, top);

	for (; top < tend; top++, bot++) {
		malloc_Face_vertex4 (fp++, FALSE, top, bot, bot + 1, top + 1);
	}
}

/*
 * La procedure "make_Pipe_Point" construit les points du tuyau unite.
 * Numero des points	| Z
 *			0
 *		    0_______col-1
 *		    |	    |
 *		    |       |
 *		    |       |
 *		 col|_______2*col-1
 *		     /  |
 *		   X/
 * Entree :
 * pp		Tableau de points issu de la construction.
 * level	Niveau de decomposition
 */
static	void
make_Pipe_Point (pp, level)
register Point3f	*pp;
Index			level;
{
	static	 char	proc_name[] = "make_Pipe_Point";

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

	/* construit les disques base et sommet du tuyau		*/

	for (i = 0; i < col; i++) { 	/* disque sommet de rayon 1	*/
		SET_COORD3(*pp,cos_lut[i],sin_lut[i],1.0);
		pp++;
	}
	for (i = 0; i < col; i++) { 	/* disque base   de rayon 1	*/
		SET_COORD3(*pp,cos_lut[i],sin_lut[i],0.0);
		pp++;
	}
	free ((char *) cos_lut);
	free ((char *) sin_lut);
}

