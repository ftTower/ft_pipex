/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:28:03 by tauer             #+#    #+#             */
/*   Updated: 2024/03/29 00:24:56 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

void	terror(char *err_msg)
{
	printf("[ %s ]\n", err_msg);
}

void	print_arg(t_data *data)
{
	t_arg *current;

	current = data->arg;
	while(current)
	{
		// printf("cc\n");
		printf("%d - %s [%s]\n", current->pos, current->name[0], current->type);
		current = current->next;
	}
}

void	print_data(t_data data)
{
	printf("argc : %d\n", data.env.argc);
	if (data.env.argv)
	{
		printf("argv : ");
		for (int i = 0; data.env.argv[i]; i++)
			printf("%s ", data.env.argv[i]);
		printf("\n");
	}
	if (data.env.envp)
		printf("envp : ok\n");
	if (data.env.path)
	{
		printf("path : ");
		for (int i = 0; data.env.path[i]; i++)
			printf("%s - ", data.env.path[i]);
		printf("\n");
	}
	print_arg(&data);
}
