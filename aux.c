/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:25:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/15 12:50:19 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}

static char *ft_clean_command(char **command)
{
	int		c;
	char	*temp;
	int		start;
	int		length;

	c = 0;
	start = -1;
	while ((*command)[c])
	{
		if (((*command)[c] != ' '|| (*command)[c] == '-') && start == -1)
			start = c;
			break ;
		c++;
	}
	length = c - start;
	//ft_putstr(ft_itoa(start));
	temp = ft_substr(*command, start, length);
	ft_strdel(command);
	return (temp);
}

static char	**ft_clean_parameter(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		command[i] = ft_clean_command(&command[i]);
		i++;
	}
	return(command);
}

static void	ft_search_command(t_data *data, char *command)
{
	char	*temp;
	char	**parameter;
	int		c;

	c = 0;
	parameter = ft_split(command, ' ');
	ft_clean_parameter(parameter);
	ft_putstr(parameter[1]);
	while (data->path[c])
	{
		temp = ft_strjoin(data->path[c], "/");
		temp = ft_strjoin(temp, parameter[0]);
		if (access(temp, X_OK) == 0)
		{
			execve(temp, parameter, data->env);
			exit(0);
		}
		free (temp);
		c++;
	}
	ft_putstr(parameter[0]);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	exit (0);
}

void	ft_rc2(t_data *data, char **c, int i, int fd[2][2])
{
	close(fd[1][1]);
	close(fd[0][1]);
	data->input_pipe = 1;
	if (c[i] != NULL)
	{
		fd[0][0] = fd[1][0];
		pipe(fd[1]);
		ft_rc(data, c, i, fd);
	}
}

void	ft_error_child(int w)
{
	if (w == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

void	ft_rc(t_data *data, char **c, int i, int fd[2][2])
{
	int	status;

	close(fd[0][1]);
	data->pid = fork();
	if (data->pid == -1)
		return ;
	if (data->pid == 0)
	{
		if (data->input_pipe)
			dup2(fd[0][0], STDIN_FILENO);
		if (c[i + 1] != NULL)
			dup2(fd[1][1], STDOUT_FILENO);
		close(fd[1][1]);
		close(fd[1][0]);
		close(fd[0][1]);
		close(fd[0][0]);
		if (ft_cases(c[i], data))
			exit (0);
		ft_search_command(data, c[i]);
	}
	else
	{
		ft_error_child(waitpid(data->pid, &status, 0));
		ft_rc2(data, c, i + 1, fd);
	}
}

void	ft_init(t_data *data, char **command)
{
	int	fd[2][2];

	pipe(fd[0]);
	pipe(fd[1]);
	data->input_pipe = 0;
	ft_rc(data, command, 0, fd);
}

void	ft_clean_command2(t_data *data, char **command)
{
	int	c;

	c = 0;
	(void)data;
	while (command[c] != NULL)
	{
		command[c] = ft_index(&command[c]);
		c++;
	}
}
