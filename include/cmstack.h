/************************************************************************

 TITLE		: cmstack.h

 DESCRIPTION	: Le module "cmstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des cameras (CaMera STACK).

 VERSION	: 1.001

 ABSTRACT	: 

 Specification de procedures.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 20/05/89

 MODIFIED BY	:

 1.001 - 20/05/89 Original.

*************************************************************************/


extern	void			fprintf_cmstack ();
extern	Camera_parameters	*get_cmstack ();
extern	void			load_cmstack ();
extern	void			pop_cmstack ();
extern	void			push_cmstack ();
extern	void			swap_cmstack ();
extern	void			add_cmstack (const char* path, ... );

