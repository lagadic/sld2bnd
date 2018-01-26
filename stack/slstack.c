/************************************************************************

 TITLE		: slstack.c

 DESCRIPTION	: Le module "slstack.c" contient les procedures de gestion
		  de la pile de niveaux de subdivision (Sudivision Level STACK).

 La pile des niveaux de subdivision comporte STACKSIZE elements.
 Le sommet de pile est le niveau de subdivision courant pour les modules
 de synthese d'image 3D.

 VERSION	: 1.001

 ABSTRACT	: 

 get_slstack		Retourne  le sommet de la pile des niveaux.
 load_slstack		Charge    le sommet de la pile des niveaux.
 pop_slstack		Depile    la pile des niveaux de subdivision.
 push_slstack		Empile    la pile des niveaux de subdivision.
 swap_slstack		Echange	  les deux premiers niveaux de la pile.
 add_slstack		Additionne le niveau de subdivision courant.

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 11/04/89

 MODIFIED BY	:

 1.001 - 11/04/89 Original.

*************************************************************************/



#include <arit.h>
#include <slstack.h>



#define	STACKSIZE	32
#define	MIN_SL		0
#define	MAX_SL		4


static	int	stack[STACKSIZE] = {MIN_SL};	/* pile		*/
static	int	*sp		 = stack;	/* sommet 	*/


/*
 * La procedure "get_slstack" retourne le niveau au sommet
 * de la pile de subdivision.
 * Sortie :
 * 		Pointeur sur le niveau de subdivision du sommet de la pile.
 */
int	*
get_slstack ()
{
	return (sp);
}

/*
 * La procedure "load_slstack" charge un niveau au sommet
 * de la pile des niveaux de subdivision.
 * Entree :
 * i		Niveau a charger.
 */
void
load_slstack (i)
int	i;
{
	*sp = i;
}

/*
 * La procedure "pop_slstack" depile le niveau au sommet
 * de la pile des niveaux de subdivision.
 */
void
pop_slstack ()
{
	static	char	proc_name[] = "pop_slstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_slstack" empile et duplique le niveau au sommet
 * de la pile des niveaux de subdivision.
 */
void
push_slstack ()
{
	static	char	proc_name[] = "push_slstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	*sp = *(sp - 1);
}

/*
 * La procedure "swap_slstack" echange les deux premiers elements
 * de la pile des niveaux de subdivision.
 */
void
swap_slstack ()
{
	int	*lp, tmp;

	lp = (sp == stack) ? sp + 1 : sp - 1; 
	SWAP(*sp, *lp, tmp);
}

/*
 * La procedure "add_slstack" additionne un niveau au sommet
 * de la pile des niveaux de subdivision.
 * Entree :
 * i		Niveau a additionner.
 */
void
add_slstack (i)
int	i;
{
	*sp += i;
}

#ifdef	standalone
main ()
{
	int	i;

	push_slstack ();
	add_slstack (10);
	add_slstack (-20);
	
	load_slstack (2);
	add_slstack (4);
	push_slstack ();
	push_slstack ();

	i = get_slstack ();
	printf ("level: %d\n", i);
}
#endif

