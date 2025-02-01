CC = gcc
CFLAGS = -Wall -g3

ifdef SANITIZE
	CFLAGS += -fsanitize=address -fsanitize=undefined
endif

.PHONY: check run sanitized-run clean

check: shd-lib.c
	$(CC) $(CFLAGS) -fPIC -shared -o libshd-lib.so $^ -fsanitize=address -fsanitize=undefined
	./sanitized_tester
	$(CC) $(CFLAGS) -fPIC -shared -o libshd-lib.so $^
	valgrind ./tester

run: libshd-lib.so
	./tester

sanitized-run: libshd-lib.so
	./sanitized_tester

libshd-lib.so: shd-lib.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

clean:
	rm -f libshd-lib.so
