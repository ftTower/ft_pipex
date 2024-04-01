/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 22:45:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool    acces_no_bonus(t_data *data, t_arg *current)
{
    if (data->env.argc == 4)
	{
		while(current)
		{
			if (current->pos == 1 || current->pos == 2)
				no_bonus(data, current);
			current = current->next;
		}
        return (true);
	}
    return (false);
}

bool	pipex(t_data *data)
{
	t_arg *current;
	
	current = data->arg;
	if (acces_no_bonus(data, current))
        return (true);
	return (false);	
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// printf("\033c");
	if (setup(argc, argv, envp, &data))
		return (1);
	print_data(data);
	if (pipex(&data))
		return (2);
	return (free_list(&data), free_tab(data.env.path), 0);
}
