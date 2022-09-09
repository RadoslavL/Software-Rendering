a.out: main.c
	gcc main.c -lX11

debug: main.c
	gcc -g main.c -lX11
