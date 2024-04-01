/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:13:51 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 14:18:57 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

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
		fd = open(arg->name[0], O_TRUNC | O_CREAT | O_WRONLY, 0000644);
		if (fd > 0)
			return (data->env.ou_fd = fd ,arg->fd = fd, arg->type = "OFD", arg->path = NULL, true);
	}
	return (false);
}

bool	access_bol(char *name)
{
	if (access(name, X_OK | F_OK) == -1)
		return (false);
	return (true);
}

bool	is_brut(t_arg *arg)
{
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

bool	setup(int argc, char **argv, char **envp, t_data *data)
{
	null_env(data);
	if (set_env(argc, argv, envp, data))
		return (terror("set_env failure"), true);
	if (set_arg(data))
		return (terror("set arg failure"), true);
	return (false);
}