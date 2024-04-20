/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:31:51 by tauer             #+#    #+#             */
/*   Updated: 2024/04/20 14:17:32 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void check_err(t_data *data, int *status)
{
    t_arg *current;

    current = data->arg;
    while (current)
    {
        if (current->pos == data->env.argc - 2 && ft_strncmp(current->type, "ERR", 3))
            *status = 3;
        else if (current->pos != data->env.argc - 2 && ft_strncmp(current->type, "ERR", 3))
            *status = 2;
        current = current->next;
    }
}

bool tryRescueCmd(t_data *data, int status)
{
    data->pip.pos = data->env.argc - 2;
    if (status == 3)
    {
        terror("last arg seems to be an error.", true);
        texit(data, EXIT_FAILURE);
    }
    else if (status == 2)
        forker(data);
    return (true);
}

bool pipex(t_data *data, int BONUS)
{
    check_err(data, &BONUS);
    if (BONUS != false && BONUS != true)
        return (tryRescueCmd(data, BONUS));
    else if (!BONUS && data->env.argc == 4)
        return (no_bonus(data, data->arg->next));
    else if (BONUS && data->env.argc >= 4)
        return (bonus(data), false);
    return (terror("wrong number of args", true), true);
}
