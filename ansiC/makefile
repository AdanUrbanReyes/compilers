run: a.out $(archivo)
	./a.out $(archivo)

a.out: lenguajec.tab.o lex.yy.o
	gcc lenguajec.tab.o lex.yy.o -ll -lm

lex.yy.c: lenguajec.l
	flex lenguajec.l

lenguajec.tab.c: lenguajec.y
	bison -d lenguajec.y

lenguajec.tab.h: lenguajec.tab.c
	#any rule

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -lfl 

lenguajec.tab.o: lenguajec.tab.c
	gcc -c lenguajec.tab.c

clean:
	rm a.out lenguajec.tab.* lex.yy.*
