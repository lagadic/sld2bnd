/************************************************************************

 TITLE		: graph.h

 DESCRIPTION	: Le module "graph.h" contien les Macros et les types 2D
		  graphiques en langage "C".

 VERSION	: 1-008

 ABSTRACT	: 

 Macros et types d'attributs pour le graphisme 2D.
 Macros et types geometriques pour la synthese 2D et 3D.
 Macros "SunCGI" sur "SUN". Pour plus de details voir "SunCGI Reference Manual".

 ENVIRONMENT	: Compilation	-
			"arit.h",
			"my.h",
			suncgi		Environnement SunCGI.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 05/01/86

 MODIFIED BY	:

 1-001 - 05/01/86 Original.
 1-008 - 14/02/89 Ajout de "Window_...".
 1-009 - 21/03/94 ajout de include <my.h> et de GRAPH_H

*************************************************************************/
#ifndef	GRAPH_H
#define	GRAPH_H

#include	<arit.h>

#define	SOLID		0
#define	DOTTED		1
#define	BORDER		2
#define	SHORT_DASHED	3
#define	LONG_DASHED	4
#define	DOT_DASHED	5
#define	CENTER_LINE	6
#define	SPACE_DASHED	7
#define	LINE_STYLE_NBR	8

#define	THIN		0
#define	THICK		1
#define	LINE_WIDTH_NBR	2

#define	DEFAULT_LINE	{ SOLID, THIN, 0 }
#define	DEFAULT_IMAGE	{ "", {0, 0}, {512, 512} }

/*----------------------------------------------------------------*/
/* Parametres pour sortie au format FIG */
/*
	#define	XMINSCREEN	0
	#define	YMINSCREEN	0
	#define	XMAXSCREEN	1280
	#define	YMAXSCREEN	1024

	#define	XMINCOORD	0
	#define	YMINCOORD	0
	#define	XMAXCOORD	512
	#define	YMAXCOORD	512

	#define	XMAXDIV2	256
	#define	YMAXDIV2	256

	#define	POLYGON_NBR	256
	#define	WINDOW_NBR	4

	#define	DEFAULT_WINDOW	{\
		-1,\
		"",\
		{ XMINCOORD, YMINCOORD },\
		{ XMAXCOORD, YMAXCOORD }\
	}
*/

/*-----------------------------------------------------------------*/
/* Parametres pour sortie Suncgi */

#define	XMINSCREEN	0	/* Macros geometriques	*/
#define	YMINSCREEN	0
#define	XMAXSCREEN	1280
#define	YMAXSCREEN	1024

#define	XMINCOORD	0
#define	YMINCOORD	0
#define	XMAXCOORD	32767
#define	YMAXCOORD	32767

#define	XMAXDIV2	16383.5
#define	YMAXDIV2	16383.5

#define	POLYGON_NBR	256
#define	WINDOW_NBR	4

#define	DEFAULT_WINDOW	{\
	-1,\
	"",\
	{ XMINCOORD, YMINCOORD },\
	{ XMAXCOORD, YMAXCOORD }\
}
/*--------------------------------------------------------------------*/


#define	RGB_NBR		256

typedef struct	{
	Byte	r[RGB_NBR];
	Byte	g[RGB_NBR];
	Byte	b[RGB_NBR];
	Index	nbr;		/* taille des listes 	*/
} RGB_list;

typedef	struct	{
	Index	color;
	Byte	style;
	Byte	width;
} Line;

typedef	struct	{
	Point2s	begin;
	Point2s	end;
} Line2s;

typedef	struct	{
	Index	x, y;
} Pixel;

typedef	struct	{
	Index	nbr;
	Point2s	*ptr;
} Polygon2s;

typedef	struct	{
	Index	nbr;
	Point3f	*ptr;
} Polygon3f;

typedef	struct	{
	Pixel	origin;
	Pixel	corner;
} Rectangle;

typedef	struct	{
	Byte	r, g, b;
} RGB;

typedef	struct	{		/* run-length coding	*/
	char	data;
	Index	length;
} Run_length;

typedef	struct	{
	char	filename[NAMESIZE];	/* nom du fichier de stockage	*/
	Pixel	origin;			/* origine en Bas,    a Gauche	*/
	Pixel	size;			/* taille  en Largeur, Hauteur	*/
} Image_parameters;

typedef	struct	{
	int	id;		/* identificateur	*/
	char	name[NAMESIZE];	/* nom de la fenetre	*/
	Point2i	origin;		/* origine 		*/
	Point2i	size;		/* taille		*/
} Window_parameters;

#endif
