/************************************************************************

 TITLE		: strip.c

 DESCRIPTION	: Le module "strip.c" contient les procedures de calcul
      de la matrice d'inertie et des valeurs propres.
      Les vecteurs propres de la matrice d'inertie forment
      une base orthonormee directe.

 CSSP	: Matrix of Centered (or Corrected) Sums and Squares and Products.

 VERSION	: 1.002

 ABSTRACT	:

 make_Bound_inertia	Construit une boite englobant les axes d'inertie.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Bruno Arnaldi 		CREATION DATE	: 01/12/88
      Jean-Luc Corrre
 MODIFIED BY	:

 1.001 - 01/12/88 Original.
 1.002 - 05/01/89 Ajout de la matrice d'inertie.
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/

#include <string.h>


#include <bound.h>


/*
 * La procedure "make_Point3f_list_inertia" constuit le parallelepipede
 * rectangle englobant les axes principaux d'inertie d'une liste de points.
 * Entree :
 * plp		Liste de points origine.
 * Entree/Sortie :
 * bp		Surface englobante a construire.
 */
void make_Point3f_list_inertia (plp, bp)
Point3f_list	*plp;
Bound		*bp;
{
  static	char	proc_name[] = "make_Point3f_list_inertia";

  Bounding_box	box;	/* boite englobante		*/
  Point3f		*p3;	/* copie des points de plp	*/
  Matrice		cssp;	/* matrice de covariance	*/
  Matrice		im;	/* rotation locale  -> inertie	*/
  Matrice		m;	/* matrice  locale <-> inertie	*/
  Vecteur		v;	/* origine <-> centre de gravite*/

  if ((p3 = (Point3f *) malloc (plp->nbr * sizeof (Point3f))) == NULL){
    perror (proc_name);
    exit (1);
  }
  /*
   * Calcule la matrice de covariance des points 3D de la surface
   * et calcule la matrice de rotation locale -> inertie.
   */
  make_Point3f_list_CSSP (plp, cssp);
  norme_CSSP (cssp);
  make_CSSP_inertia (cssp, im);
  /*
   * Calcule la matrice de passage locale -> inertie : m = T x R
   *	T = translation centre de gravite -> origine locale
   *	R = im.
   */
  bcopy ((char *) im, (char *) m, sizeof (Matrice));
  SET_COORD3(v, - cssp[3][0], - cssp[3][1], - cssp[3][2]);
  pretrans_matrix (m, &v);
  /*
   * Calcule la surface de la boite englobante dans le repere principale :
   * 1 Transforme les points  dans le repere principale d'inertie.
   * 2 Calcule 	le volume englobant dans ce repere.
   * 3 Construit	la surface du volume englobant.
   */
  point_3D_3D (plp->ptr, (int) plp->nbr, m, p3);
  set_Bounding_box (p3, (int) plp->nbr, &box);
  free ((char *) p3);
  make_Bounding_box_Bound (&box, bp);
  /*
   * Calcule la matrice de passage inertie -> locale : m = R x T
   *	R = (im)-1 = (im)t
   *	T = translation origine locale -> centre de gravite
   */
  bcopy ((char *) im, (char *) m, sizeof (Matrice));
  transpose_matrix (m);
  m[3][0] = cssp[3][0];
  m[3][1] = cssp[3][1];
  m[3][2] = cssp[3][2];
  /*
   * Passage des points de la surface englobante du repere principal
   * d'inertie au repere locale initial.
   */
  point_3D_3D (bp->point.ptr, (int) bp->point.nbr, m, bp->point.ptr);
}

/*
 * La procedure "strip_Point3f_list" constuit le parallelepipede rectangle
 * englobant les axes principaux d'inertie de la surface.
 * Entree :
 * bp		Surface origine.
 * Entree/Sortie :
 * ibp		Surface englobante a construire.
 */
