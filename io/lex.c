/************************************************************************

 TITLE		: lex.c

 DESCRIPTION	: Le module "lex.c" contient les procedures de gestion
      de l'analyse lexicale de l'analyseur lexicale "lex"
      d'un fichier source dont la grammaire possede
      les symboles terminaux suivants (ecrit en "LEX", UNIX) :

 D	[0-9]			chiffe
 S	[+-]			signe
 L	[a-zA-Z_]		lettre
 E	[Ee][+-]?{D}+		exposant

 \/\*([^*]|\*[^/])*\*\/		commentaire
 \"(\\.|[^\\"])*\"		chaine de caracteres
 {L}({L}|{D})*			identificateur
 {S}?{D}+			nombre entier
 {S}?{D}+{E}?			nombre flottant
 {S}?{D}*"."{D}+({E})?		nombre flottant
 {S}?{D}+"."{D}*({E})?		nombre flottant

 Avant usage, faire preceder les procedures d'un appel a "open_lex".
 Apres usage, faire suivre   les procedures d'un appel a "close_lex".

 Avant usage, faire preceder les procedures d'un appel a "open_lexio".
 Apres usage, faire suivre   les procedures d'un appel a "close_source".

 Pour plus de renseignements voir :

 "Compilers: Principles, Techniques, and Tools",
 ALFRED V. AHO, RAVI SETHI, JEFFREY D. ULLMAN,
 ADDISON-WESLEY PUBLISHING COMPANY. pp 89-92.

 "The Cost of Lexical Analysis",
 W. M. WAITE, SOFTWARE-PRATICE AND EXPERIENCE,
 VOL. 16(5), 473-488 (MAY 1986).

 "The Automatic Generation of Fast Lexical Analysers"
 V. P. HEURING, SOFTWARE-PRATICE AND EXPERIENCE,
 VOL. 16(9), 801-808 (SEPTEMBER 1986).

 VERSION	: 1-004

 ABSTRACT	:

 yylength	  Longueur de la chaine "yytext".
 yylineno	  Numero de la ligne courante.
 yycolumno	  Numero de la colonne du jeton courant.
 yyline	  	  Pointeur du premier caractere de la ligne courante.
 yyecho	  	  Indique si le mode echo est en action.
 yyechosptr  	  Pointeur du premier caractere a afficher si yyecho = TRUE.
 yylevel  	  Niveau de parenthesage.
 yysptr		  Pointeur du caractere courant dans le buffer d'entree.
 yytext		  Pointeur du premier caractere de la chaine reconnue.
      Note: "yytext" est a consomme juste apres l'appel a "lex"
      car le prochain appel a "lex" va detruire son contenu.

 ECHO		  Affiche  le caractere courant de l'analyseur.

 open_lex	  Alloue et initialise les variables utilisees par l'analyseur.
 close_lex	  Libere les variables utilisees par l'analyseur.
 yylex		  Analyseur lexical.

 echolex	  Analyseur lexical avec echo.
 gotolex	  Analyseur lexical avec saut.
 unlex		  Recule la tete de lecture devant le dernier jeton.

 open_lexio	  Alloue et initialise les variables utilisees par l'analyseur.
 close_lexio	  Libere les variables utilisees par l'analyseur.

 next_source	  Lit un nouveau buffer sur le fichier source.

 count		  Calcule la distance graphique entre "yysptr" et "yytext".

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 23/03/88

 MODIFIED BY	:

 1-001 - 23/03/88 Original.
 1-002 - 18/04/88 Ajout de "echolex" et def "unlex".
 1-003 - 08/10/88 Ajout de la pile "err_stack".
 1-004 - 03/03/89 Retrait de "...err...".
 1.005 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/


#include <ctype.h>
#include "my.h"

#include "y.tab.h"

static	void	count ();
static	void	next_source ();


/* Codes des symboles terminaux	*/

