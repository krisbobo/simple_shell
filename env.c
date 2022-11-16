#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int is_name_env(char *token, char *env_name);
void advance_env(char **env_token);
/**
 * print_env - Stores and prints the `env`
 *
 * @envp: Double pointer to tokens
 *
 * Return: 0 (failure) 1 (success)
 */

int print_env(char *envp[])
{
	int i, j, char_ctr, buf_ind, check_write;

	char *buffer;

	i = j = char_ctr = buf_ind = check_write = 0;


	if (!envp)
		return (0);

	while (envp[i])
	{
		j = _strlen(envp[i]);

		char_ctr += j + 1;
		i++;
	}

	buffer = malloc(sizeof(char) * char_ctr + 1);
	if (!buffer)
		return (0);

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			buffer[buf_ind++] = envp[i][j++];

		buffer[buf_ind++] = '\n';
		i++;
	}

	check_write = write(STDOUT_FILENO, buffer, char_ctr);
	free(buffer);
	if (check_write < 0)
		return (0);

	return (1);
}

/**
 * _getenv - gets an environmental variable by name
 *
 * @env_name: name of environmental variable to find, e.g: PATH, HOME, USER
 * @environ: array of pointers to environmental variables
 *
 * Return: pointer to char after equal sign in env, e.g: PATH= ->/bin:/usr/bin
 */
char *_getenv(char *env_name, char **environ)
{
	char *ret = NULL;
	int i = 0;

	if (!environ)
		return (NULL);
	while (*environ[i])
	{
		if (is_name_env(environ[i], env_name))
		{
			ret = environ[i];
			break;
		}
		i++;
	}
	/* advance pointer to after ENV=env_var */
	/*                              ^       */
	if (ret)
		advance_env(&ret);

	return (ret);
}
/**
 * is_name_env - checks if a token begins with PATH=
 * @token: token to check
 * @env_name: name of environmental variable, e.g: PATH, HOME, etc...
 *
 * Return: (1) is path environmental variables, (0) is not path env
 */
int is_name_env(char *token, char *env_name)
{
	int tok_i = 0, path_i = 0;

	if (!token)
		return (0);
	while (token[tok_i] && env_name[path_i])
	{
		if (token[tok_i++] != env_name[path_i++])
			return (0);
	}
	if (tok_i > 1)
		return (1);
	return (0);
}

/**
 * advance_env - takes a pointer to environmental variable and advances
 * to the character beyond the equal sign.
 *
 * @path_env: pointer to the pointer to path token
 *
 * Return: always void.
 */
void advance_env(char **path_env)
{
	char *token = NULL;

	if (!path_env)
		return;
	token = *path_env;
	while (*token != '=')
		token++;
	token++; /* set to character beyond equal sign */
	*path_env = token;
}
