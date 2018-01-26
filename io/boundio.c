/************************************************************************

 TITLE		: boundio.c

 DESCRIPTION	: Le module "boundio.c" contient les procedures d'entree/sortie
		  des types definis dans le module "bound.h".
		  Le format utilise appatient au langage PISYN.
		  Pour plus de renseignement, voir pisyn(1), bound(1).

 fprintf_...		Ecrit en ascii   une variable de type "...".
 write_...		Ecrit en binaire une variable de type "...".

 VERSION	: 1-004

 ABSTRACT	: 

 fprintf_Bound		Ecrit en ascii   une surface.
 fprintf_Face_list	Ecrit en ascii   une liste de faces.
 fprintf_Point_list	Ecrit en ascii   une liste de points.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 11/04/88

 MODIFIED BY	:

 1-001 - 11/04/88 Original.
 1-002 - 13/04/88 Ajout des procedures "write_...".
 1-003 - 08/10/88 Ajout de "poperr", "pusherr".
 1-004 - 01/04/89 Suppression de "fscanf_...", "push...", "pop...".
 1.005 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include "my.h"
#include "arit.h"
#include "bound.h"

/*
 * La procedure "fprintf_Bound" ecrit en ascii une surface polyedrique.
 * Entree :
 * f		Fichier en sortie.
 * bp		Surface a ecrire.
 */
fprintf_Bound (f, bp)
register FILE	*f;
register Bound	*bp;
{
	fprintf (f, "\n$ bound\ntype\t%d\n", (bp->is_polygonal) ? 1 : 0);
	fprintf_Point_list (f, &bp->point);
	fprintf_Face_list (f, &bp->face);
	fprintf (f, "\n");
}

/*
 * La procedure "fprintf_Face_list" ecrit en ascii une liste de faces.
 * Entree :
 * f		Fichier en sortie.
 * lp		Liste de faces a ecrire.
 */
fprintf_Face_list (f, lp)
register FILE	*f;
Face_list	*lp;
{
	int		b;	/* booleen		*/
	register Face	*fp;	/* face courante	*/
	register Face	*fend;	/* borne de "fp"	*/
	register Index	*vp;	/* sommet courant	*/
	register Index	*vend;	/* borne de "vp"	*/
	register int	i = 0;	/* numero de la face	*/

	fprintf (f, "face_list\t%d\n", lp->nbr);
	fp   = lp->ptr;		/* ecrit les faces une par une	*/
	fend = fp + lp->nbr;
	for (; fp < fend; fp++, i++) {
		if (i % 20 == 0) fprintf (f, "/* face %d\t*/\n", i);
		b  = fp->is_polygonal ? 1 : 0;
		vp = fp->vertex.ptr;
		switch (fp->vertex.nbr) {
		case 3	:
			fprintf (f, "%d 3\t%d\t%d\t%d\n",
				 b, *vp, *(vp+1), *(vp+2));
			break;
		case 4	:
			fprintf (f, "%d 4\t%d\t%d\t%d\t%d\n",
			 	b, *vp, *(vp+1), *(vp+2), *(vp+3));
			break;
		default :
			vend = vp + fp->vertex.nbr;
			fprintf (f,"%d %d", b, fp->vertex.nbr);
			for (; vp < vend; fprintf (f, "\t%d", *vp++));
			fprintf (f, "\n");
			break;
		}
	}
}

/*
 * La procedure "fprintf_Point_list" ecrit en ascii une liste de points.
 * Entree :
 * f		Fichier en sortie.
 * lp		Liste de points a ecrire.
 */
fprintf_Point_list (f, lp)
register FILE		*f;
register Point3f_list	*lp;
{
	register Point3f	*pp;	/* point courant	*/
	register Point3f	*pend;	/* borne de "pp"	*/
	register int		i = 0;	/* numero du point	*/

	fprintf (f, "point_list\t%d\n", lp->nbr);
	pp   = lp->ptr;		/* ecrit les points un par un	*/
	pend = pp + lp->nbr;
	for (; pp < pend; pp++, i++) {
		if (i % 20 == 0) fprintf (f, "/* point %d\t*/\n", i);
		fprintf (f, "%.3f\t%.3f\t%.3f\n", pp->x, pp->y, pp->z);
	}
}	

