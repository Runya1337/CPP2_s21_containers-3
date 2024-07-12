CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

all: clean style gcov_report

test: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: test
	@lcov -t "Containers" -o s21_containers.info -c -d . --ignore-errors mismatch,inconsistent
	@lcov -e s21_containers.info '*/src/*/*.h' -o s21_containers_filtered.info --ignore-errors mismatch,inconsistent
	@genhtml -o gcov_report s21_containers_filtered.info --ignore-errors mismatch,inconsistent
	@open ./gcov_report/index.html

clean:
	@rm -rf test *.gcda *.gcno *.o *.info *.a test.dSYM a.out gcov_report

style:
	@clang-format -style=Google -n containers/*.h containers/mapset/*.h containersplus/*.h *.h
	@clang-format -style=Google -n tests/*.cc tests/*.h

clang:
	@clang-format -style=Google -i containers/*.h containers/mapset/*.h containersplus/*.h *.h
	@clang-format -style=Google -i tests/*.cc tests/*.h

valgrind:
	@CK_FORK=no valgrind --leak-check=full --tool=memcheck --leak-check=yes make test

install_brew:
	@cd ~
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_lcov:
	@brew install lcov

