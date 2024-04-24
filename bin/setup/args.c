/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:36:00 by tauer             #+#    #+#             */
/*   Updated: 2024/04/24 16:11:22 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	choose_type(t_data *data, t_arg *arg)
{
	if (is_fd(data, arg))
		return (false);
	else if (is_nopath(data, arg) || (is_brut(arg) && arg->path))
		return (arg->fd = -1, false);
	return (arg->path = NULL, arg->fd = -1, arg->type = "ERR",
		terror("arg is no fd or cmd. trying exec last command...", true),
		false);
}

bool	data_element(t_data *data, t_arg *arg, t_arg *list, size_t i)
{
	arg->type = NULL;
	arg->name = ft_split(data->env.argv[i], " ");
	if (!arg->name)
		return (terror("failed to split name in list", false), free(arg), true);
	return (arg->pos = data->env.argc - i - 1, arg->next = list,
		data->arg = arg, choose_type(data, arg));
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
		return (terror("malloc list", false), true);
	else if (!list)
	{
		free(data->arg);
		data->arg = NULL;
	}
	return (data_element(data, arg, list, i));
}

bool	init_arg(t_data *data)
{
	data->arg = malloc(sizeof(t_arg));
	if (!data->arg)
		return (terror("error initing the list", false), true);
	data->arg->name = NULL;
	data->arg->next = NULL;
	data->arg->path = NULL;
	data->arg->type = NULL;
	data->arg->pos = 0;
	return (false);
}

bool	create_list(t_data *data)
{
	size_t	i;

	i = 0;
	reverse_argv(data);
	if (init_arg(data))
		return (true);
	while (data->env.argv[i])
		if (add_element(data, i++))
			return (terror("failed to add element in list", false),
				free_list(data), true);
	reverse_argv(data);
	return (false);
}
