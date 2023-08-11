CC	=	gcc -Wall -Wextra -Werror -std=c11 -g
SRC	=   calc.c chek.c pars.c
OBJ	=	$(SRC:%.c=%.o)

all: install
	./build/Calc.app/Contents/MacOS/Calc
%.o: %.c
	$(CC) -c $<

install: 
	cd build/ && cmake build .
	make -C build

uninstall:
	rm -Rf build/CMakeFiles
	rm -Rf build/Calc_autogen
	rm -Rf build/Calc.app
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf build/Makefile 
	

clean:
	rm -rf $(OBJ)
	rm -rf *.gcno *.gcda ./test
	rm -rf ./test_output/ test.info
	rm -rf Calc.tar
	rm -rf test.dSYM
	rm -rf html

dvi:
	doxygen doxygen/Doxyfile
	open html/index.html

dist:
	tar --totals -cvf Calc.tar build/Calc.app/Contents/MacOS/Calc

tests:
	$(CC) -lgcov -coverage test.c $(SRC) -lcheck -lm -lpthread -o test
	./test


gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o test_output test.info
	@cd ./test_output ; open index.html

