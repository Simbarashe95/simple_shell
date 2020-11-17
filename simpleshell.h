#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	scrpt_lst_s
{
	char		**av;
	struct scrpt_lst_s	*next;
	struct scrpt_lst_s	*prev;
	char		flag;
}		scrpt_lst;

int _puts(char *str);
int _strlen(char *str);
char	**strtoav(char *str, const char *delim);
#endif /* SIMPLESHELL_H */
