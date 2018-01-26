/************************************************************************

 TITLE		: cssp.c

 DESCRIPTION	: Le module "cssp.c" contient les procedures de calcul
      de la matrice d'inertie et des valeurs propres.
      Les vecteurs propres de la matrice d'inertie forment
      une base orthonormee directe.

 CSSP	: Matrice of Centered (or Corrected) Sums and Squares and Products.

 VERSION	: 1.003

 ABSTRACT	:

 equa_2			Resoud une equation du second    degre.
 equa_2			Resoud une equation du troisieme degre.
 lin_22			Resoud un systeme lineaire de deux equations.
 pow_1_3		Calcule la racine cubique d'un reel.
 newton_3		Resoud une equation du troisieme degre par Newton.
 norme_CSSP		Normalise une matrice de covariance.

 eigen_vector		Calcule un vecteur propre norme.
 make_CSSP_inertia	Construit une matrice de rotation.
 make_Point3f_list_CSSP	Construit une matrice de covariance.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Bruno Arnaldi 		CREATION DATE	: 01/12/88
      Jean-Luc Corrre
 MODIFIED BY	:

 1.001 - 01/12/88 Original.
 1.002 - 05/01/89 Ajout de la matrice d'inertie.
 1.003 - 10/02/89 Ajout de "norme_CSSP".
 1.004 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include <bound.h>

#undef	M_EPSILON
#define	M_EPSILON	(1.0E-6)


/*
 * La procedure "equa_2" cherche les racines d'un polynome du 2eme degre en X.
 *	a x^2 + b x + c = 0
 * Les racines du polynome sot triees par valeurs decroissantes.
 * Entree :
 * a, b, c	Coefficients du polynome.
 * Entree/Sortie :
 * x1, x2	Racines du polynome.
 * Sortie :
 *		Code de la nature des resultats :
 * Code 	x1	x2
 * 0		> 0	> 0	Racines indeterminees.
 * 0		< 0	< 0	Deux racines complexes.
 * 0		0	0	Pas de racines.
 * 1		x1	0	Une racine simple.
 * 2		x1	x1	Une racine double.
 * 2		x1	x2	Deux racines simples.
 */
static
equa_2 (a, b, c, x1, x2)
double	a, b, c;
double	*x1, *x2;
{
  if (fabs (a) < M_EPSILON) {
    if (fabs (b) < M_EPSILON) {
      if (fabs (c) < M_EPSILON) {
        /* racines indeterminees	*/
        *x1 = *x2 = 1.0;
        return (0);
      }
      else {
        /* pas de racine		*/
        *x1 = *x2 = 0.0;
        return (0);
      }
    }
    else {
      /* 1 racine simple		*/
      *x1 = - c / b;
      *x2 = 0.0;
      return (1);
    }
  }
  else {
    double	delta = (b * b) - (4.0 * a * c);

    if (fabs (delta) < M_EPSILON) {
      /* deux racines reelles dont une double	*/
      *x1 = *x2 = - b / (2.0 * a);
      return (2);
    }
    else if (delta > 0.0) {
      /* 2 racines reelles distinctes	*/
      delta = sqrt (delta);
        *x1 = (- b - delta) / (2.0 * a);
        *x2 = (- b + delta) / (2.0 * a);
      return (2);
    }
    else {
      /* 2 racines complexes conjuguees	*/
      *x1 = *x2 = -1.0;
      return (0);
    }
  }
}

/*
 * La procedure "pow_1_3" calcule la racine cubique d'un nombre reel.
 * Entree :
 * f		Nombre dont la racine est a calculer.
 * Sortie :
 *		Racine cubique.
 */
static double
pow_1_3 (f)
double	f;
{
#define	_1_3	(1.0 / 3.0)

  return ((f > 0.0) ? pow (f, _1_3) : - pow (- f, _1_3));
}

/*
 * La procedure "equa_3" cherche les racines d'un polynome du 3eme degre en X.
 *	a x^3 + b x^2 + c x + d = 0
 * Pour plus de renseignement, voir :
 * SHARP PC-1211 : ORDINATEUR DE POCHE, MANUEL D'APPLICATIONS, pp 18-21.
 * Entree :
 * a, b, c, d	Coefficients du polynome.
 * Entree/Sortie :
 * x1, x2, x3	Racines du polynome.
 * Sortie :
 *		Code de la nature des resultats :
 * Code 	x1	x2	x3
 * 0		> 0	> 0	0	Racines indeterminees.
 * 0		< 0	< 0	0	Deux racines complexes.
 * 0		0	0	0	Pas de racines.
 * 1		x1	0	0	Une racine simple.
 * 2		x1	x1	0	Une racine double.
 * 2		x1	x2	0	Deux racines simples.
 * 3		x1	< 0	< 0	Une racine reelle et deux complexes.
 * 3		x1	x1	x1	Une racine reelle triple.
 * 3		x1	x2	x2	Trois racines reelles dont une double.
 * 3		x1	x2	x3	Trois racines reelles simples.
 */
