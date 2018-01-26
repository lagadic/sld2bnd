/************************************************************************

 TITLE		: light.h

 DESCRIPTION	: Le fichier "light.h" contient les macros et le types
		  utilises par les modeles photometriques.

 Les intensites des sources lumineuses sont comprises entre 0 et 100.
 La somme des intensites lumineuses d'une scene doit etre inferieure
 a 100 sous peine de saturation ou de surbrillance.

 Macros pour les modeles photometriques.
 Types  pour les sources lumineuses.
  
 VERSION	: 1.001

 ABSTRACT	: 

 Light		  Source lumineuse.
 Light_list	  Liste dynamique de sources lumineuses.
 Light_scene	  Sources lumineuse d'une scene.
 
 ENVIRONMENT	: Compilation	- "my.h", "graph.h".
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 24/05/88

 MODIFIED BY	:

 1.001 - 24/05/88 Original.
 1.002 - 25/01/94 define LIGHT_H + modif include <> (BA)
*************************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

#include <my.h>


/*
 * Les intensites lumineuses sont comprises entre 0 et 100.
 * Leurs valeurs sont des pourcentages. La somme des intensites lumineuses
 * d'une scene doit etre inferieure a 100 sous peine de saturation.
 */
typedef	struct	{
	unsigned	is_ponctual:1;	/* source poctuelle 	*/
	float		intensity;	/* intensite [0..100]	*/
	Vecteur		source;		/* position/direction	*/
} Light;

typedef	struct	{
	Index		nbr;		/* nombre d'elements	*/
	Light		*ptr;		/* liste dynamique	*/
} Light_list;

typedef	struct	{
	float		ambient;	/* intensite ambiante	*/
	float		back;		/* intensite du fond	*/
	Light_list	light;		/* liste des sources	*/
} Light_scene;


#endif
