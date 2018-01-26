/************************************************************************

 TITLE		: oper.c

 DESCRIPTION	: Le fichier "bound.c" contient les procedures d'operations
		  geometriques sur les objets de modele geometrique surfacique.
		  Les operations sont effectuees dans leur ordre
		  d'apparition.

 VERSION	: 1.001

 ABSTRACT	: 
		 init_Transfo:	initialise une transformation.
		 add_Transfo:	ajout d'une transformation.

		 move_Bound:	application d'une transfo a une surface.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Thierry Bouedo		CREATION DATE	: 02/06/94

 MODIFIED BY	:

 1.001 - 02/06/94 Original.

*************************************************************************/

#include	<string.h>

#include	<bound.h>

/*------------------------------------------------------------------------
 *	Initialisation d'une transformation
 *
 * Entree/Sortie:	transfo: matrice de transformation a initialiser.
--------------------------------------------------------------------------*/

void	init_Transfo (Transfo transfo)
{
	Matrice	m = IDENTITY_MATRIX;

	bcopy ((char *) m, (char *) transfo, sizeof (Matrice));
}

/*------------------------------------------------------------------------
 *	Ajout d'une transformation
 *
 * Entree:		x, y, z: coordonnees du vecteur de la transformation.
 *			type:	rotate, scale ou translate.
 * Entree/Sortie:	transfo: matrice de transformation a premultiplier.
--------------------------------------------------------------------------*/

void	add_Transfo (Transfo transfo, char *type, float x, float y, float z)
{
	Matrice		m;
	Vecteur		vp;
	static	char	proc_name[] = "add_Transfo";

	SET_COORD3 (vp, x, y, z);

	if (strcmp (type, "rotate") == 0) { /* cas de la rotation */
		Rotate_to_Matrice (&vp, m);
		premult3_matrix (transfo, m);
	}
	else if (strcmp (type, "scale") == 0)  /* cas de l'homothetie */
		prescale_matrix (transfo, &vp);

	else if (strcmp (type, "translate") == 0)  /* cas de la translation */
		pretrans_matrix (transfo, &vp);

	else
		fprintf (stderr, "%s: Transfo's type error\n", proc_name);
}



/*-------------------------------------------------------------------------
 *	Application d'une transformation a une surface
 *
 * Entree:		transfo:	transfo a appliquer
 * Entree/Sortie:	bp:	surface a transformer.
 *------------------------------------------------------------------------*/

void	move_Bound (Bound *bp, Transfo transfo)
{
	register Point3f	*pp   = bp->point.ptr;
	register Point3f	*pend = pp + bp->point.nbr;
	register float		x, y, z, w;

	for (; pp < pend; pp++) {
		x = pp->x;
		y = pp->y;
		z = pp->z;

		w = COORD3_COL(x,y,z,transfo,3);
		if (w >= 0.0) {
			if (w <   M_EPSILON) w =   M_EPSILON;
		}
		else {
			if (w > - M_EPSILON) w = - M_EPSILON;
		}
		pp->x = COORD3_COL(x,y,z,transfo,0) / w;
		pp->y = COORD3_COL(x,y,z,transfo,1) / w;
		pp->z = COORD3_COL(x,y,z,transfo,2) / w;
	}
}	
