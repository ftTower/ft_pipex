/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:53:14 by tauer             #+#    #+#             */
/*   Updated: 2024/04/20 13:00:17 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_arg
{
	char			**name;
	char			*type;
	int				pos;
	int				fd;
	char			*path;
	struct s_arg	*next;
}					t_arg;

typedef struct s_env
{
	char			**argv;
	char			**envp;
	int				argc;
	char			**path;

}					t_env;

typedef struct s_pip
{
	int tube[2];
	
	int				in_fd;
	int				ou_fd;
	int				mid_fd;
	int				pos;
	int				status;
	//status 0 : ok
	//status 1 : ok without env
	//status 2 : try with last command
	//status 3 : not ok no in fd or ou fd or wrong args
}					t_pip;

typedef struct s_data
{
	t_arg			*arg;
	t_env			env;
	t_pip			pip;

}					t_data;

#endif