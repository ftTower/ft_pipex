/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:53:14 by tauer             #+#    #+#             */
/*   Updated: 2024/04/23 10:38:42 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

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
	int				in_fd;
	int				ou_fd;
	int				safety_fd;
	int				pos;

}					t_pip;

typedef struct s_data
{
	t_arg			*arg;
	t_env			env;
	t_pip			pip;

}					t_data;

#endif