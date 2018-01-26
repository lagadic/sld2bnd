/************************************************************************

 TITLE		: shade.h

 DESCRIPTION	: Le module "shade.h" contient les macros et les types
		  utilises par les algorithmes de calcul d'eclairement
		  en synthese d'image par balayage ("scan-line").

 VERSION	: 1-001

 ABSTRACT	: 

 Macros de mise a l'echelle.
 Macros de courbes de niveaux.
 Macros d'affichage.

 ENVIRONMENT	: Compilation	-
			csg		Modelisation solide CSG.
			gould		Machines GOULD.
			sun		Machines SUN 3.
			sun4		Machines SUN 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 01/12/89

 MODIFIED BY	:

 1-001 - 01/12/89 Original.
 1.002 - 25/01/94 intro de SHADE_H (BA)
*************************************************************************/


#ifndef SHADE_H
#define SHADE_H

#define LSHIFT		16	/* Macros de mise a l'echelle	*/

#define	CONTOUR_NULL	0	/* Macros pour les contours	*/
#define	CONTOUR_MIN	1
#define	CONTOUR_MAX	254

#define	PLOT		(~0)	/* Macros d'affichage		*/
#define	UNPLOT		0

#endif


