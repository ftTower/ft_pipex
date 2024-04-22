/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:28:03 by tauer             #+#    #+#             */
/*   Updated: 2024/04/22 15:24:43 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	terror(char *err_msg, bool isLast)
{
	write(2, err_msg, ft_strlen(err_msg));
	if (!isLast)
		write(2, " -> ", 4);
	if (isLast)
		write(1, "\n\n", 2);
}

void	print_command(t_arg *current, bool isError)
{
	size_t	i;

	i = 0;
	if (isError)
		ft_printf("[%d] | [\033[38;5;196m%s\033[0m] | [%s]", current->pos,
			current->type, current->path);
	else
		ft_printf("[%d] | [\033[38;5;27m%s\033[0m] | [%s]", current->pos,
			current->type, current->path);
	while (current->name[i])
		ft_printf("[%s]", current->name[i++]);
	ft_printf("\n");
}

void	print_fd(t_arg *current, bool isError)
{
	if (!current->pos)
		write(1, "pos   type    fd/path    name  \n", 33);
	write_line();
	if (isError)
		ft_printf("[%d] | [\033[38;5;196m%s\033[0m] | [%d] [%s]\n",
			current->pos, current->type, current->fd, current->name[0]);
	else
		ft_printf("[%d] | [\033[38;5;154m%s\033[0m] | [%d] [%s]\n",
			current->pos, current->type, current->fd, current->name[0]);
	write_line();
}

void	print_arg(t_data *data)
{
	t_arg	*current;

	current = data->arg;
	ft_printf("\n");
	while (current)
	{
		if (ft_strncmp(current->type, "CMD", 2) || (ft_strncmp(current->type,
					"ERR", 2) && (current->pos != 0
					|| current->pos != data->env.argc - 1)))
			print_command(current, ft_strncmp(current->type, "ERR", 2));
		else if (ft_strncmp(current->type, "IFD", 2)
			|| ft_strncmp(current->type, "OFD", 2) || (ft_strncmp(current->type,
					"ERR", 2) && (current->pos == 0
					|| current->pos == data->env.argc - 1)))
			print_fd(current, ft_strncmp(current->type, "ERR", 2));
		current = current->next;
	}
}

void	print_data(t_data data)
{
	print_arg(&data);
}
