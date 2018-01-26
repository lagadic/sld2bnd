/************************************************************************

 TITLE		: rdstack.h

 DESCRIPTION	: Le module "rdstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des aspects de synthese (Render STACK).

 VERSION	: 1.001

 ABSTRACT	: 

 Specification de procedures.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 10/06/89

 MODIFIED BY	:

 1.001 - 10/06/89 Original.

*************************************************************************/


extern	void			fprintf_rdstack ();
extern	Render_parameters	*get_rdstack ();
extern	void			load_rdstack ();
extern	void			pop_rdstack ();
extern	void			push_rdstack ();
extern	void			swap_rdstack ();
extern	void			add_rdstack (const char* path, ... );

