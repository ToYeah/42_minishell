#!/bin/bash

# ------------------------------------------------------------------------------
# User settings
# ------------------------------------------------------------------------------
MINISHELL_DIR="../"
MINISHELL_EXE="minishell"
# ------------------------------------------------------------------------------

CASE_DIR="./cases"

BASH_STDOUT_FILE="bash_stdout.txt"
BASH_STDERR_FILE="bash_stderr.txt"
MINISHELL_STDOUT_FILE="minishell_stdout.txt"
MINISHELL_STDERR_FILE="minishell_stderr.txt"

COLOR_RESET="\033[0m"
COLOR_GREEN="\033[32m"
COLOR_RED="\033[31m"

RESULT_ALL=0
RESULT_OK=0
RESULT_KO=0

cleanup () {
	rm -f ${BASH_STDOUT_FILE} ${BASH_STDERR_FILE} ${MINISHELL_STDOUT_FILE} ${MINISHELL_STDERR_FILE}
}

run_tests () {
	cleanup
	run_syntax_tests
}

run_syntax_tests () {
	while read -r line; do
		execute_shell "$line"
		replace_bash_error ${BASH_STDERR_FILE}
		assert_equal "$line"
		cleanup
	done < "${CASE_DIR}/syntax_test.txt"
}

execute_shell () {
	bash -c "$@" > ${BASH_STDOUT_FILE} 2> ${BASH_STDERR_FILE}
	BASH_STATUS=$?
	${MINISHELL_DIR}/${MINISHELL_EXE} -c "$1" > ${MINISHELL_STDOUT_FILE} 2> ${MINISHELL_STDERR_FILE}
	MINISHELL_STATUS=$?
}

assert_equal () {
	DIFF_STDOUT=`diff ${MINISHELL_STDOUT_FILE} ${BASH_STDOUT_FILE}`
	DIFF_STDERR=`diff ${MINISHELL_STDERR_FILE} ${BASH_STDERR_FILE}`
	if [ -z "${DIFF_STDOUT}" ] && [ -z "${DIFF_STDERR}" ] && [ ${MINISHELL_STATUS} -eq ${BASH_STATUS} ]; then
		printf "${COLOR_GREEN}case: $@ [ok]${COLOR_RESET}\n"
		let RESULT_OK++
	else
		printf "${COLOR_RED}case: $@ [ko] return code: minishell=${MINISHELL_STATUS} bash=${BASH_STATUS}${COLOR_RESET}\n"
		if [ -n "${DIFF_STDOUT}" ]; then
			printf "${DIFF_STDOUT}\n"
		fi
		if [ -n "${DIFF_STDERR}" ]; then
			printf "${DIFF_STDERR}\n"
		fi
		let RESULT_KO++
	fi
}

replace_bash_error () {
	grep "bash: -c" ${BASH_STDERR_FILE} > /dev/null
	if [ $? -eq 0 ]; then
		sed -i "" -e 's/bash: -c: line 0:/minishell:/' -e '2d' ${BASH_STDERR_FILE}
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

run_tests
show_results
