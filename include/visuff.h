/************************************************************************
 
 TITLE		: visuff.h

 DESCRIPTION	: Module de Macros et de Types de bases en langage "C".

 VERSION	: 1.001

 ABSTACT	: Type pour la sortie fil de fer.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Thierry Bouedo		CREATION DATE	: 26/04/94

 MODIFIED BY	:

 1.001 - 26/04/94 Original.

*************************************************************************/

#ifndef VISUFF_H
#define VISUFF_H

#include	<bound.h>

typedef	struct	{
	Index		nbr;			/* nombre de sommets */
	Point2f		tab_p2f[VERTEX_NBR];	/* liste de sommets 2D */
} Polygone;

typedef	struct	{
	Index		nbr;		/* nombre de polygones */
	Polygone	*ptr;		/* liste dynamique de polygones */
} Polygone_list;

#endif


