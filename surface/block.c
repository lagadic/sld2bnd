/************************************************************************

 TITLE		: block.c

 DESCRIPTION	: Le module "block.c" contient les procedures de construction
		  de la surface de la primitive "Block".

 Remarque : Le niveau de decomposition de la primitive "Block" est fixe.

 VERSION	: 1.002

 ABSTRACT	: 

 make_Block_Bound	Construit la  surface du block unite.
 make_Block_Face	Construit les faces   du block unite.
 make_Block_Point	Construit les points  du block unite.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 03/03/87

 MODIFIED BY	:

 1.001 - 03/03/87 Original.
 1.002 - 11/05/87 Ajout du champ "Face.is_polygonal".
 1.003 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/

#include <bound.h>
#include <solid.h>

static	void	make_Block_Face	();
static	void	make_Block_Point ();


/* 
 * La procedure "make_Block_Bound" construit la surface du block unite :
 * 	- origine   (0,0,0).
 *	- diagonale (1,1,1).
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Remarque : 
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * bp		Surface issue de la construction.
 */
make_Block_Bound (bp)
register Bound	*bp;
{
	malloc_Bound (bp, BND_BLOCK, TRUE, 6, 8);
	make_Block_Face (bp->face.ptr);
	make_Block_Point (bp->point.ptr);
}

/*
 * La procedure "make_Block_Face" constuit les 6 faces du block unite.
 * Le sens de parsours du contour d'une face donne le sens de la normale.
 * Numeros des faces		|Y		
 *				|    5/		
 *				|____/____
 *			       /         /|	
 *			      /    3	/ |	
 *			     /_________/  |	
 *			    |	      | 1 |
 *			0___|         |   |___X	
 *			    |    4    |  /
 *			    |         | /	
 *			    |_________|/
 *			   /    |		
 *			 Z/     |2
 * Remarque :
 * Le champ "edge" de "Face" n'est pas utilise.
 * Entree :
 * fp		Tableau de faces issu de la construction.
 */
static	void
make_Block_Face (fp)
register Face	*fp;
{ 
	malloc_Face_vertex4 (fp++,TRUE,0,4,7,1);	/* face gauche	*/
	malloc_Face_vertex4 (fp++,TRUE,3,2,6,5);	/* face droite	*/
	malloc_Face_vertex4 (fp++,TRUE,0,3,5,4);	/* face dessous	*/
	malloc_Face_vertex4 (fp++,TRUE,1,7,6,2);	/* face dessus	*/
	malloc_Face_vertex4 (fp++,TRUE,4,5,6,7);	/* face avant	*/
	malloc_Face_vertex4 (fp  ,TRUE,0,1,2,3);	/* face arriere	*/
}

/*
 * La procedure "make_Block_Point" constuit les 8 points du block unite.
 * Numeros des points		|Y
 *				| 
 *				1_________2
 *			       /|        /|
 *			      / | 	/ |
 *			    7_________6/  |
 *			    |	|     |   |
 *			    |	0_____|___3___X
 *			    |  /      |  /
 *			    | /	      | /
 *			    4/________5/
 *			    /
 *			  Z/
 * Entree :
 * pp		Tableau de points issu de la construction.
 */
static	void
make_Block_Point (pp)
register Point3f	*pp;
{ 
	SET_COORD3(*pp,0.0,0.0,0.0); pp++;
	SET_COORD3(*pp,0.0,1.0,0.0); pp++;
	SET_COORD3(*pp,1.0,1.0,0.0); pp++;
	SET_COORD3(*pp,1.0,0.0,0.0); pp++;
	SET_COORD3(*pp,0.0,0.0,1.0); pp++;
	SET_COORD3(*pp,1.0,0.0,1.0); pp++;
	SET_COORD3(*pp,1.0,1.0,1.0); pp++;
	SET_COORD3(*pp,0.0,1.0,1.0);
}

