/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:27:18 by tauer             #+#    #+#             */
/*   Updated: 2024/04/23 23:25:07 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	access_bol(char *name)
{
	if (access(name, X_OK | F_OK) == -1)
		return (false);
	return (true);
}

bool	is_brut(t_arg *arg)
{
	if (access_bol(arg->name[0]))
		return (arg->path = ft_strdup(arg->name[0]), arg->type = "CMD", true);
	return (false);
}

bool	is_nopath(t_data *data, t_arg *arg)
{
	char	*path;
	char	*full_path;
	size_t	i;

	i = 0;
	while (data->env.path[i])
	{
		path = path_maker(data->env.path[i], "/");
		full_path = path_maker(path, arg->name[0]);
		if (access_bol(full_path))
			return (arg->path = full_path, arg->type = "CMD", free(path), true);
		free(path);
		free(full_path);
		i++;
	}
	return (false);
}

void	print_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		printf("%d - %s\n", i, tab[i]);
}

void	heredoc_cleaner(t_data *data)
{
	t_arg	*current;
	t_arg	*tmp;
	size_t	pos;

	pos = 0;
	current = data->arg;
	while (current)
	{
		if (current->pos == 0 && ft_strncmp(current->type, "HDC", 3))
		{
			tmp = current->next->next;
			free_tab(current->next->name);
			if (current->next->path)
				free(current->next->path);
			if (current->next)
				free(current->next);
			current->next = tmp;
			data->env.argc--;
			ft_printf("%s %d | %s %d\n", current->name[0], current->pos,
				current->next->name[0], current->next->pos);
		}
		current->pos = pos;
		pos++;
		current = current->next;
	}
}

bool	is_heredoc(t_data *data)
{
	char	*line;

	if (ft_strncmp(data->env.argv[data->env.argc - 1], "here_doc", 8))
	{
		ft_printf("\t[HEREDOC << %s]\n\n", data->env.argv[data->env.argc - 2]);
		data->pip.in_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		write(1, "\there_doc > ", 13);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				return (false);
			else if (ft_strncmp(data->env.argv[data->env.argc - 2], line,
					ft_strlen(line) - 1))
			{
				free(line);
				return(true);
			}
			else
				write(1, "\t         > ", 13);
			write(data->pip.in_fd, line, ft_strlen(line));
			free(line);
		}
		free(line);
		close(data->pip.in_fd);
		data->pip.in_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		return (write(1, "\n", 1), true);
	}
	return (false);
}

bool	is_fd(t_data *data, t_arg *arg)
{
	int	fd;

	if (arg->pos == 0)
	{
		data->pip.safety_fd = open("/dev/null", O_RDONLY);
		if (data->pip.safety_fd < 0)
			return (false);
		if (is_heredoc(data))
			return (arg->fd = data->pip.in_fd, arg->type = "HDC",
				arg->path = NULL, true);
		fd = open(arg->name[0], O_RDONLY);
		if (fd > 0)
			return (data->pip.in_fd = fd, arg->fd = fd, arg->type = "IFD",
				arg->path = NULL, true);
	}
	else if (arg->pos == data->env.argc - 1)
	{
		fd = open(arg->name[0], O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (fd > 0)
			return (data->pip.ou_fd = fd, arg->fd = fd, arg->type = "OFD",
				arg->path = NULL, true);
	}
	return (false);
}
