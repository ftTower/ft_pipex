/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:28:03 by tauer             #+#    #+#             */
/*   Updated: 2024/04/19 15:31:04 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void terror(char *err_msg, bool	isLast)
{
	// write(2, " ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	if (!isLast)
		write(2, " -> ", 4);
	if (isLast)
		write(1, "\n", 1);
}

void print_command(t_arg *current)
{
	size_t i;

	i = 0;
	printf("[%d] | [%s] | [%s]", current->pos, current->type, current->path);
	while (current->name[i])
		printf("[%s]", current->name[i++]);
	printf("\n");
}

void	write_line(t_data *data)
{
	unsigned int max;
	unsigned int comp;
	t_arg *current;

	max = 0;
	current = data->arg;
	while(current)
	{
		if (ft_strncmp(current->type, "CMD", 2))
			comp = ft_strlen(current->path) + ft_strlen(current->name[0]) + 5;
		else if (ft_strncmp(current->type, "IFD", 2) || ft_strncmp(current->type, "OFD", 2))
			comp = 11 + ft_strlen(current->name[0]);
		if (comp > max)
			max = comp;
		current = current->next;
 	}
	write(1, "----+-------+", 14);
	while(max--)
		write(1, "-", 1);
	write(1, "\n", 1);
}

void print_fd(t_data *data, t_arg *current)
{
	if (!current->pos)
		write(1, "pos   type    fd/path    name  \n", 33);			
	write_line(data);
	printf("[%d] | [%s] | [fd : %d][%s]\n", current->pos, current->type,
		   current->fd, current->name[0]);
	write_line(data);
}

void print_arg(t_data *data)
{
	t_arg *current;

	current = data->arg;
	printf("\n");
	while (current)
	{
		if (ft_strncmp(current->type, "CMD", 2))
			print_command(current);
		else if (ft_strncmp(current->type, "IFD", 2) || ft_strncmp(current->type, "OFD", 2))
			print_fd(data, current);
		else
			printf("[%d][%s][%d][%s][%s][%p]\n", current->pos, current->type,
				   current->fd, current->path, current->name[0], current->next);
		current = current->next;
	}
}

void print_data(t_data data)
{
	print_arg(&data);
}
