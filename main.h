#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
/**
 * struct environ - linkedlist element of enviroment variable
 * @var: variable pair
 * @next: link to next node
*/
typedef struct environ
{
	char *var;
	struct environ *next;
} var_list;
/**
 * struct inbuilt_function - inbuilt functions struct
 * @name: name of function
 * @f: function pointer
*/
typedef struct inbuilt_function
{
	char *name;
	int (*f)(char **av, size_t cmd_count, var_list *head);
} inbuilt;
/*environment variable inherited from calling process*/
extern char **environ;

/* handle printing*/
int _putchar(char c);
int _puts(const char *str);
int _put(const char *str);
void print_digits(unsigned int n);
void print(char **av);

/*get line function*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/*string manipulations*/
int _atoi(char *s);
int is_number(const char *str);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
char **strsplt(char *input, const char *delim);

/*handle vectors (NULL terminated string arrays)*/
int v_count(char **vector);
void v_free(char **vector);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*build linked list from environ and handle the list*/
var_list *add_var_end(var_list **head, const char *str);
var_list *build_env_list(var_list **head, char **env);
size_t var_list_len(var_list **h);
void free_envlist(var_list *head);

/*convert linked list to string array*/
char **var_list2vector(var_list **head);

char *_getenv(var_list **env_list, const char *name);
int get_var__index(var_list **h, const char *name);

/*adding or removing environment variable with linked list*/
int _setenv(const char *name, const char *value, int overwrite,
var_list *env_list);
int _unsetenv(const char *name, var_list *env_list);
int overwrite_env_index(var_list **head, int index, char *variable);
int del_var_at_index(var_list **head, unsigned int index);

/*handling inbuilt functions*/
int (*inb_functs(char *name))(char **, size_t, var_list *);
int __exit(char **av, size_t cmd_count, var_list *head);
int env(char **av, size_t cmd_count, var_list *head);
int __setenv(char **av, size_t cmd_count, var_list *head);
int __unsetenv(char **av, size_t cmd_count, var_list *head);
int cd(char **av, size_t cmd_count, var_list *head);

/* error printing*/
void print_err(char *prc_path, size_t count, const char *err_message);
void print_err_nf(char *prc_path, size_t count, char *cmd,
const char *err_message);
void print_exit_err(char *prc_path, size_t count, const char *str);
void print_cd_err(char *prc_path, size_t count, const char *str);
void print_err_sep(char *prc_path, size_t count, char *sep);

/*helper functions*/
void frees(int n, ...);
int resetdir(int n, char *pwd, char *oldpwd, char *buffer);
int _cd(var_list *env_list, char *dir);
int issep(char *str, int *n);
int check_args(char **av, var_list *head, size_t count);

/*app execution*/
int execute(char **av, var_list *env_list, size_t *cmd_cnt);
#endif