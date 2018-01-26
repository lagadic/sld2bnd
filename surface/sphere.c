/************************************************************************

 TITLE		: sphere.c

 DESCRIPTION	: Le module "sphere.c" contient les procedures de construction
      de la surface de la primitive "Sphere".

 VERSION	: 1.002

 ABSTRACT	:

 make_Sphere_Bound	Construit la surface de la sphere unite.
 make_Sphere_Face	Construit les faces  de la sphere unite.
 make_Sphere_Point	Construit les points de la sphere unite.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 07/05/87

 MODIFIED BY	:

 1.001 - 07/05/87 Original.
 1.002 - 15/05/87 Ajout de "Face.is_polygonal".
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include	<errno.h>

#include <bound.h>
#include <solid.h>

static	void	make_Sphere_Face ();
static	void	make_Sphere_Point ();


/*
 * La procedure "make_Sphere_Bound" construit la surface de la sphere unite :
 *	- centre (0,0,0) et rayon 1
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition.
 */
void make_Sphere_Bound (bp, level)
register Bound	*bp;
register Index	level;
{
  register Index	row = TWO_POWER(level+1);
  register Index	col = TWO_POWER(level+2);

  malloc_Bound (bp, BND_SPHERE, FALSE, row * col, (row-1) * col + 2);
  make_Sphere_Face (bp->face.ptr, level);
  make_Sphere_Point (bp->point.ptr, level);
}

/*
 * La procedure "make_Sphere_Face" constuit les faces de la sphere unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Sphere_Face (fp, level)
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
 * La procedure "make_Sphere_Point" construit les points de la sphere unite.
 * Entree :
 * pp		Tableau de points issu de la construction.
 * level	Niveau de decomposition.
 * Remarque :
 * Les points des poles ne sont pas dupliques.
 */
static	void
make_Sphere_Point (pp, level)
register Point3f	*pp;
register Index		level;
{
  static	 char	proc_name[] = "make_Sphere_Point";

  register Index	row = TWO_POWER(level+1) + 1;
  register Index	col = TWO_POWER(level+2);
  register float	*cos_lut, *sin_lut;
  register Index	i, j;

  /* cree les "lookup-tables" pour les fonctions "cos" et "sin"	*/

  if ((cos_lut = (float *) malloc (col * sizeof (float))) == NULL
  ||  (sin_lut = (float *) malloc (col * sizeof (float))) == NULL) {
    perror (proc_name);
    exit (1);
  }
  cosin_to_lut (level, cos_lut, sin_lut);

  SET_COORD3(*pp,0.0,1.0,0.0);	/* pole nord	*/
  pp++;
  for (i = 1; i < row - 1; i++) {		/* parallele	*/
    for (j = 0; j < col; j++) {	/* meridien	*/
      SET_COORD3(*pp,
      sin_lut[i]*sin_lut[j],cos_lut[i],sin_lut[i]*cos_lut[j]);
      pp++;
    }
  }
  SET_COORD3(*pp,0.0,-1.0,0.0);	/* pole sud	*/
  free ((char *) cos_lut);
  free ((char *) sin_lut);
}

