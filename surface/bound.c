/************************************************************************

 TITLE		: bound.c

 DESCRIPTION	: Le fichier "bound.c" contient les procedures de gestion
		  des scenes de modele geometrique surfacique.

 VERSION	: 1.008

 ABSTRACT	: 

 free_Bound		Libere une surface.
 free_huge_Bound	Libere une surface de taille maximale.
 free_Bound_scene	Libere une scene de surfaces.
 malloc_Bound		Alloue une surface.
 malloc_huge_Bound	Alloue une surface de taille maximale.
 malloc_Bound_scene	Alloue une scene de surfaces.
 malloc_Face_vertex3	Alloue une face a 3 sommets.
 malloc_Face_vertex4	Alloue une face a 4 sommets.

 set_Bound_face_normal	Initialise les normales aux faces d'une surface.
 set_Bound_normal	Initialise les normales aux sommets  d'une surface.

 copy_Bound		copie d'une surface de type Bound.

 init_Bound_scene	initialisation d'une scene de surfaces.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 24/02/87

 MODIFIED BY	:

 1.001 - 24/02/87 Original.
 1.005 - 10/09/88 Ajout de "free_huge_Bound".
 1.006 - 16/12/88 Retrait de "move_..." et creation de "point_...".
 1.007 - 25/01/94 nettoyage option et include (BA)
 1.008 -  1/06/94 ajout de copy_Bound, init_Bound_scene.

*************************************************************************/

#include	<string.h>

#include	<errno.h>
#include	<bound.h>

/*
 * La procedure "free_Bound" libere la memoire d'une surface.
 * Les champs "bound.face.edge" ne sont pas utilises.
 * Entree :
 * bp		Surface a liberer.
 */
free_Bound (bp)
Bound	*bp;
{
	register Face	*fp   = bp->face.ptr;
	register Face	*fend = fp + bp->face.nbr;

	for (; fp < fend; fp++) {	/* libere les polygones	*/
		if (fp->vertex.ptr != fp->vertex.tbl)
			free ((char *) fp->vertex.ptr);
	}
	if (bp->face.ptr != NULL) {	/* libere les faces	*/
		free ((char *) bp->face.ptr);
		bp->face.ptr = NULL;
	}
	if (bp->point.ptr != NULL) {	/* libere les points	*/
		free ((char *) bp->point.ptr);
		bp->point.ptr = NULL;
	}
#ifdef	face_normal
	if (bp->normal.ptr != NULL) {	/* libere les vecteurs	*/
		free ((char *) bp->normal.ptr);
		bp->normal.ptr = NULL;
	}
#endif	face_normal
	bp->is_display = FALSE;
}

/*
 * La procedure "free_huge_Bound" libere  une surface de taille maximale.
 * La particularite de cette surface est le tableau unique des sommets.
 * Entree :
 * bp		Surface a liberer.
 */
free_huge_Bound (bp)
Bound	*bp;
{
	bp->face.nbr = 1;	/* pour la liberation en une fois	*/
	free_Bound (bp);
}

/*
 * La procedure "free_Bound_scene" libere une scene de surfaces.
 * Entree :
 * bsp		Scene a liberer.
 */
free_Bound_scene (bsp)
Bound_scene	*bsp;
{
	register Bound	*bp   = bsp->bound.ptr;
	register Bound	*bend = bp + bsp->bound.nbr;

	for (; bp < bend; bp++) {	/* libere les surfaces	*/
		free_Bound (bp);
	}
	if (bsp->name != NULL) {	/* libere le nom	*/
		free ((char *) bsp->name);
		bsp->name = NULL;
	}
	if (bsp->bound.ptr != NULL) {	/* libere le tableau	*/
		free ((char *) bsp->bound.ptr);
		bsp->bound.ptr = NULL;
	}
}

/*
 * La procedure "malloc_Bound" alloue une surface.
 * Les champs "bound.face.edge" ne sont pas utilises. 
 * Entree :
 * bp		Surface a allouer.
 * type		Type de la surface.
 * polygonal	Booleen indiquant si la surface est polygonale.
 * fn		Nombre de faces  de la surface.
 * pn		Nombre de points de la surface. 
 */
