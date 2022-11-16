#include "shell.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * print_no_file_error - prints the no file error message to STDOUT
 * @exec_name: name of executable (shell that is running)
 *
 * Return: always void.
 */
void print_no_file_error(char *exec_name)
{
	char *buff = NULL;
	char *msg = ": No such file or directory\n";
	int exec_len = 0, msg_len = 0, i = 0, e_i = 0, m_i = 0;

	exec_len = _strlen(exec_name);
	msg_len = _strlen(msg);

	buff = malloc(sizeof(char) * (exec_len + msg_len));
	if (!buff)
		return;
	/* fill buffer with error message */
	while (i < exec_len + msg_len)
	{
		if (i < exec_len)
			buff[i] = exec_name[e_i++];
		else
			buff[i] = msg[m_i++];
		i++;
	}
	write(STDOUT_FILENO, buff, exec_len + msg_len);
	free(buff);
}

/**
 * print_perm_denied - prints the permission denied message to STDOUT
 * @exec_name: name of executable (shell that is running)
 *
 * Return: always void.
 */
void print_perm_denied(char *exec_name)
{
	char *buff = NULL;
	char *msg = ": Permission denied\n";
	int exec_len = 0, msg_len = 0, i = 0, e_i = 0, m_i = 0;

	exec_len = _strlen(exec_name);
	msg_len = _strlen(msg);

	buff = malloc(sizeof(char) * (exec_len + msg_len));
	if (!buff)
		return;
	/* fill buffer with error message */
	while (i < exec_len + msg_len)
	{
		if (i < exec_len)
			buff[i] = exec_name[e_i++];
		else
			buff[i] = msg[m_i++];
		i++;
	}
	write(STDOUT_FILENO, buff, exec_len + msg_len);
	free(buff);
}
/**
 * print_signal_reg_error - prints the sig registry error message to STDOUT
 *
 * Return: always void.
 */
void print_signal_reg_error(void)
{
	write(STDOUT_FILENO, "Failed to register signals in kernal\n", 37);
}

/**
 * print_newline - prints a newline character to stdout
 *
 * Return: always void.
 */
void print_newline(void)
{
	write(STDOUT_FILENO, "\n", 1);
}
