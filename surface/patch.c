/************************************************************************

 TITLE		: patch.c

 DESCRIPTION	: Le module "patch.c" contient les procedures de gestion
		  des morceaux de surfaces bicubiques de type spline.

 Pour plus de renseignements voir : "Parametric Curves, Surfaces and
 Volumes in Computer Graphics and Computer-Aided Geometric Design",
 James H. Clark, Technical Report No. 221. STANFORD UNIVERSITY.
 November 1981.

 Note : Les notations employees sont celles utilisees par J. H. Clark.

 VERSION	: 1.002

 ABSTRACT	: 

 compute_M_matrix	Calcule les matrices d'interpolation.
 compute_S_matrix	Calcule les matrices d'interpolation.
 set_ForwardDiff_matrix	Initialise une matrice par les differences finies.

 free_Patch		Alloue un morceau de surface.
 malloc_Patch		Libere un morceau de surface.

 make_Bezier_Bound	Construit une surface a partir d'un patch Bezier.
 make_Bspline_Bound	Construit une surface a partir d'un patch Bspline.
 make_Cardinal_Bound	Construit une surface a partir d'un patch Cardinal.
 make_Patch_Bound	Construit la surface d'un morceau de surface.
 make_Patch_Bound_scene	Construit une scene de surface polyedrique.
 make_Patch_Point	Construit les points d'un morceau de surface.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE : 16/03/88

 MODIFIED BY	:

 1.001 - 16/03/88 Original.
 1.002 - 07/09/88 Ajout de "make_...".
 1.003 - 13/12/89 Ajout de "..._Bezier_..." et de "..._Cardinal_...".
 1.004 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/

#include	<errno.h>

#include <surface.h>

#define	FORWARD_DIFF(p,dp,ddp,dddp)	p	+= dp;\
					dp	+= ddp;\
					ddp	+= dddp

#define	SET_DIFF(m,p,dp,ddp,dddp)	p	= m[0][0];\
					dp	= m[1][0];\
					ddp	= m[2][0];\
					dddp	= m[3][0]

#define	M_IJ(m,s,i,j)	((m)+((s)*(i))+(j))	/* &m[i][j]	*/


/*
 * S	= E(t) M G Mt Et(u)
 * MAT	= E(t) M
 * TMAT	= (E(u) M)t = Mt Et(u)
 */
static	Matrice	sx, sy, sz;	/* matrices d'interpolation	*/
static	Matrice	mat, tmat;


/*
 * La procedure "set_ForwardDiff_matrix" initialise la matrice par
 * une matrice de differences finies d'ordre 3 pour le nombre d'intervalles.
 * Entree :
 * m		Matrice a initialiser.
 * n		Nombre d'intervalles.
 */
static	void
set_ForwardDiff_matrix (m, n)
register Matrice	m;
Index 		n;
{
	/* echantillonnage	*/
	register float	e  = (n == 0) ? 1.0 : 1.0 / (float) n;
	register float	e2 = e * e;
	register float	e3 = e2 * e;

	m[0][0] = 0.     ; m[0][1] = 0.     ; m[0][2] = 0.; m[0][3] = 1.;
	m[1][0] = e3     ; m[1][1] = e2     ; m[1][2] = e ; m[1][3] = 0.;
	m[2][0] = 6. * e3; m[2][1] = 2. * e2; m[2][2] = 0.; m[2][3] = 0.;
	m[3][0] = 6. * e3; m[3][1] = 0.     ; m[3][2] = 0.; m[3][3] = 0.;
}

/*
 * La procedure "compute_M_matrix" calcule les matrice de type "m...".
 * MAT	= E(t) M
 * TMAT	= (E(u) M)t = Mt Et(u)
 * Entree :
 * m		Matrice de base du morceau de surface.
 * t		Niveau de decomposition sur les lignes.
 * u		Niveau de decomposition sur les colonnes.
 */
