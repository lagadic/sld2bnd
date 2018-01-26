/************************************************************************

 TITLE		: arit.h

 DESCRIPTION	: Le module "arit.h" contient les Macros arithmetiques.

 VERSION	: 1.006

 ABSTRACT	:

 Macros arithmetiques
 Macros d'affectation.
 Types  geometriques.
		  
 ENVIRONMENT	: Compilation	- "my.h"
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 08/08/86

 MODIFIED BY	:

 1.001 - 08/08/86 Original.
 1.005 - 25/07/88 Ajout de "IDENTITY_...".
 1.006 - 16/12/88 Ajout de "point_3D_...".
 1.007 - 25/01/94 Prototype de fonctions + define ARIT_H + REGISTER (BA)

*************************************************************************/

#ifndef ARIT_H
#define ARIT_H


#include <register.h>
#include <my.h>


#define	ADD_COORD2(r,a,b)	{ (r).x = (a).x + (b).x;\
				  (r).y = (a).y + (b).y; }

#define	ADD_COORD3(r,a,b)	{ (r).x = (a).x + (b).x;\
				  (r).y = (a).y + (b).y;\
				  (r).z = (a).z + (b).z; }

#define	INC_COORD2(r,a)		{ (r).x += (a).x; (r).y += (a).y; }

#define	INC_COORD3(r,a)		{ (r).x += (a).x; (r).y += (a).y;\
				  (r).z += (a).z; }

#define	CROSS_PRODUCT(r,a,b)	{ (r).x = (a).y * (b).z - (a).z * (b).y;\
				  (r).y = (a).z * (b).x - (a).x * (b).z;\
				  (r).z = (a).x * (b).y - (a).y * (b).x; }

#define	DIF_COORD2(r,a,b)	{ (r).x = (a).x - (b).x;\
				  (r).y = (a).y - (b).y; }

#define	DIF_COORD3(r,a,b)	{ (r).x = (a).x - (b).x;\
				  (r).y = (a).y - (b).y;\
				  (r).z = (a).z - (b).z; }

#define	DOT_PRODUCT(a,b)	( ((a).x * (b).x) +\
				  ((a).y * (b).y) +\
				  ((a).z * (b).z) )

#define	LENGTH3(a)		(sqrt((double) DOT_PRODUCT((a),(a))))

#define	MID_COORD3(r,a,b)	{ (r).x = ((a).x + (b).x) / 2.0;\
				  (r).y = ((a).y + (b).y) / 2.0;\
				  (r).z = ((a).z + (b).z) / 2.0; }

#define	MUL_COORD3(r,a,b,c)	{ (r).x *= (a); (r).y *= (b); (r).z *= (c); }

#define	PAR_COORD3(r,t,a,b)	{ (r).x = ((b).x - (a).x) * (t) + (a).x;\
				  (r).y = ((b).y - (a).y) * (t) + (a).y;\
				  (r).z = ((b).z - (a).z) * (t) + (a).z; }

#define	SET_COORD2(r,a,b)	{ (r).x = (a); (r).y = (b); }

#define	SET_COORD3(r,a,b,c)	{ (r).x = (a); (r).y = (b); (r).z = (c); }

#define	SUB_COORD2(r,a)		{ (r).x -= (a).x; (r).y -= (a).y; }

#define	SUB_COORD3(r,a)		{ (r).x -= (a).x; (r).y -= (a).y;\
				  (r).z -= (a).z; }

#define	COORD3_COL(x,y,z,m,i)	( ((x) * (m)[0][i]) +\
				  ((y) * (m)[1][i]) +\
				  ((z) * (m)[2][i]) +\
				  	 (m)[3][i] )

#define	COORD4_COL(x,y,z,w,m,i)	( ((x) * (m)[0][i]) +\
				  ((y) * (m)[1][i]) +\
				  ((z) * (m)[2][i]) +\
				  ((w) * (m)[3][i]) )

#define	M_POLY1(x,a,b)		((a) * (x) +  (b))
#define	M_POLY2(x,a,b,c)	(M_POLY1((x),(a),(b)) * (x) + (c))
#define	M_POLY3(x,a,b,c,d)	(M_POLY2((x),(a),(b),(c)) * (x) + (d))


typedef	struct	{
	int	x, y;
} Point2i;

typedef	struct	{
	short	x, y;
} Point2s;

typedef	struct	{
	float	x, y;
} Point2f;

typedef	struct	{
	int	x, y, z;
} Point3i;

typedef	struct	{
	float	x, y, z;
} Point3f;

typedef	struct	{
	float	x,y,z,w;
} Point4f;

typedef	struct	{	
	float	x,y,z;
} Vecteur;

/*
 *				MATRIX
 *				______
 *
 * Matrice homogene ou non.
 *				|   Rotation  | 0 |
 * Matrice non homogene = 	|     3x3     | 0 |
 *				|-------------| 0 |
 *				| Translation | 1 |
 */
typedef	float	Matrice[4][4];

#define	IDENTITY_MATRIX		{	1.0,	0.0,	0.0,	0.0,\
					0.0,	1.0,	0.0,	0.0,\
					0.0,	0.0,	1.0,	0.0,\
					0.0,	0.0,	0.0,	1.0	}


