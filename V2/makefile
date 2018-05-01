ACCENT=/home/j/l/jlaplace/tpLanguage/Compil/accent/accent/accent 
ENTIRE=/home/j/l/jlaplace/tpLanguage/Compil/accent/entire/entire.c 
LEX=lex
CC=gcc

$(NOM) :	yygrammar.c lex.yy.c auxil.c
		$(CC) -o $(NOM) yygrammar.c lex.yy.c auxil.c $(ENTIRE)

lex.yy.c :      $(NOM).lex
		$(LEX) $(NOM).lex

yygrammar.c :   $(NOM).acc
		$(ACCENT) $(NOM).acc