static
equa_3 (a, b, c, d, x1, x2, x3)
double	a, b, c, d;
double	*x1, *x2, *x3;
{
  double	p, q, delta;
  double	u, v;

  if (fabs (a) < M_EPSILON) {	/* equation du second degre	*/
    *x3 = 0.0;
    return (equa_2 (b, c, d, x1, x2));
  }
  /*
   * Normalisation de l'equation en divisant chaque coefficient par a :
   * L'equation devient : x^3 + a x^2 + b x + c = 0
   */
  u = a;
  a = b / u;
  b = c / u;
  c = d / u;
  /*
   * Le terme de second ordre est elimine par la conversion : x = y - a/3
   * L'equation devient : y^3 + 3px + q = 0
   * avec p = b/3 - a^2/9 et q = c - ab/3 + 2a^3/27
   */
  p = (b / 3.0) - ((a * a) / 9.0);
  q = c - ((a * b) / 3.0) + ((2.0 * a * a * a) / 27.0);
  delta = (q * q) + (4.0 * (p * p * p));

  if (fabs (delta) < M_EPSILON) {	/* q^2 + 4p^3 = 0	*/
    if (fabs (p) < M_EPSILON) {
      /* 3 racines reelles dont une triple 	*/
      *x1 = *x2 = *x3 = - a / 3.0;
      return (3);
    }
    else {
      /* 3 racines reelles dont une double	*/
      u = pow_1_3 (- q / 2.0);
      /* v = u;	*/
      *x1 = (2 * u) - (a / 3.0);
      *x2 = *x3 = - u - (a / 3.0);
      return (3);
    }
  }
  else if (delta > 0.0) {		/* q^2 + 4p^3 > 0	*/
    /* 1 racine reelle et deux imaginaires	*/
    delta = sqrt (delta);
    u = pow_1_3 ((- q + delta) / 2.0);
    v = pow_1_3 ((- q - delta) / 2.0);
    *x1 = u + v - (a / 3.0);
    *x2 = *x3 = - 1.0;
    return (1);
  }
  else {				/* q^2 + 4p^3 < 0	*/
    /* 3 racines relles distinctes		*/
    double	teta;

    a	/= 3.0;
    p	= sqrt (- p) * 2.0;
    delta	= sqrt (- delta);
    teta	= atan (delta / - q) / 3.0;

    *x1 =   p * sin (M_PI / 2.0 - teta) - a;
    *x2 = - p * sin (M_PI / 6.0 + teta) - a;
    *x3 = - p * sin (M_PI / 6.0 - teta) - a;
    return (3);
  }
}

/*
 * La procedure "lin_22" resoud un systeme lineaire 2x2 :
 * 2 equations :
 * 	a0 x + b0 y = c0
 *	a1 x + b1 y = c1
 * 2 inconnues :
 *	x, y
 * Entree :
 * a0, b0, c0	Coefficients de la premiere equation.
 * a1, b1, c1	Coefficients de la seconde  equation.
 * Entree/Sortie :
 * x, y		Solutions du systeme.
 * Sortie :
 *		TRUE si le systeme admet des solutions,
 *		FALSE sinon.
 */
static
lin_22 (a0, b0, c0, a1, b1, c1, x, y)
float	a0, b0, c0;
float	a1, b1, c1;
float	*x, *y;
{
  register float	det = a0 * b1 - a1 * b0;

  if (FABS(det) < M_EPSILON) return (FALSE);
  *x = (b1 * c0 - b0 * c1) / det;
  *y = (a0 * c1 - a1 * c0) / det;
  return (TRUE);
}