#define	NULT		0	/* caractere non valide	*/
#define	EOBT		1	/* fin de buffer	*/
#define	EOFT		2	/* fin de fichier	*/
#define	EOLT		3	/* fin de ligne		*/
#define	BRIT		4	/* parenthese ouvrante	*/
#define	BROT		5	/* parenthese fermante	*/
#define	CMTT		6	/* commentaire		*/
#define	IDNT		7	/* identificateur	*/
#define	INTT		8	/* nombre entier	*/
#define	FPTT		9	/* nombre flottant	*/
#define	SGNT		10	/* signe +/-		*/
#define	SPCT		11	/* caractere blanc	*/
#define	STGT		12	/* caractere de chaine	*/
#define	NBRT		13	/* nombre de codes	*/

/* Drapeaux des caracteres	*/

#define	_NULT		0x00	/* caractere non valide	*/
#define	_CMTT		0x01	/* commentaire		*/
#define	_FPTT		0x02	/* nombre flottant	*/
#define	_IDNT		0x04	/* identificateur	*/
#define	_INTT		0x08	/* nombre entier	*/
#define	_SGNT		0x10	/* signe +/-		*/
#define	_STGT		0x20	/* caractere de chaine	*/

/* Caracteres sentinelles	*/

#define	ASCII_NBR	128	/* nombre de codes ASCII*/

#ifndef EOB
#define	EOB		(-2)	/* fin de buffer	*/
#endif
#ifndef EOF
#define	EOF		(-1)	/* fin de fichier	*/
#endif
#ifndef EOL
#define	EOL		10	/* fin de ligne		*/
#endif

#define	CHAR_NBR	130	/* nombre de caracteres	*/

/* Tests des drapeaux		*/

#define	isnult(c)	(scantbl[c] == _NULT)
#define	iscmtt(c)	(scantbl[c]  & _CMTT)
#define	isfptt(c)	(scantbl[c]  & _FPTT)
#define	isidnt(c)	(scantbl[c]  & _IDNT)
#define	isintt(c)	(scantbl[c]  & _INTT)
#define	issgnt(c)	(scantbl[c]  & _SGNT)
#define	isstgt(c)	(scantbl[c]  & _STGT)


FILE	*lexin	;//= {stdin};	/* fichier en entree	*/
FILE	*lexout	;//= {stdout};	/* fichier en sortie	*/

char	infile[NAMESIZE]  = "<stdin>";	/* nom du fichier en entree	*/
char	outfile[NAMESIZE] = "<stdout>";	/* nom du fichier en sortie	*/

static int	fdin  = STDIN;	/* descripteur de fichier en entree	*/
static int	fdout = STDOUT;	/* descripteur de fichier en sortie	*/

char	*yytext   = NULL;
int	yylength  = 0;
int	yylineno  = 1;
int	yycolumno = 0;

static	int	yyecho	    = FALSE;
static	char	*yyechosptr = NULL;
static	int	yylevel	    = 0;

static	char	*yysptr;	/* tete de lecture de la ligne courante	*/
static	char	*yyline;	/* debut de la ligne courante		*/
static	char	*lastline;	/* derniere ligne du buffer d'entree	*/

static	Byte	*chtbl;		/* premiers caracteres des terminaux	*/
static	Byte	*scantbl;	/* caracteres suivants des terminaux	*/


/*
 * La procedure "open_lex" alloue et initialise les variables utilisees
 * par l'analyseur lexical "lex".
 */
