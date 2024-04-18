/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/04/18 17:40:54 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	acces_no_bonus(t_data *data, t_arg *current)
{
	if (data->env.argc == 4)
	{
		current = current->next;
		no_bonus(data, current);
		free_list(data);
		free_tab(data->env.path);
		return (false);
	}
	return (true);
}

bool	pipex(t_data *data)
{
	if (data->env.argc >= 4)
	{
		// if (data->env.argc == 4)
		// 	no_bonus(data, data->arg->next);
		bonus(data);
		return (false);
	}
	return (terror("too few args"), true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// printf("\033c");
	if (setup(argc, argv, envp, &data))
		return (1);
	// print_data(data);
	if (pipex(&data))
		return (2);
	return (free_list(&data), free_tab(data.env.path), 0);
}
