/************************************************************************

 TITLE		: rfstack.h

 DESCRIPTION	: Le module "rfstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  des drapeaux d'elimination de faces (Remove Faces STACK).

 VERSION	: 1.001

 ABSTRACT	: 

 Specification de procedures.

 ENVIRONMENT	: Compilation	- NONE
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 10/05/89

 MODIFIED BY	:

 1.001 - 10/05/89 Original.

*************************************************************************/


extern	void	fprintf_rfstack ();
extern	int	*get_rfstack ();
extern	void	load_rfstack ();
extern	void	pop_rfstack ();
extern	void	push_rfstack ();
extern	void	swap_rfstack ();
extern	void	add_rfstack ();
extern	void	sub_rfstack ();

