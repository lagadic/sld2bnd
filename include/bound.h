/************************************************************************

 TITLE		: bound.h

 DESCRIPTION	: Le fichier "bound.h" contient les macros et le types
		  utilises par le modele geometrique surfacique polygonale 3D.

 face_edge	  Compilation du type des aretes des faces.
 face_normale	  Compilation du type des normale aux faces.

 Macros pour le positionnement geometrique.
 Macros pour le modele geometrique surfacique.
 Types  pour le modele geometrique surfacique.
  
 VERSION	: 1.002

 ABSTRACT	: 

 Point3f_list	  Liste de points 3D flottants.
 Edge		  Arete du modele polygonale.
 Edge_list	  Liste d' aretes  d'un polygone.
 Vertex_list	  Liste de sommets d'un polygone.
 Face		  Primitive polyedriqe plane.
 Face_list	  Liste de faces d'une surface.
 Bound		  Primitive surfacique polyedrique.
 Bound_list	  Liste de primitives surfaciques polyedriques.
 Bound_scene	  Scene de primitives surfaciques polyedriques.

 Bouding_box	  Volume englobant parallelepipedique.

 Transfo	  Transformation affine sur les surfaces.

 ENVIRONMENT	: Compilation	- face_edge, face_normal, "my.h", "arit.h".
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 16/06/88

 MODIFIED BY	:

 1.001 - 16/06/88 Original.
 1.002 - 15/09/88 Ajout de "vertex" et de "dft_vertex_nbr" a "Bound".
 1.003 - 25/01/94 intro de BOUND_H et modif include <>

*************************************************************************/

#ifndef BOUND_H
#define BOUND_H


#include <arit.h>

#define	START_ARG	0
#define	NEXT_ARG	1

#define	BND_NULL	(-1)

#define	BND_BLOCK	0
#define	BND_CARDIOIDE	1
#define	BND_CONE	2
#define	BND_CYLINDER	3
#define	BND_SPHERE	4
#define	BND_TORUS	5
#define	BND_WEDGE	6

#define	BND_F3		7
#define	BND_F4		8

#define	BND_GRID	9
#define	BND_PIPE	10
#define	BND_SECTION	11

#define	BND_NBR		12


#define	BOUND_NBR	1024
#define	FACE_NBR	6144		/* Tailles de tableaux	*/
#define	VERTEX_NBR	16
#define	POINT_NBR	6144
#define VECTOR_NBR	6144

/* Pour ranger la surface suivante dans une scene */
#define	NEXT_IN_SCENE(bsp)	(((bsp)->bound.ptr) + ((bsp)->bound.nbr)++)

typedef	struct	{
	Index		v0, v1;		/* extremites		*/
	Index		f0, f1;		/* faces		*/
} Edge;

typedef	struct	{
	Index		nbr;		/* nombre d'aretes	*/
	Edge		*ptr;		/* liste  dynamique	*/
} Edge_list;

#define	DEFAULT_VSIZE	4

/*
 * Vertex_list :
 * Pour optimiser l'allocation et la liberation memoire d'une liste de sommets:
 * si (nbr > DEFAULT_VSIZE)
 * |	alors ptr est alloue et libere dynamiquement
 * |	sinon ptr = tbl
 * fsi;
 */
typedef	struct	{
	Index		nbr;		/* nombre de sommets	*/
	Index		*ptr;		/* liste  dynamique	*/
	Index		tbl[DEFAULT_VSIZE];
} Vertex_list;

typedef	struct	{
	Index		nbr;		/* nombre de points	*/
	Point3f		*ptr;		/* liste  dynamique	*/
} Point3f_list;

typedef	struct	{
	Index		nbr;		/* nombre de vecteurs	*/
	Vecteur		*ptr;		/* liste  dynamique	*/
} Vecteur_list;

typedef	struct	{
	unsigned	is_polygonal:1;	/* face polygonale	*/
	unsigned	is_visible  :1;	/* face affichable	*/
#ifdef	face_edge
	Edge_list	edge;		/* liste d'aretes	*/
#endif
	Vertex_list	vertex;		/* liste de sommets	*/
#ifdef	face_normal
	Vecteur		normal;		/* vecteur normal	*/
#endif
} Face;

typedef	struct	{
	Index		nbr;		/* nombre de faces	*/
	Face		*ptr;		/* liste  dynamique	*/
} Face_list;

typedef	struct	{
	unsigned	is_display  :1;	/* surface affichable	*/
	unsigned	is_polygonal:1;	/* surface polyedrique	*/	
	Type		type;		/* type de la primitive	*/
#ifdef	face_edge
	Edge_list	edge;		/* liste d'aretes	*/
#endif
	Face_list	face;		/* liste de faces	*/
	Point3f_list	point;		/* points aux sommets	*/
#ifdef	face_normal
	Vecteur_list	normal;		/* normales aux sommets	*/
#endif
} Bound;

typedef	struct	{
	Index		nbr;		/* nombre de surfaces	*/
	Bound		*ptr;		/* liste  dynamique	*/
} Bound_list;

typedef	struct	{
	float		xmin, xmax;	/* bornes sur l'axe x	*/
	float		ymin, ymax;	/* bornes sur l'axe y	*/
	float		zmin, zmax;	/* bornes sur l'axe z	*/
} Bounding_box;

typedef	struct	{
	char		*name;		/* nom de la scene	*/
	Bound_list	bound;		/* liste de surfaces	*/
} Bound_scene;

typedef	struct	{
	Index		nbr;		/* nombre de scenes	*/
	Bound_scene	*ptr;		/* liste  dynamique	*/
} Bound_scene_list;

typedef	Matrice	Transfo;

#endif

