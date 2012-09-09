#ifndef EXPR_H
#define EXPR_H

enum ExpressionType {
	GISMU,
	CMAVO,
	BRIDI,
	TANRU
};

struct Expression {
	enum ExpressionType type;

	char *word;
	struct Expression *pred;
	struct Expression *tanru_base, *tanru_desc;
	struct Expression *x1, *x2, *x3, *x4, *x5;
};

struct Expression *makeGismu(char *word);
struct Expression *makeCmavo(char *word);
struct Expression *makeBridi(struct Expression *pred,
                             struct Expression *x1,
                             struct Expression *x2,
                             struct Expression *x3,
                             struct Expression *x4,
                             struct Expression *x5);
struct Expression *makeTanru(struct Expression *gismu,
                             struct Expression *tanru_desc);

struct Expression *getExpr(const char *input);
void deleteExpression(struct Expression *expr);

void printExpression(struct Expression *expr, int depth);

#endif /* EXPR_H */
