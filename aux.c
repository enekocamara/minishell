/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:25:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/21 14:50:41 by ecamara          ###   ########.fr       */
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
/*
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
*/
static void	ft_search_command(t_data *data, char **command)
{
	char	*temp;
	int		c;

	c = 0;
	while (data->path[c])
	{
		temp = ft_strjoin(data->path[c], "/");
		temp = ft_strjoin(temp, command[0]);
		if (access(temp, X_OK) == 0)
		{
			execve(temp, command, data->env);
			exit(0);
		}
		free (temp);
		c++;
	}
	//ft_putstr(parameter[0]);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	exit (0);
}

void	ft_rc2(t_data *data, int i, int fd[2][2])
{
	close(fd[1][1]);
	close(fd[0][1]);
	data->input_pipe = 1;
	if (data->commands[data->counter][i] != NULL)
	{
		fd[0][0] = fd[1][0];
		pipe(fd[1]);
		ft_rc(data, i, fd);
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

ft_input_c(t_data *data, int *fd[2][2])
{
	int	i;

	i = 0;
	while (data->input[data->counter].files[i] != NULL)
	{
		if(data->input[data->counter].modes[i] == 0)
		{
			(*fd)[0][1] = open(data->input[data->counter].files[i], O_RDONLY);
			dup2((*fd)[0][0], STDIN_FILENO);
		}
		i++;
	}
}

void	ft_output_c(t_data *data, int fd[2][2])
{
	int	i;

	i = 0;
	while (data->output[data->counter].files[i] != NULL)
	{
		//if(data->output[data->counter].modes[i] == 0)
			dup2(fd[1][1], STDOUT_FILENO);
		i++;
	}
}

void	ft_rc(t_data *data, int i, int fd[2][2])
{
	int	status;

	close(fd[0][1]);
	data->pid = fork();
	if (data->pid == -1)
		return ;
	if (data->pid == 0)
	{
		ft_input_c(data, &fd);
		ft_output_c(data, fd);
		close(fd[1][1]);
		close(fd[1][0]);
		close(fd[0][1]);
		close(fd[0][0]);
		if (ft_cases(data->commands[data->counter][i], data))
			exit (0);
		ft_search_command(data, data->commands[data->counter]);
	}
	else
	{
		ft_error_child(waitpid(data->pid, &status, 0));
		ft_rc2(data, i + 1, fd);
	}
}

void	ft_init(t_data *data)
{
	int	fd[2][2];

	pipe(fd[0]);
	pipe(fd[1]);
	data->input_pipe = 0;
	ft_rc(data, 0, fd);
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

int	ft_pass3(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_pass(str, str[i]);
		i++;
	}
	return (i);
}

int	ft_pass2(char *str, char c)
{
	int i;

	i = 1;
	if (str[i] == c)
		i++;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '\0' && str[i] != ' ')
		i++;
	return (i);
}

void	ft_allocate3(char *pipes, int *x, int *y, int *z)
{
	int		i;

	i = 0;
	while (pipes[i])
	{
		if (pipes[i] == '<')
		{
			i += ft_pass2(pipes + i, pipes[i]);
			(*y)++;
		}
		else if (pipes[i] == '>')
		{
			i += ft_pass2(pipes + i, pipes[i]);
			(*x)++;
		}
		else if (pipes[i] != ' ' && pipes[i] != '<' && pipes[i] != '>')
		{
			i += ft_pass3(pipes + i);
			(*z)++;
		}
		else
			i++;
	}
}

void	ft_allocate1(t_data  *data,  char **pipes)
{
	int	i;
	int	j;

	i = 0;
	while (pipes[i] != NULL)
		i++;
	data->input = malloc(sizeof(t_files) * (i + 1));
	data->output = malloc(sizeof(t_files) * (i + 1));
	data->commands = malloc(sizeof(char **) * i);
	data->input[i].id = 0;
	data->output[i].id = 0;
	j = 0;
	while (j < i)
	{
		data->input[j].id = 1;
		data->output[j].id = 1;
		j++;
	}
	ft_allocate2(data, pipes);
}

void	ft_allocate2(t_data *data, char **pipes)
{
	int	i;
	int	z;
	int	y;
	int	x;

	i = 0;
	while (pipes[i] != NULL)
	{
		x = 0;
		y = 0;
		z = 0;
		ft_allocate3(pipes[i], &x, &y, &z);
		printf("x = %d,  y = %d, z = %d, i = %d\n", x, y, z, i);
		data->input[i].files = malloc(sizeof(char *) * (y + 1));
		data->input[i].files[y] = NULL;
		data->input[i].modes = malloc(sizeof(char *) * (y + 1));
		data->input[i].modes[y] = -1;
		data->output[i].files = malloc(sizeof(char *) * (x + 1));
		data->output[i].files[x] = NULL;
		data->output[i].modes = malloc(sizeof(char *) * (x + 1));
		data->output[i].modes[x] = -1;
		data->commands[i] = malloc(sizeof(char *) * (z + 1));
		data->commands[i][z] = NULL;
		i++;
	}
}

void	ft_bucle(t_data *data,char *command, int x, int y)
{
	int		i;
	int		j;
	int		z;
	char	**pipes;

	i = 0;
	j = 0;
	z = 0;
	pipes = ft_split_ms(command, '|');
	ft_allocate1(data, pipes);
	while (pipes[j] != NULL)
	{
		while (pipes[j][i])
		{
			if ('>' == pipes[j][i])
				i += ft_output(pipes[j] + i + 1, data, &x, j);
			else if ('<' == pipes[j][i])
				i += ft_input(pipes[j] + i + 1, data, &y, j);
			else if (' ' != pipes[j][i] && '>' != pipes[j][i] && '<' != pipes[j][i])
			{
				i += ft_command(pipes[j] + i, data, &z, j);
			}
			else
				i++;
		}
		j++;
	}
}

int	ft_input(char *str, t_data *data, int *y, int j)
{
	int	i;
	int	index;

	i = 0;
	if (str[0] == '<')
	{
		data->input[j].modes[*y] = 1;
		index = 1;
	}
	else
	{
		data->input[j].modes[*y] = 0;
		index = 0;
	}
	while (str[index] && str[index] == ' ')
		index++;
	while (str[index + i] && str[index + i] != '<' && str[index + i] != '>'
		&& str[index + i] != '\0' && str[index + i] != ' ')
		i++;
	printf("j = %d, i = %d, index = %d, str = [%s], mode = %d\n", j, i, index, str, data->input[j].modes[*y]);
	data->input[j].files[*y] = ft_substr(str, index, i);
	(*y)++;
	return (i + index + 1);
}

int	ft_output(char *str, t_data *data, int *x, int j)
{
	int	i;
	int	index;

	i = 0;
	if (str[0] == '>')
	{
		data->output[j].modes[*x] = 1;
		index = 1;
	}
	else
	{
		data->output[j].modes[*x] = 0;
		index = 0;
	}
	while (str[index] && str[index] == ' ')
		index++;
	while (str[index + i] && str[index + i] != '<' && str[index + i] != '>'
		&& str[index + i] != '\0' && str[index + i] != ' ')
		i++;
	data->output[j].files[*x] = ft_substr(str, index, i);
	(*x)++;
	return (i + index + 1);
}

int	ft_command(char *str, t_data *data, int *z, int j)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_pass(str, str[i]);
		else
			i++;
	}
	//printf("%d, %d\n", j, *z);
	data->commands[j][*z] = ft_substr(str, 0, i);
	(*z)++;
	return (i);
}

