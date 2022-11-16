#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * *create_history_t - Creates a history node
 *
 * @command: Input string
 *
 * @set_p_no: "Index" of the node
 *
 * Return: Pointer to new node
 */

history_t *create_history_t(char *command, int set_p_no)
{
	int size = 0;

	int i = 0;

	char *input = NULL;

	history_t *node = NULL;

	size = _strlen(command);

	input = malloc(sizeof(char) * size + 1);
	if (!input)
		return (NULL);

	while (command[i])
	{
		input[i] = command[i];
		i++;
	}
	input[i] = '\0';

	node = malloc(sizeof(history_t));
	if (!node)
	{
		free(input);
		return (NULL);
	}

	node->command = input;
	node->priority_number = set_p_no;
	node->next = NULL;

	return (node);
}

/**
 * free_history_node - Frees node in history queue
 *
 * @node: Pointer to node
 *
 * Return: none
 */

void free_history_node(history_t *node)
{
	if (!node)
		return;

	if (node->command)
		free(node->command);
	free(node);
}

/**
 * free_history_queue - Frees node in history queue
 *
 * @q: Pointer to queue
 *
 * Return: none
 */

void free_history_queue(his_q_t *q)
{
	history_t *store = NULL, *temp = NULL;

	if (!q)
		return;
	temp = q->front;
	while (temp)
	{
		store = temp->next;
		free_history_node(temp);
		temp = store;
	}

	q->front = q->rear = NULL;
	free(q);
}
