/************************************************************************

 TITLE		: rdstack.c

 DESCRIPTION	: Le module "rdstack.c" contient les procedures de gestion
		  de la pile des aspects de synthese (Render  STACK).

 La pile des aspects comporte STACKSIZE elements.
 Le sommet de pile est l'aspect courant pour les modules de synthese d'image 3D.

 VERSION	: 1.001

 ABSTRACT	: 

 fprintf_rdstack	Affiche   un parametre du sommet de la pile.
 get_rdstack		Retourne  le sommet de la pile des aspects.
 load_rdstack		Charge    le sommet de la pile des aspects.
 pop_rdstack		Depile    la pile des aspects.
 push_rdstack		Empile    la pile des aspects.
 swap_rdstack		Echange	  les deux premieres points de vue de la pile.
 add_rdstack		Modifie	  le sommet de la pile des aspects.
 
 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 10/06/89

 MODIFIED BY	:

 1.001 - 10/06/89 Original.

*************************************************************************/


#include	<string.h>
//#include	<varargs.h>
#include	<stdarg.h>

#include <arit.h>
#include <render.h>
#include <rdstack.h>



#define	STACKSIZE	32


static	Render_parameters	stack[STACKSIZE] = DEFAULT_RENDER;
static	Render_parameters	*sp		 = stack;


/*
 * La procedure "fprintf_rdstack" affiche un parametre du sommet
 * de la pile des aspects.
 * Entree :
 * fp		Fichier de sortie.
 * argv		Argument a afficher.
 *		Si argv est nul, tous les parametres sont affiches.
 */
void
fprintf_rdstack (fp, argv)
register FILE			*fp;
register char			*argv;
{
	static	 char	proc_name[] = "fprintf_rdstack";

	if (argv == NULL || strcmp (argv, "type") == 0) {
		char	*typetoa;

		switch (sp->type) {
		case DEPTH_CUEING :
			typetoa = "depth_cueing";
			break;
		case DEPTH_MAP :
			typetoa = "depth_map";
			break;
		case FALSE_COLOR :
			typetoa = "false_color";
			break;
		case HIDDEN_EDGE :
			typetoa = "hidden_edge";
			break;
		case HIDDEN_FACE :
			typetoa = "hidden_face";
			break;
		case HIDDEN_LINE :
			typetoa = "hidden_line";
			break;
		case BOUKNIGHT :
			typetoa = "bouknight";
			break;
		case GOURAUD :
			typetoa = "gouraud";
			break;
		case PHONG :
			typetoa = "phong";
			break;
		default :
			typetoa = "unknown";
			break;
		}
		fprintf (fp, "(type\t%s)\n", typetoa);
		if (argv != NULL) return;
	}
}

/*
 * La procedure "get_rdstack" retourne le point de vue au sommet
 * de la pile des aspects.
 * Sortie :
 * 		Pointeur sur le point de vue du sommet de la pile.
 */
Render_parameters	*
get_rdstack ()
{
	return (sp);
}

/*
 * La procedure "load_rdstack" charge un point de vue au sommet
 * de la pile des aspects.
 * Entree :
 * rp		Point de vue a charger.
 */
void
load_rdstack (rp)
Render_parameters	*rp;
{
	*sp = *rp;
}

/*
 * La procedure "pop_rdstack" depile le point de vue au sommet
 * de la pile des aspects.
 */
void
pop_rdstack ()
{
	static	char	proc_name[] = "pop_rdstack";

	if (sp == stack) {
		fprintf (stderr, "%s: stack underflow\n", proc_name);
		return;
	}
	else	sp--;
}

/*
 * La procedure "push_rdstack" empile et duplique le point de vue au sommet
 * de la pile des aspects.
 */
void
push_rdstack ()
{
	static	char	proc_name[] = "push_rdstack";

	if (sp == stack + STACKSIZE - 1) {
		fprintf (stderr, "%s: stack overflow\n", proc_name);
		return;
	}
	sp++;
	*sp = *(sp - 1);
}

/*
 * La procedure "swap_rdstack" echange les deux premiers elements
 * de la pile des aspects.
 */
void
swap_rdstack ()
{
	Render_parameters	*rp, tmp;

	rp = (sp == stack) ? sp + 1 : sp - 1; 
	SWAP(*sp, *rp, tmp);
}

/*
 * La procedure "add_rdstack" modifie un agrument du point de vue au sommet
 * de la pile des aspects.
 * Entree :
 * va_alist	Nom de l'argument a modifier suivi de ses parametres.
 */
void
add_rdstack (const char* path, ... )
//add_rdstack (va_alist)
//va_dcl
{
	static	char	proc_name[] = "add_rdstack";

	va_list	ap;
	char	*argv;

	va_start (ap,path);
	argv = va_arg (ap, char *);
	if (strcmp (argv, "type") == 0) {
 		/* initialise le type d'aspect de synthese	*/
		switch ((int) va_arg (ap, int)) {
		case DEPTH_CUEING :
			sp->type	= DEPTH_CUEING;
			sp->rendering	= depth_cueing;
			sp->write_line	= write_image_line;
			break;
		case DEPTH_MAP :
			sp->type	= DEPTH_MAP;
			sp->rendering	= depth_map;
			sp->write_line	= write_depth_line;
			break;
		case FALSE_COLOR :
			sp->type	= FALSE_COLOR;
			sp->rendering	= false_color;
			sp->write_line	= write_image_line;
			break;
		case HIDDEN_EDGE :
			sp->type	= HIDDEN_EDGE;
			sp->rendering	= hidden_edge;
			sp->write_line	= write_image_line;
			break;
		case HIDDEN_FACE :
			sp->type	= HIDDEN_FACE;
			sp->rendering	= hidden_face;
			sp->write_line	= write_image_line;
			break;
		case HIDDEN_LINE :
			sp->type	= HIDDEN_LINE;
			sp->rendering	= hidden_line;
			sp->write_line	= write_image_line;
			break;
		case BOUKNIGHT :
			sp->type	= BOUKNIGHT;
			sp->rendering	= bouknight_render;
			sp->write_line	= write_image_line;
			break;
		case GOURAUD :
			sp->type	= GOURAUD;
			sp->rendering	= gouraud_render;
			sp->write_line	= write_image_line;
			break;
		case PHONG :
			sp->type	= PHONG;
			sp->rendering	= phong_render;
			sp->write_line	= write_image_line;
			break;
		default :
			fprintf (stderr, "%s: type unknown\n", proc_name);
			break;
		}
	}
	else 
		fprintf (stderr, "%s: bad argument\n", proc_name);
	va_end (ap);
}

#ifdef	standalone
main ()
{
	push_rdstack ();
	add_rdstack ("start", "type", DEPTH_MAP);
	fprintf_rdstack (stdout, NULL);

	swap_rdstack ();
	swap_rdstack ();
	add_rdstack ("start", "type", DEPTH_CUEING);
	fprintf_rdstack (stdout, "type");
}
#endif

