/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:36:00 by tauer             #+#    #+#             */
/*   Updated: 2024/03/29 00:27:23 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

bool	is_cmd(t_data *data, size_t i, t_arg *arg)
{
	char	**args;

	if (execve(arg->name[0], arg->name, data->env.envp) == -1)
		return (true);
	return (false);
}

bool	data_element(t_data *data, t_arg *arg, t_arg *list, size_t i)
{
	arg->type = NULL;
	arg->name = ft_split(data->env.argv[i], " ");
	if (!arg->name)
		return (free_tab(data->env.path), free_list(data), true);
	return (arg->pos = i, arg->next = list, data->arg = arg, false);
}

bool	add_element(t_data *data, size_t i)
{
	t_arg	*list;
	t_arg	*arg;

	list = NULL;
	if (i != 0)
		list = data->arg;
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (free_tab(data->env.path), terror("malloc list"), true);
	else if (!list)
		free(data->arg);
	return (data_element(data, arg, list, i), false);
}

void	free_list(t_data *data)
{
	t_arg	*current;
	t_arg	*temp;

	current = data->arg;
	while (current)
	{
		temp = current->next;
		free_tab(current->name);
		free(current);
		current = temp;
	}
}

bool	create_list(t_data *data)
{
	t_arg	*arg;
	size_t	i;

	i = 0;
	while (data->env.argv[i])
		if (add_element(data, i++))
			return (terror("free list"), true);
	return (false);
}

bool	set_arg(t_data *data)
{
	if (create_list(data))
		return (free_tab(data->env.path), terror("new list"), false);
	return (false);
}
