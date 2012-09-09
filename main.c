#include <stdio.h>

#include "expr.h"
#include "parser.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
	char *input = malloc(500);
	size_t size = 500;

	getline(&input, &size, stdin);

	struct Expression *expr = getExpr(input);

	printExpression(expr, 0);

	deleteExpression(expr);
	free(input);

	return 0;
}
