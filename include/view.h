/************************************************************************

 TITLE		: view.h

 DESCRIPTION	: Le module "view.h" contient les Macros et les types
		  des parametres de visualisation et de transformation 3D.

 VERSION	: 1-008

 ABSTRACT	: 

 Macros geometriques pour la synthese 3D.
 Types des parametres pour la visualisation.

 ENVIRONMENT	: Compilation	- "my.h", "graph.h".
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 05/01/86

 MODIFIED BY	:

 1-001 - 05/01/86 Original.
 1-002 - 12/02/87 Ajout des Macros "DEFAULT_...".
 1-004 - 01/02/88 Ajout de "Lgrc_view".
 1-005 - 18/03/88 Ajout de "Camera_...".
 1-006 - 19/04/88 Ajout de "file" a "Image_parameters".
 1-007 - 14/02/89 Transfert de "Image_parameters" dans "graph.h"
 1.003 - 25/01/94 intro de VIEW_H et modif include <>
 1.008 - 08/06/94 Ajout de "Camera".

*************************************************************************/
 
#ifndef VIEW_H
#define VIEW_H

#include <arit.h>


/*
 * Macros de numerotation des 6 plans de decoupage :
 * - Les 6 plans de clipping definissent le volume canonique 
 *   de la pyramide de vision dans lequel la scene est visible.
 * - les 6 plans ont pour equations :
 * Plan dessus	:  W = Y
 * Plan dessous	: -W = Y
 * Plan droit	:  W = X
 * Plan gauche	: -W = X
 * Plan arriere	:  W = Z
 * Plan avant	:  W = 0
 */
#define	PLANE_ABOVE	0
#define	PLANE_BELOW	1
#define	PLANE_RIGHT	2
#define	PLANE_LEFT	3
#define	PLANE_BACK	4
#define	PLANE_FRONT	5
#define	PLANE_NBR	6

/*
 * Macros de positionnement des points 4D :
 * Le positionnement d'un point 4D dans l'espace de l'observateur virtuel
 * se fait par rapport aux 6 plans de decoupage.
 * A chaque point 4D on associe 6 bits, un par plan de decoupage.
 */
#define	IS_INSIDE	0x00
#define	IS_ABOVE	0x01
#define	IS_BELOW	0x02
#define	IS_RIGHT	0x04
#define	IS_LEFT		0x08
#define	IS_BACK		0x10
#define	IS_FRONT	0x20

#define	DEFAULT_REMOVE	IS_INSIDE

#define	PARALLEL	0
#define	PERSPECTIVE	1

#define	DEFAULT_EYE	{ 0.0, 0.0, 1.0	}
#define	DEFAULT_TARGET	{ 0.0, 0.0, 0.0	}
#define	DEFAULT_FOCAL	1.0
#define	DEFAULT_ANGLE	45.0
#define	DEFAULT_TWIST	0.0
#define	DEFAULT_SPEED	0.0
#define	DEFAULT_CAMERA	{ DEFAULT_EYE,	DEFAULT_TARGET,\
			  DEFAULT_FOCAL,DEFAULT_ANGLE, DEFAULT_TWIST,\
			  DEFAULT_SPEED }

#define	DEFAULT_COP	{ 0.0, 0.0, 1.0	}
#define	DEFAULT_VRP	{ 0.0, 0.0, 0.0	}
#define	DEFAULT_VPN	{ 0.0, 0.0,-1.0	}
#define	DEFAULT_VUP	{ 0.0, 1.0, 0.0	}
#define	DEFAULT_VWD	{-1.0, 1.0,-1.0, 1.0 }
#define	DEFAULT_DEPTH	{ 0.0, 1.0	}
#define	DEFAULT_TYPE	PERSPECTIVE

#define	DEFAULT_VIEW	{ DEFAULT_TYPE,\
			  DEFAULT_COP, DEFAULT_VRP,\
			  DEFAULT_VPN, DEFAULT_VUP,\
			  DEFAULT_VWD, DEFAULT_DEPTH }

#define	DEFAULT_WC	{ 1.0, 0.0, 0.0, 0.0,\
			  0.0, 1.0, 0.0, 0.0,\
			  0.0, 0.0, 1.0, 0.0,\
			  0.0, 0.0, 0.0, 1.0 }


/*
 *			CAMERA PARAMETERS
 *			_________________
 *
 * La structure "Camera_parameters" definit les parametres de la camera.
 * eye		Position de l'oeil ou de la camera.
 * target	Position de la cible ou du point visee dans la scene.
 * focal	Distance eye-target
 * angle	Angle d'ouverture en degres.
 * twist	Angle de rotation sur l'axe de visee (eye,target) en degres.
 * speed	Vitesse sur l'axe de visee (eye,target).
 */
typedef	struct	{
	Point3f	eye;		/* position de l'observateur	*/
	Point3f	target;		/* point vise			*/
	float	focal;		/* focale de la camera		*/
	float	angle;		/* angle d'ouverture		*/
	float	twist;		/* rotation sur l'axe de visee	*/
	float	speed;		/* vitesse  sur l'axe de visee	*/
} Camera_parameters;

typedef	struct	{
	float	umin,umax;	/* bords gauche et droit	*/
	float	vmin,vmax;	/* bords inferieur et superieur */
} View_window;

typedef	struct	{
	float	front;		/* plan avant ("hither")	*/
	float	back;		/* plan arriere ("yon")		*/
} View_depth;

typedef	struct	{
	Type		type;	/* type de la  projection	*/
	Point3f		cop;	/* centre de projection		*/
	Point3f		vrp;	/* point de reference de visee	*/
	Vecteur		vpn;	/* vecteur nomal au plan	*/
	Vecteur		vup;	/* vecteur indiquant le "haut"	*/
	View_window	vwd;	/* fenetre de projection	*/
	View_depth 	depth;	/* profondeurs de decoupages	*/
} View_parameters;

typedef	struct	{
	Camera_parameters	*cpptr;	/* parametres de camera associes */
	View_parameters		*vpptr;	/* point de vue associe */
	Matrice			m;	/* matrice associee */
} Camera;

#endif
