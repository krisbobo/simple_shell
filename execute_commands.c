#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/* switch variables for seperators */
#define NO_SEPARATOR '\0'
#define AND_LOGIC_SEP '&'
#define OR_LOGIC_SEP '|'
#define COMMAND_SEP ';'

int can_execute(command_t *command);
int is_custom_command(char *token);
int execute_normal_command(command_t *command, char *envp[], char *);
int execute_custom_command(command_t *, char **, his_q_t *, queue_t *);
/**
 * execute_commands - executes a queue of commands in FIFO order
 * @command_q: the queue of commands to execute
 * @envp: double pointer to the tokens
 * @his_q: pointer to history queue for use in customs
 * @exec_name: name of current executable, used in error message
 *
 * Return: 1 (success) 0 (failure).
 */
int execute_commands(his_q_t *his_q, queue_t *command_q,
			char *envp[], char *exec_name)
{
	command_t *cur_node = NULL;
	int run_com = 0;
	int is_custom_com = 0;

	cur_node = dequeue(command_q); /* get first command */
	if (!cur_node || !envp) /* queue or environ is empty */
		return (0);

	while (cur_node)
	{
		run_com = can_execute(cur_node);

		if (run_com) /* run the command */
		{
			is_custom_com = is_custom_command(cur_node->command[0]);
			if (is_custom_com >= 0)
				run_com = execute_custom_command(cur_node, envp, his_q, command_q);
			else
				run_com = execute_normal_command(cur_node, envp, exec_name);
		}
		/* set validity of next->prev_valid based on result */
		if (cur_node->next)
			cur_node->next->prev_valid = (run_com == 0) ? 1 : 0;

		/* since we dequeued, free cur_node */
		free_command(cur_node);
		/* advance loop by grabbing next node from queue */
		cur_node = dequeue(command_q);
	}
	return (1);
}

/**
 * can_execute - gets whether or not a command should execute
 * @command: command_t pointer that contains command to check if code is executable
 *
 * Return: 1 (can execute) 0 (can't execute)
 */
int can_execute(command_t *command)
{
	int run_com = 0;

	switch (command->separator)
	{
	case NO_SEPARATOR: /* \0 */
		run_com = 1;
		break;
	case AND_LOGIC_SEP: /* && */
		run_com = (command->prev_valid) ? 1 : 0;
		break;
	case OR_LOGIC_SEP: /* || */
		run_com = (command->prev_valid) ? 0 : 1;
		break;
	case COMMAND_SEP: /* ; */
		run_com = 1;
		break;
	}

	return (run_com);
}

/**
 * is_custom_command - decides if a string containing a command keyword is cus
 * @token: string to check if it is a custom command or not
 *
 * Return: (-1) if it is not custom. Index in customs[] if it is custom
 *                                   (Will be >= 0 in this case)
 */
int is_custom_command(char *token)
{
	char *customs[] = { "exit", "env", "setenv", "unsetenv", "cd", "help",
			"history", NULL };
	int custom_i = 0, j = 0;

	if (!token)
		return (-1);
	while (customs[custom_i]) /* loop through our customs */
	{
		j = 0;
		while (token[j])
		{
			if (token[j] != customs[custom_i][j])
				break;
			j++;
		}
		if (customs[custom_i][j] == '\0') /* match */
			return (custom_i);
		custom_i++;
	}
	return (-1);
}

/**
 * execute_custom_command - executes the custom command in sub process
 * @command: pointer to the command to execute
 * @q: pointer to the queue
 * @envp: double pointer to the token
 * @his_q: history queue to free
 *
 * Return: (1) executed successfully, (0) failed execution
 */
int execute_custom_command(command_t *command, char *envp[], his_q_t *his_q,
				queue_t *q)
{
	char *cmd_tok;
	int check_fnc = 0, exit_status = 0;

	if (!command)
		return (0);
	cmd_tok = command->command[0];
	if (!cmd_tok)
		return (0);
	switch (cmd_tok[0])
	{
	case 'e':
		switch (cmd_tok[1])
		{
		case 'x': /* check exit */
			exit_status = _atoi(command->command[1]);
			free_command(command);
			exit_shell(his_q, q, exit_status, envp);
			break;

		case 'n': /* check env */
			check_fnc = print_env(envp);
			break;
		}
		break;
	case 'h':
		switch (cmd_tok[1])
		{
		case 'i': /* checks history */
			write_h_queue(his_q, STDOUT_FILENO);
			break;
		}
		break;
	}
	if (check_fnc < 1)
		return (0);
	return (1);
}
/**
 * execute_normal_command - executes the normal command in sub process
 * @command: pointer to the command to execute
 * @envp: double pointer to the tokens
 * @exec_name: pointer to string to pass to error message
 * Return: exit status of executed process (0 on success, error code on fail)
 */
int execute_normal_command(command_t *command, char *envp[], char *exec_name)
{
	int pid = 0;
	int process_status = 0;
	int wait_err = 0;

	char *file_w_path = NULL;

	file_w_path = get_file_path(command->command[0], envp);
	if (!file_w_path)
	{
		print_no_file_error(exec_name);
		return (98);
	}
	pid = fork();
	if (pid < 0) /* fork failure, too many processes open */
		return (98);
	else if (pid == 0) /* child process */
	{

		execve(file_w_path, command->command, envp);
		/* child process should exit on success so this shouldn't run */
		print_perm_denied(exec_name);
		exit(98); /* process failed to execute, return 98 to parent */
	}
	else /* parent */
	{
		wait_err = waitpid(pid, &process_status, 0);
		if (file_w_path != command->command[0]) /* path changed */
			free(file_w_path);
		if (wait_err < 0)
			return (98);
		return (process_status);
	}
	return (98); /* should not hit this return ever, failure if it does */
}
