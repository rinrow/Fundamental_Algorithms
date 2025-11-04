a: 
	gcc -o main.exe ./main.c ./src/solve.c

test: 
	gcc -o ./test_br.exe ./tests/test.c ./src/solve.c
	valgrind --leak-check=full ./test_br.exe
	