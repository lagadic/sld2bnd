/************************************************************************

 TITLE		: keyword.c

 DESCRIPTION	: Le module "keyword.c" contient les procedures de gestion
      des mots cles retournes par l'analyseur lexical "lex".

 Pour plus de details, voir la procedure "lex" dans le module "lex.c".

 Avant usage, faire preceder les procedures d'un appel a "open_keyword".
 Apres usage, faire suivre   les procedures d'un appel a "close_keyword".

 VERSION	: 1-002

 ABSTRACT	:

 open_keyword	  Ouvre le mode de gestion des mots cles.
 close_keyword	  Ferme le mode de gestion des mots cles.

 open_hash	  Ouvre le mode de codage par "hachage".
 close_hash	  Ferme le mode de codage par "hachage".
 hashpjw	  Fonction de "hachage".

 delete_keyword	  Efface    un   mot cle.
 get_keyword	  Retourne  un   mot cle.
 insert_keyword	  Insere    un   mot cle.
 get_cmd	  Indique si  un mot cle est le debut d'une commande.
 get_symbol	  Recherche d'un mot cle ou d'un identificateur.

 ENVIRONMENT	: Compilation	-
      standalone	Programme d'essai.
      Link 		- NONE
      Execution	- NONE

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 28/03/88

 MODIFIED BY	:

 1-001 - 28/03/88 Original.
 1-002 - 12/05/89 Ajout de "is_cmd".
 1.003 - 25/01/94 nettoyage option et include (BA)
*************************************************************************/

#include <string.h>

#include "my.h"
#include "lex.h"


static	void	open_hash ();
static	void	close_hash ();
static	int	hashplw ();
static	void	insert_keyword ();

#ifdef	debug
static	void	delete_keyword ();
static	char	*get_keyword ();
#endif


#define	PRIME		211
#define	NEXT(x)		(x) = (x)->next

typedef struct	bucket {
  struct	bucket	*next;	/* element suivant	*/
  Byte		length;	/* longueur de "ident"	*/
  char		*ident;	/* identifateur 	*/
  Index		token;	/* code du jeton 	*/
  Byte		is_cmd;	/* debut de commande	*/
} Bucket;


static	Bucket	**hash_tbl;	/* table de "hash-coding"	*/
static	int	is_cmd;		/* indique le debut de commande	*/


/*
 * La procedure "open_keyword" alloue et initialise les variables utilisees
 * par les procedures de gestion des mots cles.
 * Entree :
 * kwp		Tableau des mots cles termine par NULL.
 */
open_keyword (kwp)
register Keyword	*kwp;
{
  open_hash ();
  for (; kwp->ident != NULL; kwp++) /* recopie les mots cles	*/
    insert_keyword (kwp->ident, kwp->token, kwp->is_cmd);
}

/*
 * La procedure "close_keyword" libere les variables utilisees
 * par les procedures de gestion des mots cles.
 */
close_keyword ()
{
  close_hash ();
}

/*
 * La procedure "open_hash" alloue et initialise la table de codage.
 */
static	void
open_hash ()
{
  static	 char	proc_name[] = "open_hash";

  register Bucket	**head, **bend;

  if ((hash_tbl = (Bucket **) malloc (sizeof (Bucket *) * PRIME))==NULL){
    perror (proc_name);
    exit (1);
  }
  head = hash_tbl;
  bend = head + PRIME;
  for (; head < bend; *head++ = NULL);
}

/*
 * La procedure "close_hash" libere la table de codage et ses elements.
 */
static	void
close_hash ()
{
  register Bucket	**head = hash_tbl;
  register Bucket **bend = head + PRIME;
  register Bucket	*bp;	/* element courant	*/
  register Bucket	*next;	/* element suivant	*/

  for (; head < bend; head++) {	/* libere les listes	*/
    for (bp = *head; bp != NULL; bp = next) {
      next = bp->next;
      free ((char *) bp);
    }
  }
  free ((char *) hash_tbl);	/* libere la table	*/
}

/*
 * La procedure "hashpjw" calcule un indice code a partir de la chaine
 * de caracteres "str".
 * Pour plus de renseignements, voir :
 *	"Compilers. Principles, Techniques, and Tools",
 *	A.V. AHO, R. SETHI, J.D. ULLMAN,
 *	ADDISON-WESLEY PUBLISHING COMPANY, pp 436.
 * Entree :
 * str		Chaine de caracteres a coder.
 * Sortie :
 *		Le code de la chaine.
 */
static	int
hashpjw (str)
register char	*str;
{
  register unsigned	h = 0;	/* "hash value"	*/
  register unsigned	g;

  for (; *str != '\0'; str++) {
    h = (h << 4) + *str;
    if (g = h & ~0xfffffff) {
      h ^= g >> 24;
      h ^= g;
    }
  }
  return (h % PRIME);
}

#ifdef	debug
/*
 * La procedure "delete_keyword" efface le premier mot cle ayant pour
 * identificateur la chaine de caractere "str".
 * Entree :
 * str		Chaine de caracteres de l'identificateur du mot cle.
 */
