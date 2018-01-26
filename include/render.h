/************************************************************************

 TITLE		: render.h

 DESCRIPTION	: Le module "render.h" contient les Macros et les Types
		  des aspects de rendu des programmes de synthese.

 VERSION	: 1-003

 ABSTRACT	: 

 Macros de type de aspect.
 Type   des parametres d'un aspect.

 ENVIRONMENT	: Compilation	-
			gould		Machine GOULD.
			sun		Machine SUN 3.
			sun4		Machine SUN 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 22/07/88

 MODIFIED BY	:

 1-001 - 22/07/88 Original.
 1-003 - 06/02/89 Ajout de "DEPTH_MAP".
 1-004 - 25/01/94 intro de RENDER_H et modif include <>
*************************************************************************/


#ifndef RENDER_H
#define RENDER_H

#include <my.h>
#include <scan.h>
#include <register.h>

#define	RENDER_NULL	(-1)
#define	DEPTH_CUEING	0
#define	DEPTH_MAP	1
#define	FALSE_COLOR	2
#define	HIDDEN_EDGE	3
#define	HIDDEN_FACE	4
#define	HIDDEN_LINE	5
#define	BOUKNIGHT	6
#define	GOURAUD		7
#define	PHONG		8
#define	RENDER_NBR	9


#define	DEFAULT_RENDER	{ FALSE_COLOR,	false_color, write_image_line	}


typedef	struct	{
	Type	type;			/* type du aspect	*/
	int	(*rendering) ();	/* procedure de calcul	*/
	int	(*write_line) ();	/* procedure d'ecriture	*/
} Render_parameters;


/* prototypes des fonctions definie dans render.c */
/* ---------------------------------------------- */


/* faces en  prodondeur		*/
extern int depth_cueing (
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
	REGISTER int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);


/* carte des prodondeurs	*/
extern	int	depth_map (		
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
	REGISTER int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* faces en fausses couleurs	*/
extern	int	false_color (		
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
		 int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* aretes   visibles		*/
extern	int	hidden_edge (		
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
		 int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* faces et aretes visibles	*/
extern	int	hidden_face (		
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
		 int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* courbes de niveaux visibles	*/
extern	int	hidden_line (		
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
		 int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* Eclairement BOUKNIGHT	*/
extern	int	bouknight_render (	
#ifdef PROTOTYPE
#endif
);

/* Eclairement GOURAUD		*/
extern	int	gouraud_render (	
#ifdef PROTOTYPE
		 int		/* xres */,
	REGISTER Scan_edge **	/* sb */,
		 int *		/* zb */,
	REGISTER Byte *		/* ib */
#endif
);

/* Eclairement PHONG		*/
extern	int	phong_render (	
#ifdef PROTOTYPE
#endif
);

/* ecrit une ligne profondeur	*/
extern	int	write_depth_line (	
#ifdef PROTOTYPE
		 int *		/* zb */,
		 Byte *		/* ib */,
		 int     	/* size */
#endif
);

/* ecrit une ligne image	*/
extern	int	write_image_line (	
#ifdef PROTOTYPE
		 int *		/* zb */,
		 Byte *		/* ib */,
		 int     	/* size */
#endif
);

#endif

