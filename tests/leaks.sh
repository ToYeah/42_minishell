#!/bin/bash

# ------------------------------------------------------------------------------
# User settings
# ------------------------------------------------------------------------------
MINISHELL_DIR="../"
MINISHELL_EXE="minishell_leaks"
MAKE_TARGET="leaks"
# ------------------------------------------------------------------------------

cd `dirname $0`
SCRIPT_DIR=`pwd`
CASE_DIR="${SCRIPT_DIR}/cases"
OUTPUT_DIR="${SCRIPT_DIR}/outputs"
TEST_DIR="${SCRIPT_DIR}/test"

LOG_FILE="${SCRIPT_DIR}/leaks.log"
MINISHELL_STDOUT_FILE="${OUTPUT_DIR}/minishell_stdout.txt"

COLOR_RESET="\033[0m"
COLOR_GREEN="\033[32m"
COLOR_RED="\033[31m"

RESULT_ALL=0
RESULT_OK=0
RESULT_KO=0

run_all_tests () {
	set_minishell_path
	cleanup
	rm -f ${LOG_FILE}
	if [ -n "$1" ]; then
		run_tests "$1"
	else
		for file in `ls ${CASE_DIR} | sed 's/\.txt//'`; do
			run_tests "${file}"
		done
	fi
}

run_tests () {
	if [ ! -e "${CASE_DIR}/$1.txt" ]; then
		print_usage
		exit 1
	fi
	while read -r line; do
		TEST_CMD=`echo "$line" | cut -d ',' -f 1`
		SETUP_CMD=`echo "$line" | cut -d ',' -f 2 -s`
		execute_shell "$TEST_CMD"
		assert "$TEST_CMD" "$SETUP_CMD"
		output_log "$TEST_CMD" "$SETUP_CMD"
	done < "${CASE_DIR}/$1.txt"
	cleanup
}

print_usage () {
	echo "usage: ./leaks.sh [`ls cases | sed 's/\.txt//' | tr '\n' ' ' | sed 's/ *$//'`]"
}

cleanup () {
	rm -f ${MINISHELL_STDOUT_FILE}
	if [ -e "${TEST_DIR}" ]; then
		chmod -R 777 ${TEST_DIR}
		rm -fr ${TEST_DIR}
	fi
}

prepare_test_dir () {
	if [ -e "${TEST_DIR}" ]; then
		chmod -R 777 ${TEST_DIR}
		rm -fr ${TEST_DIR}
	fi
	mkdir -p ${TEST_DIR}
	cd ${TEST_DIR}
	eval "${SETUP_CMD}"
	cd ${TEST_DIR}
}

set_minishell_path () {
	cd ${SCRIPT_DIR}
	cd ${MINISHELL_DIR}
	MINISHELL_PATH="`pwd`/${MINISHELL_EXE}"
	cd ${SCRIPT_DIR}
}

execute_shell () {
	prepare_test_dir
	${MINISHELL_PATH} -c "$1" > ${MINISHELL_STDOUT_FILE} 2> /dev/null
}

assert () {
	if is_ok ; then
		printf "${COLOR_GREEN}"
		print_case "$1" "$2"
		printf " [ok]${COLOR_RESET}\n"
		let RESULT_OK++
	else
		printf "${COLOR_RED}"
		print_case "$1" "$2"
		printf " [ko]${COLOR_RESET}\n"
		cat ${MINISHELL_STDOUT_FILE} | grep bytes
		let RESULT_KO++
	fi
}

is_ok () {
	cat ${MINISHELL_STDOUT_FILE} | grep "0 leaks for 0 total leaked bytes." > /dev/null
	return $?
}

print_case () {
	echo  -n "case: $1"
	if [ -n "$2" ]; then
		echo -n " [setup: `echo $2`]"
	fi
}

output_log () {
	echo "---------------------------------" >> ${LOG_FILE}
	if is_ok ; then
		echo -n "[OK] " >> ${LOG_FILE}
	else
		echo -n "[KO] " >> ${LOG_FILE}
	fi
	echo `print_case "$1" "$2"` >> ${LOG_FILE}
	echo "---------------------------------" >> ${LOG_FILE}
	cat ${MINISHELL_STDOUT_FILE} | grep bytes >> ${LOG_FILE}
}

show_results () {
	let "RESULT_ALL = RESULT_OK + RESULT_KO"
	if [ ${RESULT_ALL} -eq ${RESULT_OK} ]; then
		printf "${COLOR_GREEN}${RESULT_OK}/${RESULT_ALL}${COLOR_RESET}\n"
		exit 0
	else
		printf "${COLOR_RED}${RESULT_OK}/${RESULT_ALL}${COLOR_RESET}\n"
		exit 1
	fi
}

make -C "${MINISHELL_DIR}" ${MAKE_TARGET}
run_all_tests $@
show_results
