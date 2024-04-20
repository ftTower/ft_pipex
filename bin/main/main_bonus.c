/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:51:23 by tauer             #+#    #+#             */
/*   Updated: 2024/04/20 19:02:56 by tauer            ###   ########.fr       */
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
	if (pipex(&data, true))
		texit(&data, EXIT_FAILURE);
	return (texit(&data, EXIT_SUCCESS), 0);
}
