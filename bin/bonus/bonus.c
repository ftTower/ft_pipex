/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:11 by tauer             #+#    #+#             */
/*   Updated: 2024/04/17 11:56:34 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

t_arg	*choose_arg(t_data *data)
{
	t_arg	*current;

	current = data->arg;
	while (current)
	{
		if (current->pos == data->pip.pos + 1)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	first_parent(t_data *data, int *tube, t_arg *arg)
{
	printf("first_parent : %d - %d\n", data->pip.pos, arg->pos);
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	dup2(data->pip.in_fd, STDIN_FILENO);
	close(data->pip.in_fd);
	texec(*data, *arg);
}

void	mid_parent(t_data *data, int *tube, t_arg *arg)
{
	printf("mid parent : %d - %d\n", data->pip.pos, arg->pos);
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	dup2(data->pip.mid_fd, STDIN_FILENO);
	close(data->pip.mid_fd);
	texec(*data, *arg);
	return ;
}

void	first_child(t_data *data, int *tube, t_arg *arg)
{
	printf("first_child : %d - %d\n", data->pip.pos, arg->pos);
	close(tube[1]);
	dup2(tube[0], STDIN_FILENO);
	close(tube[0]);
	dup2(data->pip.mid_fd, STDOUT_FILENO);
	close(data->pip.mid_fd);
	// texec(*data, *arg);
}


void	close_child(t_data *data, int *tube, t_arg *arg)
{
	printf("close child : %d - %d\n", data->pip.pos, arg->pos);
	close(tube[1]);
	dup2(tube[0], STDIN_FILENO);
	close(tube[0]);
	dup2(data->pip.ou_fd, STDOUT_FILENO);
	close(data->pip.ou_fd);
	texec(*data, *arg);
}

//		close_parent

void	choose_proccess(t_data *data, int *tube, int pid)
{
	if (pid != 0)
	{
		if (data->pip.pos == 0)
			first_parent(data, tube, choose_arg(data));
		else
		{
			// data->pip.pos += 1;	
			mid_parent(data, tube, choose_arg(data));
		}
	}
	else
	{
		if (data->pip.pos == data->env.argc - 2)
			close_child(data, tube, choose_arg(data));
		else
			first_child(data, tube, choose_arg(data));
	}
}

void	forker(t_data *data)
{
	int	tube[2];
	int	pid;

	if (pipe(tube) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	// printf("%d\n", data->pip.pos);
	choose_proccess(data, tube, pid);
}

void	bonus(t_data *data)
{
	while (data->pip.pos < data->env.argc - 1)
	{
		printf("[%d - %d]\n", data->pip.pos, data->env.argc);
		forker(data);
		data->pip.pos+=1;
	}
}
