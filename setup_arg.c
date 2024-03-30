/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:36:00 by tauer             #+#    #+#             */
/*   Updated: 2024/03/30 23:57:17 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

bool	access_bol(char *name)
{
	if (access(name, X_OK | F_OK) == -1)
		return (false);
	return (true);
}

bool	is_brut(t_data *data, t_arg *arg)
{
	char	**args;

	if (access_bol(arg->name[0]))
		return (arg->path = ft_strdup(arg->name[0]), arg->type = "CMD", true);
	return (false);
}

bool	is_nopath(t_data *data, t_arg *arg)
{
	char	*path;
	char	*full_path;
	size_t	i;

	i = 0;
	while (data->env.path[i])
	{
		path = path_maker(data->env.path[i], "/");
		full_path = path_maker(path, arg->name[0]);
		if (access_bol(full_path))
			return (arg->path = full_path, arg->type = "CMD", free(path), true);
		free(path);
		free(full_path);
		i++;
	}
	return (false);
}

bool	is_fd(t_data *data, t_arg *arg)
{
	int	fd;

	if (arg->pos == 0)
	{
		fd = open(arg->name[0], O_RDONLY);
		if (fd > 0)
			return (data->env.in_fd = fd ,arg->fd = fd, arg->type = "IFD", arg->path = NULL, true);
	}
	else if (arg->pos == data->env.argc - 1)
	{
		fd = open(arg->name[0], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fd > 0)
			return (data->env.ou_fd = fd ,arg->fd = fd, arg->type = "OFD", arg->path = NULL, true);
	}
	return (false);
}

bool	choose_type(t_data *data, t_arg *arg)
{
	if (is_fd(data, arg))
		return (false);
	else if ((is_brut(data, arg) && arg->path) || is_nopath(data, arg))
		return (arg->fd = -1, false);
	return (arg->path = NULL, arg->fd = -1, arg->type = "ERR", false);
}

bool	data_element(t_data *data, t_arg *arg, t_arg *list, size_t i)
{
	arg->type = NULL;
	arg->name = ft_split(data->env.argv[i], " ");
	if (!arg->name)
		return (terror("failed to split name in list"), free(arg), true);
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
		return (terror("malloc list"), true);
	else if (!list)
	{
		free(data->arg);
		data->arg = NULL;
	}
	return (data_element(data, arg, list, i));
}

void	free_list(t_data *data)
{
	t_arg	*current;
	t_arg	*temp;

	current = data->arg;
	if (!current)
		return ;
	while (current)
	{
		temp = current->next;
		if (current->fd != -1)
			close(current->fd);
		if (current->name)
			free_tab(current->name);
		if (current->path)
			free(current->path);
		free(current);
		current = temp;
	}
}

bool	init_arg(t_data *data)
{
	data->arg = malloc(sizeof(t_arg));
	if (!data->arg)
		return (terror("error initing the list"), true);
	data->arg->name = NULL;
	data->arg->next = NULL;
	data->arg->path = NULL;
	data->arg->type = NULL;
	data->arg->pos = 0;
	return (false);
}

void	swap_element(t_data *data)
{
	t_arg	*copy_first;
	t_arg	*copy_list;

	copy_first = data->arg;
	copy_list = copy_first->next;
	copy_first->next = NULL;
	while (copy_list->next)
	{
		printf("%s\n", data->arg->name[0]);
		copy_list = copy_list->next;
	}
	copy_list->next = copy_first;
	data->arg = copy_list;
	printf("\n\n");
}

void	reverse_argv(t_data *data)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (i < data->env.argc / 2)
	{
		temp = data->env.argv[i];
		data->env.argv[i] = data->env.argv[data->env.argc - 1 - i];
		data->env.argv[data->env.argc - 1 - i] = temp;
		i++;
	}
}

bool	create_list(t_data *data)
{
	t_arg	*arg;
	size_t	i;

	i = 0;
	reverse_argv(data);
	if (init_arg(data))
		return (true);
	while (data->env.argv[i])
		if (add_element(data, i++))
			return (terror("failed to add element in list"), free_list(data),
				true);
	reverse_argv(data);
	return (false);
}

bool	set_arg(t_data *data)
{
	if (create_list(data))
		return (free_tab(data->env.path), terror("new list"), true);
	return (false);
}
