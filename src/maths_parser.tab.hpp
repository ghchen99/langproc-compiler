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

#ifndef YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 2 "src/maths_parser.y" /* yacc.c:1909  */

  #include "ast.hpp"
  #include <iostream>
  #include <cassert>
  #include <stdio.h>
  #define YYDEBUG 1

  extern const Base *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 60 "src/maths_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_TIMES = 258,
    T_DIVIDE = 259,
    T_PLUS = 260,
    T_MINUS = 261,
    T_EXPONENT = 262,
    T_LBRAC = 263,
    T_RBRAC = 264,
    T_LCURL = 265,
    T_RCURL = 266,
    T_LSBRAC = 267,
    T_RSBRAC = 268,
    T_NUMBER = 269,
    T_VARIABLE = 270,
    T_SEMIC = 271,
    T_COMMA = 272,
    T_COLON = 273,
    T_DOT = 274,
    T_LSHIFT = 275,
    T_RSHIFT = 276,
    T_EQUAL = 277,
    T_NEQUAL = 278,
    T_GT = 279,
    T_LT = 280,
    T_LEQUAL = 281,
    T_GEQUAL = 282,
    T_ASSIGN = 283,
    T_BNOT = 284,
    T_NOT = 285,
    T_AND = 286,
    T_OR = 287,
    T_BAND = 288,
    T_BOR = 289,
    T_BXOR = 290,
    T_MOD = 291,
    T_ADDEQUAL = 292,
    T_SUBEQUAL = 293,
    T_INCREM = 294,
    T_DECREM = 295,
    T_DIVEQUAL = 296,
    T_MULEQUAL = 297,
    T_MODEQUAL = 298,
    T_WHILE = 299,
    T_DO = 300,
    T_IF = 301,
    T_ELSE = 302,
    T_FOR = 303,
    T_BREAK = 304,
    T_CONTINUE = 305,
    T_SWITCH = 306,
    T_CASE = 307,
    T_DEFAULT = 308,
    T_INT = 309,
    T_VOID = 310,
    T_CHAR = 311,
    T_SHORT = 312,
    T_LONG = 313,
    T_FLOAT = 314,
    T_DOUBLE = 315,
    T_SIGNED = 316,
    T_RETURN = 317,
    T_STRUCT = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "src/maths_parser.y" /* yacc.c:1909  */

  const Base *expr;
  double number;
  std::string *string;

#line 142 "src/maths_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */
