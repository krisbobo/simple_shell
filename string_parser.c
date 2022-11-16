#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

#define LOGIC_DELIMS "&|;"

int is_logic(char *token);
char **get_command_tokens(char **raw_tokens, int beg_ind, int end_ind);
/**
 * parse_string - Writes tokens to a linked list
 *
 * @str: Pointer to the token stream
 *
 * Return: NULL (failure) head (success)
 */

queue_t *parse_string(char *str)
{
	char **raw_tokens, **sub_tokens;
	char separator = '\0';
	int beg_ind = 0, tok_ind = 0, end_ind = -1, sep_ind = -1;

	queue_t *q = NULL;

	if (!str)
		return (NULL);

	q = create_queue();
	if (!q)
		return (NULL);
	raw_tokens = strtow(str, NORM_DELIMS);

	if (!raw_tokens)
		return (NULL);

	/* does not deal with logical seperators combined with words e.g: */
	/* echo cat&&echo test, echo cat&& echo test, etc... */
	while (raw_tokens[tok_ind]) /* NULL terminated array of tokens */
	{
		if (is_logic(raw_tokens[tok_ind + 1]))
		{
			/* create new node */
			end_ind = tok_ind; /* token before logic token */
			sub_tokens = get_command_tokens(raw_tokens, beg_ind, end_ind);
			if (!sub_tokens)
			{
				free_token_list(raw_tokens);
				free_command_queue(q);
				return (NULL);
			}
			separator = (sep_ind >= 0) ? *(raw_tokens[sep_ind]) : '\0';
			if (!enqueue(q, separator, sub_tokens)) /* insert fail */
			{
				/* free everything & return NULL */
				free_token_list(sub_tokens);
				free_token_list(raw_tokens);
				free_command_queue(q);
				return (NULL);
			}
			sep_ind = tok_ind + 1; /* found seperator */
			beg_ind = sep_ind + 1; /* beg command index moves forward */
		}
		tok_ind++;
	}
	free_token_list(raw_tokens);
	return (q);
}

/**
 * is_logic - checks if current token is a logical seperator token
 * @token: token to check
 *
 * Return: 1 if it is a logical seperator, 0 if not, -1 if not only sep e.g:
 * &&echo, doesn't account for words before delim, will just return 0, e.g:
 * cat&&echo, cat&&, will return 0.
 */
int is_logic(char *token)
{
	if (!token) /* NULL logical seperator, aka end of input */
		return (1);
	else if (*token == ';')
	{
		if (*(token + 1) == '\0')
			return (1);
		return (-1);
	} /* will not be run if sep is ';' */
	else if (is_delim(*token, LOGIC_DELIMS))
	{
		if (is_delim(*(token + 1), LOGIC_DELIMS))
		{
			if (*(token + 2) == '\0') /* only contains delim and NULL */
				return (1);
			return (-1); /* contains extra characters */
		}
		else
			return (0);
	}
	return (0);
}

/**
 * get_command_tokens - gets the command tokens given raw and beg to end pos's
 * @raw_tokens: array of raw tokens (contains logical tokens like &&, ||, ;
 * @beg_ind: index in raw_tokens of beginning of command, e.g: echo
 * @end_ind: index in raw_tokens of end of command, e.g: cat
 *
 * Return: Pointer to new NULL terminated array of tokens, removing logical sep
 */
char **get_command_tokens(char **raw_tokens, int beg_ind, int end_ind)
{
	char **com_tokens = NULL;

	int com_ind = 0;
	int ctrl_ctr = 0;
	int word_len = 0;

		/* +1 account for index starting at 0, +1 for NULL too */
	com_tokens = malloc(sizeof(char *) * (((end_ind + 1) - beg_ind) + 1));
	if (!com_tokens)
		return (NULL);

	while (beg_ind <= end_ind)
	{
		word_len = 0;

		/* gets length of current token */
		while (raw_tokens[beg_ind][word_len])
			word_len++;

		/* create space for chars of each word */
		com_tokens[com_ind] =  malloc(sizeof(char) * word_len + 1);
		if (!com_tokens[com_ind])
		{
			free_token_list(com_tokens);
			return (NULL);
		}

		ctrl_ctr = 0;

		/* copy the raw_token to word_copy */
		while (raw_tokens[beg_ind][ctrl_ctr])
		{
			com_tokens[com_ind][ctrl_ctr] = raw_tokens[beg_ind][ctrl_ctr];
			ctrl_ctr++;
		}
		com_tokens[com_ind][ctrl_ctr] = '\0';
		beg_ind++, com_ind++;
	}
	com_tokens[com_ind] = NULL; /* NULL terminate the array */
	return (com_tokens);
}
