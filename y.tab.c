/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "io/gram.sldbnd.y" /* yacc.c:339  */

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


#line 166 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BLOCK = 258,
    CARDIOIDE = 259,
    CONE = 260,
    CYLINDER = 261,
    HEIGHT = 262,
    IDENT = 263,
    LENGTH = 264,
    RADIUS = 265,
    RADIUSIN = 266,
    RADIUSOUT = 267,
    ROTATE = 268,
    SCALE = 269,
    SPHERE = 270,
    SUBDIVISION = 271,
    TORUS = 272,
    TRANSLATE = 273,
    WEDGE = 274,
    WIDTH = 275,
    INT = 276,
    FLOAT = 277,
    STRING = 278
  };
#endif
/* Tokens.  */
#define BLOCK 258
#define CARDIOIDE 259
#define CONE 260
#define CYLINDER 261
#define HEIGHT 262
#define IDENT 263
#define LENGTH 264
#define RADIUS 265
#define RADIUSIN 266
#define RADIUSOUT 267
#define ROTATE 268
#define SCALE 269
#define SPHERE 270
#define SUBDIVISION 271
#define TORUS 272
#define TRANSLATE 273
#define WEDGE 274
#define WIDTH 275
#define INT 276
#define FLOAT 277
#define STRING 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 102 "io/gram.sldbnd.y" /* yacc.c:355  */

	int	yyint;		/* nombre entier	*/
	float	yyfloat;	/* nombre flottant	*/
	char	*yystr;		/* identificateur	*/

#line 258 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 275 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      24,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   139,   139,   143,   144,   145,   146,   147,
     148,   149,   154,   155,   156,   157,   158,   159,   160,   161,
     153,   174,   175,   176,   177,   178,   179,   173,   192,   193,
     194,   195,   196,   197,   198,   191,   211,   212,   213,   214,
     215,   216,   217,   210,   230,   231,   232,   233,   234,   235,
     229,   248,   249,   250,   251,   252,   253,   254,   247,   268,
     269,   270,   271,   272,   273,   274,   275,   267,   287,   291,
     295,   299,   303,   310,   314,   318,   322,   326,   333,   337,
     341,   345,   349,   356,   360,   364,   368,   372,   379,   383,
     387,   391,   395,   402,   406,   410,   414,   418,   425,   430,
     434,   438,   445,   449,   456,   460,   467,   471,   478,   482,
     490,   494
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BLOCK", "CARDIOIDE", "CONE", "CYLINDER",
  "HEIGHT", "IDENT", "LENGTH", "RADIUS", "RADIUSIN", "RADIUSOUT", "ROTATE",
  "SCALE", "SPHERE", "SUBDIVISION", "TORUS", "TRANSLATE", "WEDGE", "WIDTH",
  "INT", "FLOAT", "STRING", "'('", "')'", "$accept", "list", "$@1", "cmd",
  "block", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9",
  "cardioide", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15", "cone",
  "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "$@22", "cylinder",
  "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "sphere", "$@30",
  "$@31", "$@32", "$@33", "$@34", "$@35", "torus", "$@36", "$@37", "$@38",
  "$@39", "$@40", "$@41", "$@42", "wedge", "$@43", "$@44", "$@45", "$@46",
  "$@47", "$@48", "$@49", "$@50", "height", "length", "radius", "radiusin",
  "radiusout", "width", "subdivision", "translate", "scale", "rotate",
  "vector", "float", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    40,    41
};
# endif

