/************************************************************************

 TITLE		: grid.c

 DESCRIPTION	: Le fichier "grid.c" contient les procedures de gestion
		  des surfaces definies par une grille de points.

 VERSION	: 1.001

 ABSTRACT	: 

 free_Grid		Libere une grille de points.
 malloc_Grid		Alloue une grille de points.

 make_Grid_Bound	Construit la surface de la grille 3D.
 make_Grid_Face		Construit les faces  de la grille 3D.
 make_Grid_Point	Construit les points de la grille 3D.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 02/05/88

 MODIFIED BY	:

 1.001 - 02/05/88 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include	<errno.h>
#include	<string.h>

#include <surface.h>

static	void	make_Grid_Point ();


/*
 * La procedure "free_Grid" libere la memoire d'une grille de points.
 * Entree :
 * gp		Grille a liberer.
 */
free_Grid (gp)
Grid	*gp;
{

	if (gp->point.ptr != NULL) {	/* libere les points	*/
		free ((char *) gp->point.ptr);
		gp->point.ptr = NULL;
	}
}

/*
 * La procedure "malloc_Grid" alloue une grille de points.
 * Remarque :
 * Les tailles de la grille doivent appartenir a [0,255].
 * Entree :
 * gp		Grille a allouer.
 * row		Nombre de lignes   de la grille de points.
 * col		Nombre de colonnes de la grille de points.
 */
malloc_Grid (gp, row, col)
register Grid	*gp;
register Index	row, col;
{
	static	char	proc_name[] = "malloc_Grid";

	if (row > 255 || col > 255) {
		fprintf (stderr, "malloc_Grid: memory overflow\n");
		exit (1);
	}
	if (row && col) {	/* points aux sommets	*/
		gp->row_nbr = row;
		gp->col_nbr = col;
		gp->point.nbr = row * col;
		if ((gp->point.ptr =
		    (Point3f *) malloc (row * col * sizeof(Point3f))) == NULL) {
			perror (proc_name);
			exit (1);
		}
	}
	else {
		gp->row_nbr = 0;
		gp->col_nbr = 0;
		gp->point.ptr  = NULL;
	}
}

/*
 * La procedure "make_Grid_Bound" construit la surface de la grille 3D :
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * gp		Grille  3D origine.
 * bp		Surface polyedrique issue de la construction.
 */
make_Grid_Bound (gp, bp)
Grid	*gp;
Bound	*bp;
{
	register Index	row = gp->row_nbr;
	register Index	col = gp->col_nbr;

	malloc_Bound (bp, BND_GRID, FALSE, (row - 1) * (col - 1), row * col);
	make_Grid_Face (bp->face.ptr, row, col);
	make_Grid_Point (&gp->point, bp->point.ptr);
}

/*
 * La procedure "make_Grid_Face" constuit les faces de la grille 3D.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * row, col	Tailles de la grille 3D.
 */
make_Grid_Face (fp, row, col)
register Face	*fp;
register Index	row, col;
{
	register Index	top;	/* point de la rangee superieure	*/
	register Index	tend;	/* borne de la rangee superieure	*/
	register Index	bot;	/* point de la rangee inferieure	*/

	/* construit les (row - 1) rangees de (col - 1) trapezes	*/

	top  = 0;	/* rangee i		*/
	tend = col - 1;	/* borne rangee i	*/
	bot  = col;	/* rangee i + 1		*/

	for (; 1 < row; row--) {
		for (; top < tend; top++, bot++) {
			malloc_Face_vertex4 (fp++, FALSE,
					     top, bot, bot + 1, top + 1);
		}
		top++;		/* rangee i		*/
		tend += col;	/* borne rangee i	*/
		bot++;		/* rangee i + 1		*/
	}
}

/*
 * La procedure "make_Grid_Point" construit les points de la grille 3D.
 * Entree :
 * lp		Tableau de points 3D origine.
 * pp		Tableau de points issu de la construction.
 */
static	void
make_Grid_Point (lp, pp)
Point3f_list	*lp;
Point3f		*pp;
{
	bcopy ((char *) lp->ptr, (char *) pp, lp->nbr * sizeof (Point3f));
}