/*
 * La procedure "newton_3" cherche une racine d'un polynome du 3eme degre en X.
 *	a x^3 + b x^2 + c x + d = 0
 * Pour plus de renseignement, voir :
 * INITIATION A L'ANALYSE NUMERIQUE, R. Theodor, CNAM cours A,
 * 1986, MASSON, pp 16-17.
 * Entree :
 * x		Un germe proche de la racine cherchee.
 * a, b, c, d	Coefficients du polynome.
 * Sortie :
 *		La racine si elle a ete trouvee.
 *		Le germe sinon.
 */
static	double
newton_3 (x, a, b, c, d)
double	x;
double	a, b, c, d;
{
#define	N_ITER	32

  static	char	proc_name[] = "newton_3";

  double	x0 = x;		/* element de la suite		*/
  double	aprim = 3.0 * a, bprim = 2.0 * b, cprim = c;
  double	f, fprim;	/* la fonction et sa derivee	*/
  int	i;		/* iteration courante		*/

  for (i = 0; i < N_ITER; i++) {
    if (fabs (f = M_POLY3(x0,a,b,c,d)) < M_EPSILON)
      return (x0);
    if (fabs (fprim = M_POLY2(x0,aprim,bprim,cprim)) < M_EPSILON) {
      fprintf (stderr, "%s: nul derived function\n",
        proc_name);
      return (x);
    }
    x0 -= f / fprim;	/* Un+1 = Un - f(Un) / f'(Un)	*/
  }
  fprintf (stderr, "%s: no convergence\n", proc_name);
  return (x);
}

/*
 * La procedure "norme_CSSP" normalise une matrice de covariance.
 * Seule la matrice 3x3 est normalisee, la derniere ligne n'est pas affectee.
 * Entree/Sortie :
 * m		Matrice a normer.
 */
norme_CSSP (m)
register Matrice	m;
{
  register int	i, j;
  register float	max = 0.0;

  for (i = 0; i < 3; i++)
  for (j = 0; j < 3; j++)
    if (max < m[i][j]) max = m[i][j];

  if (max > M_EPSILON)
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      m[i][j] /= max;
}

/*
 * La procedure "eigen_vector" calcule un vecteur propre norme associe
 * a une matrice une valeur propre.
 * Soient m la matrice de covariance, l la valeur propre,
 * un vecteur propre [x y z] verifie le systeme lineaire 3x3 suivant :
 * 	(m[0][0]-l) x +  m[0][1]    y + m[0][2] z     = 0
 * 	 m[1][0]    x + (m[1][1]-l) y + m[1][2] z     = 0
 * 	 m[2][0]    x +  m[2][1]    y + (m[2][2]-l) z = 0
 * Remarque :
 * Le determinant de ce systeme est nul par definition de la valeur propre.
 * Il existe donc une infinite de solutions.
 *
 * Entree :
 * m		Matrice.
 * l		Valeur propre.
 * Entree/Sortie :
 * vp		Vecteur propre.
 */
static
void eigen_vector (m, l, vp)
register Matrice	m;
register float	l;
register Vecteur	*vp;
{
  static	char	proc_name[] = "eigen_vector";

  float	a = m[0][0], b = m[1][1], c = m[2][2];
  float	d = m[2][1], e = m[2][0], f = m[1][0];

  a -= l;
  b -= l;
  c -= l;

  vp->x = 1.0;
  if (lin_22 (f, e, -a, b, d, -f, &vp->y, &vp->z)) return;
  if (lin_22 (f, e, -a, d, c, -e, &vp->y, &vp->z)) return;
  if (lin_22 (b, d, -f, d, c, -e, &vp->y, &vp->z)) return;

  vp->y = 1.0;
  if (lin_22 (a, e, -f, f, d, -b, &vp->x, &vp->z)) return;
  if (lin_22 (a, e, -f, e, c, -d, &vp->x, &vp->z)) return;
  if (lin_22 (f, d, -b, e, c, -d, &vp->x, &vp->z)) return;

  vp->z = 1.0;
  if (lin_22 (a, f, -e, f, b, -d, &vp->x, &vp->y)) return;
  if (lin_22 (a, f, -e, e, d, -c, &vp->x, &vp->y)) return;
  if (lin_22 (f, b, -d, e, d, -c, &vp->x, &vp->y)) return;

  fprintf (stderr, "%s: nul vector\n", proc_name);
}

/*
 * La procedure "make_CSSP_inertia" constuit a partir de la matrice de
 * covariance une matrice de rotation pour passer dans le repere
 * des axes principaux d'inertie (composantes principales).
 * Entree :
 * cssp		Matrice de covariance.
 * Entree/Sortie :
 * m		Matrice de rotation.
 */
