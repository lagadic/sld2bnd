/************************************************************************

 TITLE		: tmstack.c

 DESCRIPTION	: Le module "tmstack.c" contient les procedures de gestion
		  de la pile de matrices de transformation (Transformation
		  Matrice STACK).

 La pile de matrices de transformation comporte STACKSIZE elements.
 Le sommet de pile est la matrice de transformation courante pour les modules
 de synthese d'image 3D.

 VERSION	: 2.002

 ABSTRACT	: 

 get_tmstack		Retourne  le sommet de la pile des matrices.
 load_tmstack		Charge    le sommet de la pile des matrices.
 pop_tmstack		Depile    la pile des matrices de transformation.
 push_tmstack		Empile    la pile des matrices de transformation.
 swap_tmstack		Echange	  les deux premieres matrices de la pile.
 
 postmult_tmstack	Postmultiplie la matrice de transformation courante.
 postrotate_tmstack	Postmultiplie par une rotation    le sommet de la pile.
 postscale_tmstack	Postmultiplie par une homothetie  le sommet de la pile.
 posttranslate_tmstack	Postmultiplie par une translation le sommet de la pile.
 premult_tmstack	Premultiplie la matrice de transformation courante.
 prerotate_tmstack	Premultiplie par une rotation    le sommet de la pile.
 prescale_tmstack	Premultiplie par une homothetie  le sommet de la pile.
 pretranslate_tmstack	Premultiplie par une translation le sommet de la pile.

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 25/07/88

 MODIFIED BY	:

 1.001 - 25/07/88 Original.
 2.001 - 11/04/89 Pile statique.
 2.002 - 19/04/89 Ajout de "post...".

*************************************************************************/

#include <string.h>


#include <arit.h>
#include <tmstack.h>

#define	STACKSIZE	32


static	Matrice	stack[STACKSIZE] = IDENTITY_MATRIX;	/* pile		*/
static	Matrice	*sp		 = stack;		/* sommet 	*/


/*
 * La procedure "get_tmstack" retourne la matrice au sommet
 * de la pile des matrices de transformation.
 * Sortie :
 *		Pointeur de la matrice au sommet de la pile.
 */
Matrice	*
get_tmstack ()
{
	return (sp);
}

/*
 * La procedure "load_tmstack" charge une matrice au sommet
 * de la pile des matrices de transformation.
 * Entree :
 * m		Matrice a charger.
 */
void
load_tmstack (m)
Matrice	m;
{
	bcopy ((char *) m, (char *) *sp, sizeof (Matrice));
}

/*
 * La procedure "pop_tmstack" depile la matrice au sommet
 * de la pile des matrices de transformation.
 */
void
pop_tmstack ()
{
	static	char	proc_name[] = "pop_tmstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_tmstack" empile et duplique le sommet
 * de la pile des matrices de transformation.
 */
void
push_tmstack ()
{
	static	char	proc_name[] = "push_tmstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	bcopy ((char *) (sp - 1), (char *) sp, sizeof (Matrice));
}

/*
 * La procedure "swap_tmstack" echange les deux premieres matrices
 * de la pile des matrices de transformation.
 */
void
swap_tmstack ()
{
	Matrice	*mp, tmp;

	mp = (sp == stack) ? sp + 1 : sp - 1; 
	bcopy ((char *) *sp, (char *) tmp, sizeof (Matrice));
	bcopy ((char *) *mp, (char *) *sp, sizeof (Matrice));
	bcopy ((char *) tmp, (char *) *mp, sizeof (Matrice)); 
}

/*
 * La procedure "postmult_tmstack" postmultiplie la matrice au sommet
 * de la pile des matrices de transformation.
 * Entree :
 * m		Matrice multiplicative.
 */
void
postmult_tmstack (m)
Matrice	m;
{
	postmult_matrix (*sp, m);
}

/*
 * La procedure "postrotate_tmstack" postmultiplie la matrice au sommet
 * de la pile des matrices de transformation par une rotation.
 * Entree :
 * vp		Vecteur de rotation.
 */
void
postrotate_tmstack (vp)
Vecteur *vp;
{
	Matrice	m;

	Rotate_to_Matrice (vp, m);
	postmult3_matrix (*sp, m);
}

/*
 * La procedure "postscale_tmstack" postmultiplie la matrice au sommet
 * de la pile des matrices de transformation par une homothetie.
 * Entree :
 * vp		Vecteur d'homothetie.
 */
void
postscale_tmstack (vp)
Vecteur *vp;
{
	postscale_matrix (*sp, vp);
}

/*
 * La procedure "posttranslate_tmstack" postmultiplie la matrice au sommet
 * de la pile des matrices de transformation par une translation.
 * Entree :
 * vp		Vecteur de translation.
 */
void
posttranslate_tmstack (vp)
Vecteur *vp;
{
	posttrans_matrix (*sp, vp);
}

/*
 * La procedure "premult_tmstack" premultiplie la matrice au sommet
 * de la pile des matrices de transformation.
 * Entree :
 * m		Matrice multiplicative.
 */
void
premult_tmstack (m)
Matrice	m;
{
	premult_matrix (*sp, m);
}

/*
 * La procedure "prerotate_tmstack" premultiplie la matrice au sommet
 * de la pile des matrices de transformation par une rotation.
 * Entree :
 * vp		Vecteur de rotation.
 */
void
prerotate_tmstack (vp)
Vecteur *vp;
{
	Matrice	m;

	Rotate_to_Matrice (vp, m);
	premult3_matrix (*sp, m);
}

/*
 * La procedure "prescale_tmstack" premultiplie la matrice au sommet
 * de la pile des matrices de transformation par une homothetie.
 * Entree :
 * vp		Vecteur d'homothetie.
 */
void
prescale_tmstack (vp)
Vecteur *vp;
{
	prescale_matrix (*sp, vp);
}

/*
 * La procedure "pretranslate_tmstack" premultiplie la matrice au sommet
 * de la pile des matrices de transformation par une translation.
 * Entree :
 * vp		Vecteur de translation.
 */
void
pretranslate_tmstack (vp)
Vecteur *vp;
{
	pretrans_matrix (*sp, vp);
}

#ifdef	standalone
main ()
{
	Matrice	m;
	Vecteur	v;

	ident_matrix (m);
	SET_COORD3(v, 90.0, 0.0, 0.0);

	push_tmstack ();
	prerotate_tmstack (&v);
	SET_COORD3(v, -90.0, 0.0, 0.0);
	postrotate_tmstack (&v);

	fprintf_matrix (stdout, get_tmstack ());
}
#endif