#define YYPACT_NINF -143

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-143)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -143,     2,   -10,  -143,   104,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    56,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,    92,    29,    58,
      58,    58,    58,    60,    29,  -143,     4,  -143,    94,  -143,
    -143,    12,  -143,  -143,  -143,  -143,  -143,     8,  -143,  -143,
    -143,  -143,  -143,    55,    62,  -143,    68,    44,    63,    63,
      44,  -143,    70,    64,    62,  -143,  -143,  -143,     7,  -143,
     111,  -143,  -143,     9,    57,  -143,  -143,    14,  -143,  -143,
    -143,  -143,    10,  -143,    99,  -143,  -143,  -143,  -143,  -143,
      77,    63,  -143,  -143,    80,    91,  -143,    82,    44,    44,
      91,  -143,  -143,  -143,    84,    44,    63,  -143,    19,  -143,
    -143,    27,    75,   103,  -143,  -143,    30,  -143,  -143,  -143,
    -143,    35,  -143,  -143,  -143,  -143,    44,  -143,  -143,    75,
      80,    96,  -143,  -143,    91,    91,    96,  -143,  -143,    91,
      44,  -143,  -143,    48,    76,  -143,  -143,  -143,  -143,  -143,
    -143,    91,  -143,  -143,    80,    97,    96,    96,   105,    96,
      91,  -143,    49,  -143,  -143,  -143,  -143,  -143,  -143,    96,
    -143,  -143,   106,   107,   108,    96,  -143,  -143,  -143,  -143,
    -143,   109,   110,  -143,  -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     2,     5,     6,     7,     8,
       9,    10,    11,     4,    12,    21,    28,    36,    44,    51,
      59,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      22,    29,    37,    45,    52,    60,   101,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,    97,     0,    14,
      82,     0,    23,    30,    38,    46,    87,     0,    53,    61,
      99,    98,    96,     0,     0,    81,     0,     0,     0,     0,
       0,    86,     0,     0,     0,    95,   110,   111,     0,    72,
       0,    15,    80,     0,     0,    24,    77,     0,    31,    39,
      47,    85,     0,    92,     0,    54,    62,    94,    93,    71,
       0,     0,    79,    78,     0,     0,    76,     0,     0,     0,
       0,    84,    83,    91,     0,     0,     0,    70,     0,    16,
     109,     0,     0,     0,    25,    75,     0,    32,    40,    48,
      90,     0,    55,    63,    69,    68,     0,   107,   106,     0,
       0,     0,    74,    73,     0,     0,     0,    89,    88,     0,
       0,    17,   108,     0,     0,    26,    33,    41,    49,    56,
      64,     0,   105,   104,     0,     0,     0,     0,     0,     0,
       0,    18,     0,    27,    34,    42,    50,    57,    65,     0,
     103,   102,     0,     0,     0,     0,    19,    35,    43,    58,
      66,     0,     0,    20,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,  -143,   114,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
      65,   -68,   -24,  -143,  -143,    93,   102,  -142,  -103,   -70,
     -89,   -60
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    21,    38,    64,   101,   136,
     161,   179,   191,     7,    22,    39,    67,   105,   141,   165,
       8,    23,    40,    68,   108,   144,   166,   182,     9,    24,
      41,    69,   109,   145,   167,   183,    10,    25,    42,    70,
     110,   146,   168,    11,    26,    43,    73,   115,   149,   169,
     184,    12,    27,    44,    74,   116,   150,   170,   185,   192,
      81,    88,    52,    58,    95,    49,    29,   155,   124,    85,
     121,   122
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      90,    89,     3,    78,   158,    60,    83,   129,    97,    71,
     102,   111,    92,    65,     4,   106,    53,    54,    55,    72,
     134,    28,    66,   107,   174,   175,     4,   177,   137,    61,
      47,   142,    98,   119,   103,   112,   147,   186,   127,   128,
     118,   156,   157,   190,   135,   132,   159,   126,   133,   162,
     180,   153,   138,    48,   131,   143,    75,    36,   171,    50,
     148,    56,   139,    79,    86,    93,   151,   178,    84,    82,
     104,    91,    37,   163,   181,   172,    76,    77,   117,   152,
     160,   120,    51,   125,    57,   130,    80,    87,    94,    76,
      77,    76,    77,    45,   164,    62,    76,    77,    76,    77,
     113,    76,    77,    76,    77,    76,    77,    14,    15,    16,
      17,   114,    99,    46,    63,   123,    13,   140,   100,    18,
     154,    19,   173,    20,    30,    31,    32,    33,    34,    35,
     176,   187,   188,   189,   193,   194,     0,    59,     0,    96
};

