.PHONY: build run valgrind s21_matrix_oop_oop.a clean test test_valgrind

OS = $(shell uname)
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
LCOVFLAGS = -fprofile-arcs -ftest-coverage
# LDFLAGS =  -lgtest_main -pthread -fprofile-arcs -ftest-coverage
GTESTFLAGS = -lgtest -lstdc++
SOURCE_FILE = array/s21_array.h list/s21_list.h map/s21_map.h multiset/s21_multiset.h queue/s21_queue.h set/s21_set.h stack/s21_stack.h vector/s21_vector.h
TEST_FILE = tests/array_tests.cc tests/list_tests.cc tests/queue_tests.cc tests/stack_tests.cc tests/map_tests.cc tests/multiset_tests.cc tests/set_tests.cc tests/vector_tests.cc

ifeq ($(OS), Linux)
	CHECKFLAGS = -lgtest -lgtest_main -lrt -lm -lstdc++ -pthread 
else
	CHECKFLAGS = -lgtest -lgtest_main -lm -lpthread  -lstdc++
endif


all: test valgrind

valgrind: test
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_set
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_map
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_multiset
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_vector
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_array	
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_list
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_queue
	valgrind -s --leak-check=full --track-origins=yes ./s21_test_stack
	
test: test_set test_map test_multiset test_vector test_array test_list test_queue test_stack

test_set: clean
	g++ $(CXXFLAGS) tests/set_tests.cc  -o s21_test_set $(CHECKFLAGS)
	./s21_test_set

test_map: clean
	g++ $(CXXFLAGS) tests/map_tests.cc  -o s21_test_map $(CHECKFLAGS)
	./s21_test_map

test_multiset: clean
	g++ $(CXXFLAGS) tests/multiset_tests.cc  -o s21_test_multiset $(CHECKFLAGS)
	./s21_test_multiset

test_vector: clean
	g++ $(CXXFLAGS) tests/vector_tests.cc  -o s21_test_vector $(CHECKFLAGS)
	./s21_test_vector

test_array: clean
	g++ $(CXXFLAGS) tests/array_tests.cc  -o s21_test_array $(CHECKFLAGS)
	./s21_test_array

test_list: clean
	g++ $(CXXFLAGS) tests/list_tests.cc  -o s21_test_list $(CHECKFLAGS)
	./s21_test_list

test_queue: clean
	g++ $(CXXFLAGS) tests/queue_tests.cc  -o s21_test_queue $(CHECKFLAGS)
	./s21_test_queue

test_stack: clean
	g++ $(CXXFLAGS) tests/stack_tests.cc  -o s21_test_stack $(CHECKFLAGS)
	./s21_test_stack

gcov_report: clean
	g++ $(CXXFLAGS)  -c $(SOURCE_FILE) $(CHECKFLAGS) $(LCOVFLAGS)
	g++ $(CXXFLAGS) -c $(TEST_FILE) $(CHECKFLAGS) $(LCOVFLAGS)
	g++ $(LCOVFLAGS)  *.o  -o s21_test $(CHECKFLAGS)
	./s21_test
	lcov --capture --output-file=s21_test.info --directory=.
	genhtml -o report/ s21_test.info
	open ./report/index.html

style:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -n $$(find . -maxdepth 4 -name "s21_*") containers.h containersplus.h
	rm -rf .clang-format

style_in_OK:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -i $$(find . -maxdepth 4 -name "s21_*") containers.h containersplus.h
	rm -rf .clang-format

clean:
	rm -rf s21_test* *.gcno *.gcda *.o *.gch s21_test s21_test.info
	rm -rf $$(find . -maxdepth 2 -name "*.gch")
	rm -rf report
	rm -rf .clang-format