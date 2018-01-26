%{
/************************************************************************

 TITLE		: gram.y

 DESCRIPTION	: Le module "gram.y" contient l'analyseur syntaxique 
		  en langage "YACC" du programme "sldbnd".

 VERSION	: 1-002

 ABSTRACT	:

 yyclearin
 yyerrok
 yyparse	  Analyseur syntaxique en langage "YACC".
 yywrap		  Reboucle  sur l'analyseur syntaxique.

 fatal	  	  Affiche un message d'erreur sur "stderr".
 warning	  Affiche un avertissement sur "stderr".

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD NP/1.
			sun		Machines SUN 3. 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 06/04/89

 MODIFIED BY	:

 1-001 - 06/04/89 Original.
 1-002 - 17/11/89 Ajout de "cardioide".
 1-003 - 10/03/94 Nettoyage sun/vax (TB)

*************************************************************************/


#include	"my.h"
#include	"arit.h"
#include	"bound.h"
#include	"lex.h"
#include	"slstack.h"

static	int	subdivision;

static	Matrice		m;
static	Position	position;
static	Vecteur		vector;

static	float	height;
static	float	length;
static	float	radius;
static	float	radiusin;
static	float	radiusout;
static	float	width;

static	Bound	bound;		/* modele surfacique	*/


yyerror(str)
char *str;
{
#ifdef	debug
	fflush(stdout);
	fprintf (stderr, "%s: %d: %s\n", infile, yylineno, str);
#endif	debug
}

yywrap()
{
	return(1);
}

/*
 * La procedure "fatal" affiche un message d'erreur fatale.
 * Entree :
 * str		Massage d'erreur a afficher sur "stderr".
 */
fatal (str)
char	*str;
{
	fprintf (stderr, "%s: %d: error %s\n", infile, yylineno, str);
	exit (1);
}

/*
 * La procedure "warning" affiche un message d'avertissement.
 * Entree :
 * str		Avertissement a afficher sur "stderr".
 */
warning (str)
char	*str;
{
	fprintf (stderr, "%s: %d: warning %s\n", infile, yylineno, str);
	exit (1);
}

%}


%union	{
	int	yyint;		/* nombre entier	*/
	float	yyfloat;	/* nombre flottant	*/
	char	*yystr;		/* identificateur	*/
}

%token		BLOCK
%token		CARDIOIDE
%token		CONE
%token		CYLINDER
%token		HEIGHT
%token		IDENT
%token		LENGTH
%token		RADIUS
%token		RADIUSIN
%token		RADIUSOUT
%token		ROTATE
%token		SCALE
%token		SPHERE
%token		SUBDIVISION
%token		TORUS
%token		TRANSLATE
%token		WEDGE
%token		WIDTH

%token	<yyint>		INT
%type	<yyint>		IDENT
%token	<yyfloat>	FLOAT
%token	<yystr>		STRING

%type	<yyfloat>	float


%%	/* debut de l'analyseur	*/

list
	: list cmd { echolex ();}
	| { echolex ();} cmd { echolex ();}
	;

cmd
	: block
	| cardioide
	| cone
	| cylinder
	| sphere
	| torus
	| wedge
	;

block
	: '(' BLOCK
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("width", WIDTH);}	width 
	{ gotolex ("height", HEIGHT);}	height 
	{ gotolex ("length", LENGTH);}	length
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Block_Bound (&bound);
		scale(&bound, width, height, length);
		move_bound(&bound, m);
                fprintf_Bound (lexout, &bound);
                free_Bound (&bound);
	}
	;

cardioide
	: '(' CARDIOIDE
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("radius", RADIUS);}	 radius
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Cardioide_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, radius);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

cone
	: '(' CONE
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("radius", RADIUS);}	 radius
	{ gotolex ("length", LENGTH);}	 length
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Cone_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

cylinder
	: '(' CYLINDER
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("radius", RADIUS);}	 radius
	{ gotolex ("length", LENGTH);}	 length
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Cylinder_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

sphere
	: '(' SPHERE
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("radius", RADIUS);}	 radius
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Sphere_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, radius);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

