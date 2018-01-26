/************************************************************************

 TITLE		: vwstack.h

 DESCRIPTION	: Le module "vwstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des points de vue (VieW STACK).

 VERSION	: 1.001

 ABSTRACT	: 

 Specification de procedures.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 17/05/89

 MODIFIED BY	:

 1.001 - 17/05/89 Original.

*************************************************************************/


extern	void		fprintf_vwstack ();
extern	View_parameters	*get_vwstack ();
extern	void		load_vwstack ();
extern	void		pop_vwstack ();
extern	void		push_vwstack ();
extern	void		swap_vwstack ();
extern	void		add_vwstack (const char* path, ... );

