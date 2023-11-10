OS:=$(shell uname -s)
PATH_TO_THIS = ./
THIS = ${PATH_TO_THIS}Makefile
SUPPLEMENTAL_FLAGS = 
#=============================================================================================#
#============================={Настройка компиляторов и библиотек}============================#
#=============================================================================================#
PKG_CONFIG ?= pkg-config 
CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm -Wall -Wextra -Werror -Wunreachable-code ${SUPPLEMENTAL_FLAGS}
INC_DIR = -L./ -I./
CHECK_LIB := ${shell ${PKG_CONFIG} --libs check}
CCOV = -lgcov --coverage 
MATH_LIB := -lm

VALGRIND = valgrind  --leak-check=full --show-leak-kinds=all -s
VALGRIND_LOG = "${PATH_TO_THIS}valgrind_log.log"
number_of_test = $(shell grep -e "ERROR SUMMARY" -c ${PATH_TO_THIS}valgrind_log.log)
number_of_test_with_no_leaks = $(shell grep -e "ERROR SUMMARY: 0" -c ${PATH_TO_THIS}valgrind_log.log)



ifeq (${DEBUG}, 1)
	CFLAGS += -O0
else
	CFLAGS += -O1
endif

ifeq (${PROFILE}, 1)
	CFLAGS += -pg
endif
#=============================================================================================#
#=============================================================================================#
#=============================================================================================#
OBJ_DIR = ${PATH_TO_THIS}obj/
BUILD_DIR = ${PATH_TO_THIS}build/
COV_DIR = ${PATH_TO_THIS}coverage_info/
COV_OBJ_DIR = ${COV_DIR}obj/

COV_EXEC = ${COV_DIR}test_cov
COV_INFO = ${COV_DIR}string.info
COV_REPORT = ${COV_DIR}index.html
#=============================================================================================#
#============================={Файлы библиотеки}==============================================#
#=============================================================================================#
LIB_DIR = ${PATH_TO_THIS}src/
ifeq ($(OS), Darwin)
	LIB = ${BUILD_DIR}string.a
else
	LIB = ${BUILD_DIR}lib_string.a
endif

LIB_OBJ_DIR = ${OBJ_DIR}lib/

