/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:28:03 by tauer             #+#    #+#             */
/*   Updated: 2024/03/29 15:09:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

void	terror(char *err_msg)
{
	printf("[ %s ]\n", err_msg);
}

void	print_command(t_data *data, t_arg *current)
{
	size_t	i;

	i = 0;
	printf("[%d][%s][%s]", current->pos, current->type, current->path);
	while (current->name[i])
		printf("[%s]", current->name[i++]);
	printf("\n");
}

void	print_arg(t_data *data)
{
	t_arg	*current;

	current = data->arg;
	printf("\n");
	while (current)
	{
		if (ft_strncmp(current->type, "CMD", 2))
			print_command(data, current);
		else if (ft_strncmp(current->type, "IFD", 2)
			|| ft_strncmp(current->type, "OFD", 2))
			printf("\n[%d][%s][%d][%s]\n\n", current->pos, current->type,
				current->fd, current->name[0]);
		else
			printf("[%d][%s][%d][%s][%s][%p]\n", current->pos, current->type,
				current->fd, current->path, current->name[0], current->next);
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
