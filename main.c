#include <stdio.h>

#include "expr.h"
#include "parser.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
	struct Expression *expr = getExpr("ta cmalu nixli ckule");

	printExpression(expr, 0);

	deleteExpression(expr);

	return 0;
}