void	ft_print_data(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	printf("\n---------COMMANDS--------\n\n");
	while (data->commands[j] != NULL)
	{
		i = 0;
		while (data->commands[j][i] != NULL)
		{
			printf("i = %d\n", i);
			printf("command [%d/%d] = [%s]\n", j , i, data->commands[j][i]);
			i++;
		}
		j++;
	}
	printf("\n---------INFILES--------\n\n");
	j = 0;
	while (data->input[j].id)
	{
		i = 0;
		printf("id == [%d]\n", data->input[j].id);
		printf("j = %d i = %d\n", j, i);
		while (data->input[j].files[i] != NULL)
		{
			printf("infile [%d/%d] = [%s]   mode = %d\n", j , i, data->input[j].files[i], data->input[j].modes[i]);
			i++;
		}
		j++;
	}
	printf("\n---------OUTFILES--------\n\n");
	j = 0;
	while (data->output[j].id)
	{
		i = 0;
		printf("id == [%d]\n", data->output[j].id);
		printf("j = %d i = %d\n", j, i);
		while (data->output[j].files[i] != NULL)
		{
			printf("enashrs\n");
			printf("infile [%d/%d] = [%s]   mode = %d\n", j , i, data->output[j].files[i], data->output[j].modes[i]);
			i++;
		}
		j++;
	}
}