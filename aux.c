/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:25:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/14 13:08:14 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static char	*ft_clean_command(char *command)
{
	int	c;

	c = 0;
	while (command[c] && ft_isalpha(command[c]))
		c++;
	return (ft_substr(command, 0,c));
}

static void	ft_search_command(t_data *data, char *command)
{
	char	*temp;
	char	**parameter;
	int		c;

	c = 0;
	while (data->path[c])
	{
		temp = ft_strjoin(data->path[c], "/");
		temp = ft_strjoin(temp, ft_clean_command(command));
		if (access(temp, X_OK) == 0)
		{
			ft_putstr(temp);
			parameter = ft_split(command, ' ');
			ft_putstr(parameter[0]);
			execve(temp, parameter, data->env);
			exit(0);
		}
		c++;
	}
	//write(2, "command not found\n", 18);
	exit (0);
}

void	ft_read_pipe(int *pipe)
{
	char	str[999];

	read(pipe[0], str, 2);
	//write(2, str, ft_strlen(str));
}

void	ft_change_0_for_1(t_pipes *pipes)
{
	//int	temp;

	//temp = pipes->pipe0[1];
	pipes->pipe0[0] = pipes->pipe1[0];
	//pipes->pipe0[1] = temp;
	close(pipes->pipe0[1]);
	//close(pipes->pipe0[0]);
	close(pipes->pipe1[1]);
	close(pipes->pipe1[0]);
	//pipe(pipes->pipe0);
	pipe(pipes->pipe1);
}

static void	ft_recursive_child_2(t_data *data, char **command, int command_line, t_pipes *pipes)
{
	int	w;
	int	status;

	w = waitpid(data->pid, &status, 0);
	if (w == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	if (command[command_line] != NULL)
	{
		data->input_pipe = 1;
		close(pipes->pipe0[0]);
		if (command[command_line] != NULL)
		{
			ft_change_0_for_1(pipes);
			ft_recursive_child(data, command, command_line + 1, pipes);
		}
	}

}

void	ft_recursive_child(t_data *data, char **command, int command_line, t_pipes *pipes)
{

	close(pipes->pipe0[1]);
	data->pid = fork ();
	if (data->pid == -1)
		return ;
	if (data->pid == 0)
	{
		close(pipes->pipe0[1]);
		close(pipes->pipe1[0]);
		if (ft_cases(command[command_line], data))
			exit (0);
		if (data->input_pipe)
		{
			write (2,"1\n", 2);
			dup2(pipes->pipe0[0], STDIN_FILENO);
		}
		if (command[command_line + 1] != NULL)
		{
			write (2,"2\n", 2);
			dup2(pipes->pipe1[1], STDOUT_FILENO);
			close(pipes->pipe1[1]);
		}
		write (2,"3\n", 2);
		ft_search_command(data, command[command_line]);
	}
	else
		ft_recursive_child_2(data, command, command_line, pipes);
}
/*
	else
	{
		w = waitpid(pid, &status, 0);
		if (w == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (command[command_line] != NULL)
		{
			data->input_pipe = 0;
			close(pipe1[0]);
			if (command[command_line] != NULL)
				ft_recursive_child(data, command, command_line + 1, pipe2);
		}
	}
}*/

void	ft_init(t_data *data, char **command)
{
	t_pipes pipes;

	pipe(pipes.pipe0);
	pipe(pipes.pipe1);
	data->input_pipe = 0;
	ft_recursive_child(data, command, 0, &pipes);

}

void	ft_clean_command2(t_data *data, char **command)
{
	int	c;

	c = 0;
	(void)data;
	while(command[c] != NULL)
	{
		command[c] = ft_index(&command[c]);
		c++;
	}
}
