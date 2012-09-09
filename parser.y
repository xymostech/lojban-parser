%{

#include "expr.h"
#include "parser.h"
#include "lexer.h"

int yyerror(yyscan_t scanner, struct Expression **expression, const char *msg);

%}

%output "parser.c"
%defines "parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { struct Expression **expression }
%parse-param { yyscan_t scanner }

%union {
	char *string;
	struct Expression *expression;
}

%token <string> TOKEN_CMAVO
%token <string> TOKEN_GISMU

%token TOKEN_BO

%type <expression> gismu;
%type <expression> bridi
%type <expression> cmavo
%type <expression> brivla;
%type <expression> sampubrivla;

%%

input
    : bridi { *expression = $1; }
    ;

bridi
    : cmavo brivla cmavo { $$ = makeBridi($2, $1, $3, NULL, NULL, NULL); }
    | cmavo brivla { $$ = makeBridi($2, $1, NULL, NULL, NULL, NULL); }
    ;

brivla
    : brivla sampubrivla { $$ = makeTanru($2, $1); }
    | sampubrivla { $$ = $1; }
    ;

sampubrivla
    : gismu { $$ = $1; }
    | gismu TOKEN_BO sampubrivla { $$ = makeTanru($3, $1); }
    ;

gismu
    : TOKEN_GISMU { $$ = makeGismu($1); }
    ;

cmavo
    : TOKEN_CMAVO { $$ = makeCmavo($1); }
    ;

%%
