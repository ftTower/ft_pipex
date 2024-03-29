/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:45 by tauer             #+#    #+#             */
/*   Updated: 2024/03/29 14:40:44 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
# include <fcntl.h>
typedef struct s_arg
{
	char **name;
	char *type;
	int	pos;
	int fd;
	char *path;
	struct s_arg *next;
}		t_arg;

typedef struct s_env
{
	char **argv;
	char **envp;
	int argc;
	char **path;
	
}	t_env;

typedef struct s_data
{
	t_arg *arg;
	t_env env;
	
} t_data;

void	terror(char *err_msg);
void	print_data(t_data data);
void	free_tab(char **tab);


size_t	ft_strlen(const char *str);
bool	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *str, char *charset);
char	*ft_strdup(const char *s);

void	null_data(t_data *data);
bool	set_env(int argc, char **argv, char **envp, t_data *data);


bool	set_arg(t_data *data);
void	free_list(t_data *data);
bool	init_arg(t_data *data);

char	*path_maker(const char *path, const char *exec_name);

#endif