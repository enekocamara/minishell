/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:55:18 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/14 12:47:40 by ecamara          ###   ########.fr       */
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

typedef struct s_data
{
	char	**env;
	char	**path;
	int		pid;
	int		input_pipe;
	int		counter;
}t_data;

void	sighandler(int signal, siginfo_t *a, void *b);
void 	rl_replace_line(const char *a, int b);
int		ft_cases(char *command, t_data *data);
void	ft_recursive_child(t_data *data, char **command, int command_line, t_pipes *pipes);

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
void	ft_init( t_data *data, char **command);
void	ft_new_line(void);
void	ft_clean_command2(t_data *data, char **command);

#endif
