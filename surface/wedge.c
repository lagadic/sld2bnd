/************************************************************************

 TITLE		: wedge.c

 DESCRIPTION	: Le module "wedge.c" contient les procedures de construction
      de la surface de la primitive "Wedge".

 Remarque : Le niveau de decompostion de la primitive "Wedge" est fixe.

 VERSION	: 1.001

 ABSTRACT	:

 make_Wedge_Bound	Construit la  surface du coin unite.
 make_Wedge_Face	Construit les faces   du coin unite.
 make_Wedge_Point	Construit les points  du coin unite.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 23/02/88

 MODIFIED BY	:

 1.001 - 23/02/88 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/



#include <bound.h>
#include <solid.h>


static	void	make_Wedge_Face ();
static	void	make_Wedge_Point ();


/*
 * La procedure "make_Wedge_Bound" construit la surface du coin unite :
 * 	- origine   (0,0,0).
 *	- diagonale (1,1,1).
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 */
void make_Wedge_Bound (bp)
register Bound	*bp;
{
  malloc_Bound (bp, BND_WEDGE, TRUE, 5, 6);
  make_Wedge_Face (bp->face.ptr);
  make_Wedge_Point (bp->point.ptr);
}

/*
 * La procedure "make_Wedge_Face" constuit les 6 faces du coin unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Numeros des faces		|Y
 *				|
 *				|    4/
 *			       /  \  /
 *			      /     \
 *			     /        \
 *			    | \	        \
 *		       0 ___|   \    1    \___X
 *			    |     \      /
 *			    | 	3   \   /
 *			    |_________\/
 *			    /   |
 *			  Z/    |2
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 */
static	void
make_Wedge_Face (fp)
register Face	*fp;
{
  malloc_Face_vertex4 (fp++,TRUE,0,3,5,1);	/* face gauche	*/
  malloc_Face_vertex4 (fp++,TRUE,1,5,4,2);	/* face oblique	*/
  malloc_Face_vertex4 (fp++,TRUE,0,2,4,3);	/* face dessous	*/
  malloc_Face_vertex3 (fp++,TRUE,3,4,5);		/* face avant	*/
  malloc_Face_vertex3 (fp  ,TRUE,0,1,2);		/* face arriere	*/
}

/*
 * La procedure "make_Wedge_Point" constuit les 8 points du coin unite.
 * Numeros des points		|Y
 *				|
 *				1
 *			       /| \
 *			      / |   \
 *			    5   |     \
 *			    | \	|       \
 *			    |   \0________2___X
 *			    |  /  \      /
 *			    | /	    \   /
 *			    3/________4/
 *			    /
 *			  Z/
 * Entree :
 * pp		Tableau de points issu de la construction.
 */
static	void
make_Wedge_Point (pp)
register Point3f	*pp;
{
  SET_COORD3(*pp,0.0,0.0,0.0); pp++;
  SET_COORD3(*pp,0.0,1.0,0.0); pp++;
  SET_COORD3(*pp,1.0,0.0,0.0); pp++;
  SET_COORD3(*pp,0.0,0.0,1.0); pp++;
  SET_COORD3(*pp,1.0,0.0,1.0); pp++;
  SET_COORD3(*pp,0.0,1.0,1.0);
}

