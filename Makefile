y:	y.l y.y
	bison -d y.y
	flex y.l
	gcc -o compiler y.tab.c lex.yy.c -lfl
