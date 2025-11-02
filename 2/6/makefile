all:
	gcc -o ./a.out -g ./main.c ./src/Sol.c ./src/ErrorHandler.c

check_mem:
	gcc -o ./a.out -g ./main.c ./src/Sol.c ./src/ErrorHandler.c
	valgrind --leak-check=full ./a.out in.txt out.txt