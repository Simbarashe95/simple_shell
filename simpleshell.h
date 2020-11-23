#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 1024

#define INTERACTIVE 0
#define NONINTERACTIVE 1
#define FROMFILE 2

typedef struct			cmd_lst_s
{
	char			*cmd;
	char			**av;
	int			exe;
	char			flag;
	struct cmd_lst_s	*next;
	struct cmd_lst_s	*prev;
}				cmd_lst_t;

typedef struct	cmd_lst_lst_s
{
		char			*list;
		cmd_lst_t		*head;
		struct cmd_lst_lst_s	*next;
}					cmd_lst_lst_t;

int	add_cmd_lst(char *cmd, cmd_lst_t **head, char flag);
int	strsplit(cmd_lst_lst_t *llav, char *str);

/**
 * struct data_s - the data structure
 *
 * @env: environment
 * @mode: interactive, non interactive or from file
 * @bash: the argv[0]
 */

typedef struct data_s
{
	char **env;
	char **alias;
	int mode;
	int lines;
	char *bash;
	cmd_lst_lst_t *llav_head;
} data_t;

/* MAIN */
int sh_start(data_t *data, int fd);

/* SH_GETLINE  */
int sh_getline(char **line, int fd);
const char *_strchr(const char *str, char c);	

/* UTIL_DATA */
data_t *sh_data_new(char **argv, char **env);
void *sh_data_delete(data_t *data);

/* UTIL_ENV */
char **sh_get_env(char **env);
void sh_delete_env(char **env);
char *sh_get_env_var(char *var, char **env);

/* UTIL_MEM */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* UTIL_STR */
int _puts(char *str);
int _strlen(char *str);
char *_strdup(char *str);
const char	*_strchr(const char *s, char c);
char	**strtoav(char *str, const char *delim);
int	_strcmp(char *s1, char *s2);
char *_strndup(char *str, int n);
char *str_concat(char *s1, char *s2);
char *c_concat(char *s, char c);

/* FREE_LISTS */
int	free_av(char **av);
void	free_cmd_lst(cmd_lst_t *node);
void	free_cmd_lst_lst(cmd_lst_lst_t *llav);
int	free_all(cmd_lst_lst_t **head);

void expansion_path(char **arg, char *path_var);

#endif /* SIMPLESHELL_H */
