#ifndef MAIN_H
#define MAIN_H

#include <signal.h>
#include <stdbool.h> 
#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define BUF_READ 1024    
#define BUF_WRITE 1024
#define MAX 100
#define NEGATIV -1
#define FLAG 0  /*REG_FLAG 0*/
#define OR 1
#define AND 2
#define CHAIN 3
#define LOWER 1
#define UNSIG 2
#define GETLINE 0
#define STRTOK 0
#define H_NAME "history"
#define HIST_SIZE 4096

extern char **envrmt;

/**
 * struct Node - singly linked list
 * @value: the number field
 * @ptr: a string
 * @next: points to the next node
 */
typedef struct Node
{
	int value;
	char *ptr;
	struct Node *next;
} node;

/**
 * struct DataNode - contains simulated arguments for a function pointer.
 * @arg: a string generated from getline that holds arguments.
 * @av: an array of strings generated from @arg.
 * @path: the path string for the current command.
 * @ac: the number of arguments.
 * @line: the number of errors encountered.
 * @code_err: the exit() error code.
 * @flag: a flag indicating whether this line of input should be counted.
 * @pname: the name of the program's file.
 * @env: a linked list representing a local copy of the environment variables.
 * @envrmt: a custom-modified copy of the environ from the linked list env.
 * @history: the node for the command history.
 * @alias: the node for the command alias.
 * @rep_env: a flag that indicates whether environ has been changed.
 * @status: the return status of the most recent executed command.
 * @buff: the address of the pointer to sep_buff, used for chaining.
 * @buff_type: the type of command buffer (CMD_type ||, &&, ;).
 * @fd_get: the file descriptor used for reading line input.
 * @hlines: the number of lines in the history.
 */

typedef struct DataNode
{
	size_t line;
    int ac;
	int code_err;
	char *arg;
    int rep_env;
    int status;
    int flag;
	char **av;
	char *path;
	
	char *pname;
	node *env;
	char **envrmt;
	node *history;
	node *alias;
	
	char **buff;
	int buff_type;
	int get_fd;
	int hline;
} data;

/**
 * struct bult - contains a builtin string and related function.
 * @cmd: the builtin command flag.
 * @fun: the function
 */

typedef struct bult
{
	char *cmd;
	int (*fun)(data *);
} bult_cmd;


void process_makings(data *arr);
char *base_convert(long int n, int base, int flag);
int start_shell(data *arr, char **av);
bool executable_file(data *arr, char *pth);
char *test_filepath(data *arr, char *pstr, char *cmd);
int other_alias(data *arr);
int exit_fun(data *arr);
int cd_fun(data *arr);
int help_fun(data *arr);
int history_fun(data *arr);
int builtin_commands(data *arr);
void test_cmd(data *arr);
void process_makings(data *arr);
const char *const *take_environ(data *arr);
int adjustenv(data *arr, char *var, char *value);
int notsetenv(data *arr, char *var);
char *value_env(data *arr, const char *name);
int test_setenv(data *arr);
int test_notsetenv(data *arr);
int displayenv_fun(data *arr);
ssize_t accept_array(data *arr, char **buf, size_t *l);
ssize_t accept_data(data *arr);
ssize_t take_buf(data *arr, char *buf, size_t *m);
int _getline(data *arr, char **ptr, size_t *l);
void interrupt_sigint(int num);
char *take_history(data *arr);
int history_creation(data *arr);
int new_history(data *arr, char *buf, int linecount);
void data_remove(data *arr);
void data_set(data *arr, char **av);
void data_free(data *arr, int n);
void node_frre(node **ptr_h);
node *append_node_end(node **h, const char *ptr, int n);
size_t display_ptr(const node *f);
int removenode_nindex(node **first, unsigned int ind);
node *start_node(node *nod, char *prefix, char c);
size_t length(const node *f);
char **vector_display(node *first);
int free_buffer(void **ptr);
char *_memset(char *p, char a, unsigned int h);
void twod_free(char **av);
void *_realloc(void *ptr, unsigned int os, unsigned int ns);
char **_strtok(char *ptr, char *d);
int intractiv(data *arr);
bool delimiter_found(char c, char *delim);
char *begin(const char *stack_high, const char *needl);
int char_display(char d, int fd);
int string_display(char *strr, int fd);
void comment_place(char *buff);
int number_of_err(const char *s);
void _puts(char *str);
void show_error(char *str);
void error_display(data *arr, char *error);
int error_pchar(char c);
int decimal(int val, int fd);
int _putchar(char c);
char *base_convert(long int n, int base, int flag);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
char *_strdup(const char *str);
char *_strncat(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
int var_handle(data *arr);
bool connected(data *arr, char *buf, size_t *p);
void filter_connection(data *arr, char *buf, size_t *s, size_t i, size_t len);
char *mult_chars(const char *div, int beg, int end);
int number_of_err(const char *s);
int string_replace(char **o, char *n);


#endif /* MAIN_H */