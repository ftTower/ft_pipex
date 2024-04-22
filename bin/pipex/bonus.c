/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:11 by tauer             #+#    #+#             */
/*   Updated: 2024/04/22 14:09:26 by tauer            ###   ########.fr       */
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

void	redir(t_data *data, int in, int out)
{
	if (in < 0 || out < 0)
		return (texit(data, EXIT_FAILURE));
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	child_process(t_data *data, int *tube, t_arg *arg, bool RescueCmd)
{
	close(tube[0]);
	if (data->pip.pos == 1)
		redir(data, data->pip.in_fd, tube[1]);
	else if (RescueCmd && data->pip.pos == data->env.argc - 2)
		redir(data, data->pip.safetyFd, data->pip.ou_fd);
	else if (data->pip.pos == data->env.argc - 2)
		redir(data, tube[0], data->pip.ou_fd);
	else
		redir(data, tube[0], tube[1]);
	close(tube[1]);
	texec(*data, *arg);
}

void	choose_proccess(t_data *data, int *tube, int pid, bool RescueCmd)
{
	if (pid == -1)
		return ;
	else if (pid == 0)
		child_process(data, tube, choose_arg(data), RescueCmd);
	else
	{
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}
}

void	forker(t_data *data, bool RescueCmd)
{
	int	tube[2];
	int	pid;

	if (pipe(tube) == -1)
		texit(data, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		texit(data, EXIT_FAILURE);
	choose_proccess(data, tube, pid, RescueCmd);
}

void	bonus(t_data *data)
{
	data->pip.pos = 0;
	while (data->pip.pos < data->env.argc - 2)
	{
		data->pip.pos++;
		forker(data, false);
	}
	while (wait(NULL) > 0)
		;
	close(data->pip.in_fd);
	close(data->pip.ou_fd);
}
