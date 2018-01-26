/************************************************************************

 TITLE		: compress.c

 DESCRIPTION	: Le module "compress.c" contient les procedures de compression
		  de surfaces de modele geometrique surfacique polygonale.

 VERSION	: 1.002

 ABSTRACT	: 

 check_Face		Verifie		une face et genere une face valide.
 compress_huge_Face	Concatene	un tableau de faces.
 compress_Point3f	Concatene 	un tableau de points 3D.
 copy_Face		Copie		un tableau de faces.
 copy_huge_Face		Copie		un talb;eau de faces de travail.
 mark_Face_point	Marque		les points presents sur une face.
 rename_Face_vertex	Renomme		les sommets d'un tableau de faces.

 ENVIRONMENT	: Compilation	-
			clipinout	Version "clipping" de modelisation.
			gould		Machines GOULD.
			sun		Machines SUN 3.
			sun4		Machines SUN 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 18/09/89

 MODIFIED BY	:

 1.001 - 18/09/89 Original.
 1.002 - 28/10/89 Ajout de "..._huge_...".
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/

#include <string.h>

#include <bound.h>

static	int	check_Face ();
static	int	copy_Face ();


/*
 * La procedure "check_Face" verifie une face et genere une face valide.
 * La verification porte sur les cas suivants :
 *	- une face de moins de 3 sommmets n'est pas valide.
 * 	- deux sommets consecutifs identiques (... v v ...)
 *	- deux aretes consecutives formant une boucle (... v0 v1 v0 ...)
 * La procedure recopie les sommets valides dans la face resultat.
 * Entree :
 * from		Face a verifier.
 * Entree/Sortie :
 * to		Face valide.
 * Sortie :
 *		Nombre de sommet de la face apres verification.
 */
static	int
check_Face (from, to)
register Face	*from, *to;
{
	register Index	*v2   = from->vertex.ptr;
	register Index	*vend = v2 + from->vertex.nbr;
	register Index	*v1   = vend - 1;
	register Index	*v0   = vend - 2;

	to->vertex.nbr   = from->vertex.nbr;
	to->is_visible   = from->is_visible; 
	to->is_polygonal = from->is_polygonal;

	switch (from->vertex.nbr) {
	case 0	: break;
	case 1	: to->vertex.ptr[0] = *v2;
		  break;
	case 2	: to->vertex.ptr[0] = *v2;
		  to->vertex.ptr[1] = *v1;
		  if (*v1 == *v2)
			to->vertex.nbr--;
		  break;
	default	: to->vertex.nbr = 0;
		  for (; v2 < vend; v0 = v1, v1 = v2++) {
			if (*v1 != *v2) {
				to->vertex.ptr[to->vertex.nbr++] = *v2;
				if (*v0 == *v2)
					to->vertex.nbr--;
			}
		  }
		  break;
	}
	return ((int) to->vertex.nbr);
}

/*
 * La procedure "compress_huge_Face" concatene un tableau de faces issues
 * d'une surface de travail allouee par "malloc_Huge_Bound".
 * La concatenation s'effectue par recopie dess faces valides dans le tableau
 * de faces en sortie.
 * Entree :
 * from		Tableau de faces en entree.
 * size		Taille du tableau de faces en entree.
 * Entree/Sortie :
 * to		Tableau de faces apres compression.
 * Sortie :
 *		Nombre de faces du tableau apres compression.
 */
compress_huge_Face (from, size, to)
register Face	*from;
int		size;
register Face	*to;
{
	register Face	*fend   = from + size;
	Face		*tobase = to;

	for (; from < fend; from++) {
		if (check_Face (from, to) > 2) {
			(to+1)->vertex.ptr = to->vertex.ptr + to->vertex.nbr;
			to++;
		}
	}
	return (to - tobase);
}

/*
 * La procedure "compress_Point3f" concatene un tableau de points en recopiant
 * uniquement les points valides dans le tableau en sortie.
 * Un point est non valide si sa marque correspondante (de meme indice) est
 * nulle, un point est valide dans le cas contraire.
 * Apres concatenation, le tableau des marques contient les nouveaux indices
 * des points dans le tableau en sortie.
 * Entree :
 * from		Tableau de points 3D a concatener.
 * size		Taille du tableau de points 3D.
 * Entree/Sortie :
 * ip		Tableau des marques de validation des points.
 *		Tableau des nouveaux indices des points.
 * to		Tableau de points 3D apres concatenation
 * Sortie :
 *		Taille du tableau de points 3D apres concatenation.
 */
