all: build mtest

build: laba_2_2.c
	gcc laba_2_2.c -o main -lm -std=c89
run:
	./main
mtest:
	gcc -o test -Dmain=_main laba_2_2.c laba_2_2_test.c -lm
	./test
valgrind:
	valgrind --leak-check=full ./main
linter:
	cppcheck -q --enable=all --inconclusive laba_2_2.c