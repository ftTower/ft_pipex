/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:45 by tauer             #+#    #+#             */
/*   Updated: 2024/04/16 22:39:29 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
#define DEF_H

bool setup(int argc, char **argv, char **envp, t_data *data);
bool	is_brut(t_arg *arg);
bool	is_nopath(t_data *data, t_arg *arg);
void	reverse_argv(t_data *data);
bool	is_fd(t_data *data, t_arg *arg);
void	null_env(t_data *data);


bool no_bonus(t_data *data, t_arg *arg);
void	bonus(t_data *data);

void terror(char *err_msg);
void print_data(t_data data);
void free_tab(char **tab);

size_t ft_strlen(const char *str);
bool ft_strncmp(const char *s1, const char *s2, size_t n);
char **ft_split(char *str, char *charset);
char *ft_strdup(const char *s);

void null_data(t_data *data);
bool set_env(int argc, char **argv, char **envp, t_data *data);

bool set_arg(t_data *data);
void free_list(t_data *data);
bool init_arg(t_data *data);

char *path_maker(const char *path, const char *exec_name);
bool texec(t_data data, t_arg arg);
char	*ft_itoa(int nb);

bool	envl(t_data *data);

#endif