compress_Point3f (from, size, ip, to)
register Point3f	*from;
int			size;
register int		*ip;
register Point3f	*to;
{
	register Point3f	*fend   = from + size;
	register Point3f	*tobase = to;	/* base du tableau	*/

	for (; from < fend; from++, ip++) {
		if (*ip == 0)
			continue;	/* point non valide	*/
		*ip   = to - tobase;	/* reindicage du point	*/
		*to++ = *from;		/* recopie    du point	*/
	} 
	return (to - tobase);		/* nombre de points	*/
}

/*
 * La procedure "copy_Face" copie "size" faces du tableau de faces "from"
 * dans le tableau de faces "to".
 * Entree :
 * from		Tableau de faces a recopier.
 * to		Tableau de faces resultat.
 * size		Nombre de faces a recopier.
 * Sortie :
 *		Nombre de faces recopier de "from" dans "to".
 */
static	int
copy_Face (from, to, size)
register Face	*from, *to;
int		size;
{
	static	char	proc_name[] = "copy_Face";

	register Face	*fend   = from + size;	/* borne de from	*/
	Face		*tobase = to;

	for (; from < fend; from++, to++) {
		to->vertex.nbr   = from->vertex.nbr;
		to->is_visible   = from->is_visible; 
		to->is_polygonal = from->is_polygonal;

		if (to->vertex.ptr != to->vertex.tbl && to->vertex.ptr != NULL)
			free ((char *) to->vertex.ptr);
		if (to->vertex.nbr  <= DEFAULT_VSIZE)
			to->vertex.ptr = to->vertex.tbl;
		else if ((to->vertex.ptr = (Index *) malloc (to->vertex.nbr *
			sizeof (Index))) == NULL) {
			perror (proc_name);
			return (to - tobase);
		}
		bcopy ((char *) from->vertex.ptr, (char *) to->vertex.ptr,
			(int) to->vertex.nbr * sizeof (Index));
	}
	return (to - tobase);
}

/*
 * La procedure "copy_huge_Face" copie "size" faces du tableau de faces "from"
 * dans le tableau de faces de travail "to" alloue par "malloc_huge_Bound".
 * Entree :
 * from		Tableau de faces a recopier.
 * to		Tableau de faces de travail resultat.
 * size		Nombre de faces a recopier.
 * Sortie :
 *		Nombre de faces recopier de "from" dans "to".
 */
copy_huge_Face (from, to, size)
register Face	*from, *to;
int		size;
{
	register Face	*fend   = from + size;	/* borne de from	*/
	Face		*tobase = to;

	for (; from < fend; from++, to++) {
		to->vertex.nbr   = from->vertex.nbr;
		to->is_visible   = from->is_visible; 
		to->is_polygonal = from->is_polygonal;

		bcopy ((char *) from->vertex.ptr, (char *) to->vertex.ptr,
			(int) from->vertex.nbr * sizeof (Index));
		(to+1)->vertex.ptr = to->vertex.ptr + to->vertex.nbr;
	}
	return (to - tobase);
}

/*
 * La procedure "mark_Face_point" marque les points appartenant aux faces.
 * Un point appartient a une face si son indice correspond a un sommet
 * de la face. Un compteur de meme indice est associe a chaque point.
 * Un compteur positif indique le nombre de faces auquelles appartient le point.
 * Un compteur nul indique que le point correspondant (de meme indice)
 * n'appartient a aucune face.
 * Entree :
 * fp		Tableau des faces.
 * fsize	Taille du tableau des faces.
 * cp		Tableau des compteurs.
 * csize	Taille du tableau des compteurs.
 */
mark_Face_point (fp, fsize, cp, csize)
register Face	*fp;
int		fsize;
register int	*cp;
int		csize;
{
	register Face	*fend = fp + fsize;
	register int	*ip, *iend;

	ip   = cp;	/* initialise le tableau des compteurs	*/
	iend = ip + csize;
	for (; ip < iend; *ip++ = 0);

	/*
	 * Incremente les compteurs des points appartenant aux faces.
	 */
	for (; fp < fend; fp++) {
		register Index	*vp   = fp->vertex.ptr;
		register Index	*vend = vp + fp->vertex.nbr;

		for (; vp < vend; cp[*vp++]++);
	}
}

/*
 * La procedure "rename_Face_vertex" renomme les sommets des faces.
 * Un sommet est l'indice du point correspondant dans un tableau de points 3D.
 * Entree :
 * fp		Tableau de faces dont les sommets sont a reindicer.
 * size		Taille du tableau de faces.
 * ip		Tableau de reindicage des sommets.
 */
rename_Face_vertex (fp, size, ip)
register Face	*fp;
int		size;
register int	*ip;
{
	register Face	*fend   = fp + size;	/* borne de fp	*/

	for (; fp < fend; fp++) {
		register Index	*vp    = fp->vertex.ptr;
		register Index	*vend  = vp + fp->vertex.nbr;

		for (; vp < vend; vp++)
			*vp = (Index) ip[*vp];	/*  renommage 	*/
	}
}

