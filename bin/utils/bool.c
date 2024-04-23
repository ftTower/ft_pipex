/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:27:18 by tauer             #+#    #+#             */
/*   Updated: 2024/04/23 12:12:35 by tauer            ###   ########.fr       */
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

bool	is_heredoc(t_data *data)
{
	int		tmp_stdin;
	char	*line;

	line = "";
	if (ft_strncmp(data->env.argv[data->env.argc - 1], "here_doc", 8))
	{
		ft_printf("\t[HEREDOC << %s]\n\n", data->env.argv[data->env.argc - 2]);
		data->pip.in_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		tmp_stdin = dup(STDIN_FILENO);
		write(1, "\there_doc > ", 13);
		while (1)
		{
			line = get_next_line(tmp_stdin);
			if (!line)
				break ;
			if (ft_strncmp(line, data->env.argv[data->env.argc - 2],
					ft_strlen(data->env.argv[data->env.argc - 2])))
				close(tmp_stdin);
			else
				write(1, "\there_doc > ", 13);
			free(line);
		}
		return (write(1, "\n", 2), true);
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
