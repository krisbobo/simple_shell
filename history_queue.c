#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * get_history - checks if there is a history file present, pulls from that
 * or creates a new queue if no file is found.
 *
 * Return: pointer to new queue in memory
 */
his_q_t *get_history()
{
	/* check if history file exists, if it does read / build q from it */
	/* else */
	return (create_h_queue());
}
/**
 * create_h_queue - Creates the queue of nodes
 *
 * Return: Address of node
 */

his_q_t *create_h_queue()
{
	his_q_t *q = malloc(sizeof(his_q_t));

	if (!q)
		return (NULL);

	q->front = q->rear = NULL;
	return (q);
}

/**
 * h_enqueue - Adds new node to the front
 *
 * @q: Pointer to queue
 *
 * @command: Points to the first char
 * in the stream
 *
 * Return: (0) failure (1) success
 */

int h_enqueue(his_q_t *q, char *command)
{
	int p_no = 0;

	history_t *new_node;

	if (q->rear)
		p_no = q->rear->priority_number + 1;

	new_node = create_history_t(command, p_no);
	if (!new_node)
		return (0);

	if (!q->rear)
	{
		q->front = new_node;
		q->rear = new_node;
		return (1);
	}

	q->rear->next = new_node;
	q->rear = new_node;
	return (1);
}


/**
 * h_dequeue - Removes the node after executed
 *
 * @q: Pointer to the history queue
 *
 * Return: Node that was removed
 */

history_t *h_dequeue(his_q_t *q)
{
	history_t *old_node = NULL;

	if (!q->front)
		return (NULL);

	old_node = q->front;
	q->front = q->front->next;

	if (!q->front)
		q->rear = NULL;

	return (old_node);
}

/**
 * write_h_queue - Writes the input node to a file
 * descriptor
 *
 * @q: Pointer to the queue
 * @fd: File descriptor
 *
 * Description:  4 bytes = \t + 2 spaces + \n
 *               3 bytes = \t + 2 spaces.
 * Return: none
 */

void write_h_queue(his_q_t *q, int fd)
{
	int s_command = 0, s_number = 0, total = 0, i, j, k, s_i = 0;
	char *priority_n_s = NULL, *node_buffer = NULL;
	history_t *temp = NULL;

	if (!q)
		return;
	temp = q->front;
	while (temp)
	{
		priority_n_s = get_int(temp->priority_number);
		if (!priority_n_s)
			return;
		/* grab len needed for chars in string and number of comm */
		s_number = _strlen(priority_n_s);
		s_command = _strlen(temp->command);
		/* make sure there is enough space for spaces, tabs, + null */
		total = s_number + s_command + 4;
		s_i = s_number + 3;
		node_buffer = malloc(sizeof(char) * total);
		if (!node_buffer)
			return;
		i = j = k = 0;
		while (i < total)
		{
			/* write the tab */
			if (i == 0)
				node_buffer[i] = '\t';
			/* write the number for the history */
			else if (i < s_number + 1)
				node_buffer[i] = priority_n_s[j++];
			/* index of the number, could be refactored */
			else if (i < s_i)
				node_buffer[i] = ' ';
			/* now above index of number, write the command */
			else if (i < total - 1)
				node_buffer[i] = temp->command[k++];
			/* end with a newline, move to next item in history */
			else
				node_buffer[i] = '\n';
			i++;
		}
		free(priority_n_s); /* total - 1: forget \0 */
		write(fd, node_buffer, total - 1);
		free(node_buffer);
		temp = temp->next;
	}
}
