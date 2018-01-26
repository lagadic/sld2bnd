/************************************************************************

 TITLE		: lex.h

 DESCRIPTION	: Le module "lex.h" contient les Macros et les Types
		  des jetons de l'analyseur lexicale "lex.c".

 VERSION	: 1-002

 ABSTRACT	: 

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 03/03/89

 MODIFIED BY	:

 1-001 - 03/03/89 Original.
 1-002 - 12/05/89 Ajout de "...is_cmd".

*************************************************************************/

#ifndef LEX_H
#define LEX_H


typedef	struct	{
	char	*ident;	/* identifateur 	*/
	Index	token;	/* code du jeton 	*/
	Byte	is_cmd;	/* debut de commande	*/
} Keyword;

extern	FILE	*lexin;		/* fichier en entree	*/
extern	FILE	*lexout;	/* fichier en sortie	*/

extern	char	infile[];	/* nom du fichier en entree	*/
extern	char	outfile[];	/* nom du fichier en sortie	*/

extern	int	yylineno;	/* numero de la ligne courante	*/
extern	int	yylength;	/* longueur du jeton courant	*/

#endif