a.out: main.o analyzer.o list.o
	gcc main.o analyzer.o list.o -Wall -Werror

main.o: main.c
	gcc -c main.c -Wall -Werror

analyzer.o: analyzer.c
	gcc -c analyzer.c -Wall -Werror

list.o: list.c
	gcc -c list.c -Wall -Werror

clean:
	rm *.o a.out
