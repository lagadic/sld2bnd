/************************************************************************

 TITLE		: cmstack.c

 DESCRIPTION	: Le module "cmstack.c" contient les procedures de gestion
		  de la pile des cameras (CaMera STACK).

 La pile des cameras comporte STACKSIZE elements.
 Le sommet de pile est la camera pour les modules de synthese d'image 3D.

 VERSION	: 1.001

 ABSTRACT	: 

 fprintf_cmstack	Affiche   un parametre du sommet de la pile.
 get_cmstack		Retourne  le sommet de la pile des cameras.
 load_cmstack		Charge    le sommet de la pile des cameras.
 pop_cmstack		Depile    la pile des cameras.
 push_cmstack		Empile    la pile des cameras.
 swap_cmstack		Echange	  les deux premieres cameras de la pile.
 add_cmstack		Modifie	  le sommet de la pile des cameras.
 
 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 20/05/89

 MODIFIED BY	:

 1.001 - 20/05/89 Original.

*************************************************************************/


#include	<string.h>
//#include	<varargs.h>
#include	<stdarg.h>

#include <view.h>
#include <cmstack.h>

#define	STACKSIZE	4


static	Camera_parameters 	stack[STACKSIZE] = { DEFAULT_CAMERA };
static	Camera_parameters	*sp		 = stack;


/*
 * La procedure "fprintf_cmstack" affiche un parametre du sommet
 * de la pile des cameras.
 * Entree :
 * fp		Fichier de sortie.
 * argv		Argument a afficher.
 *		Si argv est nul, tous les parametres sont affiches.
 */
void
fprintf_cmstack (fp, argv)
register FILE			*fp;
register char			*argv;
{
	static	 char	proc_name[] = "fprintf_cmstack";

	if (argv == NULL || strcmp (argv, "eye") == 0) {
		fprintf (fp, "(eye\t%.3f\t%.3f\t%.3f)\n",
			sp->eye.x, sp->eye.y, sp->eye.z);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "target") == 0) {
		fprintf (fp, "(target\t%.3f\t%.3f\t%.3f)\n",
			sp->target.x, sp->target.y, sp->target.z);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "focal") == 0) {
		fprintf (fp, "(focal\t%.3f)\n", sp->focal);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "angle") == 0) {
		fprintf (fp, "(angle\t%.3f)\n", sp->angle);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "twist") == 0) {
		fprintf (fp, "(twist\t%.3f)\n", sp->twist);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "speed") == 0) {
		fprintf (fp, "(speed\t%.3f)\n", sp->speed);
		if (argv != NULL) return;
	}
	if (argv != NULL)
		fprintf (stderr, "%s: argument unknown\n", proc_name);
}

/*
 * La procedure "get_cmstack" retourne la camera au sommet
 * de la pile des cameras.
 * Sortie :
 * 		Pointeur sur la camera du sommet de la pile.
 */
Camera_parameters	*
get_cmstack ()
{
	return (sp);
}

/*
 * La procedure "load_cmstack" charge une camera au sommet
 * de la pile des cameras.
 * Entree :
 * cp		Point de vue a charger.
 */
void
load_cmstack (cp)
Camera_parameters	*cp;
{
	*sp = *cp;
}

/*
 * La procedure "pop_cmstack" depile la camera au sommet
 * de la pile des cameras.
 */
void
pop_cmstack ()
{
	static	char	proc_name[] = "pop_cmstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_cmstack" empile et duplique la camera au sommet
 * de la pile des cameras.
 */
void
push_cmstack ()
{
	static	char	proc_name[] = "push_cmstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	*sp = *(sp - 1);
}

/*
 * La procedure "swap_cmstack" echange les deux premiers elements
 * de la pile des cameras.
 */
void
swap_cmstack ()
{
	Camera_parameters	*cp, tmp;

	cp = (sp == stack) ? sp + 1 : sp - 1; 
	SWAP(*sp, *cp, tmp);
}

/*
 * La procedure "add_cmstack" modifie un argument de la camera au sommet
 * de la pile des cameras.
 * Entree :
 * va_alist	Nom de l'argument a modifier suivi de ses parametres.
 */
void
add_cmstack (const char* path, ... )
//add_cmstack (va_alist)
//va_dcl
{
	static	char	proc_name[] = "add_cmstack";

	va_list	ap;
	char	*argv;

	va_start (ap,path);
	argv = va_arg (ap, char *);

	if (strcmp (argv, "angle") == 0) {
 		/* initialise l'angle d'ouverture	*/
		float	a = (float) va_arg (ap, double);

		if (fabs ((double) a) > 180.0)
			fprintf (stderr, "%s: angle too large\n", proc_name);
		else
			sp->angle = a;
	}
	else if (strcmp (argv, "eye") == 0) {
 		/* initialise l'oeil ou centre optique 	*/
		SET_COORD3(sp->eye,
			(float) va_arg (ap, double),
			(float) va_arg (ap, double),
			(float) va_arg (ap, double));
	}
	else if (strcmp (argv, "focal") == 0) {
 		/* initialise la distance focale	*/
		float	f = (float) va_arg (ap, double);

		if (f <= 0.0)
			fprintf (stderr, "%s: focal negative\n", proc_name);
		else
			sp->focal = f;
	}
	else if (strcmp (argv, "speed") == 0) {
		/* initialise la norme de la vitesse	*/
		sp->speed = (float) va_arg (ap, double);
	}
	else if (strcmp (argv, "target") == 0) {
		/* initialise la cible ou point vise	*/
		SET_COORD3(sp->target,
			(float) va_arg (ap, double),
			(float) va_arg (ap, double),
			(float) va_arg (ap, double));
	}
	else if (strcmp (argv, "twist") == 0) {
		/* initialise l'angle de torsion	*/
		float	a = (float) va_arg (ap, double);

		if (fabs ((double) a) > 360.0)
			fprintf (stderr, "%s: twist too large\n", proc_name);
		else
			sp->twist = a;
	}
	else 
		fprintf (stderr, "%s: bad argument\n", proc_name);
	va_end (ap);
}

#ifdef	standalone
main ()
{
	fprintf_cmstack (stdout, NULL);
	push_cmstack ();
	swap_cmstack ();
	swap_cmstack ();
	add_cmstack ("start", "target", 1.0, 2.0, 3.0);
	fprintf_cmstack (stdout, "target");
	add_cmstack ("start", "focal", 4321.0);
	fprintf_cmstack (stdout, "focal");
	add_cmstack ("start", "twist", -12.34);
	fprintf_cmstack (stdout, "twist");
}
#endif

