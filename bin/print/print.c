/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:28:03 by tauer             #+#    #+#             */
/*   Updated: 2024/04/02 16:41:39 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	terror(char *err_msg)
{
	printf("[ %s ]\n", err_msg);
}

void	print_command(t_arg *current)
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
			print_command(current);
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

void	set_envl(t_data *data)
{
	data->envl.max_size_line = 117;
	data->envl.argc_pos = 17;
	data->envl.status_pos = 1;
}

bool	print_stopper(t_data *data, int pos)
{
	// printf("%d - %d", pos, data->envl.argc_pos);
	if (pos == data->envl.max_size_line || pos == data->envl.argc_pos - 3
		|| pos == data->envl.status_pos - 3)
		return (printf("\033[48;5;248m..\033[0m\033[0;47m\033[0m"),true);
	return (false);
}

void	print_limited(t_data *data, char *str, int number, int *pos)
{
	int		i;
	char	*num;

	i = 0;
	if (!str && number == 0)
		*pos += printf("\033[48;5;248m \033[0m\033[0;47m\033[0m") - 26;
	if (str != NULL)
	{
		while (str[i] && !print_stopper(data, *pos))
		{
			*pos += printf("\033[48;5;248m%c\033[0m\033[0;47m\033[0m", str[i++])
				- 26;
		}
		i = 0;
	}
	if (number != 0)
	{
		num = ft_itoa(number);
		while (num[i] && !print_stopper(data, *pos))
		{
			*pos += printf("\033[48;5;248m%c\033[0m\033[0;47m\033[0m", num[i++])
				- 26;
		}
		free(num);
	}
}

void	first_line(t_data *data)
{
	int	pos;

	pos = 0;
	while (pos < data->envl.max_size_line)
	{
		if (pos == data->envl.status_pos)
			print_limited(data, "status : ", data->env.status, &pos);
		else if (pos == data->envl.argc_pos)
			print_limited(data, "argc : ", data->env.argc, &pos);
		else
			print_limited(data, NULL, 0, &pos);
	}
	printf("\n%d\n", pos);
}

void	env_line(t_data *data)
{
	int	i;

	i = 0;
	first_line(data);
	printf("\n%d", data->env.argc);
}

void	print_data(t_data data)
{
	set_envl(&data);
	env_line(&data);
	print_arg(&data);
}
