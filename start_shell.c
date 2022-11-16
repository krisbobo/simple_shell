#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int do_shell_eof_or_newline(char *input, int bytes_read);

/**
 * start_shell - starts our loop looking for user's commands
 *
 * @environ: array of environmental variables
 * @exec_name: name of executable (name of our shell)
 *
 * Return: 0 on success, anything else on failure, error code dependent
 */
int start_shell(char **environ, char *exec_name)
{
	char *input = NULL;
	size_t input_buff_size = 0;
	ssize_t bytes_read = 0;
	queue_t *com_q = NULL;
	his_q_t *his_q = NULL;

	/* attempt to register signal handlers and build history */
	if (register_signal_handlers() < 0)
		return (-1);
	his_q = get_history();
	if (!his_q)
		return (-1);
	while (1)
	{
		/* check if being used in interactive mode, if so: print */
		if (isatty(STDIN_FILENO))
			print_prompt();
		bytes_read = getline(&input, &input_buff_size, stdin);
		if (bytes_read <= 0 || input[0] == '\n')
		{
			/* EOF was received if return is 0 */
			if (!do_shell_eof_or_newline(input, bytes_read))
				return (0);
			continue;
		}
		fflush(stdin);
		/* attempt to parse the inputted line into a command queue */
		com_q = parse_string(input);
		if (!com_q)
			return (0);
		/* add the input to history & disgard b/c command Q built */
		if (input)
		{
			h_enqueue(his_q, input); /* add command to history */
			free(input);
			input = NULL;
		}
		/* attempt to execute the current command queue and move to */
		/* the next line after freeing the queue */
		if (execute_commands(his_q, com_q,
					environ, exec_name) < 0)
			return (-1);
		free_command_queue(com_q);
	}
	return (0);
}
/**
 * print_prompt - prints the prompt for user to input command
 *
 * Return: always void.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "> ", 2);
}
/**
 * do_shell_eof_or_newline - decides if received input is EOF or \n
 * @input: pointer to input string to be freed b/c will either exit
 *         or reprint prompt and get new input, so we must free.
 * @bytes_read: bytes read by getline(), used to determine if EOF
 *
 * Return: (1) newline was received, (0) EOF was received
 */
int do_shell_eof_or_newline(char *input, int bytes_read)
{

	/* user pressed return, got new line, free input and continue */
	if (input)
	{
		free(input);
		input = NULL;
	}
	if (bytes_read <= 0)
	{
		if (isatty(STDIN_FILENO))
			print_newline();
		fflush(stdin);
		return (0); /* EOF received, exit shell */
	}
	return (1);
}