open_lex ()
{
  static	 char	proc_name[] = "open_lex";

  register int	i;

  if ((chtbl   = (Byte *) malloc (CHAR_NBR * sizeof (Byte))) == NULL
  ||  (scantbl = (Byte *) malloc (CHAR_NBR * sizeof (Byte))) == NULL) {
    perror (proc_name);
    exit (1);
  }
  chtbl   += 2;	/* 2 sentinelles non affichables	*/
  scantbl += 2;

  /* initialise les premiers caracteres des symboles terminaux	*/

  for (i = 0; i < ASCII_NBR; i++) {
    if (isalpha(i))		chtbl[i] = IDNT;
    else if (isdigit(i))	chtbl[i] = INTT;
    else if (isspace(i))	chtbl[i] = SPCT;
    else switch (i) {
      case '"' :	chtbl[i] = STGT; break;
      case '(' :	chtbl[i] = BRIT; break;
      case ')' :	chtbl[i] = BROT; break;
      case '+' :
      case '-' :	chtbl[i] = SGNT; break;
      case '.' :	chtbl[i] = FPTT; break;
      case '/' :	chtbl[i] = CMTT; break;
      case '_' :	chtbl[i] = IDNT; break;
      default	 :	chtbl[i] = NULT; break;
    }
  }

  /* Initialise les sentinelles comme des terminaux.		*/

  chtbl[EOB] = EOBT;
  chtbl[EOF] = EOFT;
  chtbl[EOL] = EOLT;

  /* Initialise les caracteres suivants des symboles terminaux.	*/

  for (i = 0; i < ASCII_NBR; i++) {
    if (isalpha(i))		scantbl[i] = _CMTT|_IDNT|_STGT;
    else if (isdigit(i))	scantbl[i] = _CMTT|_IDNT|_INTT|_STGT;
    else switch (i) {
      case '"' :	scantbl[i] = _CMTT; break;
      case '+' :
      case '-' :	scantbl[i] = _CMTT|_SGNT|_STGT; break;
      case '.' :	scantbl[i] = _CMTT|_FPTT|_STGT; break;
      case '/' :	scantbl[i] = _STGT; break;
      case '_' :	scantbl[i] = _CMTT|_IDNT|_STGT; break;
      default  :	scantbl[i] = _CMTT|_STGT; break;
    }
  }

  /* Initialise les sentinelles comme des terminaux.		*/

  scantbl[EOB] = _NULT;
  scantbl[EOF] = _NULT;
  scantbl[EOL] = _NULT;
}

/*
 * La procedure "close_lex" libere les variables utilisees
 * par l'analyseur lexical "lex".
 */
close_lex ()
{
  free ((char *) (chtbl   - 2));	/* voir "open_lex" pour "- 2"	*/
  free ((char *) (scantbl - 2));
}


#define	ECHO	printf ("%c", *(yysptr))
#define	CURC	(*yysptr)	/* caractere courant	*/
#define	NEXTC	(*(yysptr+1))	/* caractere suivant	*/
#define	PREVC	(*(yysptr-1))	/* caractere precedent	*/


/*
 * La procedure "yylex" contient l'analyseur lexical.
 * Note :
 * La tete de lecture (yysptr) n'est pas systematiquement avancee apres lecture.
 * Le caractere courant est celui sous la tete de lecture.
 * Ainsi on accede de maniere symetrique aux caracteres precedent et suivant.
 * Sortie :
 *		Code du symbole terminale analyse.
 */
