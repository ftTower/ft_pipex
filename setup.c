/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:25:18 by tauer             #+#    #+#             */
/*   Updated: 2024/03/28 23:36:11 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

bool	set_var(char *const envp[], char **out_var, const char *name_var)
{
	size_t	i;
	size_t	size;

	if (!envp || !name_var)
		return (terror("no env"), true);
	i = 0;
	size = ft_strlen(name_var) - 1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_var, size))
			return (*out_var = envp[i] + size + 1, false);
		i++;
	}
	return (terror("no var"), true);
}

bool	set_path(t_data *data)
{
	char	*path;

	path = NULL;
	if (set_var(data->env.envp, &path, "PATH="))
		return (terror("set_var"), true);
	data->env.path = ft_split(path, ":");
	if (!data->env.path)
		return (terror("path split"), true);
	return (false);
}

bool	set_env(int argc, char **argv, char **envp, t_data *data)
{
	if (argc < 4 || !argv || !envp)
		return (terror("arg main"), true);
	data->env.argc = argc - 1;
	data->env.argv = argv + 1;
	data->env.envp = envp;
	if (set_path(data))
		return (terror("env path"), true);
	return (false);
}

bool	init_arg(t_data *data)
{
	// data->arg = NULL;
	data->arg = malloc(sizeof(t_arg));
	if (!data->arg)
		return (true);
	data->arg->name = NULL;
	data->arg->next = NULL;
	data->arg->path = NULL;
	data->arg->type = NULL;
	data->arg->pos = 0;
	return (false);
}

void	null_data(t_data *data)
{
	if (init_arg(data))
		exit(1);
	data->env.argc = 0;
	data->env.argv = NULL;
	data->env.envp = NULL;
	data->env.path = NULL;
}
