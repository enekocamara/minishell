/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:55:18 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/23 13:40:29 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipes
{
	int	pipe0[2];
	int	pipe1[2];
}t_pipes;
typedef struct s_files
{
	char	**files;
	int		*modes;
	int		id;
}t_files;

typedef struct s_data
{
	int		fd[2][2];
	char	**env;
	char	**path;
	int		pid;
	int		input_pipe;
	int		counter;
	char	***commands;
	t_files	*input;
	t_files	*output;
}t_data;

/*----------------UTILS-----------------*/

int	ft_search_str_ms(char **str, char *str2, int cs);
void	ft_strdel(char **as);
char	**ft_split_ms(char *str, char c);
int		ft_strncmp_sh(const char *str1, const char *str2, size_t n, int cs);
void	ft_superprintf(char **str);
void	ft_superfree(char **str);
void	ft_putstr(char *s);
char	**ft_copy_2d(char **str);
void	ft_print_data(t_data *data);
void	ft_print_fd(int fd);
char	*ft_strjoin_ms(char const *s1, char const *s2, int i, int c);
char	*ft_superjoin(char **s);

/*--------------PROCESS----------------*/

void		ft_search_command(t_data *data, char **command);
int			ft_output_c(t_data *data, int i,int fd0[2], int fd1[2]);
int			ft_input_c(t_data *data, int i,int fd0[2], int fd1[2]);
void		ft_rc(t_data * data,int fd0[2], int fd1[2]);
void		ft_init(t_data * data, int fd0[2]);

/*-----------------INPUT-----------------*/

int			ft_input(char *str, t_data *data, int *y, int j);
int			ft_output(char *str, t_data *data, int *x, int j);
int			ft_command(char *str, t_data *data, int *z, int j);
void		ft_bucle(t_data *data,char *command, int x, int y);
char		**ft_allocate1(t_data  *data, char *command);
void		ft_expansion(t_data *data, int k);

/*-----------------AUX-------------------*/

int	ft_pass(char *str, char c);
int	ft_pass3(char *str);
int	ft_pass2(char *str, char c);

/*---------------BUILDINS----------------*/

int		ft_cases(char **command, t_data *data);
void	ft_echo(int boo, char **str);
void	ft_cd(char *str, t_data *data);

/*-----------------ERROR-----------------*/

void	ft_error_child(int w);

#endif