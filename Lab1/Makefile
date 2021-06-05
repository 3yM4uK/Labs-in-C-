all: build mtest

build: laba_1.c
	gcc laba_1.c -o main -lm -std=c89
run:
	./main
mtest:
	gcc -o test -Dmain=_main laba_1.c laba_1_test.c
	./test
valgrind:
	valgrind --leak-check=full ./main
linter:
	cppcheck -q --enable=all --inconclusive laba_1.c