#include "shell.h"
#include <stdlib.h>
/**
 * create_command - creates space for command structure containing data passed
 * @command: array of pointers to tokens used in command including command
 * itself.
 * @separator: the character separator, either ';', '|', '&', or '\0'(none)
 *
 * Return: pointer to the newly allocated command
 */

command_t *create_command(char separator, char **command)
{
	command_t *ret;

	ret = malloc(sizeof(command_t));
	if (!ret)
		return (NULL);
	ret->separator = separator;
	ret->command = command;
	ret->prev_valid = 1; /* default validity of previous command is true */
	ret->next = NULL;
	return (ret);
}

/**
 * free_command_queue - frees a queue_t of command_t's
 * @q: pointer to our queue containing commands
 *
 * Return: always void.
 */

void free_command_queue(queue_t *q)
{
	command_t *temp = NULL;

	if (!q)
		return;
	temp = q->front;
	while (temp)
	{
		free_command(temp);
		temp = temp->next;
	}
	q->front = q->rear = NULL;
	free(q);
}

/**
 * free_token_list - frees an array of tokens previously malloced
 * @tokens: 2D array of tokens
 *
 * Return: always void.
 */

void free_token_list(char **tokens)
{
	int i = 0;

	if (!tokens)
		return;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * free_command - frees a command pointer of its token list and itself
 * @command: command to free
 *
 * Return: always void.
 */
void free_command(command_t *command)
{
	if (command)
	{
		free_token_list(command->command);
		free(command);
	}
}
