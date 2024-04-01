/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:25:18 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 13:56:23 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	set_var(char *const envp[], char **out_var, const char *name_var)
{
	size_t	i;
	size_t	size;

	if (!envp || !name_var)
		return (terror("envp not found"), true);
	i = 0;
	size = ft_strlen(name_var) - 1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_var, size))
			return (*out_var = envp[i] + size + 1, false);
		i++;
	}
	return (terror("no var found"), true);
}

bool	set_path(t_data *data)
{
	char	*path;

	path = NULL;
	if (set_var(data->env.envp, &path, "PATH="))
		return (true);
	data->env.path = ft_split(path, ":");
	if (!data->env.path)
		return (terror("failed to split path"), true);
	return (false);
}

bool	set_env(int argc, char **argv, char **envp, t_data *data)
{
	if (argc < 4 || !argv || !envp)
		return (terror("bad args"), true);
	data->env.argc = argc - 1;
	data->env.argv = argv + 1;
	data->env.envp = envp;
	if (set_path(data))
		return (true);
	return (false);
}

void	null_data(t_data *data)
{
	data->env.argc = 0;
	data->env.argv = NULL;
	data->env.envp = NULL;
	data->env.path = NULL;
}
