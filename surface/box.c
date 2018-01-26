/************************************************************************

 TITLE		: box.c

 DESCRIPTION	: Le fichier "box.c" contient les procedures de gestion
      des parallelepipedes rectangles englobants
      ou boites englobantes.

 VERSION	: 1.001

 ABSTRACT	:

 make_Bounding_box_Bound	Construit la  surface de la boite englobante.
 make_Bounding_box_Face		Construit les faces   de la boite englobante.
 make_Bounding_box_Point	Construit les points  de la boite englobante.

 set_Bounding_box		Initialise une boite  englobante.
 union_Bounding_box		Union      de  boites englobantes.

 ENVIRONMENT	: Compilation	-
      gould		Machines GOULD.
      sun		Machines SUN 3.
      sun4		Machines SUN 4.
      vax		Machines VAX 750, 8250.
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 24/11/88

 MODIFIED BY	:

 1.001 - 24/11/88 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/


#include	<errno.h>


#include <bound.h>
static	void	make_Bounding_box_Face ();
static	void	make_Bounding_box_Point ();


/*
 * La procedure "make_Bounding_box_Bound" contruit la surface polygonale
 * d'une boite englobante :
 * 	- origine   (xmin,ymin,zmin).
 *	- diagonale (xmax,ymax,zmax).
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bbp		Boite englobante origine.
 * Entree/Sortie :
 * bp		Surface issue de la construction.
 */
make_Bounding_box_Bound (bbp, bp)
register Bounding_box	*bbp;
register Bound		*bp;
{
  malloc_Bound (bp, BND_BLOCK, TRUE, 6, 8);
  make_Bounding_box_Face (bp->face.ptr);
  make_Bounding_box_Point (bbp, bp->point.ptr);
}

/*
 * La procedure "make_Bounding_box_Face" constuit les 6 faces d'une boite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Numeros des faces		|Y
 *				|    5/
 *				|____/____
 *			       /         /|
 *			      /    3	/ |
 *			     /_________/  |
 *			    |	      | 1 |
 *			0___|         |   |___X
 *			    |    4    |  /
 *			    |         | /
 *			    |_________|/
 *			   /    |
 *			 Z/     |2
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 */
static	void
make_Bounding_box_Face (fp)
register Face	*fp;
{
  malloc_Face_vertex4 (fp++,TRUE,0,4,7,1);	/* face gauche	*/
  malloc_Face_vertex4 (fp++,TRUE,3,2,6,5);	/* face droite	*/
  malloc_Face_vertex4 (fp++,TRUE,0,3,5,4);	/* face dessous	*/
  malloc_Face_vertex4 (fp++,TRUE,1,7,6,2);	/* face dessus	*/
  malloc_Face_vertex4 (fp++,TRUE,4,5,6,7);	/* face avant	*/
  malloc_Face_vertex4 (fp  ,TRUE,0,1,2,3);	/* face arriere	*/
}

/*
 * La procedure "make_Bounding_box_Point" constuit les 8 points d'une boite.
 * Numeros des points		|Y
 *				|
 *				1_________2
 *			       /|        /|
 *			      / | 	/ |
 *			    7_________6/  |
 *			    |	|     |   |
 *			    |	0_____|___3___X
 *			    |  /      |  /
 *			    | /	      | /
 *			    4/________5/
 *			    /
 *			  Z/
 * Entree :
 * bbp		Boite englobante.
 * Entree/Sortie :
 * pp		Tableau de points issu de la construction.
 */
static	void
make_Bounding_box_Point (bbp, pp)
register Bounding_box	*bbp;
register Point3f	*pp;
{
  SET_COORD3(*pp,bbp->xmin,bbp->ymin,bbp->zmin); pp++;
  SET_COORD3(*pp,bbp->xmin,bbp->ymax,bbp->zmin); pp++;
  SET_COORD3(*pp,bbp->xmax,bbp->ymax,bbp->zmin); pp++;
  SET_COORD3(*pp,bbp->xmax,bbp->ymin,bbp->zmin); pp++;
  SET_COORD3(*pp,bbp->xmin,bbp->ymin,bbp->zmax); pp++;
  SET_COORD3(*pp,bbp->xmax,bbp->ymin,bbp->zmax); pp++;
  SET_COORD3(*pp,bbp->xmax,bbp->ymax,bbp->zmax); pp++;
  SET_COORD3(*pp,bbp->xmin,bbp->ymax,bbp->zmax);
}

/*
 * La procedure "set_Bounding_box" initialise la boite englobante
 * par les bornes du tableau de points 3D sur les axes (x,y,z).
 * Entree :
 * pp		Tableau de points 3D.
 * size		Taille  du tableau "pp".
 * Entree/Sortie :
 * bbp		Boite a initialiser.
 */
void set_Bounding_box (pp, size, bbp)
register Point3f	*pp;
int			size;
register Bounding_box	*bbp;
{
  static	char	proc_name[] = "set_Bounding_box";

  register Point3f	*pend = pp + size;	/* borne de "pp" */

  if (size == 0) {
    fprintf (stderr, "%s: empty Point3f list\n", proc_name);
    return;
  }
  bbp->xmin = bbp->xmax = pp->x;
  bbp->ymin = bbp->ymax = pp->y;
  bbp->zmin = bbp->zmax = pp->z;
  for (pp++; pp < pend; pp++) {
    MIN_MAX(pp->x,bbp->xmin,bbp->xmax);
    MIN_MAX(pp->y,bbp->ymin,bbp->ymax);
    MIN_MAX(pp->z,bbp->zmin,bbp->zmax);
  }
}

/*
 * La procedure "union_Bounding_box" calcule la boite englobant deux boites.
 * Entree/Sortie :
 * bbp		Boite englobante resultat : bbp = bbp0 U bbp1.
 * Entree :
 * bbp0, bbp1	Boites englobantes a unir.
 */
union_Bounding_box (bbp, bbp0, bbp1)
register Bounding_box	*bbp, *bbp0, *bbp1;
{
  bbp->xmin = MIN(bbp0->xmin, bbp1->xmin);
  bbp->xmax = MAX(bbp0->xmax, bbp1->xmax);
  bbp->ymin = MIN(bbp0->ymin, bbp1->ymin);
  bbp->ymax = MAX(bbp0->ymax, bbp1->ymax);
  bbp->zmin = MIN(bbp0->zmin, bbp1->zmin);
  bbp->zmax = MAX(bbp0->zmax, bbp1->zmax);
}

