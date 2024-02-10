CC = g++
WWW = -std=c++17 -Wall -Werror -Wextra -lstdc++
LIBS= -lsubunit -lrt -lpthread -lm -g -lgtest -c


all: clean test

test: clean
	$(CC) $(WWW) $(LIBS) test.cc -o test
	./test
clean:
	rm -rf a.out test test.dSYM
style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n *.cc ./headers/*.h
	sleep 0.5
	clang-format -style=Google -n *.cc ./headers/*.h
	rm -rf .clang-format
leaks: test
	leaks -atExit -- ./test