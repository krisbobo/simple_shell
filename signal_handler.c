#include "shell.h"
#include <stdio.h>
#include <signal.h>

void signal_handler(int sig_no);

/**
 * register_signal_handlers - registers signal handlers for kernal
 *
 * Return: 1 (success) -1 (failure).
 */
int register_signal_handlers(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		print_signal_reg_error();
		return (-1);
	}
	/* register more signals if needed */
	return (1);
}

/**
 * signal_handler - Prevents CTRL-C from interrupting shell
 *
 * @sig_no: Holds the signal number
 *
 * Return: none
 */

void signal_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		print_newline();
		print_prompt();
	}
}
