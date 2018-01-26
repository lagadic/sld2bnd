/************************************************************************

 TITLE		: slstack.h

 DESCRIPTION	: Le module "slstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des niveaux de subdivision (Subdivision Level STACK).

 VERSION	: 1.001

 ABSTRACT	: 

 Specification de procedures.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 11/04/89

 MODIFIED BY	:

 1.001 - 11/04/89 Original.

*************************************************************************/


extern	int	*get_slstack ();
extern	void	load_slstack ();
extern	void	pop_slstack ();
extern	void	push_slstack ();
extern	void	swap_slstack ();
extern	void	add_slstack ();

