/************************************************************************

 TITLE		: solid.h

 DESCRIPTION	: Le fichier "solid.h" contient les macros et le types
		  utilises par le modele geometrique solide 3D.

 Macros pour le modele geometrique solide.
 Types  pour le modele geometrique solide.
  
 VERSION	: 1.002

 ABSTRACT	: 

 Block		  Primitive geometrique solide cubique.
 Cardioide	  Primitive geometrique solide cardioide.
 Cone		  Primitive geometrique solide conique.
 Cylinder	  Primitive geometrique solide cylindrique.
 Sphere		  Primitive geometrique solide spherique.
 Torus		  Primitive geometrique solide torique.
 Wedge		  Primitive geometrique solide coin.

 Geometry_solid	  Primitives geometriques solides.
 Solid		  Primitive solide.
 Solid_list	  Liste de primitives solides.
 Solid_scene	  Scene de primitives solides.

 ENVIRONMENT	: Compilation	- "my.h", "arit.h".
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 16/06/88

 MODIFIED BY	:

 1.001 - 16/06/88 Original.
 1.002 - 17/11/89 Ajout de "Cardioide".
 1.003 - 25/01/94 intro de SOLID_H et modif include <>

*************************************************************************/


#ifndef SOLID_H
#define SOLID_H


#include <arit.h>

#define	START_ARG	0
#define	NEXT_ARG	1

/*
 * Macros de numerotation des primitives solides.
 */
#define	PRIM_NULL	(-1)
#define	PRIM_BLOCK	0
#define	PRIM_CARDIOIDE	1
#define	PRIM_CONE	2
#define	PRIM_CYLINDER	3
#define	PRIM_SPHERE	4
#define	PRIM_TORUS	5
#define	PRIM_WEDGE	6
#define	PRIM_NBR	7


/*
 * Macros de subdivision des primitives solides sous forme surfacique.
 */
#define	DEFAULT_BLOCK		0
#define	DEFAULT_CARDIOIDE	2
#define	DEFAULT_CONE		2
#define	DEFAULT_CYLINDER	2
#define	DEFAULT_SPHERE		2
#define	DEFAULT_TORUS		2
#define	DEFAULT_WEDGE		0

#define	SOLID_NBR	1024
 

/*
 *				BLOCK
 *				_____
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Cube unite		X = 0				0 <= Y,Z <= 1
 *			X = 1				0 <= Y,Z <= 1
 *			Y = 0				0 <= X,Z <= 1
 *			Y = 1				0 <= X,Z <= 1
 *			Z = 0				0 <= X,Y <= 1
 *			Z = 1				0 <= X,Y <= 1
 */
typedef	struct	{
	float	x;	/* taille du block sur l'axe X	*/
	float	y;	/* taille du block sur l'axe Y	*/
	float	z;	/* taille du block sur l'axe Z	*/
} Block;

/*
 * 				CARDIOIDE
 * 				_________
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Cardioide 		ro = r (1 + cos (teta))
 */
typedef	struct	{
	float	r;	/* rayon sur les axes X, Y et Z	*/
} Cardioide;

/*
 *				CONE
 *				____
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Cone unite		Z = 0				X**2 + Y**2 <= 1
 *			X**2 + Y**2 - Z**2 = 0		0 <= Z <= 1
 *
 */
typedef	struct	{
	float	l;	/* longueur sur l'axe Z		*/
	float	r;	/* rayon    sur les axes X et Y	*/
} Cone;

/*
 *				CYLINDRE
 *				________
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Cylindre		Z = 0				X**2 + Y**2 <= 1
 *			Z = 1				X**2 + Y**2 <= 1
 *			X**2 + Y**2 = 1			0 <= Z <= 1
 */
typedef	struct	{
	float	l;	/* longueur sur l'axe Z		*/
	float	r;	/* rayon   sur les axes X et Y	*/
} Cylinder;

/*
 * 				SPHERE
 * 				______
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Sphere 		X**2 + Y**2 + Z**2 = 1		X**2 + Y**2 + Z**2 <= 1
 */
typedef	struct	{
	float	r;	/* rayon sur les axes X, Y et Z	*/
} Sphere;

/*
 * 				TORE
 * 				____
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Tore 		(X**2+Y**2+Z**2-(R**2+r**2))**2-4*R**2*(r**2-Z**2) = 0
 *
 * avec	R = rayon exterieur
 *	r = rayon interieur
 */
typedef	struct	{
	float	ri;	/* rayon interieur 	*/
	float	ro;	/* rayon exterieur 	*/
} Torus;

/*
 *				WEDGE
 *				_____
 *
 * Primitive		Equation de la surface		Equation des domaines
 * _________		______________________		_____________________
 *
 * Coin			X = 0				0 <= Y,Z <= 1
 *			Y = 0				0 <= X,Z <= 1
 *			X = 1 - Y			0 <= Z   <= 1
 *			Z = 0				0 <= X,Y <= 1
 *			Z = 1				0 <= X,Y <= 1
 */
typedef	struct	{
	float	x;	/* taille du block sur l'axe X	*/
	float	y;	/* taille du block sur l'axe Y	*/
	float	z;	/* taille du block sur l'axe Z	*/
} Wedge;

typedef	union	{
	Block		block;
	Cardioide	cardioide;
	Cone		cone;
	Cylinder	cylinder;
	Sphere		sphere;
	Torus		torus;
	Wedge		wedge;
} Geometry_solid;

typedef	struct	{
	Type		type;		/* type de la primitive	*/
	Geometry_solid	geometry;	/* geometrie		*/
	Matrice		lsm;		/* passage Local/Scene	*/
	Position	position;	/* positionnement	*/
	Index		subdivision;	/* niveau de subdivision*/
} Solid;

typedef	struct	{
	Index		nbr;		/* nombre de solides	*/
	Solid		*ptr;		/* liste  dynamique	*/
} Solid_list;

typedef	struct	{
	char		*name;		/* nom de la scene	*/
	Solid_list	solid;		/* liste de solides	*/
} Solid_scene;

typedef	struct	{
	Index		nbr;		/* nombre de scenes	*/
	Solid_scene	*ptr;		/* liste  dynamique	*/
} Solid_scene_list;

#endif
