/************************************************************************

 TITLE		: scan.h

 DESCRIPTION	: Le module "scan.h" contient les macros et les types
		  utilises par les algorithmes de synthese d'image par
		  balayage ("scan-line").

 VERSION	: 2-001

 ABSTRACT	: 

 Macros de mise a l'echelle.
 Macros de gestion de la liste des lignes d'apparition des aretes.
 Macros de gestion de la liste des aretes actives (LAA).
 Macros de gestion de la liste des empans actifs (LEA).
 Macros de gestion de la liste des faces  actives (LFA).
 Types des aretes.
 Types des empans.
 Types des faces.

 ENVIRONMENT	: Compilation	-
			csg		Modelisation solide CSG.
			shade		Environnement d'eclairement.
			gould		Machines GOULD.
			sun		Machines SUN 3.
			sun4		Machines SUN 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 17/04/87

 MODIFIED BY	:

 1-001 - 17/04/87 Original.
 1-002 - 22/06/87 Suppression de "flags".
 1-003 - 30/12/87 Ajout de "csg".

 2-001 - 27/09/88 Original.
 2.002 - 25/01/94 intro de SCAN_H et modif include <>
*************************************************************************/


#ifndef SCAN_H
#define SCAN_H

#include <my.h>

#define	XSHIFT		16	/* Macros de mise a l'echelle	*/
#define	YSHIFT		16
#define	ZSHIFT		30

#define	X_MINLIST	(-1)
#define	X_MAXLIST	(4096 << XSHIFT)
#define	Z_MINLIST	(-1)
#define Z_MAXLIST	(1 << ZSHIFT)

/*
 * Macros de gestion des pointeurs de chainage.
 */
#define	NEXT(x)		(x) = (x)->next
#define	PREV(x)		(x) = (x)->prev
#define	RIGHT(x)	(x) = (x)->right

/*
 * Macros de gestion d'une liste a double chainage avec sentinelles
 * en tete et en queue de la liste.
 */
#define	D_FRONT(l)	(l).head
#define	D_END(l)	(l).tail
#define	D_HEAD(l)	(l).head->next
#define	D_TAIL(l)	(l).tail->prev
/*
 * Ajoute l'element "n" derriere l'element "p".
 */
#define	D_ADD(n,p)	{ (n)->prev = (p);\
			  (n)->next = (p)->next;\
			  (p)->next->prev = (n);\
			  (p)->next = (n); }
/*
 * Retire l'element "p" de devant l'element "n".
 */
#define	D_DELETE(p,n)	{ (n)->prev = (p)->prev;\
			  (p)->prev->next = (n); }
/*
 * Insert l'element "p" devant l'element "n".
 */
#define	D_INSERT(p,n)	{ (p)->prev = (n)->prev;\
			  (p)->next = (n);\
			  (n)->prev->next = (p);\
			  (n)->prev = (p); }
/*
 * Echange les elements connexes "p" et "n".
 * Attention : l'ordre des elements est : (p->next == n).
 */
#define	D_SWAP(p,n)	{ (p)->prev->next = (n);\
			  (n)->prev = (p)->prev;\
			  (n)->next->prev = (p);\
			  (p)->next = (n)->next;\
			  (p)->prev = (n);\
			  (n)->next = (p); }

/*
 * Macros de gestion d'une liste a simple chainage.
 * en tete et en queue de la liste.
 */
#define S_HEAD(l)	(l)
#define	S_TAIL(l)	NULL
#define	S_ADD_HEAD(l,e)	{ (e)->next = (l); (l) = (e); }


/*
 * SCAN_EDGE :
 * Arete active ou inactive.
 * next		Chainage arriere de l'arete dans la LAA.
 * right	Chainage arriere des aretes actives. d'une faces.
 * bound	Numero de la surface de l'arete.
 * ymin		Ordonnee minimum de l'arete sur l'image.
 * x, dx	Abscisse   et increment suivant l'axe Y negatif.
 * z, dz	Profondeur et increment suivant l'axe Y negatif.
 * l, dl	Luminosite et increment suivant l'axe Y negatif.
 */
typedef	struct	escan	{
	struct	escan	*next;
	struct	escan	*right;
	struct	fscan	*face;
	Index		ymin;
	int		x, dx;
	int		z, dz;
#ifdef	shade
	int		l, dl;
#endif	/* shade	*/
} Scan_edge;

#ifdef	csg
/*
 * SCAN_SPAN :	Empan de la liste des empans actifs (LEA).
 * prev, next	Chainages avant et arriere de l'empan dans la LEA.
 * edge		Arete gauche dans la LAA de l'empan .
 * bound 	Numero de la surface qui contient l'empan.
 * xmax		Abscisse maximale de l'empan sur l'image.
 * z, dz	Profondeur et increment suivant l'axe X positif.
 */
typedef	struct	sscan	{
	struct	sscan	*prev, *next;
	Scan_edge	*edge;
	Index		bound;
	int		xmax;
	int		z, dz;
} Scan_span;

/*
 * SORT_SPAN : Liste des empans actifs (LEA).
 * La liste des empans actifs comporte un element fictif en tete et en queue.
 * Ces elements fictifs sont initialises et sont coherents pour le tri suivants
 * les Z croissants.
 */
typedef	struct	{
	Scan_span	*head;
	Scan_span	*tail;
} Sort_span;
#endif	/* csg	*/

/*
 * SCAN_FACE :  Faces dans la liste des faces actives (LFA).
 * next		Chainage arriere de la face dans la LFA.
 * ael		Tete de la liste des aretes actives de la face triees en X.
 * ptr		Tableau dynamique de toutes les aretes de la faces.
 * bound	Numero de la surface contenant la face.
 * ymin		Ordonnee minimum de la face sur l'image.
 */
typedef	struct	fscan	{
	struct	fscan	*next;
	Scan_edge	*ael;
	Scan_edge	*ptr;
	Index		bound;
	Index		ymin;
} Scan_face;



#endif