/*
 * 				POSITION
 *				________
 * 
 * La structure "Position" definit le positionnement d'un objet.
 * Matrice de positionnement = R.S.T
 * avec R = Rx.Ry.Rz	Matrice de rotation autour des axes (Ox,Oy,Oz),
 *			Les angles sont donnes en degres;
 *	S = Sx.Sy.Sz	Matrice d'homothetie sur les axes;
 *	T = Tx.Ty.Tz	Matrice de translation sur les axes.
 */

typedef	struct	{
	Vecteur		rotate;		/* vecteur rotation	*/
	Vecteur		scale;		/* vecteur homothetie	*/
	Vecteur		translate;	/* vecteur translation	*/
} Position;

#define	IDENTITY_ROTATE		{	0.0,	0.0,	0.0	}	
#define	IDENTITY_SCALE		{	1.0,	1.0,	1.0	}
#define	IDENTITY_TRANSLATE	{	0.0,	0.0,	0.0	}

#define	IDENTITY_POSITION	{	IDENTITY_ROTATE,\
					IDENTITY_SCALE,\
					IDENTITY_TRANSLATE	}

/* prototypes des fonctions definie dans arit.c */
/* -------------------------------------------- */

extern	void	fprintf_matrix (
#ifdef PROTOTYPE
	REGISTER	FILE	*	/* fp */,
	REGISTER	Matrice		/* m */
#endif
);


extern void	ident_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* m */
#endif
);


extern void	premult_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* a */,
	REGISTER Matrice		/* b */
#endif
);


extern void	premult3_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* a */,
	REGISTER Matrice		/* b */
#endif
);


extern void	prescale_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice 	/* m */,
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	pretrans_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice 	/* m */,
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	postleft_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* m */,
		 char           /* axis */
#endif
);


extern void	postmult_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* a */,
	REGISTER Matrice		/* b */
#endif
);


extern void	postmult3_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* a */,
	REGISTER Matrice		/* b */
#endif
);


extern void	postscale_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* m */,
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	posttrans_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice		/* m */,
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	transpose_matrix (
#ifdef PROTOTYPE
	REGISTER Matrice 	/* m */
#endif
);




extern float	cosin_to_angle (
#ifdef PROTOTYPE
	REGISTER float 		/* ca */,
	REGISTER float 		/* sa */
#endif
);


extern void	cosin_to_lut (
#ifdef PROTOTYPE
		 Index          /* level */,
	REGISTER float  *	/* coslut */,
	REGISTER float  *	/* sinlut */
#endif
);


extern float	norm_vector (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	plane_norme (
#ifdef PROTOTYPE
		 Vecteur  *	/* np */,
		 Point3f *	/* ap */,
		 Point3f *	/* bp */,
		 Point3f *	/* cp */
#endif
);


extern void	point_matrix (
#ifdef PROTOTYPE
	REGISTER Point4f *	/* p4 */,
	REGISTER Point3f *	/* p3 */,
	REGISTER Matrice        	/* m */
#endif
);


extern void	point_3D_3D (
#ifdef PROTOTYPE
	REGISTER Point3f *	/* ip */,
		 int            /* size */,
	REGISTER Matrice        	/* m */,
	REGISTER Point3f *	/* op */
#endif
);


extern void	point_3D_4D (
#ifdef PROTOTYPE
	REGISTER Point3f *	/* p3 */,
		 int            /* size */,
	REGISTER Matrice        	/* m */,
	REGISTER Point4f *	/* p4 */
#endif
);


extern void	rotate_vector (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */,
		 float   	/* a */,
		 Vecteur *	/* axis */
#endif
);


extern void	upright_vector (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */,
	REGISTER Vecteur *	/* up */
#endif
);




extern void	Matrice_to_Position (
#ifdef PROTOTYPE
		 Matrice         /* m */,
		 Position *	/* pp */
#endif
);


extern void	Matrice_to_Rotate (
#ifdef PROTOTYPE
	REGISTER Matrice         /* m */,
	REGISTER Vecteur *	/* vp */
#endif
);


extern void	Position_to_Matrice (
#ifdef PROTOTYPE
	REGISTER Position *	/* pp */,
	REGISTER Matrice         /* m */
#endif
);


extern void	Rotate_to_Matrice (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */,
	REGISTER Matrice         /* m */
#endif
);


extern void	Rotaxis_to_Matrice (
#ifdef PROTOTYPE
		 float          /* a */,
		 Vecteur *	/* axis */,
	REGISTER Matrice         /* m */
#endif
);


extern void	Rotrans_to_Matrice (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* rp */,
	REGISTER Vecteur *	/* tp */,
	REGISTER Matrice         /* m */
#endif
);


extern void	Scale_to_Matrice (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */,
	REGISTER Matrice         /* m */
#endif
);


extern void	Translate_to_Matrice (
#ifdef PROTOTYPE
	REGISTER Vecteur *	/* vp */,
	REGISTER Matrice         /* m */
#endif
);


#endif


