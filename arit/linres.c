/************************************************************************

 TITLE		: linres.c

 DESCRIPTION	: Le module "linres.c" contient les procedures de resolution
      d'un systeme lineaire 4x4.

 VERSION	: 1.002

 ABSTRACT	:

 decomp
 forbak
 inverse_matrix	  Initialise une matrice par une matrice inverse.

 ENVIRONMENT	: Compilation	-
      gould		Machines GOULD.
      sun		Machines SUN 3, 4.
      vax		Machines VAX 750, 8250.
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Bruno Arnaldi 		CREATION DATE	: 25/05/88
      Jean-Luc Corrre
 MODIFIED BY	:

 1.001 - 25/05/88 Original.
 1.002 - 02/12/88 Ajout de "equa_...".
 1.003 - 21/03/94 Modif des include <>.

*************************************************************************/


#include	<arit.h>

#define	MSIZE	4

static	Matrice	lud;		/* decomposition LU			*/
static	int	irow[MSIZE];	/* permutation des lignes de la matrice	*/


/*
 * La procedure "decomp" effectue la decomposition LU de la matrice homogene
 * dans la matrice "lud", "irow" donne les permutations de lignes.
 * Entree :
 * ma		Matrice su systeme lineaire "A".
 * Sortie :
 * 		TRUE aux s'il n'y a pas de singularite => solution,
 *		FALSE sinon.
 */
static	int
decomp (ma)
Matrice	ma;
{
  register int	i, j, k, m, ii;
  register float  accum, condit, ratio;
    int		im, kpvt;
    float 		mthpvt;
  float		s[MSIZE];

  /* Initialisation 	*/

  for (i = 0; i < MSIZE; i++) {
    irow[i] = i;	/* aucune permutation initiale	*/

    /* "s[i]" contient le maximum de la ligne "i"	*/

    s[i] = FABS(ma[i][0]);
    for (j = 1; j < MSIZE; j++)
      if (s[i] < FABS(ma[i][j])) s[i] = FABS(ma[i][j]);
  }

  /* Iteration  principale formant la matrice LU "lud"	*/

  for (m = 0; m < MSIZE; m++) {
          /*
     * Prend les entrees de la colonne M de L^.
     */
          for (i = m; i < MSIZE; i++) {
              ii = irow[i];
              accum = ma[ii][m];
      for(k = 0; k < m; k++)
                    accum -= lud[ii][k] * lud[irow[k]][m];
      lud[ii][m] = accum;
    }
    /*
     * Chargement condit = le plus grand L^ / S^
     * de la colonne "m" de L^
     */
    condit = 0.0;
    kpvt = m;
    for(k = m; k < MSIZE; k++) {
      ratio = FABS(lud[irow[k]][m]) / s[irow[k]];
      if (ratio > condit) {
        condit = ratio;
        kpvt   = k;
      }
    }
    im = irow[kpvt];
    if (kpvt != m) {
      /*
       * Echange ligne "m" et "kpvt" dans "irow".
       */
      irow[kpvt] = irow[m];
      irow[m]    = im;
    }
    /*
     * Test de sortie si "ma" est singuliere.
     */
    mthpvt = lud[im][m];
    if (condit < M_EPSILON || FABS(mthpvt) < M_EPSILON)
      return (FALSE);
    /*
     * Prend l'entree de la ligne m de U^ (dans la ligne im de lud)
     */
    for(j = m + 1; j < MSIZE; j++) {
      accum = ma[im][j];
      for(k = 0; k < m; k++)
        accum -= lud[im][k] * lud[irow[k]][j];
      lud[im][j] = accum / mthpvt;
    }
  }
  return (TRUE);
}

/*
 * La procedure "forbak" resoud "A.X = B" en resolvant
 * 1 L^C = B^	(forward substitution)
 * 2 U^X = CBAR (backward substitution)
 * en utilisant "lud" et "irow" etablies par la procedure "decomp".
 * Entree :
 * tx		Vecteur resultat "X".
 * tb		Vecteur du systeme "B".
 */
static	void
forbak (tx, tb)
register float	*tx;
register float	*tb;
{
  register int	i, ii, k, ind;
  register float	ithpvt, accum;

  /*
   * Resolution avant, resoud L^C^ = B^ pour cbar mit dans "tx".
   */
  for (i = 0; i < MSIZE; i++) {
    ii     = irow[i];
    ithpvt = lud[ii][i];
    accum  = tb[ii];
    for(k = 0; k < i; k++)
      accum -= lud[ii][k] * tx[k];
          tx[i] = accum / ithpvt;
  }
  /*
   * Resolution arriere, resoud U^X^ = cbar pour la solution "tx".
   */
  for (ind = 1; ind < MSIZE; ind++) {
    i     = MSIZE - ind - 1;
    accum = tx[i];
    for(k = i + 1; k < MSIZE; k++)
      accum -= lud[irow[i]][k] * tx[k];
    tx[i] = accum;
        }
}

/*
 * La procedure "inverse_matrix" initialise la matrice par une matrice inverse.
 * Entree :
 * im		Matrice a initialiser.
 * m		Matrice initiale.
 * Sortie :
 *		TRUE si la matrice "m" est inversible,
 *		FALSE sinon.
 */
int inverse_matrix (im, m)
register Matrice im;
register Matrice	m;
{
  static	char	proc_name[] = "inverse_matrix";

  float		bi[MSIZE], bj[MSIZE], bk[MSIZE], bl[MSIZE];
  register int	i;

  if (! decomp (m)) {
    fprintf (stderr, "%s: singular matrix\n", proc_name);
    return (FALSE);
  }
  /*
   * Resoud les 4 systemes lineaires "m x bi = ident[i] T = ident[i]"
   */
  ident_matrix (im);
  forbak (bi, &im[0][0]);
  forbak (bj, &im[1][0]);
  forbak (bk, &im[2][0]);
  forbak (bl, &im[3][0]);
  for (i = 0; i < MSIZE; i++) {
    im[i][0] = bi[i];
    im[i][1] = bj[i];
    im[i][2] = bk[i];
    im[i][3] = bl[i];
  }
  return (TRUE);
}

