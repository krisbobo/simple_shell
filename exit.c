#include "shell.h"
#include <stdlib.h>

/**
 * exit_shell - Frees the queue and return exit code
 *
 * @q: Pointer to the queue
 * @status: exit code to exit with
 * @his_q: history queue to free
 * @environ: array of pointers to environmental variables
 *
 * Return: See macro values
 */

void exit_shell(his_q_t *his_q, queue_t *q, int status, char **environ)
{
	write_queue_to_file(his_q, environ);

	free_command_queue(q);
	free_history_queue(his_q);
	exit(status);
}
