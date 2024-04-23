/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:13:51 by tauer             #+#    #+#             */
/*   Updated: 2024/04/23 22:21:36 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	null_all(t_data *data)
{
	data->env.argc = 0;
	data->env.argv = NULL;
	data->env.envp = NULL;
	data->env.path = NULL;
	data->pip.pos = 0;
}

bool	set_env(int argc, char **argv, char **envp, t_data *data)
{
	if (argc < 4 || !argv)
		return (terror("bad args", false), true);
	if (envp)
		data->env.envp = envp;
	if (set_path(data))
		return (true);
	return (data->env.argc = argc - 1, data->env.argv = argv + 1, false);
}

bool	set_arg(t_data *data)
{
	if (create_list(data))
		return (free_tab(data->env.path), terror("failed to create args list",
				false), true);
	return (false);
}

bool	setup(int argc, char **argv, char **envp, t_data *data)
{
	null_all(data);
	if (set_env(argc, argv, envp, data))
		return (terror("set_env failure", true), true);
	if (set_arg(data))
		return (terror("set arg failure", true), true);
	return (heredoc_cleaner(data), false);
}
