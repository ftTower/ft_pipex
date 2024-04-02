/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:53:14 by tauer             #+#    #+#             */
/*   Updated: 2024/04/02 15:11:48 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_arg
{
	char **name;
	char *type;
	int	pos;
	int fd;
	char *path;
	struct s_arg *next;
}		t_arg;

typedef struct s_envL
{
	int	max_size_line;

	int argv_pos;
	int envp_pos;
	int argc_pos;
	int path_pos;
	int status_pos;
	int in_fd_pos;
	int ou_fd_pos;
	
}	t_envL;

typedef struct s_env
{
	char **argv;
	char **envp;
	int argc;
	char **path;
	int	status;
	int	in_fd;
	int ou_fd;
	
}	t_env;

typedef struct s_data
{
	t_arg *arg;
	t_env env;
	t_envL envl;
	
} t_data;

#endif