torus
	: '(' TORUS
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("radiusin", RADIUSIN);}	 radiusin
	{ gotolex ("radiusout", RADIUSOUT);}	 radiusout
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Torus_Bound (&bound, (Index) *get_slstack (),
			radiusin < M_EPSILON ? radiusout : radiusout/radiusin);
		scale(&bound, radiusin, radiusin, radiusin);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

wedge
	: '(' WEDGE
	{ gotolex ("subdivision", SUBDIVISION);} subdivision
	{ gotolex ("width", WIDTH);}	width 
	{ gotolex ("height", HEIGHT);}	height 
	{ gotolex ("length", LENGTH);}	length
	{ gotolex ("rotate", ROTATE);} rotate		
	{ gotolex ("scale", SCALE);} scale
	{ gotolex ("translate", TRANSLATE);} translate
	{ gotolex (")", ')');}			')'
	{
		Position_to_Matrice (&position, m);
		make_Wedge_Bound (&bound);
		scale(&bound, width, height, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
	;

height
	: '(' HEIGHT float ')'
	{
		height = $3;
	}
	| '(' HEIGHT float error
	{
		warning ("missing ')' in \"height\"");
	}
	| '(' HEIGHT error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"height\" expected");
	}
	| error
	{
		fatal ("item \"(height...)\" expected");
	}
	;

length
	: '(' LENGTH float ')'
	{
		length = $3;
	}
	| '(' LENGTH float error
	{
		warning ("missing ')' in \"length\"");
	}
	| '(' LENGTH error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"length\" expected");
	}
	| error
	{
		fatal ("item \"(length...)\" expected");
	}
	;

radius
	: '(' RADIUS float ')'
	{
		radius = $3;
	}
	| '(' RADIUS float error
	{
		warning ("missing ')' in \"radius\"");
	}
	| '(' RADIUS error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"radius\" expected");
	}
	| error
	{
		fatal ("item \"(radius...)\" expected");
	}
	;

radiusin
	: '(' RADIUSIN float ')'
	{
		radiusin = $3;
	}
	| '(' RADIUSIN float error
	{
		warning ("missing ')' in \"radiusin\"");
	}
	| '(' RADIUSIN error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"radiusin\" expected");
	}
	| error
	{
		fatal ("item \"(radiusin...)\" expected");
	}
	;

radiusout
	: '(' RADIUSOUT float ')'
	{
		radiusout = $3;
	}
	| '(' RADIUSOUT float error
	{
		warning ("missing ')' in \"radiusout\"");
	}
	| '(' RADIUSOUT error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"radiusout\" expected");
	}
	| error
	{
		fatal ("item \"(radiusout...)\" expected");
	}
	;

width
	: '(' WIDTH float ')'
	{
		width = $3;
	}
	| '(' WIDTH float error
	{
		warning ("missing ')' in \"width\"");
	}
	| '(' WIDTH error
	{
		fatal ("float expected");
	}
	| '(' error
	{
		fatal ("keyword \"width\" expected");
	}
	| error
	{
		fatal ("item \"(width...)\" expected");
	}
	;

subdivision
	: '(' SUBDIVISION INT ')'
	{
		subdivision = $3;
		load_slstack (subdivision);
	}
	| '(' SUBDIVISION INT error
	{
		warning ("missing ')' in \"subdivision\"");
	}
	| '(' SUBDIVISION error
	{
		fatal ("integer expected");
	}
	| '(' error
	{
		fatal ("keyword \"subdivision\" expected");
	}
	;

translate
	: '(' TRANSLATE vector ')'
	{
		position.translate = vector;
	}
	| '(' TRANSLATE vector error
	{
		warning ("missing ')' in \"translate\"");
	}
	;

scale
	: '(' SCALE vector ')'
	{
		position.scale = vector;
	}
	| '(' SCALE vector error
	{
		warning ("missing ')' in \"scale\"");
	}
	;

rotate
	: '(' ROTATE vector ')'
	{
		position.rotate = vector;
	}
	| '(' ROTATE vector error
	{
		warning ("missing ')' in \"rotate\"");
	}
	;

vector
	: float float float
	{
		SET_COORD3(vector, $1, $2, $3);
	}
	| error
	{
		fatal ("vector 3D [X,Y,Z] expected");
	}
	;


float
	: INT
	{
		$$ = (float) $1;
	}
	| FLOAT
	{
		$$ = $1;
	}
	;

%%	/* fin de l'analyseur	*/

