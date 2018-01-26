/************************************************************************

 TITLE		: tmstack.h

 DESCRIPTION	: Le module "tmstack.h" contient les macros, les types et
		  les specifications des procedures de gestion de la pile
		  de matrices de transformation (Transformation Matrice STACK).

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


extern	Matrice	*get_tmstack ();
extern	void	load_tmstack ();
extern	void	pop_tmstack ();
extern	void	push_tmstack ();
extern	void	swap_tmstack ();

extern	void	postmult_tmstack ();
extern	void	postrotate_tmstack ();
extern	void	postscale_tmstack ();
extern	void	posttranslate_tmstack ();
extern	void	premult_tmstack ();
extern	void	prerotate_tmstack ();
extern	void	prescale_tmstack ();
extern	void	pretranslate_tmstack ();

