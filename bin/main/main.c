/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by tauer             #+#    #+#             */
/*   Updated: 2024/04/20 14:12:12 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	write(1, "\033c", 3);
	if (setup(argc, argv, envp, &data))
		return (1);
	print_data(data);
	if (pipex(&data, false))
		texit(&data, EXIT_FAILURE);
	return (texit(&data, EXIT_FAILURE), 0);
}
