/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/03/31 00:42:15 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

bool	setup(int argc, char **argv, char **envp, t_data *data)
{
	null_data(data);
	if (set_env(argc, argv, envp, data))
		return (terror("set_env failure"), true);
	if (set_arg(data))
		return (terror("set arg failure"), true);
	return (false);
}

bool	texec(t_data data, t_arg arg)
{
	if (execve(arg.path, arg.name, data.env.envp) == -1)
		return (true);
	return (false);
}

bool	no_bonus(t_data *data, t_arg *arg)
{
	t_arg *current;
	int tube[2];
	int pid = 0;
	
	if (pipe(tube) == -1)
		return (true);
	pid = fork();
	if (pid == -1)
		return (true);
	else if (pid != 0)
	{
		if (arg->pos == 1)
		{
			dup2(tube[1], 1);
			close(tube[1]);
			close(tube[0]);
			dup2(data->env.in_fd, 0);			
		}
		else if (arg->pos == 2)
		{
			dup2(tube[0], 0);
			close(tube[0]);
			close(tube[1]);
			dup2(data->env.ou_fd, 1);
		}
		texec(*data, *arg);
	}
	else
	{
		close(tube[0]);
		close(tube[1]);
		waitpid(pid, NULL, 0);
	}
	return (false);
}

bool	pipex(t_data *data)
{
	t_arg *current;
	
	current = data->arg;
	if (data->env.argc == 4)
	{
		while(current)
		{
			if (current->pos == 1 || current->pos == 2)
				no_bonus(data, current);
			current = current->next;
		}
	}
	return (false);	
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	printf("\033c");
	if (setup(argc, argv, envp, &data))
		return (1);
	print_data(data);
	if (pipex(&data))
		return (2);
	return (free_list(&data), free_tab(data.env.path), 0);
}
