/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 13:59:09 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

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
