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
	cp ../materials/linters/.clang-format Tests/
	cp ../materials/linters/.clang-format C_source/ 
	cp ../materials/linters/.clang-format Qt/ 
	clang-format -i C_source/*c C_source/*h
	clang-format -i Qt/*cpp Qt/*h
	clang-format -i Tests/*c
	rm -rf C_source/.clang-format
	rm -rf Qt/.clang-format
	rm -rf Tests/.clang-format

check_style:
	cp ../materials/linters/.clang-format Tests/
	cp ../materials/linters/.clang-format C_source/ 
	cp ../materials/linters/.clang-format Qt/ 
	clang-format -n C_source/*c C_source/*h
	clang-format -n Qt/*cpp Qt/*h
	clang-format -n Tests/*c
	rm -rf C_source/.clang-format
	rm -rf Qt/.clang-format
	rm -rf Tests/.clang-format
