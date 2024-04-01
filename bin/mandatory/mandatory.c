/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:58:52 by tauer             #+#    #+#             */
/*   Updated: 2024/04/02 00:19:15 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	no_bonus(t_data *data, t_arg *arg)
{
	int	tube[2];
	int	tube2[2];
	int	pid;
	int	pid2;

	pid = 0;
	// Création du tube
	if (pipe(tube) == -1)
		return (true);
	// Création d'un processus enfant
	pid = fork();
	if (pid == -1)
		return (true);
	else if (pid != 0)
	{
		// Processus parent
		close(tube[0]);
		dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		dup2(data->env.in_fd, STDIN_FILENO);
		close(data->env.in_fd);
		texec(*data, *arg);
	}
	else
	{
		// Processus enfant
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
		if (pipe(tube2) == -1)
			return (true);
		pid2 = fork();
		if (pid2 == -1)
			return (true);
		else if (pid2 != 0)
		{
			close(tube2[0]);
			close(tube2[1]);
			dup2(data->env.ou_fd, STDOUT_FILENO);
			close(data->env.ou_fd);
			texec(*data, *arg->next);
		}
		else
		{
			close(tube2[1]);
			dup2(tube2[0], STDIN_FILENO);
			close(tube2[0]);
			// texec(*data, *arg);
			exit(1);
		}
	}
	return (false);
}
