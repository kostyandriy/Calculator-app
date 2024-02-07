CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRC = C_source/*c
OS = $(shell uname)
QMAKE = qmake6

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	EXE_FILE=SmartCalc.app
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lcheck_pic -lrt -lm
	EXE_FILE=SmartCalc
endif

all: install

install:
	mkdir -p build
	cd Qt && $(QMAKE) && make && mv $(EXE_FILE) ../build
    
uninstall:
	rm -rf build
    
dist: install
	tar -cf SmartCalc.tar.gz build/
	rm -rf build
    
extract:
	tar -xvf SmartCalc.tar.gz
    
dvi: open

open:
	open dvi/dvi.html

clean: clean_tests
	cd Qt && rm -rf *.o moc_* -rf ui_* Makefile .qmake.stash
	rm -rf build SmartCalc.tar.gz

gcov_report:
	cd Tests && \
    $(CC) $(GCOVFLAGS) s21_smart_calc_tests.c ../$(SRC) -o s21_smart_calc_tests $(TEST_LIBS) && \
	./s21_smart_calc_tests && \
    gcov -f *gcno *gcda 
	cd Tests && \
	rm -rf *.gcda *.gcno *gcov s21_smart_calc_tests

tests:
	cd Tests && \
	$(CC) s21_smart_calc_tests.c ../$(SRC) -o s21_smart_calc_tests $(TEST_LIBS) -L. --coverage && \
	./s21_smart_calc_tests

valgrind: clean
	cd Tests && \
	$(CC) s21_smart_calc_tests.c ../$(SRC) -o s21_smart_calc_tests $(TEST_LIBS) && \
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./s21_smart_calc_tests

sanitize: clean
	cd Tests && \
	$(CC) s21_smart_calc_tests.c ../$(SRC) -o s21_smart_calc_tests $(TEST_LIBS) -fsanitize=address && \
	./s21_smart_calc_tests

clean_tests:
	cd Tests && \
	rm -rf *.gcno *.gcda s21_smart_calc_tests report *.info *gcov *txt

do_style:
	clang-format -style=Google -i C_source/*c C_source/*h
	clang-format -style=Google -i Qt/*cpp Qt/*h
	clang-format -style=Google -i Tests/*c

check_style:
	clang-format -style=Google -n C_source/*c C_source/*h
	clang-format -style=Google -n Qt/*cpp Qt/*h
	clang-format -style=Google -n Tests/*c
