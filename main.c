/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:32 by tauer             #+#    #+#             */
/*   Updated: 2024/03/28 00:32:29 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

void	terror(char *err_msg)
{
	printf("[ %s ]\n", err_msg);
}

bool	set_var(char *const envp[], char **out_var, const char *name_var)
{
	size_t	i;
	size_t	size;

	if (!envp || !name_var)
		return (terror("no env") ,true);
	i = 0;
	size = ft_strlen(name_var) - 1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_var, size))
		{
			*out_var = envp[i] + size + 1;
			return (false);
		}
		i++;
	}
	return (terror("no var"),true);
}

bool	set_path(t_data *data)
{
	char	*path;

	path = NULL;
	if (!data->env.envp || set_var(data->env.envp, &path, "PATH="))
		return (terror("set_var"),true);
	data->env.path = ft_split(path, ":");
	if (!data->env.path)
		return (terror("path split"),true);
	return (false);
}

bool	set_env(int argc, char **argv, char **envp, t_data *data)
{
	if (argc < 4 || !argv || !envp)
		return (terror("arg main"),true);
	else if (set_path(data))
		return (terror("env path"), true);
	data->env.argc = argc - 1;
	data->env.argv = argv + 1;
	data->env.envp = envp;
	return (false);
}

void	null_data(t_data *data)
{
	data->env.argc = 0;
	data->env.argv = NULL;
	data->env.envp = NULL;
	data->env.path = NULL;
}

bool setup(int argc, char **argv, char **envp, t_data *data)
{
	null_data(data);
	if (set_env(argc, argv, envp, data))
		return (terror("set_env failure"),true);
	return (false);
}

void	print_data(t_data data)
{
	printf("argc : %d\n", data.env.argc);
	if (data.env.argv)
		printf("argv : ok\n");
	if (data.env.envp)
		printf("envp : ok\n");
	if (data.env.path)
		printf("path : ok\n");
	
}


int	main(int argc, char **argv, char **envp)
{
	t_data data;

	if (setup(argc, argv, envp, &data))
		return (1);

	print_data(data);

	return (0);
}