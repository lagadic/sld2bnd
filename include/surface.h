/************************************************************************

 TITLE		: surface.h

 DESCRIPTION	: Le fichier "surface.h" contient les macros et le types
		  utilises par le modele geometrique surfacique 3D.

 Macros pour le modele geometrique surfaciques fractales.
 Types  pour le modele geometrique surfaciques fractales.

 Macros pour le modele geometrique surfaciques cubiques.
 Types  pour le modele geometrique surfaciques cubiques.
 Bases  matricielles pour les surfaces parametrees.
  
 VERSION	: 1.001

 ABSTRACT	: 

 F3		  Primitive fractale triangulaire.
 F4		  Primitive fractale trapezoidale.

 Geometry_frac	  Primitives geometriques fractales.
 Fractal	  Primitive fractale.
 Fractal_list	  Liste de primitives fractales.
 Fractal_scene	  Scene de primitives fractales.

 Point3f_list	  Liste de points 3D.
 Grid		  Grille de points.
 Patch	 	  Morceau de surface.
 Patch_list	  Liste de morceaux de surfaces.
 Patch_scene	  Scene de morceaux de surfaces.

 ENVIRONMENT	: Compilation	- "my.h", "arit.h".
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 03/08/88

 MODIFIED BY	:

 1.001 - 03/08/88 Original.
 1.003 - 25/01/94 intro de SURFACE_H et modif include <>
*************************************************************************/


#ifndef SURFACE_H
#define SURFACE_H

#include <bound.h>

/*
 * Macros de numerotation des primitives fractales.
 */
#define	FRAC_NULL	(-1)
#define	FRAC_F3		0
#define	FRAC_F4		1
#define	FRAC_NBR	2


/*
 * Macros de subdivision des primitives fractales sous forme surfacique.
 */
#define	DEFAULT_F3	4
#define	DEFAULT_F4	4

#define	FRACTAL_NBR	512
 

/*
 *				F3
 *				__
 *
 *		P0
 *		 X
 *		/ \
 *	       /   \
 *	      / F1  \
 *	     /	     \
 * 	 M0 X---------X M2
 *	   / \	     / \
 * 	  /   \	F0  /	\
 *  	 / F2  \   /  F3 \
 *	/       \ /	  \
 *     X---------X---------X
 *    P1	M1	  P2 
 *
 * Pi	Points origines de la fractale.
 * Mi	Points milieux des aretes.
 * Fi	Faces  apres la subdivision.
 *
 * Apres n subdisions de la fractale, la surface comporte :
 * Points : (2**n + 1) * (2**n + 2) / 2
 * Faces  : 4**n
 */
typedef	struct	{
	float	dimension;	/* dimension de la deformation	*/
	float	scale;		/* echelle   de la deformation	*/
	Vecteur	distortion;	/* direction de la deformation	*/	
	Point3f	point[3];	/* 3 sommets de la fractale	*/
} F3;

/*
 *				F4
 *				__
 *
 *     P0	 M3	   P3
 *	X---------X---------X
 *      |	  |	    |
 *	|   F0	  |   F3    |
 *	|	  |	    |
 *	|	M4|	    |
 *   M0 X---------X---------X M2
 *      |	  |	    |
 *	|   F1	  |   F2    |
 *	|	  |	    |
 *	|	  |	    |
 *	X---------X---------X
 *     P1	 M1	   P2 
 *
 * Pi	Points origines de la fractale.
 * Mi	Points milieux des aretes.
 * Fi	Faces  apres la subdivision.
 *
 * Apres n subdisions de la fractale, la surface comporte :
 * Points : (2**n + 1) * (2**n + 1)
 * Faces  : 4**n
 */
typedef	struct	{
	float	dimension;	/* dimension de la deformation	*/
	float	scale;		/* echelle   de la deformation	*/
	Vecteur	distortion;	/* direction de la deformation	*/	
	Point3f	point[4];	/* 4 sommets de la fractale	*/
} F4;

typedef	union	{
	F3		f3;
	F4		f4;
} Geometry_frac;

typedef	struct	{
	Type		type;		/* type de la fractale	*/
	Geometry_frac	geometry;	/* geometrie		*/
	Matrice		lsm;		/* passage Local/Scene	*/
	Position	position;	/* positionnement	*/
	Index		subdivision;	/* niveau de subdivision*/
} Fractal;

typedef	struct	{
	Index		nbr;		/* nombre de fractales	*/
	Fractal		*ptr;		/* liste  dynamique	*/
} Fractal_list;

typedef	struct	{
	char		*name;		/* nom de la scene	*/
	Fractal_list	fractal;	/* liste de fractales	*/
} Fractal_scene;


/*
 * Macros de primitives sous forme surfacique.
 */
#define	PATCH_NULL	(-1)
#define	PATCH_GRID	0
#define	PATCH_BEZIER	1
#define	PATCH_BSPLINE	2
#define	PATCH_CARDINAL	3
#define	PATCH_NBR	4

/*
 * Macros de subdivision des primitives surfaciques.
 */
#define	DEFAULT_GRID		4
#define	DEFAULT_BEZIER		4
#define	DEFAULT_BSPLINE		4
#define	DEFAULT_CARDINAL	4


#ifndef	POINT_NBR
typedef	struct	{
	Index		nbr;		/* nombre de points	*/
	Point3f		*ptr;		/* liste  dynamique	*/
} Point3f_list;
#endif	POINT_NBR

typedef	struct	{
	Index		col_nbr;	/* nombre de colonnes 	*/
	Index		row_nbr;	/* nombre de lignes	*/
	Point3f_list	point;		/* matrice de points	*/
} Grid;

typedef	struct	{
	unsigned	is_polygonal:1;	/* surface polygonale	*/	
	Type		type;		/* type de la surface	*/
	Grid		grid;		/* grille de points	*/
	Matrice		lsm;		/* passage Local->Scene	*/
	Position	position;	/* positionnement	*/
	Index		col_sub;	/* subdivision colonne	*/ 
	Index		row_sub;	/* subdivision ligne	*/
} Patch;

typedef	struct	{
	Index		nbr;		/* nombre de surfaces	*/
	Patch		*ptr;		/* liste  dynamique	*/
} Patch_list;

typedef	struct	{
	char		*name;		/* nom de la scene	*/
	Patch_list	patch;		/* liste de surfaces	*/
} Patch_scene;

static	Matrice	bezier_matrix = {
	{ -1.0,	 3.0, -3.0,  1.0 },
	{  3.0,	-6.0,  3.0,  0.0 },
	{ -3.0,  3.0,  0.0,  0.0 },
	{  1.0,  0.0,  0.0,  0.0 }
};

static	Matrice	bspline_matrix = {
	{ -1.0/6.0,  3.0/6.0, -3.0/6.0,  1.0/6.0 },
	{  3.0/6.0, -6.0/6.0,  3.0/6.0,  0.0     },
	{ -3.0/6.0,  0.0,      3.0/6.0,  0.0     },
	{  1.0/6.0,  4.0/6.0,  1.0/6.0,  0.0     }
};

static	Matrice	cardinal_matrix = {
	{ -0.5,	 1.5, -1.5,  0.5 },
	{  1.0,	-2.5,  2.0, -0.5 },
	{ -0.5,  0.0,  0.5,  0.0 },
	{  0.0,  1.0,  0.0,  0.0 }
};


#endif
