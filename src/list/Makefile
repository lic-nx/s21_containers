OS :=$(shell uname -s)
NAME :=$(shell whoami)
CC=gcc
FLAGS:=-lstdc++ -std=c++17 -Wall -Wextra -Werror -g
LIB:=s21_list
TEST:=tests
GCOV:=--coverage


ifeq ($(OS), Darwin)
	FLAGS_PLATFORM =-lgtest --coverage
else
	FLAGS_PLATFORM =-lgtest -lrt -lm -lpthread --coverage
endif

all : test clean
clean :
	rm -rf report test.info gcov f test main *.txt *dSYM *.a *.o *.g* */*.o */*.a */*/*.o *.g* */*.g* */*/*.g*

test : clean $(LIB).a $(TEST).o
	$(CC) $(TEST).o -L. $(LIB).a -o test $(FLAGS_PLATFORM) $(FLAGS)
	./test
	
$(TEST).o : $(TEST).cc
	$(CC) $(FLAGS) -c $(TEST).cc -o $@

# библиотека для теста
$(LIB).a : $(LIB).cc
	$(CC) -g -c $^ -o $(LIB).o $(FLAGS_PLATFORM)
	ar rc $@ $(LIB).o
	ranlib $@

#gcov
gcov_report : clean $(TEST).o $(LIB).a
	$(CC) $(TEST).o -L. $(LIB).a -o gcov $(FLAGS_PLATFORM) $(FLAGS)
	./gcov 
	gcov $(LIB).c
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info 
	open report/index.html 
	

valgrind: clean test
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose ./test
	

check: 
	@# cp ../materials/linters/.clang-format .clang-format && cp ../materials/linters/.clang-format Tests/.clang-format
	clang-format -style=Google -n *.h *.cc 
	 
	

