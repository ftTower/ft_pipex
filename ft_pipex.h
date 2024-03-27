/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:45 by tauer             #+#    #+#             */
/*   Updated: 2024/03/28 00:21:29 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//path

typedef struct s_memory
{
	char *name;
	struct s_memory *next;
}	t_memory;

typedef struct s_arg
{
	char *type;
	int	pos;
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
	t_memory mem;
	t_arg arg;
	t_env env;
	
} t_data;

size_t	ft_strlen(const char *str);
bool	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *str, char *charset);

#endif