make_CSSP_inertia (cssp, m)
register Matrice	cssp, m;
{
#define	M_EIGEN		M_EPSILON

  double		a = (double) cssp[0][0];
  double		b = (double) cssp[1][1];
  double		c = (double) cssp[2][2];
  double		d = (double) cssp[2][1];
  double		e = (double) cssp[2][0];
  double		f = (double) cssp[1][0];
  double		l0, l1, l2, l;
  Vecteur		v0, v1, v2;

  if (fabs(d) < M_EPSILON && fabs(e) < M_EPSILON && fabs(f) < M_EPSILON) {
    /* matrice diagonale	*/
    l0 = a;
    l1 = b;
    l2 = c;
  }
  else {	/* resolution de l'equation caracteristique	*/
    double	a2 = a + b + c,
      a1 = d*d + e*e + f*f - a*b - a*c - b*c,
      a0 = a*b*c - a*d*d - b*e*e - c*f*f + 2.0*d*e*f;

    equa_3 (-1.0, a2, a1, a0, &l0, &l1, &l2);

    /* trie des valeurs propres l0 >= l1 >= l2	*/
    if (l0 < l1) SWAP(l0,l1,l);
    if (l1 < l2) SWAP(l1,l2,l);
    if (l0 < l1) SWAP(l0,l1,l);

    /* recherche plus precise des racines	*/
    l0 = newton_3 (l0, -1.0, a2, a1, a0);
    l2 = newton_3 (l2, -1.0, a2, a1, a0);
    /* l0 + l1 + l2 = Trace(CSSP)		*/
    l1 = a + b + c - l0 - l2;
  }

  /* trie des valeurs propres l0 >= l1 >= l2	*/
  if (l0 < l1) SWAP(l0,l1,l);
  if (l1 < l2) SWAP(l1,l2,l);
  if (l0 < l1) SWAP(l0,l1,l);

  if (fabs (l0 - l1) < M_EIGEN)
    if (fabs (l1 - l2) < M_EIGEN) {	/* l0 == l1 == l2	*/
      SET_COORD3(v0, 1.0, 0.0, 0.0);
      SET_COORD3(v1, 0.0, 1.0, 0.0);
      SET_COORD3(v2, 0.0, 0.0, 1.0);
    }
    else { 				/* l0 == l1 != l2	*/
      eigen_vector (cssp, (float) l2, &v2);
      norm_vector (&v2);
      upright_vector (&v2, &v0);
      norm_vector (&v0);
      CROSS_PRODUCT (v1, v2, v0);
      norm_vector (&v1);
    }
  else	if (fabs (l1 - l2) < M_EIGEN) {	/* l0 != l1 == l2	*/
      eigen_vector (cssp, (float) l0, &v0);
      norm_vector (&v0);
      upright_vector (&v0, &v1);
      norm_vector (&v1);
      CROSS_PRODUCT (v2, v0, v1);
      norm_vector (&v2);
    }
    else {				/* l0 != l1 != l2	*/
      eigen_vector (cssp, (float) l0, &v0);
      norm_vector (&v0);
      eigen_vector (cssp, (float) l1, &v1);
      norm_vector (&v1);
      CROSS_PRODUCT (v2, v0, v1);
      norm_vector (&v2);
      /* pour plus de securite	*/
      CROSS_PRODUCT (v1, v2, v0);
      norm_vector (&v1);
    }
  ident_matrix (m);
  m[0][0] = v0.x; m[0][1] = v1.x; m[0][2] = v2.x;
  m[1][0] = v0.y; m[1][1] = v1.y; m[1][2] = v2.y;
  m[2][0] = v0.z; m[2][1] = v1.z; m[2][2] = v2.z;
}

#ifdef	inertia
/*
 * La procedure "make_Point3f_list_CSSP" construit la matrice d'inertie
 * a partir d'une liste de point 3D.
 *
 *			| A  F  E |
 *	M inertie = 	| F  B  D |
 *			| E  D  C |
 *
 * avec les variables centrees :
 *
 * A = Zi Y^2 + Z^2
 * F = - Zi X Y 	B = Zi X^2 + Z^2
 * E = - Zi X Z 	D = - Zi Y Z	 	C = Zi X^2 + Y^2
 *
 * En posant :
 *
 * a = Zi X^2		b = Zi Y^2		c = Zi Z^2
 * A = b + c		B = a + c		C = a + b
 *
 * Entree :
 * lp		Liste de points 3D.
 * Entree/Sortie :
 * m		Matrice d'inertie.
 */
