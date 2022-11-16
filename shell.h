#ifndef _SHELL_H_
#define _SHELL_H_
#include <unistd.h>
/* delimeter macros */
#define NORM_DELIMS " \t\a\r\n"
#define PATH_DELIMS ":"

/* external environmental variable array */
extern char **environ;

/**
 * struct command_s - Structure of each node
 *
 * @prev_valid: Check if previous command
 * was successful
 *
 * @separator: Used for character that
 * that separates each command
 *
 * @command: Points to the first char
 * in the stream
 *
 * @next: Address of next node
 *
 */
typedef struct command_s
{
	int prev_valid;

	char separator;
	char **command;
	struct command_s *next;
} command_t;

/**
 * struct queue_s - Structure of queue
 *
 * @front: Pointer to the first node
 *
 * @rear: Pointer to the front+1 node
 *
 */

typedef struct queue_s
{
	command_t *front, *rear;
} queue_t;

/**
 * struct history_s - Structure of history queue
 *
 * @command: Holds the command from getline()
 *
 * @priority_number: Holds the number coorelated
 * to the command input order
 *
 * @next: Pointer to the next node
 *
 */

typedef struct history_s
{
	char *command;

	int priority_number;
	struct history_s *next;
} history_t;

/**
 * struct his_q_s - Structure of queue
 *
 * @front: Pointer to the first node
 *
 * @rear: Pointer to the front+1 node
 *
 */

typedef struct his_q_s
{
	history_t *front, *rear;
} his_q_t;

/* main functionality */
int start_shell(char **environ, char *exec_name);
queue_t *parse_string(char *input_str);
int execute_commands(his_q_t *his_q, queue_t *command_q,
			char *envp[], char *exec_name);
char *get_file_path(char *filename, char *envp[]);

/* free memory */
void free_token_list(char **tokens);
void free_command_queue(queue_t *command_q);
void free_command(command_t *command);

/* build the queue of commands */
command_t *create_command(char separator, char **command);
char **strtow(char *str, char *delims);
int is_delim(char ch, char *delims);
queue_t *create_queue();

/* using our queue */
int enqueue(queue_t *q, char separator, char **command);
command_t *dequeue(queue_t *q);
void print_queue(queue_t *q);

/* history queue */
history_t *create_history_t(char *command, int set_p_no);
void free_history_node(history_t *node);
void free_history_queue(his_q_t *q);

/* history enqueue/dequeue */
his_q_t *get_history();
his_q_t *create_h_queue();
int h_enqueue(his_q_t *q, char *command);
history_t *h_dequeue(his_q_t *q);
void write_h_queue(his_q_t *q, int fd);

/* writing/loading history file */
void write_queue_to_file(his_q_t *q, char **env);

/* custom functions for custom commands */
void exit_shell(his_q_t *his_q, queue_t *q, int status, char **env);
int print_env(char *envp[]);

/* handling signals */
void signal_handler(int sig_no);
int register_signal_handlers(void);

/* custom stdlib */
int _atoi(char *str);
int _strlen(char *str);
char *get_int(int num);
char *_getenv(char *env_name, char **environ);
char *combine_path(char *dir, char *file);

/* print errors */
void print_no_file_error(char *executable_name);
void print_perm_denied(char *executable_name);
void print_signal_reg_error(void);
void print_prompt(void);
void print_newline(void);

#endif /* _SHELL_H_ */
