/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:11 by tauer             #+#    #+#             */
/*   Updated: 2024/04/18 18:14:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

t_arg	*choose_arg(t_data *data)
{
	t_arg	*current;

	current = data->arg;
	while (current)
	{
		if (current->pos == data->pip.pos)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	child_process(t_data *data, int *tube, t_arg *arg)
{
	close(tube[0]);
	if (arg->pos == 1)
	{
		write(2, "ici1\n", 5);
		dup2(data->pip.in_fd, STDIN_FILENO);
	}
	else if (arg->pos == data->env.argc - 2)
	{
		write(2, "ici2\n", 5);
		dup2(data->pip.ou_fd, STDOUT_FILENO);	
	}
	else
	{
		write(2, "ici3\n", 5);
		dup2(tube[1], STDOUT_FILENO);
	}
	close(tube[1]);
	texec(*data, *arg);
}

void	choose_proccess(t_data *data, int *tube, int pid)
{
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		// printf("[child]\n");
		child_process(data, tube, choose_arg(data));
	}
	else
	{
		// printf("[parent]\n");
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
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
	// choose_proccess(data, tube, pid);
	if (pid == 0)
	{
		close(tube[0]);
		if (data->pip.pos == 1)
		{
			write(2, "ici1\n", 5);
			dup2(data->pip.in_fd, STDIN_FILENO);
		}
		if (data->pip.pos == data->env.argc - 2)
		{
			write(2, "ici2\n", 5);
			dup2(data->pip.ou_fd, STDOUT_FILENO);
		}
		else
			dup2(tube[1], STDOUT_FILENO);
	}
}

void	bonus(t_data *data)
{
	data->pip.pos = 0;
	while (data->pip.pos < data->env.argc - 2)
	{
		data->pip.pos++;
		// printf("[%d - %d]\n", data->pip.pos, data->env.argc);
		// printf("%s - %d\n", choose_arg(data)->name[0], choose_arg(data)->pos);
		forker(data);
	}
	while(wait(NULL) > 0)
		;
	close(data->pip.in_fd);
	close(data->pip.ou_fd);
}
