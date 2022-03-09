
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99

obj/parsing.o: src/preprocessing/parsing.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $^ -o $@

obj/padding.o: src/preprocessing/padding.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $^ -o $@

obj/sha256.o: src/sha256.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $^ -o $@

paddingtest: obj/padding.o obj/parsing.o
	mkdir -p out/
	$(CC) $(CFLAGS) $^ test/padding.c -o out/$@

sha256test: obj/padding.o obj/parsing.o obj/sha256.o
	mkdir -p out/
	$(CC) $(CFLAGS) $^ test/sha256.c -o out/$@

clean:
	rm -rf out/
	rm -rf obj/