static const yytype_int16 yycheck[] =
{
      70,    69,     0,    63,   146,     1,    66,   110,     1,     1,
       1,     1,    72,     1,    24,     1,    40,    41,    42,    11,
       1,    24,    10,     9,   166,   167,    24,   169,     1,    25,
       1,     1,    25,   101,    25,    25,     1,   179,   108,   109,
     100,   144,   145,   185,    25,   115,   149,   107,   116,     1,
       1,   140,    25,    24,   114,    25,     1,     1,   161,     1,
      25,     1,   122,     1,     1,     1,   136,   170,    24,     1,
      13,     1,    16,    25,    25,   164,    21,    22,     1,   139,
     150,     1,    24,     1,    24,     1,    24,    24,    24,    21,
      22,    21,    22,     1,    18,     1,    21,    22,    21,    22,
       1,    21,    22,    21,    22,    21,    22,     3,     4,     5,
       6,    12,     1,    21,    20,    24,     2,    14,     7,    15,
      24,    17,    25,    19,    22,    23,    24,    25,    26,    27,
      25,    25,    25,    25,    25,    25,    -1,    44,    -1,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    28,     0,    24,    29,    30,    39,    46,    54,
      62,    69,    77,    29,     3,     4,     5,     6,    15,    17,
      19,    31,    40,    47,    55,    63,    70,    78,    24,    92,
      92,    92,    92,    92,    92,    92,     1,    16,    32,    41,
      48,    56,    64,    71,    79,     1,    21,     1,    24,    91,
       1,    24,    88,    88,    88,    88,     1,    24,    89,    91,
       1,    25,     1,    20,    33,     1,    10,    42,    49,    57,
      65,     1,    11,    72,    80,     1,    21,    22,    97,     1,
      24,    86,     1,    97,    24,    95,     1,    24,    87,    87,
      95,     1,    97,     1,    24,    90,    86,     1,    25,     1,
       7,    34,     1,    25,    13,    43,     1,     9,    50,    58,
      66,     1,    25,     1,    12,    73,    81,     1,    97,    87,
       1,    96,    97,    24,    94,     1,    97,    95,    95,    94,
       1,    97,    95,    87,     1,    25,    35,     1,    25,    97,
      14,    44,     1,    25,    51,    59,    67,     1,    25,    74,
      82,    95,    97,    96,    24,    93,    94,    94,    93,    94,
      95,    36,     1,    25,    18,    45,    52,    60,    68,    75,
      83,    94,    96,    25,    93,    93,    25,    93,    94,    37,
       1,    25,    53,    61,    76,    84,    93,    25,    25,    25,
      93,    38,    85,    25,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    28,    27,    29,    29,    29,    29,    29,
      29,    29,    31,    32,    33,    34,    35,    36,    37,    38,
      30,    40,    41,    42,    43,    44,    45,    39,    47,    48,
      49,    50,    51,    52,    53,    46,    55,    56,    57,    58,
      59,    60,    61,    54,    63,    64,    65,    66,    67,    68,
      62,    70,    71,    72,    73,    74,    75,    76,    69,    78,
      79,    80,    81,    82,    83,    84,    85,    77,    86,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    92,    92,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      97,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,    16,     0,     0,     0,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     4,     4,
       3,     2,     1,     4,     4,     3,     2,     1,     4,     4,
       3,     2,     1,     4,     4,     3,     2,     1,     4,     4,
       3,     2,     1,     4,     4,     3,     2,     1,     4,     4,
       3,     2,     4,     4,     4,     4,     4,     4,     3,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 138 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { echolex ();}
#line 1485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 139 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { echolex ();}
#line 1491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 139 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { echolex ();}
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 154 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("width", WIDTH);}
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("height", HEIGHT);}
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 157 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("length", LENGTH);}
#line 1521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 158 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 159 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 160 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 161 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Block_Bound (&bound);
		scale(&bound, width, height, length);
		move_bound(&bound, m);
                fprintf_Bound (lexout, &bound);
                free_Bound (&bound);
	}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 174 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 175 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radius", RADIUS);}
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 176 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 177 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 178 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 179 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 180 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Cardioide_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, radius);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 192 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 193 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radius", RADIUS);}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 194 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("length", LENGTH);}
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 195 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 196 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 197 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 198 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 199 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Cone_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 211 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 212 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radius", RADIUS);}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 213 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("length", LENGTH);}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 214 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 215 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 216 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 217 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 218 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Cylinder_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 230 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 231 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radius", RADIUS);}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 232 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 233 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 234 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 235 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 236 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Sphere_Bound (&bound, (Index) *get_slstack ());
		scale(&bound, radius, radius, radius);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 248 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 249 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radiusin", RADIUSIN);}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 250 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("radiusout", RADIUSOUT);}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 251 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 253 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 254 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 255 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Torus_Bound (&bound, (Index) *get_slstack (),
			radiusin < M_EPSILON ? radiusout : radiusout/radiusin);
		scale(&bound, radiusin, radiusin, radiusin);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 268 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("subdivision", SUBDIVISION);}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 269 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("width", WIDTH);}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 270 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("height", HEIGHT);}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 271 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("length", LENGTH);}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 272 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("rotate", ROTATE);}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 273 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("scale", SCALE);}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 274 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex ("translate", TRANSLATE);}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 275 "io/gram.sldbnd.y" /* yacc.c:1646  */
    { gotolex (")", ')');}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 276 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		Position_to_Matrice (&position, m);
		make_Wedge_Bound (&bound);
		scale(&bound, width, height, length);
		move_bound(&bound, m);
		fprintf_Bound (lexout, &bound);
		free_Bound (&bound);
	}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 288 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		height = (yyvsp[-1].yyfloat);
	}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 292 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"height\"");
	}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 296 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 300 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"height\" expected");
	}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 304 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(height...)\" expected");
	}
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 311 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		length = (yyvsp[-1].yyfloat);
	}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 315 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"length\"");
	}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 319 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 323 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"length\" expected");
	}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 327 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(length...)\" expected");
	}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 334 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		radius = (yyvsp[-1].yyfloat);
	}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 338 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"radius\"");
	}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 342 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 346 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"radius\" expected");
	}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 350 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(radius...)\" expected");
	}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 357 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		radiusin = (yyvsp[-1].yyfloat);
	}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 361 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"radiusin\"");
	}
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 365 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 369 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"radiusin\" expected");
	}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 373 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(radiusin...)\" expected");
	}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 380 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		radiusout = (yyvsp[-1].yyfloat);
	}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 384 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"radiusout\"");
	}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 388 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 392 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"radiusout\" expected");
	}
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 396 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(radiusout...)\" expected");
	}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 403 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		width = (yyvsp[-1].yyfloat);
	}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 407 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"width\"");
	}
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 411 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("float expected");
	}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 415 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"width\" expected");
	}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 419 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("item \"(width...)\" expected");
	}
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 426 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		subdivision = (yyvsp[-1].yyint);
		load_slstack (subdivision);
	}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 431 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"subdivision\"");
	}
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 435 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("integer expected");
	}
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 439 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("keyword \"subdivision\" expected");
	}
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 446 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		position.translate = vector;
	}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 450 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"translate\"");
	}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 457 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		position.scale = vector;
	}
#line 2180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 461 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"scale\"");
	}
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 468 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		position.rotate = vector;
	}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 472 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		warning ("missing ')' in \"rotate\"");
	}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 479 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		SET_COORD3(vector, (yyvsp[-2].yyfloat), (yyvsp[-1].yyfloat), (yyvsp[0].yyfloat));
	}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 483 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		fatal ("vector 3D [X,Y,Z] expected");
	}
#line 2220 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 491 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		(yyval.yyfloat) = (float) (yyvsp[0].yyint);
	}
#line 2228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 495 "io/gram.sldbnd.y" /* yacc.c:1646  */
    {
		(yyval.yyfloat) = (yyvsp[0].yyfloat);
	}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2240 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 500 "io/gram.sldbnd.y" /* yacc.c:1906  */
	/* fin de l'analyseur	*/