void strip_Point3f_list (level, point, plp, bsp)
int			level, point;
register Point3f_list	*plp;
Bound_scene		*bsp;
{
  static	char	proc_name[] = "strip_Point3f_list";

  Bounding_box	box;	/* boite englobante		*/
  Bound		*bp;	/* surface englobante		*/
  Point3f		*p3;	/* copie des points de plp	*/
  Matrice		cssp;	/* matrice de covariance	*/
  Matrice		im;	/* rotation locale  -> inertie	*/
  Matrice		m;	/* matrice  locale <-> inertie	*/
  Vecteur		v;	/* origine <-> centre de gravite*/
  Point3f_list	pinf;
  Point3f_list	psup;
  char		axe;
  int		i, le;

  if ((p3 = (Point3f *) malloc (plp->nbr * sizeof (Point3f))) == NULL){
    perror (proc_name);
    exit (1);
  }
  /*
   * Calcule la matrice de covariance des points 3D de la surface
   * et calcule la matrice de rotation locale -> inrertie.
   */
  make_Point3f_list_CSSP (plp, cssp);
  norme_CSSP (cssp);
  make_CSSP_inertia (cssp, im);
  /*
   * Calcule la matrice de passage locale -> inertie : m = T x R
   *	T = translation centre de gravite -> origine locale
   *	R = im.
   */
  bcopy ((char *) im, (char *) m, sizeof (Matrice));
  SET_COORD3(v, - cssp[3][0], - cssp[3][1], - cssp[3][2]);
  pretrans_matrix (m, &v);
  /*
   * Calcule la surface de la boite englobante dans le repere principale :
   * 1 Transforme les points  dans le repere principale d'inertie.
   * 2 Calcule 	le volume englobant dans ce repere.
   * 3 Construit	la surface du volume englobant.
   */
  point_3D_3D (plp->ptr, (int) plp->nbr, m, p3);
  set_Bounding_box (p3, (int) plp->nbr, &box);

  if ((pinf.ptr = (Point3f *)malloc(plp->nbr*sizeof (Point3f))) == NULL
  ||  (psup.ptr = (Point3f *)malloc(plp->nbr*sizeof (Point3f))) == NULL){
    perror (proc_name);
    exit (1);
  }
  pinf.nbr = psup.nbr = 0;

  /*
   * Recherche l'axe principal d'inertie.
   * Cree une partition des points sur l'axe principal :
   * - ensemble des points <= 0 sur l'axe (pinf).
   * - ensemble des points >  0 sur l'axe (psup).
   */
  if (box.xmax - box.xmin >= box.ymax - box.ymin
  &&  box.xmax - box.xmin >= box.zmax - box.zmin)
    axe = 'x';
  else if (box.ymax - box.ymin >= box.xmax - box.xmin
       &&  box.ymax - box.ymin >= box.zmax - box.zmin)
    axe = 'y';
  else
    axe = 'z';

  for (i = 0; i < plp->nbr; i++) {
    switch (axe) {
    case 'x' : le = (p3[i].x <= 0.0); break;
    case 'y' : le = (p3[i].y <= 0.0); break;
    case 'z' : le = (p3[i].z <= 0.0); break;
    }
    if (le) pinf.ptr[pinf.nbr++] = plp->ptr[i];
    else	psup.ptr[psup.nbr++] = plp->ptr[i];
  }
  free ((char *) p3);

  /*
   * Le partitionnement n'est pas significatif par manque de points.
   * Les deux ensembles "pinf" et "psup" sont mixes pour la creation
   * d'un seul volume englobant.
   */
  if (level-1  <= 0
  ||  pinf.nbr == 0
  ||  psup.nbr == 0
  || (pinf.nbr <= point && psup.nbr <= point)) {
    free ((char *) pinf.ptr);
    free ((char *) psup.ptr);
    bp = bsp->bound.ptr + bsp->bound.nbr++;
    make_Bounding_box_Bound (&box, bp);
    bcopy ((char *) im, (char *) m, sizeof (Matrice));
    transpose_matrix (m);
    m[3][0] = cssp[3][0];
    m[3][1] = cssp[3][1];
    m[3][2] = cssp[3][2];
    point_3D_3D (bp->point.ptr,(int) bp->point.nbr,m,bp->point.ptr);
    return;
  }

  /*
   * L'ensemble "pinf" n'est pas significatif.
   * Le volume englobant de "pinf" correspond au morceau inferieur du
   * volume englobant initial sur l'axe principal.
   * L'ensemble "psup" est subdivise recursivement.
   */
  if (pinf.nbr <= point && psup.nbr > point) {
    free ((char *) pinf.ptr);
    switch (axe) {
    case 'x' : box.xmax = 0.0; break;
    case 'y' : box.ymax = 0.0; break;
    case 'z' : box.zmax = 0.0; break;
    }
    bp = bsp->bound.ptr + bsp->bound.nbr++;
    make_Bounding_box_Bound (&box, bp);
    bcopy ((char *) im, (char *) m, sizeof (Matrice));
    transpose_matrix (m);
    m[3][0] = cssp[3][0];
    m[3][1] = cssp[3][1];
    m[3][2] = cssp[3][2];
    point_3D_3D (bp->point.ptr,(int) bp->point.nbr,m,bp->point.ptr);
    strip_Point3f_list (level-1, point, &psup, bsp);
    free ((char *) psup.ptr);
    return;
  }

  /*
   * L'ensemble "pinf" est subdivise recursivement.
   * L'ensemble "psup" n'est pas significatif.
   * Le volume englobant de "psup" correspond au morceau superieur du
   * volume englobant initial sur l'axe principal.
   */
  if (pinf.nbr > point && psup.nbr <= point) {
    free ((char *) psup.ptr);
    strip_Point3f_list (level-1, point, &pinf, bsp);
    free ((char *) pinf.ptr);
    switch (axe) {
    case 'x' : box.xmin = 0.0; break;
    case 'y' : box.ymin = 0.0; break;
    case 'z' : box.zmin = 0.0; break;
    }
    bp = bsp->bound.ptr + bsp->bound.nbr++;
    make_Bounding_box_Bound (&box, bp);
    bcopy ((char *) im, (char *) m, sizeof (Matrice));
    transpose_matrix (m);
    m[3][0] = cssp[3][0];
    m[3][1] = cssp[3][1];
    m[3][2] = cssp[3][2];
    point_3D_3D (bp->point.ptr,(int) bp->point.nbr,m,bp->point.ptr);
    return;
  }
  /*
   * L'ensemble "pinf" est subdivise recursivement.
   * L'ensemble "psup" est subdivise recursivement.
   */
  if (pinf.nbr > point && psup.nbr > point) {
    strip_Point3f_list (level-1, point, &pinf, bsp);
    free ((char *) pinf.ptr);
    strip_Point3f_list (level-1, point, &psup, bsp);
    free ((char *) psup.ptr);
    return;
  }
}