LIB_SRCS = $(shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
LIB_SRCS_NO_PATH = ${shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print | sed 's/.*\///'}
LIB_HEADERS = $(shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)
LIB_OBJS = ${patsubst %.c, ${LIB_OBJ_DIR}%.o, ${LIB_SRCS_NO_PATH}}


#=============================================================================================#
#============================={Файлы Тестов}==================================================#
#=============================================================================================#
TEST_DIR = ${PATH_TO_THIS}tests/
ifeq (${DEBUG}, 1)
	TEST_EXEC = test-debug.out
else
	TEST_EXEC = ${BUILD_DIR}test.out
endif


TEST_OBJ_DIR = ${OBJ_DIR}tests/

TEST_SRCS_NO_PATH = ${shell find ${TEST_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print | sed 's/.*\///'}
TEST_SRCS = $(shell find ${TEST_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
TEST_HEADERS = $(shell find ${TEST_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)
TEST_OBJS = ${patsubst %.c, ${TEST_OBJ_DIR}%.o, ${TEST_SRCS_NO_PATH}}
#=============================================================================================#
#================================={Файлы для покрытия}==========================================#
#=============================================================================================#
COV_OBJS = ${patsubst %.c, ${COV_OBJ_DIR}%.o, ${TEST_SRCS_NO_PATH} ${LIB_SRCS_NO_PATH}}
#=============================================================================================#
#============================={Исполниемый файл}==============================================#
#=============================================================================================#
EXECUTED_DIR = ${PATH_TO_THIS}executed/
EXEC_OBJ_DIR = ${OBJ_DIR}executed/

EXEC_SRCS_NO_PATH = ${shell find ${EXECUTED_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print | sed 's/.*\///'}
EXEC_SRCS = $(shell find ${EXECUTED_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
EXEC_HEADERS = $(shell find ${EXECUTED_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)
EXEC_OBJS = ${patsubst %.c, ${EXEC_OBJ_DIR}%.o, ${EXEC_SRCS_NO_PATH}}

EXEC = ${BUILD_DIR}executable.out
#=============================================================================================#
#============================={Основные цели}=================================================#
#=============================================================================================#

all: clean ${BUILD_DIR} string.a test
executed: ${BUILD_DIR} ${EXEC} run_executed

#=============================================================================================#
#=============================={Сборка библиотеки}============================================#
#=============================================================================================#
.PHONY: string.a
string.a:${BUILD_DIR} ${LIB}
	cp ${LIB} ${PATH_TO_THIS}string.a
	cp ${LIB} ${PATH_TO_THIS}lib_string.a


${LIB}: ${LIB_OBJS}
	ar rc $@ $^
	ranlib $@

${LIB_OBJS}: $(LIB_SRCS) $(LIB_HEADERS) ${LIB_OBJ_DIR}
	$(CC) $(CFLAGS) $(LIB_SRCS) -c ${MATH_LIB}
	mv *.o ${LIB_OBJ_DIR}

${LIB_OBJ_DIR}:
	mkdir -p $(LIB_OBJ_DIR)

#=============================================================================================#
#=============================={Сборка тестов}================================================#
#=============================================================================================#
.PHONY: run_tests
test: ${BUILD_DIR} ${TEST_EXEC}
	${TEST_EXEC}

${TEST_EXEC}: ${TEST_OBJS} ${LIB}
	$(CC) $(CFLAGS)  ${INC_DIR}  $(TEST_OBJS) -o "$@" ${LIB} ${CHECK_LIB} ${MATH_LIB}

${TEST_OBJS}: $(TEST_SRCS) $(TEST_HEADERS) ${TEST_OBJ_DIR}
	$(CC) $(CFLAGS) $(TEST_SRCS) -c
	mv *.o ${TEST_OBJ_DIR}

${TEST_OBJ_DIR}:
	mkdir -p $(TEST_OBJ_DIR)
#=============================================================================================#
#=============================={Сборка Исполняемого файла}====================================#
#=============================================================================================#
.PHONY: run_executed
run_executed: ${EXEC}
	${EXEC}
${EXEC}: ${EXEC_OBJS} ${LIB}
	$(CC) $(CFLAGS)  ${INC_DIR}  $(EXEC_OBJS) -o "$@" ${LIB} ${MATH_LIB}

${EXEC_OBJS}: $(EXEC_SRCS) $(EXEC_HEADERS) ${EXEC_OBJ_DIR}
	$(CC) $(CFLAGS) $(EXEC_SRCS) -c
	mv *.o ${EXEC_OBJ_DIR}

${EXEC_OBJ_DIR}:
	mkdir -p $(EXEC_OBJ_DIR)


#=============================================================================================#
#================================={Покрытие тестами}==========================================#
#=============================================================================================#

${COV_OBJS}:${BUILD_DIR} ${COV_OBJ_DIR}
	make -f ${THIS} SUPPLEMENTAL_FLAGS="${CCOV}" PATH_TO_THIS="${PATH_TO_THIS}"  ${LIB} ${TEST_EXEC}
	mv *.gc* ${COV_OBJ_DIR}
	mv ${LIB_OBJ_DIR}*.o ${TEST_OBJ_DIR}*.o ${COV_OBJ_DIR}

${COV_EXEC}: ${COV_OBJS}
	mv ${TEST_EXEC} ${COV_EXEC}

.PHONY:gcov_report
gcov_report: ${COV_EXEC}
	$(COV_EXEC)
	mv *.gcda ${COV_OBJ_DIR}
	lcov -q -c -d $(COV_OBJ_DIR) -o $(COV_INFO) --exclude "${TEST_SRCS}"
	genhtml -q $(COV_INFO) -o $(COV_DIR)
	open $(COV_REPORT)
	rm -rf *.gc*


${COV_OBJ_DIR}:
	mkdir -p $(COV_OBJ_DIR)
#=============================================================================================#
#=============================================================================================#
#=============================================================================================#
Profile: ${TEST_EXEC} ${LIB}
	${TEST_EXEC}
	gprof app gmon.out
	gprof ./${TEST_EXEC} | python3 gprof2dot.py -s | dot -Tpng -o output.png
	rm -f gmon.out

.PHONY: run_leak
leak: ${BUILD_DIR} ${TEST_EXEC}
	${VALGRIND} ${TEST_EXEC}
.PHONY: run_leak_count
leak_count: ${BUILD_DIR} ${TEST_EXEC}
	${VALGRIND} --log-file=${VALGRIND_LOG} ${TEST_EXEC}
	@echo NUMBER OF ALL TESTS: ${number_of_test}
	@echo NUMBER OF TESTS WITHOUT LEAKS: ${number_of_test}
#=============================================================================================#
#==============================={Вспомогательные функции}=====================================#
#=============================================================================================#
${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

.PHONY: style_check
style_check:
	clang-format -style=google -n ${LIB_SRCS} ${LIB_HEADERS} ${TEST_SRCS} ${TEST_HEADERS}

.PHONY: style_correct
style_correct:
	clang-format -style=google -i ${LIB_SRCS} ${LIB_HEADERS} ${TEST_SRCS} ${TEST_HEADERS}

.PHONY: files_and_dir_counter
files_and_dir_counter:
	@echo Number of files:
	@echo 	"	"[${shell find ${PATH_TO_THIS}src ${PATH_TO_THIS}tests -type f -print | wc -l}]
	@echo Number of directories:
	@echo 	"	"[${shell find ${PATH_TO_THIS}src ${PATH_TO_THIS}tests -type d -print | wc -l}]

.PHONY: string_counter
string_counter:
	@echo Number of strings in C files:
	@echo 	"	"[${shell find ${PATH_TO_THIS}src ${PATH_TO_THIS}tests -name '*.c' -type f -print0 | xargs -0 cat | wc -l}]
	@echo Number of strings in H files:
	@echo 	"	"[${shell find ${PATH_TO_THIS}src ${PATH_TO_THIS}tests -name '*.h' -type f -print0 | xargs -0 cat | wc -l}]

.PHONY: stat
stat: files_and_dir_counter string_counter

CPPCHECK_OUT_FILE = ${PATH_TO_THIS}cppcheck.output.md

cppcheck:
	@cppcheck --enable=all --std=c11  --inconclusive --output-file=${CPPCHECK_OUT_FILE} --template=' | *___{id}___* | {file} |```{line}``` | __{message}`__ |' ${LIB_SRCS} ${LIB_HEADERS}
	@echo '|--|--|--|--|' | cat - ${CPPCHECK_OUT_FILE} > temp && mv temp ${CPPCHECK_OUT_FILE}
	@echo '|id| file| line| message|' | cat - ${CPPCHECK_OUT_FILE} > temp && mv temp ${CPPCHECK_OUT_FILE}
	@sed -i -e 's/'"'"'/`/g' ${CPPCHECK_OUT_FILE}

.PHONY: mini_verter
mini_verter:
	sudo bash ../materials/build/run.sh


GCH = ${shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.gch' -print}
.PHONY: clean
clean:
	rm -fr ${OBJ_DIR}
	rm -rf ${BUILD_DIR}
	rm -f ${GCH}
	rm -f *.o
	rm -f *.log
	rm -fr ${COV_DIR}
	rm -f ${CPPCHECK_OUT_FILE}
	rm -f *.gc*
	rm -f *.a
#=============================================================================================#
#=============================================================================================#
#=============================================================================================#

