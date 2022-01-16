CC=g++
DEBUG =
OPT = -O3
INCLUDE = .



polygon : main.o
	$(CC) $(OPT) $(DEBUG) main.o -o $@

main.o : main.cpp
	$(CC) $(OPT) $(DEBUG) -c -I $(INCLUDE) main.cpp -o $@



