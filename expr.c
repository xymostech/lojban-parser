#include "expr.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"

struct Expression *makeExpr(enum ExpressionType type) {
	struct Expression *expr = malloc(sizeof(*expr));

	expr->type = type;

	expr->word = NULL;
	expr->pred = NULL;
	expr->tanru_desc = NULL;
	expr->tanru_base = NULL;
	expr->x1 = NULL;
	expr->x2 = NULL;
	expr->x3 = NULL;
	expr->x4 = NULL;
	expr->x5 = NULL;

	return expr;
}

struct Expression *makeGismu(char *word) {
	struct Expression *expr = makeExpr(GISMU);

	expr->word = strdup(word);

	return expr;
}

struct Expression *makeCmavo(char *word) {
	struct Expression *expr = makeExpr(CMAVO);

	expr->word = strdup(word);

	return expr;
}

struct Expression *makeBridi(struct Expression *pred,
                             struct Expression *x1,
                             struct Expression *x2,
                             struct Expression *x3,
                             struct Expression *x4,
                             struct Expression *x5) {
	struct Expression *expr = makeExpr(BRIDI);

	expr->pred = pred;
	expr->x1 = x1;
	expr->x2 = x2;
	expr->x3 = x3;
	expr->x4 = x4;
	expr->x5 = x5;

	return expr;
}

struct Expression *makeTanru(struct Expression *tanru_base,
                             struct Expression *tanru_desc) {
	struct Expression *expr = makeExpr(TANRU);

	expr->tanru_base = tanru_base;
	expr->tanru_desc = tanru_desc;

	return expr;
}

void deleteExpression(struct Expression *expr) {
	if (expr == NULL) {
		return;
	}

	if (expr->word) {
		free(expr->word);
	}

	deleteExpression(expr->pred);
	deleteExpression(expr->tanru_base);
	deleteExpression(expr->tanru_desc);
	deleteExpression(expr->x1);
	deleteExpression(expr->x2);
	deleteExpression(expr->x3);
	deleteExpression(expr->x4);
	deleteExpression(expr->x5);

	free(expr);
}

void printExpression(struct Expression *expr, int depth) {
	if (expr == NULL) {
		printf("%*sNothing\n", depth, "");
		return;
	}

	if (expr->type == BRIDI) {
		printf("%*sbridi\n", depth, "");
		printf("%*sPredicate:\n", depth, "");
		printExpression(expr->pred, depth + 2);
		printf("%*sx1:\n", depth, "");
		printExpression(expr->x1, depth + 2);
		printf("%*sx2:\n", depth, "");
		printExpression(expr->x2, depth + 2);
		printf("%*sx3:\n", depth, "");
		printExpression(expr->x3, depth + 2);
		printf("%*sx4:\n", depth, "");
		printExpression(expr->x4, depth + 2);
		printf("%*sx5:\n", depth, "");
		printExpression(expr->x5, depth + 2);
	} else if (expr->type == GISMU) {
		printf("%*sgismu: %s\n", depth, "", expr->word);
	} else if (expr->type == CMAVO) {
		printf("%*scmavo: %s\n", depth, "", expr->word);
	} else if (expr->type == TANRU) {
		printf("%*stanru\n", depth, "");
		printf("%*stanru base:\n", depth, "");
		printExpression(expr->tanru_base, depth + 2);
		printf("%*stanru descriptor:\n", depth, "");
		printExpression(expr->tanru_desc, depth + 2);
	}
}

int yyparse(struct Expression **expression, yyscan_t scanner);

struct Expression *getExpr(const char *input) {
	struct Expression *expr;

	yyscan_t scanner;
	YY_BUFFER_STATE state;

	if (yylex_init(&scanner)) {
		return NULL;
	}

	state = yy_scan_string(input, scanner);

	if (yyparse(&expr, scanner)) {
		return NULL;
	}

	yy_delete_buffer(state, scanner);
	yylex_destroy(scanner);

	return expr;
}
