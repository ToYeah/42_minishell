#!/bin/bash

# ------------------------------------------------------------------------------
# User settings
# ------------------------------------------------------------------------------
MINISHELL_DIR="../"
MINISHELL_EXE="minishell"
# ------------------------------------------------------------------------------

cd `dirname $0`
GRADEME_DIR=`pwd`
CASE_DIR="${GRADEME_DIR}/cases"
OUTPUT_DIR="${GRADEME_DIR}/outputs"
TEST_DIR="${GRADEME_DIR}/test"

LOG_FILE="${GRADEME_DIR}/result.log"
BASH_STDOUT_FILE="${OUTPUT_DIR}/bash_stdout.txt"
BASH_STDERR_FILE="${OUTPUT_DIR}/bash_stderr.txt"
MINISHELL_STDOUT_FILE="${OUTPUT_DIR}/minishell_stdout.txt"
MINISHELL_STDERR_FILE="${OUTPUT_DIR}/minishell_stderr.txt"

COLOR_RESET="\033[0m"
COLOR_GREEN="\033[32m"
COLOR_RED="\033[31m"

RESULT_ALL=0
RESULT_OK=0
RESULT_KO=0

run_all_tests () {
	set_minishell_path
	cleanup
	rm ${LOG_FILE}
	if [ -n "$1" ]; then
		run_tests "$1"
	else
		run_tests "syntax_error"
		run_tests "echo"
		run_tests "exit"
		run_tests "simple_command"
		run_tests "shlvl"
		run_tests "pwd"
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
	 	mkdir -p ${TEST_DIR}
	 	cd ${TEST_DIR}
	 	eval "$SETUP_CMD"
		execute_shell "$TEST_CMD"
		replace_bash_error
		assert_equal "$TEST_CMD" "$SETUP_CMD"
		output_log "$TEST_CMD" "$SETUP_CMD"
		cleanup
	done < "${CASE_DIR}/$1.txt"
}

print_usage () {
	echo "usage: ./grademe.sh [`ls cases | sed 's/\.txt//' | tr '\n' ' ' | sed 's/ *$//'`]"
}

cleanup () {
	rm -f ${BASH_STDOUT_FILE} ${BASH_STDERR_FILE} ${MINISHELL_STDOUT_FILE} ${MINISHELL_STDERR_FILE}
	rm -fr ${TEST_DIR}
}

set_minishell_path () {
	cd ${GRADEME_DIR}
	cd ${MINISHELL_DIR}
	MINISHELL_PATH="`pwd`/${MINISHELL_EXE}"
	cd ${GRADEME_DIR}
}

execute_shell () {
	bash -c "$@" > ${BASH_STDOUT_FILE} 2> ${BASH_STDERR_FILE}
	BASH_STATUS=$?
	${MINISHELL_PATH} -c "$1" > ${MINISHELL_STDOUT_FILE} 2> ${MINISHELL_STDERR_FILE}
	MINISHELL_STATUS=$?
}

assert_equal () {
	DIFF_STDOUT=`diff ${MINISHELL_STDOUT_FILE} ${BASH_STDOUT_FILE}`
	DIFF_STDERR=`diff ${MINISHELL_STDERR_FILE} ${BASH_STDERR_FILE}`
	if is_ok ; then
		printf "${COLOR_GREEN}"
		print_case "$1" "$2"
		printf " [ok]${COLOR_RESET}\n"
		let RESULT_OK++
	else
		printf "${COLOR_RED}"
		print_case "$1" "$2"
		printf " [ko]${COLOR_RESET}\n"
		if [ ${MINISHELL_STATUS} -ne ${BASH_STATUS} ]; then
			printf "exit status: minishell=${MINISHELL_STATUS} bash=${BASH_STATUS}\n"
		fi
		if [ -n "${DIFF_STDOUT}" ]; then
			printf "${DIFF_STDOUT}\n"
		fi
		if [ -n "${DIFF_STDERR}" ]; then
			printf "${DIFF_STDERR}\n"
		fi
		let RESULT_KO++
	fi
}

is_ok () {
	if [ -z "${DIFF_STDOUT}" ] && [ -z "${DIFF_STDERR}" ] && [ ${MINISHELL_STATUS} -eq ${BASH_STATUS} ]; then
		return 0
	fi
	return 1
}

print_case () {
	printf "case: $1"
	if [ -n "$2" ]; then
output_log () {
	echo "---------------------------------" >> ${LOG_FILE}
	if is_ok ; then
		echo -n "[OK] " >> ${LOG_FILE}
	else
		echo -n "[KO] " >> ${LOG_FILE}
	fi
	echo `print_case "$1" "$2"` >> ${LOG_FILE}
	echo "---------------------------------" >> ${LOG_FILE}
	echo "# minishell: stdout" >> ${LOG_FILE}
	cat "${MINISHELL_STDOUT_FILE}" >> ${LOG_FILE}
	echo "# bash     : stdout" >> ${LOG_FILE}
	cat "${BASH_STDOUT_FILE}" >> ${LOG_FILE}
	echo "# minishell: stderr" >> ${LOG_FILE}
	cat "${MINISHELL_STDERR_FILE}" >> ${LOG_FILE}
	echo "# bash     : stderr" >> ${LOG_FILE}
	cat "${BASH_STDERR_FILE}" >> ${LOG_FILE}
	echo "# minishell: exit status = ${MINISHELL_STATUS}" >> ${LOG_FILE}
	echo "# bash     : exit status = ${BASH_STATUS}" >> ${LOG_FILE}
}

replace_bash_error () {
	grep "bash: -c" ${BASH_STDERR_FILE} > /dev/null
	if [ $? -eq 0 ]; then
		sed -i "" -e 's/bash: -c: line 0:/minishell:/' -e '2d' ${BASH_STDERR_FILE}
	else
		sed -i "" -e 's/bash: line 0:/bash:/' ${BASH_STDERR_FILE}
		sed -i "" -e 's/bash:/minishell:/' ${BASH_STDERR_FILE}
	fi
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

run_all_tests $@
show_results
