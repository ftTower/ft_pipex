/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:53:14 by tauer             #+#    #+#             */
/*   Updated: 2024/04/03 20:05:52 by tauer            ###   ########.fr       */
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


typedef struct s_env
{
	char **argv;
	char **envp;
	int argc;
	char **path;
	int	status;
	
	int	in_fd;
	int ou_fd;
	int	mid_fd;
	int	pos;

}	t_env;

typedef struct s_data
{
	t_arg *arg;
	t_env env;
	
} t_data;

#endif