static	void
delete_keyword (str)
register char	*str;
{
  register int	i  = hashpjw (str);
  register Bucket	*bp = hash_tbl[i];
  register Bucket	*prev;	/* element precedant	*/

  for (prev = NULL; bp != NULL; prev = bp, NEXT(bp)) {
    if (strcmp (str, bp->ident) == 0) {
      if (prev == NULL)	/* en tete de la liste*/
        hash_tbl[i] = bp->next;
      else	prev->next  = bp->next;
      free ((char *) bp);
      return;
    }
  }
}
#endif	debug

#ifdef	debug
#define	START_ARG	0
#define	NEXT_ARG	1

/*
 * La procedure "get_keyword" retourne un a un les mots cles contenus
 * dans la table de "hachage".
 * La procedure permet le parcourt de la table de "hachage" avec
 * Entree :
 * START_ARG	initialise le parcourt de la table.
 * NEXT_ARG	continue   le parcourt de la table.
 * Sortie :
 *		Pointeur sur le mot cle, NULL en fin de liste pour NEXT_ARG.
 *		NULL pour tout autre entree.
 */
static	char
*get_keyword (mode)
int	mode;
{
  static	Bucket	*bucket = NULL;	/* element courant de la table	*/
  static	int	ibucket = 0;	/* indice  courant de la table	*/

  if (mode != START_ARG && mode != NEXT_ARG) {	/* mode inconnu	*/
    return (NULL);
  }
  if (mode == START_ARG) {/* initialise le parcourt de la table	*/
    bucket  = NULL;
    ibucket = 0;
    return (NULL);
  }
  /* mode == NEXT_ARG	*/
  if (bucket == NULL) {	/* recherche de l'element suivant	*/
    while (ibucket < PRIME &&
      (bucket = hash_tbl[ibucket++]) == NULL);
  }
  if (bucket == NULL) {	/* fin de la liste	*/
    return (NULL);
  }
  else {			/* retourne l'element	*/
    register Bucket	*b = bucket;

    NEXT(bucket);
    return (b->ident);
  }
}
#endif	debug

/*
 * La procedure "insert_keyword" insere en tete d'un point d'entree
 * de la table de "hachage" le mot cle ayant pour identificateur
 * la chaine de caracteres "str" et pour valeur "token".
 * Entree :
 * str		Chaine de caracteres du mot cle.
 * token	Valeur du jeton associe au mot cle.
 */
static	void
insert_keyword (str, token, b)
char	*str;
int	token;
Byte	b;
{
  static	 char	proc_name[] = "insert_keyword";

  register Bucket	**head = hash_tbl + hashpjw (str);
  register Bucket	*bp;
  register int	length;

  length = strlen (str);
  if ((bp = (Bucket *) malloc (sizeof (Bucket) + length  + 1)) == NULL) {
    perror (proc_name);
    exit (1);
  }
  bp->is_cmd = b ? TRUE : FALSE;
  bp->length = length;
  bp->token  = token;
  bp->ident  = (char *) (bp + 1);
  strcpy (bp->ident, str);

  bp->next = *head;	/* insere "b" en tete de "head"	*/
  *head = bp;
}

/*
 * La procedure "get_cmd" retourne le boolean indiquant si le dernier symbole
 * recherche par la procedure "get_symbol" est le debut d'une commande.
 * Sortie :
 * 		TRUE si le dernier symbole est le debut d'une commande.
 *		FALSE sinon.
 */
get_cmd ()
{
  return (is_cmd);
}

/*
 * La pocedure "get_symbol" verifie que la chaine pointee par "ident"
 * de longeur "length" est un mot cle.
 * Global :
 * is_cmd	Booleen indiquant le debut d'une commande.
 * Entree :
 * ident	Chaine de l'identificateur.
 * length	Nombre de caracteres de la chaine.
 * Note :
 * La chaine "ident" n'est pas terminee par '\0'.
 * Sortie :
 * 		Valeur du jeton associe si c'est un mot cle, 0 sinon.
 */
get_symbol (ident, length)
char	*ident;
int	length;
{
  register Bucket	*bp;
  register char	*kwd;
  register char	*idn = ident;
  register int	len  = length;

  {	/* calcule le code de hachage (voir "hashpjw")	*/
    register unsigned	h = 0;	/* "hash value"	*/
    register unsigned	g;

    for (; len != 0; idn++, len--) {
      h = (h << 4) + *idn;
      if (g = h & ~0xfffffff) {
        h ^= g >> 24;
        h ^= g;
      }
    }
    bp = hash_tbl[h % PRIME];
  }

  /* recherche le mot cle	*/

  for (; bp != NULL; NEXT(bp)) {
    if (length == bp->length) {
      idn = ident;
      len = length;
      kwd = bp->ident;
      for (; *idn == *kwd; idn++, kwd++) {
        if (--len == 0) {
          is_cmd = (int) bp->is_cmd;
          return (bp->token);
        }
      }
    }
  }
  is_cmd = FALSE;
  return (0);	/* mot cle absent	*/
}

