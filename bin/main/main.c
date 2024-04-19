/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/04/19 16:07:47 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	pipex(t_data *data, int BONUS)
{
	if (BONUS == false && data->env.argc == 4)
		return (no_bonus(data, data->arg->next));
	if (BONUS == true && data->env.argc >= 4)
		return (bonus(data), false);
	return (terror("wrong number of args", true), true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	write(1, "\033c", 3);
	if (setup(argc, argv, envp, &data))
		return (1);
	print_data(data);
	if (pipex(&data, false))
		texit(&data, EXIT_FAILURE);
	return (texit(&data, EXIT_FAILURE), 0);
}