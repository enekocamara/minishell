/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:55:18 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/21 14:12:42 by ecamara          ###   ########.fr       */
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
	char	**env;
	char	**path;
	int		pid;
	int		input_pipe;
	int		counter;
	char	***commands;
	t_files	*input;
	t_files	*output;
}t_data;

void	sighandler(int signal, siginfo_t *a, void *b);
void	rl_replace_line(const char *a, int b);
int		ft_cases(char *command, t_data *data);
void	ft_rc(t_data *data, int i, int fd[2][2]);

/*----------------UTILS-----------------*/

int		ft_strncmp_sh(const char *str1, const char *str2, size_t n);
char	**ft_copy_2d(char **str);
void	ft_superprintf(char **str);
char	*ft_index(char **str);
void	ft_superfree(char **str);
void	ft_putstr(char *s);

/*----------------FUNCTIONS------------*/
void	ft_echo(int boo, char *str);
void	ft_cd(char *str);

/*---------------AUX-------------------*/
void	ft_init( t_data *data);
void	ft_new_line(void);
void	ft_clean_command2(t_data *data, char **command);
void	ft_print_data(t_data *data);
int		ft_command(char *str, t_data *data, int *z, int j);
int		ft_output(char *str, t_data *data, int *x, int j);
int		ft_input(char *str, t_data *data, int *y, int j);
void	ft_bucle(t_data *data, char *command, int x, int y);
int		ft_pass(char *str, char c);
char	**ft_split_ms(char *s, char c);
void	ft_allocate2(t_data *data, char **pipes);

#endif