make_Point3f_list_CSSP (lp, m)
Point3f_list	*lp;
register Matrice	m;
{
  register Point3f	*pp;
  register Point3f	*pend = lp->ptr + lp->nbr;
  register float		cx, cy, cz;
  float			n = (float) lp->nbr;
  float			x = 0.0, y = 0.0, z = 0.0;
  float			a = 0.0, b = 0.0, c = 0.0;
  float			d = 0.0, e = 0.0, f = 0.0;

  /* calcule des moyennes	*/

  for (pp = lp->ptr; pp < pend; pp++) {
    x += pp->x; y += pp->y; z += pp->z;
  }
  x /= n; y /= n; z /= n;

  /* calcule des variances et des covariances	*/

  for (pp = lp->ptr; pp < pend; pp++) {
    cx = pp->x - x; cy = pp->y - y; cz = pp->z - z;
    a += cx * cx  ; b += cy * cy  ; c += cz * cz  ;
    d += cy * cz  ; e += cx * cz  ; f += cx * cy  ;
  }

  /* initialise la matrice d'inertie	*/

  m[0][0] = b + c; m[0][1] = - f  ; m[0][2] = - e  ; m[0][3] = 0.0;
  m[1][0] = - f  ; m[1][1] = a + c; m[1][2] = - d  ; m[1][3] = 0.0;
  m[2][0] = - e  ; m[2][1] = - d  ; m[2][2] = a + b; m[2][3] = 0.0;
  m[3][0] = x    ; m[3][1] = y    ; m[3][2] = z    ; m[3][3] = 1.0;
}
#else
/*
 * La procedure "make_Point3f_list_CSSP" construit la matrice de covariance
 * a partir d'une liste de point 3D.
 *
 *			| varx  covxy covxz |
 *	M covariance =	| covxy vary  covyz |
 *			| covxz covyz varz  |
 *
 * avec les variables centrees :
 *
 * Moyenne	: x     = 1/n Zi xi
 * Variable	: cx    = xi - x
 * Variance	: varx  = covxx =  1/n Zi cx^2
 * Covariance	: covxy = covyx =  1/n Zi cx cy
 *
 * Entree :
 * lp		Liste de points 3D.
 * Entree/Sortie :
 * m		Matrice d'inertie.
 */
make_Point3f_list_CSSP (lp, m)
Point3f_list	*lp;
register Matrice	m;
{
  register Point3f	*pp;
  register Point3f	*pend = lp->ptr + lp->nbr;
  register float		cx, cy, cz;
  float			n = (float) lp->nbr;
  float			x = 0.0, y = 0.0, z = 0.0;
  float			varx = 0.0, vary = 0.0, varz = 0.0;
  float			covx = 0.0, covy = 0.0, covz = 0.0;

  /* calcule des moyennes	*/

  for (pp = lp->ptr; pp < pend; pp++) {
    x += pp->x; y += pp->y; z += pp->z;
  }
  x /= n; y /= n; z /= n;

  /* calcule des variances et des covariances	*/

  for (pp = lp->ptr; pp < pend; pp++) {
    cx = pp->x - x; cy = pp->y - y; cz = pp->z - z;
    varx += cx * cx; vary += cy * cy; vary += cz * cz;
    covx += cy * cz; covy += cx * cz; covz += cx * cy;
  }
  varx /= n; vary /= n; varz /= n;
  covx /= n; covy /= n; covz /= n;

  /* initialise la matrice de covariance	*/

  m[0][0] = varx; m[0][1] = covz; m[0][2] = covy; m[0][3] = 0.0;
  m[1][0] = covz; m[1][1] = vary; m[1][2] = covx; m[1][3] = 0.0;
  m[2][0] = covy; m[2][1] = covx; m[2][2] = varz; m[2][3] = 0.0;
  m[3][0] = x   ; m[3][1] = y    ; m[3][2] = z  ; m[3][3] = 1.0;
}
#endif	inertia

#ifdef	standalone
main ()
{
  Matrice		cssp, m;
  register int	i, j;

  for (i = 0; i < 3; i++)
  for (j = 0; j < 3; j++)
    scanf ("%f", &cssp[i][j]);

  make_CSSP_inertia (cssp, m);
  printf ("Matrice de rotation :\n");
  fprintf_matrix (stdout, m);
}
#endif	standalone

