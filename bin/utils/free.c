/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:16:14 by tauer             #+#    #+#             */
/*   Updated: 2024/04/26 17:16:53 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	close_if_fd(t_data *data)
{
	if (data->pip.in_fd >= 0)
		close(data->pip.in_fd);
	if (data->pip.ou_fd >= 0)
		close(data->pip.ou_fd);
	if (data->pip.safety_fd >= 0)
		close(data->pip.safety_fd);
}

void	texit(t_data *data, int exitMsg)
{
	free_list(data);
	free_tab(data->env.path);
	exit(exitMsg);
}

void	free_list(t_data *data)
{
	t_arg	*current;
	t_arg	*temp;

	current = data->arg;
	if (!current)
		return ;
	while (current)
	{
		temp = current->next;
		if (current->fd != -1)
			close(current->fd);
		if (current->name)
			free_tab(current->name);
		if (current->path)
			free(current->path);
		free(current);
		current = temp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
