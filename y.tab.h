/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 102 "io/gram.sldbnd.y" /* yacc.c:1909  */

	int	yyint;		/* nombre entier	*/
	float	yyfloat;	/* nombre flottant	*/
	char	*yystr;		/* identificateur	*/

#line 106 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