static	void
compute_M_matrix (m, t, u)
Matrice	m;
Index	t, u;
{
	set_ForwardDiff_matrix (mat, t);
	postmult_matrix (mat, m);	/* MAT	= E(t) M	*/

	set_ForwardDiff_matrix (tmat, u);
	postmult_matrix (tmat, m);
	transpose_matrix (tmat);	/* TMAT	= (E(u) M) t	*/
}

/*
 * La procedure "compute_S_matrix" calcule les matrices de type "s_".
 * S	= E(t) M G Mt Et(u)
 * MAT	= E(t) M
 * TMAT	= (E(u) M)t = Mt Et(u)
 * Entree :
 * gpp		Point origine dans la matrice des points de controle.
 * col_nbr	Nombre de colonnes de la matrice.
 * row, col	Indice du point origine dans la matrice.
 */
static	void
compute_S_matrix (gpp, col_nbr, row, col)
register Point3f	*gpp;
int			col_nbr;
int			row, col;
{
	register Point3f	*gppij;	/* point courant	*/
	register int		i, j;

	gpp = M_IJ (gpp,col_nbr,row,col);
	for (i = 0; i < 4; i++) {
		gppij = gpp;
		for (j = 0; j < 4; j++) {
			sx[i][j] = gppij->x;	/* S	= G	*/
			sy[i][j] = gppij->y;
			sz[i][j] = gppij->z;
			gppij++;
		}
		gpp += col_nbr;
	}
	premult_matrix (sx, mat); postmult_matrix (sx, tmat);
	premult_matrix (sy, mat); postmult_matrix (sy, tmat);
	premult_matrix (sz, mat); postmult_matrix (sz, tmat);
}

/*
 * La procedure "free_Patch" libere un morceau de surface.
 * Entree :
 * pp		Morceau de surface a liberer.
 */
free_Patch (pp)
Patch	*pp;
{
	if (pp->grid.point.ptr != NULL) {	/* libere les points	*/
		free ((char *) pp->grid.point.ptr);
		pp->grid.point.ptr = NULL;
	}
}

/*
 * La procedure "malloc_Patch" alloue un morceau de surface.
 * Remarque :
 * Les tailles de la grille doivent appartenir a [4,255].
 * Entree :
 * pp		Morceau de surface a allouer.
 * row		Nombre de lignes   de la grille de points de controle.
 * col		Nombre de colonnes de la grille de points de controle.
 * row, col	Tailles de la grille des points de controle de la "pp".
 */
