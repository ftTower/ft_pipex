/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:11 by tauer             #+#    #+#             */
/*   Updated: 2024/04/16 22:39:05 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	first_parent(t_data *data, int *tube, t_arg *arg)
{
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	dup2(data->env.in_fd, STDIN_FILENO);
	close(data->env.in_fd);
	texec(*data, *arg);
}


void	close_child(t_data *data, int *tube, t_arg *arg)
{
	close(tube[1]);
	dup2(tube[0], STDIN_FILENO);
	close(tube[0]);
	dup2(data->env.ou_fd, STDOUT_FILENO);
	close(data->env.ou_fd);
	texec(*data, *arg->next);
}

//		close_parent

t_arg	*choose_arg(t_data *data)
{
	t_arg *current;

	current = data->arg;
	while(current)
	{
		if (current->pos == data->env.pos)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// void	choose_proccess(t_data *data)
// {
	
// }

void	forker(t_data *data)
{
	int	tube[2];
	int	pid;

	if (pipe(tube) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	printf("%d\n", data->env.argc);
	// choose_process(data, tube, pid);
}

void	bonus(t_data *data)
{
	data->env.pos = 0;
	while (data->env.pos < data->env.argc)
		forker(data);
}