malloc_Bound (bp, type, polygonal, fn, pn)
register Bound	*bp;
Type		type;
int		polygonal;
Index		fn, pn;
{
	static	char	proc_name[] = "malloc_Bound";

	if ((bp->face.nbr = fn) == 0)	/* faces	*/
		bp->face.ptr = NULL;
	 else if ((bp->face.ptr = (Face *) malloc (fn * sizeof (Face)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}

	if ((bp->point.nbr = pn) == 0) 	/* points	*/
		bp->point.ptr = NULL;
	else if ((bp->point.ptr = (Point3f *) malloc (pn * sizeof (Point3f)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}

#ifdef	face_normal
	/* normales aux sommets	*/
	if ((bp->normal.nbr = (bp->is_polygonal ? 0 : pn)) == 0)
		bp->normal.ptr = NULL;
	else if ((bp->normal.ptr = (Vecteur *) malloc (pn * sizeof (Vecteur)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}
#endif	face_normal

	bp->type	 = type;
	bp->is_display	 = TRUE;
	bp->is_polygonal = polygonal;
}

/*
 * La procedure "malloc_huge_Bound" alloue une surface de taille maximale.
 * La surface est adaptee pour la reception de tout type de surface.
 * La surface allouee peut etre utilisee comme une surface de travail.
 * Sa taille est definie par les macros "..._NBR" de "world.h".
 * FACE_NBR	: son nombre de faces
 * POINT_NBR	: son nombre de points
 * VECTOR_NBR	: son monbre de vecteurs
 * VERTEX_NBR	: son nombre de sommets par face.
 * La particularite de la surface vient de l'allocation en une seule fois
 * d'un tableau de sommets. Les polygones des faces ne sont pas initialiser,
 * exepte celui de la premiere face qui est la base du tableau des sommets.
 * Les champs "bound.face.edge" ne sont pas utilises.
 * Entree :
 * bp		Surface maximale a allouer.
 */
malloc_huge_Bound (bp)
Bound	*bp;
{
	static	char	proc_name[] = "malloc_Huge_Bound";

#ifdef	face_normal
	malloc_Bound (bp, (Type) BND_NULL, FALSE, FACE_NBR, POINT_NBR);
#else
	malloc_Bound (bp, (Type) BND_NULL, TRUE, FACE_NBR, POINT_NBR);
#endif	face_normal
	if ((bp->face.ptr->vertex.ptr = 
	   (Index *) malloc (FACE_NBR * VERTEX_NBR * sizeof (Index))) == NULL) {
		perror (proc_name);
		exit (1);
	}
}


/****************************************************************************
 * La procedure "copy_Bound" permet de recopier une surface de type Bound
 * en reduisant eventuellement la taille si la surface source a ete creee
 * par malloc_huge_Bound.
 * Entree:	bpin:	surface source
 *		bpout:	surface destination
 ****************************************************************************/

void	copy_Bound (Bound *bpin, Bound *bpout)

{
	Index	pn = bpin->point.nbr;	/* nb de points */
	Index	fn = bpin->face.nbr;	/* nb de faces */
	Point3f	*ppin = bpin->point.ptr, *ppinend, *ppout;
	Face	*fpin = bpin->face.ptr, *fpinend, *fpout;
	Index	*vpin, *vpout, *vpoutend;

	malloc_Bound (bpout, bpin->type, bpin->is_polygonal, fn, pn);

	/* recopie des points */
	ppinend = ppin + pn;
	ppout = bpout->point.ptr;
	while (ppin < ppinend) {
		*ppout = *ppin;
		ppin++;
		ppout++;
	}

	/* recopie des faces */
	vpout = (Index *) malloc (VERTEX_NBR * fn * sizeof(Index));
	fpinend = fpin + fn;
	fpout = bpout->face.ptr;
	while (fpin < fpinend) {
		*fpout = *fpin;
		fpout->vertex.ptr = vpout;
		vpin = fpin->vertex.ptr;
		vpoutend = vpout + (fpin->vertex.nbr);
		while (vpout < vpoutend) {
			*vpout = *vpin;
			vpout++;
			vpin++;
		}
		fpin++;
		fpout++;
	}
}

	
/*
 * La procedure "malloc_Bound_scene" alloue une scene de surfaces.
 * Stocke le nom de la scene et alloue l'espace memoire necessaire. 
 * Les champs "bound.face.edge" ne sont pas utilises.
 * Entree :
 * bsp		Scene a allouer.
 * name		Nom de la scene.
 * bn		Nombre de surfaces de la scene.
 */
malloc_Bound_scene (bsp, name, bn)
Bound_scene	*bsp;
char		*name;
Index		bn;
{
	static	char	proc_name[] = "malloc_Bound_scene";

	if ((bsp->name = (char *) malloc ((strlen (name) + 1) * sizeof (char)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}
	if ((bsp->bound.nbr = bn) == 0)
		bsp->bound.ptr = NULL;
	else if ((bsp->bound.ptr = (Bound *) malloc (bn * sizeof (Bound)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}
	strcpy (bsp->name, name);
	bsp->bound.nbr = 0;
}

/**************************************************************************
 * La procedure "init_Bound_scene" initialise une scene de surface.
 * Cette scene pourra accueillir BOUND_NBR surfaces.
 * Entree/Sortie:	bsp:	scene a initialiser
 * Entree:		name:	nom de la scene.
 **************************************************************************/

void	init_Bound_scene (Bound_scene *bsp, char *name)
{
	malloc_Bound_scene (bsp, name, BOUND_NBR);
}

/**************************************************************************
 * La procedure "malloc_Face_vertex3" initiale une face a 3 sommets.
 * Le champ "face.edge" n'est pas utilise.
 * Entree :
 * fp		Face a initialiser.
 * polygonal	Booleen indiquant si la face est une approximation polygonale.
 * i0, i1, i2	Indices des points aux sommets.
 */
malloc_Face_vertex3 (fp, polygonal, i0, i1, i2)
Face	*fp;
int	polygonal;
Index	i0, i1, i2;
{
	static	 char	proc_name[] = "malloc_Face_vertex3";
	register Index	*vp;	/* sommet courant	*/

	if (3  <= DEFAULT_VSIZE)
		fp->vertex.ptr = fp->vertex.tbl;
	else if ((fp->vertex.ptr = (Index *) malloc (3 * sizeof (Index)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}

	fp->vertex.nbr	 = 3;	/* nombre de sommets	*/
	fp->is_visible   = TRUE; 
	fp->is_polygonal = polygonal;
	vp = fp->vertex.ptr;
	*vp++ = i0;
	*vp++ = i1;
	*vp   = i2;
}

/*
 * La procedure "malloc_Face_vertex4" initialise une face a 4 sommets.
 * Le champ "face.edge" n'est pas utilise.
 * Entree :
 * fp		Face a initialiser.
 * polygonal	Booleen indiquant si la face est une approximation polygonale.
 * i0,i1,i2,i3	Indices des points aux sommets.
 */
malloc_Face_vertex4 (fp, polygonal, i0, i1, i2, i3)
Face	*fp;
int	polygonal;
Index	i0, i1, i2, i3;
{
	static	 char	proc_name[] = "malloc_Face_vertex4";
	register Index	*vp;	/* sommet courant	*/

	if (4  <= DEFAULT_VSIZE)
		fp->vertex.ptr = fp->vertex.tbl;
	else if ((fp->vertex.ptr = (Index *) malloc (4 * sizeof (Index)))
		== NULL) {
		perror (proc_name);
		exit (1);
	}

	fp->vertex.nbr	 = 4;	/* nombre de sommets	*/
	fp->is_visible	 = TRUE;
	fp->is_polygonal = polygonal;
	vp = fp->vertex.ptr;
	*vp++ = i0;
	*vp++ = i1;
	*vp++ = i2;
	*vp   = i3;
}

#ifdef	face_normal
/*
 * La procedure "set_Bound_face_normal" initialise les normales des faces
 * de la surface "bp".
 * Algorithme de Martin Newell :
 * Soit le polygone :
 *	- de n sommets "i" : 1 <= i <= n.
 *	- appartenant au plan definie par : a * x + b * y + c * z + d = 0
 * Avec j = 1 si i = n, i + 1 sinon, on a :
 *	a = Z (yi - yj)(zi + zj)
 *	b = Z (zi - zj)(xi + xj)
 *	c = Z (xi - xj)(yi + yj)
 * Entree :
 * bp		Surface a initialiser.
 */
set_Bound_face_normal (bp)
Bound	*bp;
{
	Face		*fp   = bp->face.ptr;
	Face		*fend = fp + bp->face.nbr;
	Point3f		*pp   = bp->point.ptr;

	for (; fp < fend; fp++) {
		register Index		*vp   = fp->vertex.ptr;
		register Index		*vend = vp + fp->vertex.nbr;
		register Point3f 	*pi   = pp + *(vend - 1);
		register float		x = 0.0;
		register float		y = 0.0;
		register float		z = 0.0;
		register float		denom;

		for (; vp < vend; vp++) {
			register Point3f	*pj = pp + *vp;

			x += (pi->y - pj->y) * (pi->z + pj->z);
			y += (pi->z - pj->z) * (pi->x + pj->x);
			z += (pi->x - pj->x) * (pi->y + pj->y);
			pi = pj;
		}
		if (denom = (float) sqrt ((double) (x * x + y * y + z * z))) {
			SET_COORD3 (fp->normal,x/denom,y/denom,z/denom);
		}
		else {
			SET_COORD3 (fp->normal,x,y,z);
		}
	}
}
#endif	face_normal

#ifdef	face_normal
/*
 * La procedure "set_Bound_normal" initialise les normales aux sommets
 * de la surface "bp".
 * Deux cas se presentent :
 * La surface "bp" est polygonale.
 *	La normale a un sommet est egale a la normale a la face
 *	contenant le sommet.
 *	Les normales aux sommets sont deja connues et ne sont pas recalculees.
 * La surface "bp" n'est pas polygonale.
 *	La normale a un sommet est egale a la moyenne des normales des faces
 *	non polygonale partageant le sommet.
 * Entree :
 * bp		Surface a initialiser.
 */
set_Bound_normal (bp)
Bound	*bp;
{
	register Face	*fp   = bp->face.ptr;
	register Face	*fend = fp + bp->face.nbr;
	register Vecteur	*np, *nend;

	if (bp->is_polygonal) return;	/* surface polygonale	*/

	np   = bp->normal.ptr;	/* initialise les normales	*/
	nend = np + bp->normal.nbr;
	for (; np < nend; np++) {
		np->x = np->y = np->z = 0.0;	/* vecteur nul	*/
	}

	/* cumule les normales des faces partageant le sommet	*/

	for (; fp < fend; fp++) {
		register Index	*vp, *vend;
		register float	x, y, z;

		if (fp->is_polygonal) continue;	/* face polygonale	*/
		vp   = fp->vertex.ptr;		/* sommet courant	*/
		vend = vp + fp->vertex.nbr;	/* borne du polygone	*/
		x = fp->normal.x;		/* coordonnees normale	*/
		y = fp->normal.y;
		z = fp->normal.z;
		for (; vp < vend; vp++) {	/* parcourt les sommets	*/
			np = bp->normal.ptr + *vp;
			np->x += x;		/* cumule la normale	*/
			np->y += y;
			np->z += z;
		}
	}

	np   = bp->normal.ptr;	/* normalise les normales	*/
	nend = np + bp->normal.nbr;
	for (; np < nend; np++) {
		register float	denom = (float)
		sqrt ((double) (np->x * np->x + np->y * np->y + np->z * np->z));

		if (denom > M_EPSILON) {
			np->x /= denom; np->y /= denom; np->z /= denom;
		}
	}
}
#endif	face_normal

