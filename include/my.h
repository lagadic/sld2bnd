/************************************************************************
 
 TITLE		: my.h

 DESCRIPTION	: Module de Macros et de Types de bases en langage "C".

 VERSION	: 1.005

 ABSTACT	: Macros d'entrees/sorties, arithmetiques.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 01/12/86

 MODIFIED BY	:

 1.001 - 01/12/86 Original.
 1.002 - 13/05/87 Ajout de "MIN" et "MAX".
 1.003 - 07/09/87 Ajout des "STD...".
 1.004 - 10/10/87 Tranfert de "ABS" du fichier "arit.h".
 1.005 - 21/11/87 Tranfert des "M_..." du fichier "arit.h".
 1.006 - 25/01/94 define MY_H + virer option gould et vax (BA)

*************************************************************************/

#ifndef MY_H
#define MY_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef	NULL
#define	NULL		0
#endif
#ifndef	FALSE
#define	FALSE		0
#endif
#ifndef	TRUE
#define	TRUE		1
#endif

#ifndef	STDIN
#define	STDIN		0
#endif
#ifndef	STDOUT
#define	STDOUT		1
#endif
#ifndef	STDERR
#define	STDERR		2
#endif

#define	BUFSIZE		1024
#define	NAMESIZE	80
#define	LINESIZE	256

#define	M_EPSILON	1E-06

#define	ABS(X)		(((X) < 0)   ? -(X) : (X))
#define	FABS(X)		(((X) < 0.0) ? -(X) : (X))
#define	MAX(A,B)	(((A) > (B)) ? (A) : (B))
#define	MAX3(A,B,C)	(MAX(MAX(A,B),C))
#define	MIN(A,B)	(((A) < (B)) ? (A) : (B))
#define	MIN3(A,B,C)	(MIN(MIN(A,B),C))

#define	MIN_MAX(M,MIN,MAX)	if ((M) < (MIN)) (MIN) = (M);\
			 	else if ((M) > (MAX)) (MAX) = (M) 

#define	TWO_POWER(P)	(((P) > 0) ? 1 << (P) : 1)
#define	SWAP(A,B,T)	{ (T) = (A); (A) = (B); (B) = (T); }

typedef	unsigned char	Byte;
typedef	unsigned short	Index;
typedef	char		Type;


#endif


