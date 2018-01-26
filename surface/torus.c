/************************************************************************

 TITLE		: torus.c

 DESCRIPTION	: Le module "torus.c" contient les procedures de construction
      de la surface de la primitive "Torus".

 VERSION	: 1.001

 ABSTRACT	:

 make_Torus_Bound	Construit la surface du tore unite.
 make_Torus_Face	Construit les faces  du tore unite.
 make_Torus_Point	Construit les points du tore unite.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 16/06/88

 MODIFIED BY	:

 1.001 - 16/06/88 Original.
 1.002 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/


#include	<errno.h>

#include <bound.h>
#include <solid.h>


static	void	make_Torus_Face ();
static	void	make_Torus_Point ();


/*
 * La procedure "make_Torus_Bound" construit la surface du tore unite :
 *	- la section generatrice est le centre unite de centre (r,0,0)
 *	  et d'axe Y
 *	- la surface de revolution est obtenue par rotation de la section
 *	  autour de l'axe Z dans le sens direct du repere droit (X,Y,Z).
 * Le sens de parcours du contour d'une face donne le sens de la normale.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 * level	Niveau de decomposition.
 * r		Rayon exterieur du tore.
 */
void make_Torus_Bound (bp, level, r)
register Bound	*bp;
register Index	level;
float		r;
{
  register Index	row = TWO_POWER(level+2);
  register Index	col = TWO_POWER(level+2);

  malloc_Bound (bp, BND_TORUS, FALSE, row * col, row * col);
  make_Torus_Face (bp->face.ptr, level);
  make_Torus_Point (bp->point.ptr, level, r);
}

/*
 * La procedure "make_Torus_Face" constuit les faces du tore unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Les faces d'une ligne "row" decrivent la surface de l'anneau compris
 * entre deux sections consecutives.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 * level	Niveau de decomposition.
 */
static	void
make_Torus_Face (fp, level)
register Face	*fp;
register Index	level;
{
  register Index	row = TWO_POWER(level+2);
  register Index	col = TWO_POWER(level+2);
  register Index	top;	/* point de la section precedante	*/
  register Index	tend;	/* borne de la section precedante	*/
  register Index	bot;	/* point de la section suivante		*/
  register Index	bend;	/* borne de la section suivante		*/

  /* construit les "row - 1" anneaux de trapezes	*/

  top  = 0;
  tend = top + col - 1;
  bot  = col;
  bend = bot + col - 1;
  for (; 1 < row; row--) {
    /* ferme l'anneau	*/
    malloc_Face_vertex4 (fp++, FALSE, tend, bend, bot, top);
    for (; top < tend; top++, bot++) {
      malloc_Face_vertex4 (fp++, FALSE,
               top, bot, bot + 1, top + 1);
    }
    top++;
    tend += col;
    bot++;
    bend += col;
  }

  /* ferme le tore par le dernier anneau	*/

  row  = TWO_POWER(level+2);
  top  = (row - 1) * col;
  tend = top + col - 1;
  bot  = 0;
  bend = col - 1;
  /* ferme l'anneau	*/
  malloc_Face_vertex4 (fp++, FALSE, tend, bend, bot, top);
  for (; top < tend; top++, bot++) {
    malloc_Face_vertex4 (fp++, FALSE,
             top, bot, bot + 1, top + 1);
  }
}

/*
 * La procedure "make_Torus_Point" construit les points du tore unite.
 * Les points d'une ligne "row" decrivent une section.
 * La premiere section (ligne 0) est le cercle unitaire d'axe Y
 * translate par le vecteur (r,0,0).
 * Les autres sections sont obtenues par rotation de la premiere section
 * par rapport a l'axe Z du repere droit (X,Y,Z) dans le sens direct.
 * Entree :
 * pp		Tableau de points issu de la construction.
 * level	Niveau de decomposition.
 * r		Rayon exterieur du tore.
 */
static	void
make_Torus_Point (pp, level, r)
register Point3f	*pp;
Index			level;
float			r;
{
  static	 char		proc_name[] = "make_Torus_Point";

  register Index		row = TWO_POWER(level+2);
  register Index		col = TWO_POWER(level+2);
  register Point3f	*ps   = pp;
  register Point3f	*pend = ps + col;
  register float		*cos_lut, *sin_lut;
  register Index		i;

  /* cree les "lookup-tables" pour les fonctions "cos" et "sin"	*/

  if ((cos_lut = (float *) malloc (col * sizeof (float))) == NULL
  ||  (sin_lut = (float *) malloc (col * sizeof (float))) == NULL) {
    perror (proc_name);
    exit (1);
  }
  cosin_to_lut (level, cos_lut, sin_lut);

  /*
   * Construction de la premier section :
   * cercle unitaire de centre (r, 0, 0).
   */
  for (i = 0; i < col; i++) {
    SET_COORD3(*pp,cos_lut[i] + r,0.0,sin_lut[i]);
    pp++;
  }

  /*
     * Construction des autres section par rotation d'ange "i" d'axe Y
   * de la premiere section.
   */
  for (i = 1; i < row; i++) {		/* angle de la section	*/
    for (; ps < pend; ps++) {	/* description section	*/
      SET_COORD3(*pp,
        ps->x * cos_lut[i],
        ps->x * sin_lut[i],
        ps->z);
      pp++;
    }
    ps -= col;
  }
  free ((char *) cos_lut);
  free ((char *) sin_lut);
}

