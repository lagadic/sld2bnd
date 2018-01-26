/************************************************************************

 TITLE		: main.c

 DESCRIPTION	: Le module "main.c" contient l'appel du programme "sldbnd" :
		  		SoLiD to BouND

		  Le programme "sldbnd" transforme un fichier de scenes 3D
		  de modele geometrique solide (SoLiD) en un fichier de scenes
		  3D de modele geometrique surfacique (BouND).

 Le programme "sldbnd" a pour parametres :

 -?		  Affiche le mode d'emploi du programme.
 -p		  Utilise le preprocesseur "cpp" avant le compilateur.
 -o outfile	  Fichier objet  en sortie.
 sourcefile	  Fichier source en entree.

 VERSION	: 1-003

 ABSTRACT	: 

 print_usage	  Affiche le mode d'emploi du programme.
 main		  Module principal.

 ENVIRONMENT	: Compilation	-
			gould		Machines GOULD NP/1.
			sun		Machines SUN 3, 4.
			vax		Machines VAX 750, 8250.
		  Link 		- NONE
		  Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 12/04/88 

 MODIFIED BY	:

 1-001 - 12/04/88 Original.
 1-002 - 07/04/89 Ajout de "yyparse".
 1-003 - 17/11/89 Ajout de "cardioide".
 1-004 - 14/03/94 Nettoyage include et options de compilation (TB)

*************************************************************************/

#include	"string.h"

#include	"my.h"
#include	"lex.h"
#include	"y.tab.h"

static	char	prog_name[] = "sldbnd";
static	char	options[]   = "o:p?";
static	char	cpp[]	    = "/lib/cpp -P";


/*
 * KEYWORD_TBL : Tableau des mots cles et des jetons de la grammaire.
 */
static	Keyword	keyword_tbl[] = {
	"block",	BLOCK,		TRUE,
	"cardioide",	CARDIOIDE,	TRUE,
	"cone",		CONE,		TRUE,
	"cylinder",	CYLINDER,	TRUE,
	"height",	HEIGHT,		FALSE,
	"length",	LENGTH,		FALSE,
	"radius",	RADIUS,		FALSE,
	"radiusin",	RADIUSIN,	FALSE,
	"radiusout",	RADIUSOUT,	FALSE,
	"rotate",	ROTATE,		FALSE,
	"scale",	SCALE,		FALSE,
	"sphere",	SPHERE,		TRUE,
	"subdivision",	SUBDIVISION,	FALSE,
	"torus",	TORUS,		TRUE,
	"translate",	TRANSLATE,	FALSE,
	"wedge",	WEDGE,		TRUE,
	"width",	WIDTH,		FALSE,
	NULL,		0,		FALSE
};


/*
 * La procedure "print_usage" affiche le mode d'emploi du programme
 * sur le fichier standard d'erreur.
 */
print_usage ()
{
	fprintf (stderr, "Usage: %s [-?] [-p] [-o outfile] [sourcefile ...]\n",
	prog_name);
}

/*
 * La procedure "main" contient le module principal du programme.
 * Entree :
 * -?		Affiche le mode d'emploi du programme.
 * -p		Utilise le preprocesseur "cpp" avant le compilateur.
 * -o file	Fichier objet en sortie.
 * files	Fichiers sources en entree.
 */
main (argc, argv)
int	argc;
char	**argv;
{
	extern	 int	optind, opterr;	/* man 3 getopt	*/
	extern	 char	*optarg;


	int	oflg = 0;	/* fichier objet  en sortie	*/
	int	pflg = 0;	/* preprocesseur cpp		*/
	int	sflg = 0;	/* fichier source en entree 	*/
	char	line[LINESIZE];

	opterr = 0;	/* sans message d'erreur	*/

	for (optind = 1; optind < argc; ) {
		switch (getopt (argc, argv, options)) {
		case EOF:
			optind++;
			sflg++;
			break;
		case 'o':
			oflg++;
			strncpy (outfile, optarg, NAMESIZE);
			break;
		case 'p':
			pflg++;
			break;
		case '?':
			print_usage ();
			exit (0);
			break;
		default :
			print_usage ();
			exit (1);
			break;
		}
	}

	open_lex ();
	open_keyword (keyword_tbl);

	if (oflg) {	/* ouverture du fichier objet	*/

		for (optind = 1; sflg && optind < argc; ) {
			if (getopt (argc, argv, options) == EOF
			&& strcmp (argv[optind++], outfile) == 0) {
				fprintf (stderr,
				"%s: Outfile %s would overwrite infile\n",
				prog_name, outfile);
				exit (1);
			}
		}
		if ((lexout = fopen (outfile, "w")) == NULL) {
			sprintf (line, "%s: %s", prog_name, outfile);
			perror (line);
			exit (1);
		}
	}
	else {		/* fichier objet = stdout	*/
		strncpy (outfile, "<stdout>", NAMESIZE);
		lexout = stdout;
	}

	if (! sflg) {	/* fichier source = stdin	*/
		strncpy (infile, "<stdin>", NAMESIZE);
		if (pflg) {
			if ((lexin = popen (cpp, "r")) == NULL) {
				sprintf (line, "%s: %s", cpp, infile);
				perror (line);
				exit (1);
			}
		}
		else {
			lexin = stdin;
		}
		open_lexio ();
		yyparse ();
		if (pflg)
			pclose (lexin);
		close_lexio ();	
	}

	for (optind = 1; sflg && optind < argc; ) {
		if (getopt (argc, argv, options) != EOF)
			continue;
		strncpy (infile, argv[optind++], NAMESIZE);
		if (pflg) {
			sprintf (line, "%s %s", cpp, infile);
			if ((lexin = popen (line, "r")) == NULL) {
				sprintf (line, "%s: %s", cpp, infile);
				perror (line);
				exit (1);
			}
		}
		else {
			if ((lexin = fopen (infile, "r")) == NULL) {
				sprintf (line, "%s: %s", prog_name, infile);
				perror (line);
				exit (1);
			}
		}
		open_lexio ();
		yyparse ();
		if (pflg)
			pclose (lexin);
		else
			fclose (lexin);
		close_lexio ();	
	}
	if (oflg)
		fclose (lexout);
	else
		fflush (lexout);
	
	close_keyword ();
	close_lex ();
	exit (0);
}