yylex ()
{
lex_loop :

  for (; chtbl[CURC] == SPCT; yysptr++);	/* saute les espaces	*/

  switch (chtbl[CURC]) {

  case NULT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    return (*yytext);
    break;
  case EOBT	:
    next_source ();
    goto lex_loop;
    break;
  case EOFT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    return (0);
    break;
  case EOLT	:
    if (yysptr == lastline) next_source ();
    else	yysptr++;
    yylineno++;
    yyline = yysptr;
    goto lex_loop;
    break;
  case BRIT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    yylevel++;
    return (*yytext);
    break;
  case BROT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    yylevel--;
    return (*yytext);
    break;
  case CMTT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    if (CURC != '*')
      return (*yytext);
    yysptr++;
lex_comment :
    for (; iscmtt(CURC); yysptr++);
    switch (chtbl[CURC]) {
    case EOBT	:
      next_source ();
      goto lex_comment;
      break;
    case EOFT	:
      fatal ("Unexpected EOF in comment");
      return (0);
      break;
    case EOLT	:
      if (yysptr == lastline) next_source ();
      else	yysptr++;
      yylineno++;
      yyline = yysptr;
      goto lex_comment;
      break;
    case CMTT	:
      if (PREVC == '*') {	/* veritable fin	*/
        yysptr++;
        goto lex_loop;
      }
      yysptr++;		/* pseudo fin 		*/
      goto lex_comment;
      break;
    }
    break;
  case IDNT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    for (; isidnt(CURC); yysptr++);
    yylength = yysptr - yytext;
    yylval.yystr = yytext;
    {
      int	t = get_symbol (yytext, yylength);

      if (t == 0)	return (IDENT);
      else		return (t);
    }
    break;
  case INTT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
lex_int_part :
    yylval.yyint  = (int) (CURC - '0');
    yysptr++;
    for (; isintt(CURC); yysptr++)
      yylval.yyint = yylval.yyint * 10 + (int) (CURC - '0');
    switch (CURC) {
    case '.'	:	/* lecture fraction	*/
lex_float_part :
      yysptr++;
      for (; isintt(CURC); yysptr++);
      if (CURC != 'E' && CURC != 'e') {
        yylval.yyfloat = (float) atof (yytext);
        return (FLOAT);
      }
    case 'E'	:	/* lecture exposant	*/
    case 'e'	:
      yysptr++;
      if (isintt(CURC))
        yysptr++;
      else if (issgnt(CURC) && isintt(NEXTC))
        yysptr +=2;
      else {
        yysptr--;
        yylval.yyfloat = (float) atof (yytext);
        return (FLOAT);
      }
      for (; isintt(CURC); yysptr++);
      yylval.yyfloat = (float) atof (yytext);
      return (FLOAT);
      break;
    default		:
      if (*yytext == '-')
        yylval.yyint = - yylval.yyint;
      return (INT);
      break;
    }
    break;
  case FPTT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    if (! isintt(CURC)) 	/* pas de fraction	*/
      return (*yytext);
    goto lex_float_part;
    break;
  case SGNT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
    if (isintt(CURC))
      goto lex_int_part;
    if (isfptt(CURC) && isintt(NEXTC))
      goto lex_float_part;
    return (*yytext);
    break;
  case STGT	:
    yytext = yysptr;	/* sauvegarde le jeton	*/
    yysptr++;
lex_string :
    for (; isstgt(CURC); yysptr++);
    switch (chtbl[CURC]) {
    case EOBT	:
      next_source ();
      goto lex_string;
      break;
    case EOFT	:
      fatal ("Unexpected EOF in string or char constant");
      return ('\n');
      break;
    case EOLT	:
      fatal ("Newline in string or char constant");
      return ('\n');
      break;
    case STGT	:
      if (PREVC != '\\') {	/* veritable fin	*/
        yytext++;
        yylength = yysptr - yytext;
        yysptr++;
        yylval.yystr = yytext;
        return (STRING);
      }
      yysptr++;		/* pseudo fin 		*/
      goto lex_string;
      break;
    }
    break;
  default		:
    break;
  }
  return (0);
}

/*
 * La procedure "echolex" boucle sur l'analyse lexicale avec echo
 * jusqu'a une occurence "( keyword..." ou keyword est un mot cle pouvant
 * debuter une commande, c'est-a-dire appartenant au tableau "cmd_tbl".
 */
void echolex ()
{
  char		errmess[LINESIZE];
  register int	level = yylevel;
  register int	t;

echo_loop :

  yyecho = FALSE;
  if ((t = yylex ()) == 0) {
    unlex ();
    return;
  }
  if (t != '(') {
    fatal ("item \"(keyword...)\" expected");
    goto echo_loop;
  }
  if ((t = yylex ()) == 0) {
    fatal ("item \"(keyword...)\" expected");
    unlex ();
    return;
  }
  if (get_cmd ()) {
    yysptr = --yytext;
    *yytext = '(';
    yylevel--;
    return;
  }

  fprintf (lexout, "\n(");
  yyecho = TRUE;
  yyechosptr = yytext;

  while (yylevel > level) {
    if (yylex () == 0) {
      warning ("missing ')' for an unknown command");
      fwrite (yyechosptr, yysptr - yyechosptr, sizeof(char),
        lexout);
      yyecho = FALSE;
      unlex ();
      return;
    }
  }
  fwrite (yyechosptr, yysptr - yyechosptr, sizeof(char), lexout);
  fprintf (lexout, "\n");
  yyecho = FALSE;
  goto echo_loop;
}

/*
 * La procedure "gotolex" boucle sur l'analyse lexicale
 * jusqu'a l'occurence "( keyword..." ou keyword est le mot cle cherche.
 * Entree :
 * str		Mot cle a rechercher.
 * token	Jeton du mot cle a rechercher.
 */
