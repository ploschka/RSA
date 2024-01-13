CC=gcc
CCFLAGS=-O3 -Wall -Wextra -pedantic

rsa: clean
	$(CC) $(CCFLAGS) alg.c rsa.c main.c -o rsa

clean:
	rm -f rsa
