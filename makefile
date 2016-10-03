compile:
	clear
	gcc main.c umabiblioteca.c heuristica.c -O3 -w -o tp2

executa:
	./tp2

clean:
	rm -r tp2
	clear
