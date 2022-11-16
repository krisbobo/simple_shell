#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * write_queue_to_file - Writes history to file upon exit
 *
 * @q: Pointer to the queue
 * @environ: array of pointers to environmental variables
 *
 * Return: none
 */

void write_queue_to_file(his_q_t *q, char **environ)
{
	int check_status = 0, open_fd = 0;
	char *fn = ".simple_shell_history";
	char *home = _getenv("HOME", environ);
	char *abs_path = NULL;

	if (!q)
		return;

	abs_path = combine_path(home, fn);
	if (!abs_path)
		return;
	open_fd = open(abs_path, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (open_fd < 0)
	{
		free(abs_path);
		return;
	}

	write_h_queue(q, open_fd);

	check_status = close(open_fd);
	if (check_status < 0)
	{
		;/* close error */
	}
	free(abs_path);
}

/**
 * combine_path - combines two paths, a directory and a file
 * @dir: directory to combine, presumed to be missing '/' at the end
 * @file: file to combine after directory
 *
 * Description: Example output: /bin/ls
 *              Where "/bin" is the dir, and "ls" is the filename
 * Return: pointer to newly allocated string contaiing both
 */
char *combine_path(char *dir, char *file)
{
	int f_i = 0, d_i = 0, n_i = 0;
	int f_len = 0, d_len = 0, n_len = 0;
	char *new_path = NULL;

	if (!dir || !file)
		return (NULL);

	f_len = _strlen(file);
	d_len = _strlen(dir);
	n_len = d_len + f_len + 1; /* '/' & '\0' */

	new_path = malloc(sizeof(char) * n_len + 1);
	if (!new_path)
		return (NULL);

	while (n_i < n_len)
	{
		if (n_i < d_len)
			new_path[n_i] = dir[d_i++];
		else if (n_i == d_len)
			new_path[n_i] = '/';
		else
			new_path[n_i] = file[f_i++];
		n_i++;
	}
	new_path[n_i] = '\0';
	return (new_path);
}
