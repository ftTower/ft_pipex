/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:18:07 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 14:18:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	texec(t_data data, t_arg arg)
{
	if (execve(arg.path, arg.name, data.env.envp) == -1)
		return (true);
	return (false);
}