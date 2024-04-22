/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:31:51 by tauer             #+#    #+#             */
/*   Updated: 2024/04/22 15:36:54 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	check_err(t_data *data, int *status)
{
	t_arg	*current;

	current = data->arg;
	while (current)
	{
		if ((current->pos == 0 || current->pos == data->env.argc - 1)
			&& (ft_strncmp(current->type, "ERR", 3)))
			return (*status = 4, terror("\nbad in_fd or ou_fd", true));
		if (current->pos != data->env.argc - 2 && ft_strncmp(current->type,
				"ERR", 3))
			*status = 2;
		else if (current->pos == data->env.argc - 2 && ft_strncmp(current->type,
				"ERR", 3))
			return (*status = 3, terror("\nlast arg seems to be an error.",
					true));
		current = current->next;
	}
}

bool	try_rescue_cmd(t_data *data, int status)
{
	if (status == 3 || status == 4)
		texit(data, EXIT_FAILURE);
	else if (status == 2)
	{
		data->pip.pos = data->env.argc - 2;
		terror("executing rescue cmd", true);
		forker(data, true);
	}
	return (true);
}

bool	pipex(t_data *data, int BONUS)
{
	check_err(data, &BONUS);
	if (BONUS != false && BONUS != true)
		return (try_rescue_cmd(data, BONUS));
	else if (!BONUS && data->env.argc == 4)
		return (no_bonus(data), false);
	else if (BONUS && data->env.argc >= 4)
		return (bonus(data), false);
	return (terror("wrong number of args", true), true);
}

void	bonus(t_data *data)
{
	while (data->pip.pos < data->env.argc - 2)
	{
		data->pip.pos++;
		forker(data, false);
	}
	while (wait(NULL) > 0)
		;
	close_if_fd(data);
}

void	no_bonus(t_data *data)
{
	if (data->env.argc <= 5)
		bonus(data);
	texit(data, EXIT_FAILURE);
}
