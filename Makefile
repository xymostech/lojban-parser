CC=clang

OBJS=main.o expr.o parser.o lexer.o
HEADERS=$(wildcard *.h)

CFLAGS=-g

all: lojban test

lojban: main.o expr.o parser.o lexer.o
	$(CC) -o $@ $^

test: test.o expr.o parser.o lexer.o
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

parser.o: lexer.h
lexer.o: parser.h
main.o: parser.h lexer.h

parser.c parser.h: parser.y
	bison parser.y

lexer.c lexer.h: lexer.l
	flex lexer.l

clean:
	rm -f *.o lojban lexer.c lexer.h parser.c parser.h
