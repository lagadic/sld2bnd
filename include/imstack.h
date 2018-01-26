/************************************************************************

 TITLE		: imstack.h

 DESCRIPTION	: Le module "imstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des images (IMage STACK).

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


extern	void			fprintf_imstack ();
extern	Image_parameters	*get_imstack ();
extern	void			load_imstack ();
extern	void			pop_imstack ();
extern	void			push_imstack ();
extern	void			swap_imstack ();
extern	void			add_imstack (const char* path, ... );

