/************************************************************************

 TITLE		: rfstack.c

 DESCRIPTION	: Le module "rfstack.c" contient les procedures de gestion
		  de la pile d'elimination de faces (Remove Faces STACK).

 La pile d'elimination de faces comporte STACKSIZE elements.
 Le sommet de pile contient les drapeaux d'elimination de faces
 pour les modules de synthese d'image 3D.

 VERSION	: 1.001

 ABSTRACT	: 

 fprintf_rfstack	Affiche   un parametre du sommet de la pile.
 get_rfstack		Retourne  le sommet de la pile des drapeaux.
 load_rfstack		Charge    le sommet de la pile des drapeaux.
 pop_rfstack		Depile    la pile des drapeaux d'elimination.
 push_rfstack		Empile    la pile des drapeaux d'elimination.
 swap_rfstack		Echange	  les deux premieres drapeaux de la pile.
 add_rfstack		Ajoute	  des drapeaux au sommet de la pile.
 sub_rfstack		Soustrait des drapeaux au sommet de la pile.

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 10/05/89

 MODIFIED BY	:

 1.001 - 10/05/89 Original.

*************************************************************************/


#include	<string.h>

#include <view.h>
#include <rfstack.h>




#define	STACKSIZE	32


static	int	stack[STACKSIZE] = {DEFAULT_REMOVE};	/* pile		*/
static	int	*sp		 = stack;		/* sommet 	*/


/*
 * La procedure "fprintf_rfstack" affiche le sommet
 * de la pile des drapeaux d'elimination de faces.
 * Entree :
 * fp		Fichier en sortie.
 */
void
fprintf_rfstack (fp)
FILE	*fp;
{
	int	flg = 0;	/* nul si element unique	*/

	if (*sp == IS_INSIDE) {
		fprintf (fp, "(null)\n");
		return;
	}
	fprintf (fp, "(");
	if (*sp & IS_ABOVE) {
		if (flg++) fprintf (fp, " ");
		fprintf (fp, "above");
	}
	if (*sp & IS_BELOW) {
		if (flg++) fprintf (fp, " ");
		fprintf (fp, "below");
	}
	if (*sp & IS_RIGHT) {
		if (flg++) fprintf (fp, " ");
		fprintf (fp, "right");
	}
	if (*sp & IS_LEFT) {
		if (flg++) fprintf (fp, " ");
	 	fprintf (fp, "left");
	}
	if (*sp & IS_BACK) {
		if (flg++) fprintf (fp, " ");
		fprintf (fp, "back");
	}
	if (*sp & IS_FRONT) {
		if (flg++) fprintf (fp, " ");
		fprintf (fp, "front");
	}
	fprintf (fp, ")\n");
}

/*
 * La procedure "get_rfstack" retourne les drapeaux au sommet
 * de la pile des drapeaux d'elimination de faces.
 * Sortie :
 * 		Pointeur sur les drapeaux d'elimination du sommet de la pile.
 */
int	*
get_rfstack ()
{
	return (sp);
}

/*
 * La procedure "load_rfstack" charge des drapeaux au sommet
 * de la pile des drapeaux d'elimination de faces.
 * Entree :
 * i		Niveau a charger.
 */
void
load_rfstack (i)
int	i;
{
	*sp = i;
}

/*
 * La procedure "pop_rfstack" depile les drapeaux au sommet
 * de la pile des drapeaux d'elimination de faces.
 */
void
pop_rfstack ()
{
	static	char	proc_name[] = "pop_rfstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_rfstack" empile et duplique les drapeaux du sommet
 * de la pile des drapeaux d'elimination de faces.
 */
void
push_rfstack ()
{
	static	char	proc_name[] = "push_rfstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	*sp = *(sp - 1);
}

/*
 * La procedure "swap_rfstack" echange les deux premiers elements
 * de la pile des drapeaux d'elimination de faces.
 */
void
swap_rfstack ()
{
	int	*ip, tmp;

	ip = (sp == stack) ? sp + 1 : sp - 1; 
	SWAP(*sp, *ip, tmp);
}

/*
 * La procedure "add_rfstack" ajoute des drapeaux au sommet
 * de la pile des drapeaux d'elimination de faces.
 */
void
add_rfstack (i)
register int	i;
{
	*sp |= i;
}

/*
 * La procedure "sub_rfstack" soustrait des drapeaux au sommet
 * de la pile des drapeaux d'elimination de faces.
 */
void
sub_rfstack (i)
{
	*sp &= ~i;
}

#ifdef	standalone
main ()
{
	push_rfstack ();
	load_rfstack (IS_FRONT | IS_LEFT);
	fprintf_rfstack (stdout);

	load_rfstack (IS_FRONT | IS_LEFT | IS_INSIDE);
	add_rfstack (IS_RIGHT | IS_BACK);
	push_rfstack ();
	swap_rfstack ();
	fprintf_rfstack (stdout);
	swap_rfstack ();
	load_rfstack (IS_FRONT | IS_LEFT | IS_INSIDE | IS_RIGHT);
	sub_rfstack (IS_RIGHT | IS_BACK);
	fprintf_rfstack (stdout);
}
#endif	standalone

