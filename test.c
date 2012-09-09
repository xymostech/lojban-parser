#include <stdio.h>
#include <string.h>

#include "expr.h"

char *typenames[4];

int checkExpr(struct Expression *correct, struct Expression *test) {
	if (correct == NULL && test == NULL) {
		return 0;
	}

	if (correct->type != test->type) {
		printf("Expression types don't match: %s vs %s\n",
		       typenames[correct->type], typenames[test->type]);
		printExpression(correct, 0);
		printExpression(test, 0);
		return 1;
	}

	int error = 0;

	if (correct->type == BRIDI) {
		if (checkExpr(correct->pred, test->pred)) {
			return 1;
		} else if (checkExpr(correct->x1, test->x1)) {
			return 1;
		} else if (checkExpr(correct->x1, test->x1)) {
			return 1;
		} else if (checkExpr(correct->x1, test->x1)) {
			return 1;
		} else if (checkExpr(correct->x1, test->x1)) {
			return 1;
		}
	} else if (correct->type == GISMU) {
		if (strcmp(correct->word, test->word)) {
			printf("Gismu words do not match: %s vs %s\n",
			       correct->word, test->word);
			return 1;
		}
	} else if (correct->type == CMAVO) {
		if (strcmp(correct->word, test->word)) {
			printf("Cmavo words do not match: %s vs %s\n",
			       correct->word, test->word);
			return 1;
		}
	} else if (correct->type == TANRU) {
		if (checkExpr(correct->x1, test->x1)) {
			return 1;
		} else if (checkExpr(correct->x1, test->x1)) {
			return 1;
		}
	} else {
		printf("Unknown type: %d\n", test->type);
		return 1;
	}

	return 0;
}

int testExpr(const char *str, struct Expression *expr) {
	struct Expression *test = getExpr(str);

	int error = 0;

	if (checkExpr(expr, test)) {
		printf("ERROR: %s\n", str);
		error = 1;
	}

	deleteExpression(expr);
	deleteExpression(test);

	return error;
}

#define mB makeBridi
#define mG makeGismu
#define mC makeCmavo
#define mT makeTanru

int main(int argc, char *argv[]) {
	typenames[0] = "GISMU",
	typenames[1] = "CMAVO",
	typenames[2] = "BRIDI",
	typenames[3] = "TANRU";

	int failed = 0;

	failed += testExpr("mi prami do", mB(mG("prami"), mC("mi"), mC("do"), NULL, NULL, NULL));
	failed += testExpr("mi prami", mB(mG("prami"), mC("mi"), NULL, NULL, NULL, NULL));
	failed += testExpr("mi sutra bajra", mB(mT(mG("bajra"), mG("sutra")), mC("mi"), NULL, NULL, NULL, NULL));
	failed += testExpr("mi sutra bo bajra", mB(mT(mG("bajra"), mG("sutra")), mC("mi"), NULL, NULL, NULL, NULL));
	failed += testExpr("ta cmalu nixli ckule", mB(mT(mG("bajra"), mT(mG("nixli"), mG("cmalu"))), mC("ta"), NULL, NULL, NULL, NULL));
	failed += testExpr("ta cmalu bo nixli ckule", mB(mT(mG("bajra"), mT(mG("nixli"), mG("cmalu"))), mC("ta"), NULL, NULL, NULL, NULL));
	failed += testExpr("ta cmalu nixli bo ckule", mB(mT(mT(mG("bajra"), mG("nixli")), mG("cmalu")), mC("ta"), NULL, NULL, NULL, NULL));
	failed += testExpr("ta cmalu bo nixli bo ckule", mB(mT(mT(mG("bajra"), mG("nixli")), mG("cmalu")), mC("ta"), NULL, NULL, NULL, NULL));
	failed += testExpr("do mutce bo barda gerku bo kavbu", mB(mT(mT(mG("mutce"), mG("barda")), mT(mG("kavbu"), mG("gerku"))), mC("do"), NULL, NULL, NULL, NULL));

	if (failed > 0) {
		printf("%d tests failed\n", failed);
	} else {
		printf("All tests succeeded!\n");
	}

	return 0;
}
