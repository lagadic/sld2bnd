/************************************************************************

 TITLE		: imstack.c

 DESCRIPTION	: Le module "imstack.c" contient les procedures de gestion
		  de la pile des images (IMage STACK).

 La pile des images comporte STACKSIZE elements.
 Le sommet de pile est l'image pour les modules de synthese d'image 3D.

 VERSION	: 1.001

 ABSTRACT	: 

 fprintf_imstack	Affiche   un parametre du sommet de la pile des images.
 get_imstack		Retourne  le sommet de la pile des images.
 load_imstack		Charge    le sommet de la pile des images.
 pop_imstack		Depile    la pile des images.
 push_imstack		Empile    la pile des images.
 swap_imstack		Echange	  les deux premieres images de la pile.
 add_imstack		Modifie	  le sommet de la pile des images.
 
 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 22/05/89

 MODIFIED BY	:

 1.001 - 22/05/89 Original.
 1.002 - 15/04/94 Nettoyage des options de compilation et include <> (TB)

*************************************************************************/


#include	<stdio.h>
#include	<string.h>
//#include	<varargs.h>
#include	<stdarg.h>

#include	<arit.h>
#include	<graph.h>
#include	<imstack.h>


#define	STACKSIZE	4


static	Image_parameters	stack[STACKSIZE] = DEFAULT_IMAGE;
static	Image_parameters	*sp		 = stack;


/*
 * La procedure "fprintf_imstack" affiche un parametre du sommet
 * de la pile des images.
 * Entree :
 * fp		Fichier de sortie.
 * argv		Argument a afficher.
 *		Si argv est nul, tous les parametres sont affiches.
 */
void
fprintf_imstack (fp, argv)
register FILE			*fp;
register char			*argv;
{
	static	 char	proc_name[] = "fprintf_imstack";

	if (argv == NULL || strcmp (argv, "file") == 0) {
		fprintf (fp, "(file\t\"%s\")\n", sp->filename);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "origin") == 0) {
		fprintf (fp, "(origin\t%4d\t%4d)\n", 
			(int) sp->origin.x, (int) sp->origin.y);
		if (argv != NULL) return;
	}
	if (argv == NULL || strcmp (argv, "size") == 0) {
		fprintf (fp, "(size\t%4d\t%4d)\n", 
			(int) sp->size.x, (int) sp->size.y);
		if (argv != NULL) return;
	}
	if (argv != NULL)
		fprintf (stderr, "%s: argument unknown\n", proc_name);
}

/*
 * La procedure "get_imstack" retourne l'image au sommet
 * de la pile des images.
 * Sortie :
 * 		Pointeur sur l'image du sommet de la pile.
 */
Image_parameters	*
get_imstack ()
{
	return (sp);
}

/*
 * La procedure "load_imstack" charge un point de vue au sommet
 * de la pile des images.
 * Entree :
 * ip		Point de vue a charger.
 */
void
load_imstack (ip)
Image_parameters	*ip;
{
	*sp = *ip;
}

/*
 * La procedure "pop_imstack" depile l'image au sommet
 * de la pile des images.
 */
void
pop_imstack ()
{
	static	char	proc_name[] = "pop_imstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_imstack" empile et duplique l'image au sommet
 * de la pile des images.
 */
void
push_imstack ()
{
	static	char	proc_name[] = "push_imstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	*sp = *(sp - 1);
}

/*
 * La procedure "swap_imstack" echange les deux premiers elements
 * de la pile des images.
 */
void
swap_imstack ()
{
	Image_parameters	*ip, tmp;

	ip = (sp == stack) ? sp + 1 : sp - 1; 
	SWAP(*sp, *ip, tmp);
}

/*
 * La procedure "add_imstack" modifie un agrument de l'image au sommet
 * de la pile des images.
 * Entree :
 * va_alist	Nom de l'argument a modifier suivi de ses parametres.
 */
void
add_imstack (const char* path, ... )
//add_imstack (va_alist)
//va_dcl
{
	static	char	proc_name[] = "add_imstack";

	va_list	ap;
	char	*argv;

	va_start (ap,path);
	argv = (char *) va_arg (ap, char *);
	if (strcmp (argv, "file") == 0) {
 		/* initialise le nom du fichier image	*/
		char	*str = (char *) va_arg (ap, char *);

		if (str == NULL) {
			fprintf (stderr, "%s: null image file name\n",
				proc_name);
			sp->filename[0] = '\0';
		}
		else if (strlen (str) >= NAMESIZE) {
			fprintf (stderr, "%s: image file name too long\n",
				proc_name);
			sp->filename[0] = '\0';
		}
		else {
			strncpy (sp->filename, str, NAMESIZE);
			sp->filename[NAMESIZE-1] = '\0';
		}
	}
	else if (strcmp (argv, "origin") == 0) {
 		/* initialise l'origine de l'image	*/
		int	x = (int) va_arg (ap, int);
		int	y = (int) va_arg (ap, int);

		if (x < 0 || y < 0)
			fprintf (stderr, "%s: bad image origin\n", proc_name);
		else {
			SET_COORD2(sp->origin, (Index) x, (Index) y);
		}
	}
	else if (strcmp (argv, "size") == 0) {
 		/* initialise la taille de l'image	*/
		int	x = (int) va_arg (ap, int);
		int	y = (int) va_arg (ap, int);

		if (x < 1 || y < 1)
			fprintf (stderr, "%s: bad image size\n", proc_name);
		else {
			SET_COORD2(sp->size, (Index) x, (Index) y);
		}
	}
	else 
		fprintf (stderr, "%s: bad argument\n", proc_name);
	va_end (ap);
}

#ifdef	standalone
main ()
{
	push_imstack ();
	add_imstack ("start", "file", "toto.dab");
	add_imstack ("start", "origin", 1, -2);
	add_imstack ("start", "origin", 1, 2);
	fprintf_imstack (stdout, NULL);

	swap_imstack ();
	swap_imstack ();
	add_imstack ("start", "size", 0, 1);
	add_imstack ("start", "size", 2, 1);
	fprintf_imstack (stdout, "size");
	fprintf_imstack (stdout, "origin");
}
#endif