malloc_Patch (pp, row, col)
Patch	*pp;
Index	row, col;
{
	static	 char	proc_name[] = "malloc_Patch";

	register Grid	*gp = &pp->grid;

	if (row < 1 || row > 255) {
		fprintf (stderr, "%s: row under|overflow\n", proc_name);
		exit (1);
	}
	if (col < 1 || col > 255) {
		fprintf (stderr, "%s: col under|overflow\n", proc_name);
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
 * La procedure "make_Patch_Point" construit une grille de points
 * a partir d'un morceau de surface echantillonnee.
 * Entree :
 * pi		Tableau de points en entree.
 * row_nbr	Nombre de lignes   du tableau "pi".
 * col_nbr	Nombre de colonnes du tableau "pi".
 * nsegt	Niveau de decomposition pour les lignes.
 * nsegu	Niveau de decomposition pour les colonnes.
 * po		Tableau de points a construire.
 */
static	void
make_Patch_Point (pi, row_nbr, col_nbr, nsegt, nsegu, po)
register Point3f	*pi;
Index			row_nbr, col_nbr;
Index 			nsegt, nsegu;
register Point3f	*po;
{
	float		px, dpx, ddpx, dddpx;
	float		py, dpy, ddpy, dddpy;
	float		pz, dpz, ddpz, dddpz;
	Point3f		*pp;	/* pp = po[t][u]	*/
	int		col = (col_nbr - 4) * nsegu + nsegu + 1;
	int		i, j;	/* indices de "pi"	*/
	register int	t, u;	/* indices de "po"	*/
	register int	nt, nu;	/* bornes de "u", "t"	*/
	register int	m;

	for (i = 0; i < row_nbr - 3; i++) {
		for (j = 0; j < col_nbr - 3; j++) {
			compute_S_matrix (pi, col_nbr, i, j);
			u  = j * nsegu;
			nu = u + ((j == col_nbr-4) ? nsegu + 1 : nsegu);
			for (; u < nu; u++) {
				SET_DIFF(sx,px,dpx,ddpx,dddpx);
				SET_DIFF(sy,py,dpy,ddpy,dddpy);
				SET_DIFF(sz,pz,dpz,ddpz,dddpz);
				t  = i * nsegt;
		 		nt = t + ((i == row_nbr-4) ? nsegt + 1 : nsegt);
				for (; t < nt; t++) {
					pp = M_IJ (po,col,t,u);	
					SET_COORD3(*pp,px,py,pz);
					FORWARD_DIFF(px,dpx,ddpx,dddpx);
					FORWARD_DIFF(py,dpy,ddpy,dddpy);
					FORWARD_DIFF(pz,dpz,ddpz,dddpz);
				}
			 	for (m = 0; m < 4; m++) {
					FORWARD_DIFF
					(sx[m][0],sx[m][1],sx[m][2],sx[m][3]);	
					FORWARD_DIFF
					(sy[m][0],sy[m][1],sy[m][2],sy[m][3]);	
					FORWARD_DIFF
					(sz[m][0],sz[m][1],sz[m][2],sz[m][3]);					}
			}
		}
	}
}

/*
 * La procedure "make_Bezier_Bound" construit la surface polyedrique
 * d'un morceau de surface Bezier.
 * Le sens de parcours du contour d'une face donne le sens de
 * la normale a la face.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * pp		Morceau de surface en entree.
 * bp		Surface issue de la construction.
 */
make_Bezier_Bound (pp, bp)
Patch	*pp;
Bound	*bp;
{
	static	char	proc_name[] = "make_Bezier_Bound";

	register Grid	*gp = &pp->grid;
	register Index	row = (gp->row_nbr - 4)*pp->row_sub + pp->row_sub + 1;
	register Index	col = (gp->col_nbr - 4)*pp->col_sub + pp->col_sub + 1;

	if (row > 255 || col > 255) {
		fprintf (stderr, "%s: too much points\n", proc_name);
		exit (1);
	}
	compute_M_matrix (bezier_matrix, pp->row_sub, pp->col_sub);
	malloc_Bound (bp, PATCH_BEZIER, pp->is_polygonal,
		(row - 1) * (col - 1), row * col);
	make_Grid_Face (bp->face.ptr, row, col);
	make_Patch_Point (gp->point.ptr, gp->row_nbr, gp->col_nbr, 
			pp->row_sub, pp->col_sub, bp->point.ptr);
}

/*
 * La procedure "make_Bspline_Bound" construit la surface polyedrique
 * d'un morceau de surface Bspline.
 * Le sens de parcours du contour d'une face donne le sens de
 * la normale a la face.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * pp		Morceau de surface en entree.
 * bp		Surface issue de la construction.
 */
make_Bspline_Bound (pp, bp)
Patch	*pp;
Bound	*bp;
{
	static	char	proc_name[] = "make_Bspline_Bound";

	register Grid	*gp = &pp->grid;
	register Index	row = (gp->row_nbr - 4)*pp->row_sub + pp->row_sub + 1;
	register Index	col = (gp->col_nbr - 4)*pp->col_sub + pp->col_sub + 1;

	if (row > 255 || col > 255) {
		fprintf (stderr, "%s: too much points\n", proc_name);
		exit (1);
	}
	compute_M_matrix (bspline_matrix, pp->row_sub, pp->col_sub);
	malloc_Bound (bp, PATCH_BSPLINE, pp->is_polygonal,
		(row - 1) * (col - 1), row * col);
	make_Grid_Face (bp->face.ptr, row, col);
	make_Patch_Point (gp->point.ptr, gp->row_nbr, gp->col_nbr, 
			pp->row_sub, pp->col_sub, bp->point.ptr);
}

/*
 * La procedure "make_Cardinal_Bound" construit la surface polyedrique
 * d'un morceau de surface Cardinal.
 * Le sens de parcours du contour d'une face donne le sens de
 * la normale a la face.
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * pp		Morceau de surface en entree.
 * bp		Surface issue de la construction.
 */
make_Cardinal_Bound (pp, bp)
Patch	*pp;
Bound	*bp;
{
	static	char	proc_name[] = "make_Cardinal_Bound";

	register Grid	*gp = &pp->grid;
	register Index	row = (gp->row_nbr - 4)*pp->row_sub + pp->row_sub + 1;
	register Index	col = (gp->col_nbr - 4)*pp->col_sub + pp->col_sub + 1;

	if (row > 255 || col > 255) {
		fprintf (stderr, "%s: too much points\n", proc_name);
		exit (1);
	}
	compute_M_matrix (cardinal_matrix, pp->row_sub, pp->col_sub);
	malloc_Bound (bp, PATCH_CARDINAL, pp->is_polygonal,
		(row - 1) * (col - 1), row * col);
	make_Grid_Face (bp->face.ptr, row, col);
	make_Patch_Point (gp->point.ptr, gp->row_nbr, gp->col_nbr, 
			pp->row_sub, pp->col_sub, bp->point.ptr);
}

/*
 * La procedure "make_Patch_Bound" construit une surface polyedrique
 * a partir d'un "patch" ou morceau de surface.
 * Entree :
 * pp		Morceau de surface en entree.
 * bp		Surface polyedrique a construire.
 * Sortie :
 *		TRUE si la primitive surfacique "pp" est valide, FALSE sinon.
 */
make_Patch_Bound (pp, bp)
Patch	*pp;
Bound	*bp;
{
	switch (pp->type) {
/*
	case PATCH_GRID	:
		make_Grid_Bound (pp, bp);
		break;
*/
/*
	case PATCH_BEZIER :
		make_Bezier_Bound (pp, bp);
		break;
*/
	case PATCH_BSPLINE :
		make_Bspline_Bound (pp, bp);
		break;
/*
	case PATCH_CARDINAL :
		make_Cardinal_Bound (pp, bp);
		break;
*/
	default	:
		fprintf (stderr, "make_Patch_Bound: patch unknown\n");
		return (FALSE);
	}
	Position_to_Matrice (&pp->position, pp->lsm);
	point_3D_3D (bp->point.ptr,(int) bp->point.nbr, pp->lsm, bp->point.ptr);
#ifdef	face_normal
	set_Bound_face_normal (bp);
#endif	face_normal
	return (TRUE);
}

/*
 * La procedure "make_Patch_Bound_scene" construit une scene de surfaces
 * polyedriques a partir d'une scene de "patches" ou  morceaux de surfaces.
 * Le champ "face.edge" n'est pas utilise.
 * Entree :
 * psp		Scene de morceaux de surfaces en entree.
 * bsp		Scene de surfaces polyedriques a construire.
 */
make_Patch_Bound_scene (psp, bsp)
Patch_scene	*psp;
Bound_scene	*bsp;
{
	register Patch	*pp   = psp->patch.ptr;
	register Patch	*pend = pp + psp->patch.nbr;
	register Bound	*bp;	/* surface courante	*/

	free_Bound_scene (bsp);
	malloc_Bound_scene (bsp,psp->name, psp->patch.nbr);

	bp = bsp->bound.ptr;
	for (; pp < pend; pp++)
		if (make_Patch_Bound (pp, bp)) bp++;
	bsp->bound.nbr = bp - bsp->bound.ptr;
}