void gotolex (str, token)
char	*str;
int	token;
{
  char		errmess[LINESIZE];
  register int	level = yylevel;
  register int	t;

goto_loop :

  if ((t = yylex ()) == 0) {
    sprintf (errmess, "string \"%s\" expected", str);
    fatal (errmess);
    unlex ();
    return;
  }
  if (t == token) {
    unlex ();
    return;
  }
  if (t != '(') {
    sprintf (errmess, "string \"%s\" expected", str);
    fatal (errmess);
    goto goto_loop;
  }
  if ((t = yylex ()) == 0) {
    sprintf (errmess, "string \"%s\" expected", str);
    fatal (errmess);
    unlex ();
    return;
  }
  if (t == token) {
    yysptr = --yytext;
    *yytext = '(';
    yylevel--;
    return;
  }

  while (yylevel > level) {
    if (yylex () == 0) {
      warning ("missing ')' for an unknown item");
      unlex ();
      return;
    }
  }
  goto goto_loop;
}

/*
 * La procedure "unlex" recule la tete de lecture devant le dernier jeton.
 */
unlex ()
{
  yysptr = yytext;
}


#undef	BUFSIZ
#undef	BUFSIZE
#undef	LINESIZE
#undef	TEXTSIZE

#define	BUFSIZ		1024
#define	BUFSIZE		(BUFSIZ << 2)	/* taille maximum pour "pipe"	*/
#define	LINESIZE	(BUFSIZ-1)
#define	TEXTSIZE	(1 + LINESIZE + BUFSIZE + 1)


static	int	fdi;		/* descripteur du fichier source	*/
static	int	fdo;		/* descripteur du fichier objet		*/
static	char	*botbuf;	/* fond	  du buffer d'entree du fichier	*/
static	char	*buf;		/* base   du buffer d'entree du fichier	*/
static	char	*topbuf;	/* sommet du buffer d'entree du fichier	*/


/*
 * La procedure "open_lexio" alloue et initialise les variables utilisees
 * pour la gestion des entrees/sorties du programme source.
 */
open_lexio ()
{
  static	char	proc_name[] = "open_lexio";

  if ((botbuf = (char *) malloc (TEXTSIZE * sizeof (char))) == NULL) {
    perror (proc_name);
    exit (1);
  }
  buf = botbuf + 1 + LINESIZE;
  topbuf = buf + 1;
  next_source ();
  yylineno   = 1;
  yycolumno  = 0;
  yyecho	   = FALSE;
  yyechosptr = NULL;
  yylevel	   = 0;
}

/*
 * La procedure "close_lexio" libere les variables utilisees pour la gestion
 * des entrees du programme source.
 */
close_lexio ()
{
  free ((char *) botbuf);
}

/*
 * La procedure "next_source" remplit le buffer courant.
 */
static	void
next_source ()
{
  register int	size;
  register char	*bot = buf;
  register char	*top = topbuf;

  /* recopie la derniere ligne devant "buf"	*/

  if (yyecho)
    fwrite (yyechosptr,yysptr+1-yyechosptr, sizeof (char), lexout);

  *bot = EOL;	/* evite le debordement de "buf"	*/
  while ((*--bot = *--top) != EOL);
  yyline = yysptr = bot + 1;

  if ((fdin = fileno (lexin)) == -1) {
    perror (infile);
    exit (1);
  }
  if ((size = read (fdin, buf, BUFSIZE)) < 0) {
    perror (infile);
    exit (1);
  }
  if (size == 0) {
    topbuf  = buf + 1;
    *buf    = EOF;
    *topbuf = EOB;	/* sentinelle de fin de fichier	*/
    yysptr  = buf;
  }
  else {
    topbuf  = buf + size;
    *topbuf = EOB;	/* sentinelle de fin de buffer	*/

    /* recherche de la derniere ligne	*/
    top = topbuf;
    while (*--top != EOL);
    lastline = top;
  }
  if (yyecho)
    yyechosptr = yysptr;
}

/*
 * La procedure "count" calcule la distance en espaces entre
 * le premier caractere "*yytext" et le caractere de debut de ligne "*yyline".
 */
static	void
count ()
{
  register char	*str;

  yycolumno = 0;
  for (str = yyline; str <= yytext; str++)
    (*str == '\t') ? yycolumno += 8 - (yycolumno % 8) : yycolumno++;
}

