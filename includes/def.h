/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:45 by tauer             #+#    #+#             */
/*   Updated: 2024/04/23 10:38:05 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

bool		setup(int argc, char **argv, char **envp, t_data *data);
bool		is_brut(t_arg *arg);
bool		is_nopath(t_data *data, t_arg *arg);
void		reverse_argv(t_data *data);
bool		is_fd(t_data *data, t_arg *arg);
void		null_all(t_data *data);

void		no_bonus(t_data *data);
void		bonus(t_data *data);

void		print_data(t_data data);
void		free_tab(char **tab);

size_t		ft_strlen(const char *str);
bool		ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char *str, char *charset);
char		*ft_strdup(const char *s);

void		null_data(t_data *data);
bool		set_env(int argc, char **argv, char **envp, t_data *data);

bool		set_arg(t_data *data);
void		free_list(t_data *data);
bool		init_arg(t_data *data);

char		*path_maker(const char *path, const char *exec_name);
bool		texec(t_data data, t_arg arg);
char		*ft_itoa(int nb);

void		terror(char *err_msg, bool isLast);
void		texit(t_data *data, int exitMsg);

void		forker(t_data *data, bool RescueCmd);

bool		envl(t_data *data);
bool		pipex(t_data *data, int BONUS);
bool		try_rescue_cmd(t_data *data, int status);
void		check_err(t_data *data, int *status);

size_t		ft_strlen_printf(const char *str);
int			selecter(const char c, int ret_size, va_list arg);

void		ft_putchar_len(const char c, int *len);
void		ft_putstr_len(const char *s, int *len);
void		ft_putnbr_len(int nb, int *len);
void		ft_putnbr_ptr(size_t nbr, char *base, int *len);
void		ft_putptr_len(void *ptr, int *len);

void		ft_putnbr_base(int nbr, char *base, int *len);
void		ft_putnbr_un(unsigned int nbr, char *base, int *len);
void		write_line(void);
void		close_if_fd(t_data *data);
bool		set_path(t_data *data);
bool		create_list(t_data *data);

extern int	ft_printf(const char *str, ...);

t_list		*ft_lst_get_last(t_list *stash);
int			find_newline(t_list *stash);
void		add_to_stash(t_list **stash, char *buff, int readed);
void		read_and_stash(t_list **stash, int *readed_ptr, int fd);
void		generate_line(char **line, t_list *stash);
char		*get_next_line(int fd);

#endif