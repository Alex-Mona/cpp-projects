OS := $(shell uname -s)
CC = g++
FLAG_C = -c
WWW = -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest
LINUX = -lsubunit -lrt -lpthread -lm -g
NAME = SmartCalc_v2
FILES_CC = ./model/model.cc ./controller/controller.cc
FILES_H = ./model/model.h ./controller/controller.h
FILES_O = model.o

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM = $(LIBS)
else
	FLAGS_PLATFORM = $(LIBS) $(LINUX)
endif

all: clean $(NAME).a

$(NAME).a:
	@$(CC) $(FLAG_C) $(FILES_CC) $(FILES_H)
	@ar rcs $(NAME).a $(FILES_O) 

test: $(NAME).a
ifeq ($(OS), Darwin)
	@$(CC) $(WWW) ./unit_test/unit_test.cc ./model/model.cc -o tests.o $(LIBS)
else
	@$(CC) $(WWW) ./unit_test/unit_test.cc ./model/model.cc -o tests.o $(LIBS) $(LINUX)
endif
	@./tests.o

install: clean
ifeq ($(OS), Darwin)
	@mkdir build
	@cd view && qmake && make && make clean && rm Makefile && mv SmartCalc_v2.app ../build/ && cd ../
else
	@mkdir build
	@cd view && qmake && make && make clean && rm Makefile && mv SmartCalc_v2 ../build/ && cd ../
endif
	
uninstall:
	@rm -rf build*

clean:
	@rm -f *.a
	@rm -f *.o
	@rm -f *.out
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
	@rm -f *.info
	@rm -f ./*/*.gch
	@rm -rf build
	@rm -f RESULT_VALGRIND.txt

dvi:
	open dvi.html

dist:
ifeq ($(OS), Darwin)
	rm -rf Archive_SmartCalc_v2/
	mkdir Archive_SmartCalc_v2/
	mkdir Archive_SmartCalc_v2/src
	mv  ./build/SmartCalc_v2.app  Archive_SmartCalc_v2/src/
	tar cvzf Archive_SmartCalc_v2.tgz Archive_SmartCalc_v2/
	rm -rf Archive_SmartCalc_v2/
else
	rm -rf Archive_SmartCalc_v2/
	mkdir Archive_SmartCalc_v2/
	mkdir Archive_SmartCalc_v2/src
	mv  ./build/SmartCalc_v2 Archive_SmartCalc_v2/src/
	tar cvzf Archive_SmartCalc_v2.tgz Archive_SmartCalc_v2/
	rm -rf Archive_SmartCalc_v2/
endif

leaks: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./tests.o

style:
	@cp ../materials/linters/.clang-format ./
	@cd view && clang-format -i ./*.cc ./*.h
	@cd model && clang-format -i ./*.cc ./*.h
	@cd controller && clang-format -i ./*.cc ./*.h
	@cd unit_test && clang-format -n ./*.cc
	@cd view && rm -rf .clang-format
	@cd model && rm -rf .clang-format
	@cd controller && rm -rf .clang-format
	@rm -rf .clang-format