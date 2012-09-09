%{

#include "expr.h"
#include "parser.h"

#include <stdio.h>

%}

%option outfile="lexer.c" header-file="lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

DOT \.
V [aeiou]
C [bcdfgjklmnprstvxyz']

%%

bo { yylval->string = yytext; return TOKEN_BO; }

{DOT}{V}  { yylval->string = yytext; return TOKEN_CMAVO; }
{C}{V}    { yylval->string = yytext; return TOKEN_CMAVO; }
{DOT}{V}{V}    { yylval->string = yytext; return TOKEN_CMAVO; }
{C}{V}{V} { yylval->string = yytext; return TOKEN_CMAVO; }

{C}{V}{C}{C}{V} { yylval->string = yytext; return TOKEN_GISMU; }
{C}{C}{V}{C}{V} { yylval->string = yytext; return TOKEN_GISMU; }

. { }
\n { }

%%

int yyerror(yyscan_t scanner, struct Expression **expression, const char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
	return 0;
}
