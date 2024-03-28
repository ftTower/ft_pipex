/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:32 by tauer             #+#    #+#             */
/*   Updated: 2024/03/28 23:49:22 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

bool	setup(int argc, char **argv, char **envp, t_data *data)
{
	null_data(data);
	if (set_env(argc, argv, envp, data))
		return (terror("set_env failure"), true);
	if (set_arg(data))
		return (terror("set arg failure"), true);
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	printf("\033c");
	if (setup(argc, argv, envp, &data))
		return (1);
	print_data(data);
	return (free_list(&data), free_tab(data.env.path) ,0);
}
