%option noyywrap
%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);
#include "maths_parser.tab.hpp"
%}
%%
"int"           { yylval.string = new std::string(yytext); return T_INT; }
"return"        { yylval.string = new std::string(yytext); return T_RETURN; }
[;]             { return T_SEMIC; }
[:]             { return T_COLON; }
[{]             { return T_LCURL; }
[}]             { return T_RCURL; }
[(]             { return T_LBRAC; }
[)]             { return T_RBRAC; }
[~]             { return T_BNOT; }
[!]             { return T_NOT; }
[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[%]             { return T_MOD; }
[&][&]          { return T_AND; }
[|][|]          { return T_OR; }
[=][=]          { return T_EQUAL; }
[!][=]          { return T_NEQUAL; }
[<]             { return T_LT; }
[>]             { return T_GT; }
[<][=]          { return T_LEQUAL; }
[>][=]          { return T_GEQUAL; }
[&]             { return T_BAND; }
[|]             { return T_BOR; }
[\^]            { return T_BXOR; }
[<][<]          { return T_LSHIFT; }
[>][>]          { return T_RSHIFT; }
[=]             { return T_ASSIGN; }
[,]             { return T_COMMA; }
[.]             { return T_DOT; }
[\[]             { return T_LSBRAC; }
[\]]             { return T_RSBRAC; }

"break"         { yylval.string = new std::string(yytext); return T_BREAK; }

"char"          { yylval.string = new std::string(yytext); return T_CHAR; }

"continue"      { yylval.string = new std::string(yytext); return T_CONTINUE; }

"do"            { yylval.string = new std::string(yytext); return T_DO; }
"double"        { yylval.string = new std::string(yytext); return T_DOUBLE; }
"else"          { yylval.string = new std::string(yytext); return T_ELSE; }

"float"         { yylval.string = new std::string(yytext); return T_FLOAT; }
"for"           { yylval.string = new std::string(yytext); return T_FOR; }

"if"            { yylval.string = new std::string(yytext); return T_IF; }


"signed"        { yylval.string = new std::string(yytext); return T_SIGNED; }
"short"         { yylval.string = new std::string(yytext); return T_SHORT; }
"long"          { yylval.string = new std::string(yytext); return T_LONG; }


"switch"        { yylval.string = new std::string(yytext); return T_SWITCH; }
"case"          { yylval.string = new std::string(yytext); return T_CASE; }
"default"       { yylval.string = new std::string(yytext); return T_DEFAULT; }
"break"         { yylval.string = new std::string(yytext); return T_BREAK; }

"void"          { yylval.string = new std::string(yytext); return T_VOID; }
"while"         { yylval.string = new std::string(yytext); return T_WHILE; }
"+="            { yylval.string = new std::string(yytext); return T_ADDEQUAL; }
"-="            { yylval.string = new std::string(yytext); return T_SUBEQUAL; }
"/="            { yylval.string = new std::string(yytext); return T_DIVEQUAL; }
"*="            { yylval.string = new std::string(yytext); return T_MULEQUAL; }
"%="            { yylval.string = new std::string(yytext); return T_MODEQUAL; }
"++"            { yylval.string = new std::string(yytext); return T_INCREM; }
"--"            { yylval.string = new std::string(yytext); return T_DECREM; }

"struct"        { yylval.string = new std::string(yytext); return T_STRUCT; }




[A-Za-z_]([A-Za-z_]|[0-9])* { yylval.string=new std::string(yytext); return T_VARIABLE; }
[0-9]+([.][0-9]*)? { yylval.number=strtod(yytext, 0); return T_NUMBER; }


[ \t\r\n]+		{;}
.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%
void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
