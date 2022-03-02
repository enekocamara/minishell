/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:25:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/23 13:40:19 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
# include <readline/history.h>
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

void	ft_search_command(t_data *data, char **command)
{
	char	*temp;
	int		c;

	c = 0;
	while (data->path[c] != NULL)
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
	ft_putstr(command[0]);
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	exit (0);
}

void	ft_error_child(int w)
{
	if (w == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

int	ft_pass3(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\'' || str[i] == '\"')
	{
		i += ft_pass(str, str[i]);
		i++;
		return (i);
	}
	i++;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '\0' && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
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

void	ft_allocate2(t_data *data, char **pipes)
{
	int	i;
	int	z;
	int	y;
	int	x;

	i = 0;
	while (pipes != NULL && pipes[i] != NULL)
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

char	**ft_allocate1(t_data *data, char *command)
{
	int		i;
	int		j;
	char	**pipes;

	i = 0;
	pipes = ft_split_ms(command, '|');
	while (pipes != NULL && pipes[i] != NULL)
		i++;
	data->input = malloc(sizeof(t_files) * (i + 1));
	data->output = malloc(sizeof(t_files) * (i + 1));
	data->commands = (char ***)malloc(sizeof(char **) * (i + 1));
	data->commands[i] = NULL;
	j = 0;
	while (j <= i)
	{
		data->input[j].id = 0;
		data->output[j].id = 0;
		j++;
	}
	ft_allocate2(data, pipes);
	return (pipes);
}

void	ft_bucle(t_data *data,char *command, int x, int y)
{
	int		i;
	int		j;
	int		z;
	char	**pipes;

	j = -1;
	pipes = ft_allocate1(data, command);
	while (pipes != NULL && pipes[++j] != NULL)
	{
		i = 0;
		x = 0;
		y = 0;
		z = 0;
		while (pipes[j][i] != '\0')
		{
			if ('>' == pipes[j][i])
				i += ft_output(pipes[j] + i + 1, data, &x, j);
			else if ('<' == pipes[j][i])
				i += ft_input(pipes[j] + i + 1, data, &y, j);
			else if (32 != pipes[j][i])
				i += ft_command((pipes[j]) + i, data, &z, j);
			else
				i++;
		}
	}
}

int	ft_input(char *str, t_data *data, int *y, int j)
{
	int	i;
	int	index;

	i = 0;
	data->input[j].id = 1;
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
	data->input[j].files[*y] = ft_substr(str, index, i);
	(*y)++;
	return (i + index + 1);
}

int	ft_output(char *str, t_data *data, int *x, int j)
{
	int	i;
	int	index;

	i = 0;
	data->output[j].id = 1;
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
	data->output[j].id = 1;
	return (i + index + 1);
}

int	ft_command(char *str, t_data *data, int *z, int j)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\'' || str[i] == '\"')
	{
		printf("return i = %d\n", ft_pass(str, str[i]));
		i += ft_pass(str, str[i]);
		i++;
	}
	else
	{	
		while (str[i] && str[i] != '<' && str[i] != '>'
			&& str[i] != '\0' && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
				i++;
	}
	printf("str = [%s] i = %d\n",str, i);
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
			printf("command [%d/%d]", j , i);
			printf(" = [%s]\n", data->commands[j][i]);
			i++;
		}
		j++;
	}
	printf("id = %d, mode = %d", data->input[0].id, data->input[0].modes[0]);
	printf("\n---------INFILES--------\n\n");
	j = 0;
	while (data->input[j].id)
	{
		i = 0;
		while (data->input[j].files[i] != NULL)
		{
			printf("infile [%d/%d] = [%s]   mode = %d\n", j , i, data->input[j].files[i], data->input[j].modes[i]);
			i++;
		}
		j++;
	}
	printf("\n---------OUTFILES--------\n\n");
	printf("id = %d, mode = %d\n", data->output[0].id, data->output[0].modes[0]);
	j = 0;
	while (data->output[j].id)
	{
		i = 0;
		while (data->output[j].files[i] != NULL)
		{
			printf("outfile [%d/%d] = [%s]   mode = %d\n", j , i, data->output[j].files[i], data->output[j].modes[i]);
			i++;
		}
		j++;
	}
}


void	ft_print_fd(int fd)
{
	char	str[1000];
	read(fd, str, 999);
	write(2, str, 999);
}

void	ft_rc(t_data * data, int fd0[2], int fd1[2])
{
	if (ft_input_c(data, 0, fd0, fd1) && data->counter)
		dup2(fd0[0], STDIN_FILENO);
	if (ft_output_c(data, 0, fd0, fd1) && data->commands[data->counter + 1] != NULL)
		dup2(fd1[1], STDOUT_FILENO);
	close(fd0[1]);
	close(fd1[1]);
	close(fd1[0]);
	close(fd0[0]);
	if (ft_cases(data->commands[data->counter], data))
		exit(0);
	ft_search_command(data, data->commands[data->counter]);
}

void	ft_init(t_data *data,int fd0[2])
{
	int	status;
	int	pid;
	int	fd1[2];

	pipe(fd1);
	if (data->commands[data->counter] != NULL)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			//close(fd0[1]);
			ft_rc(data, fd0, fd1);
		}
		else
		{
			close(fd0[1]);
			ft_error_child(waitpid(pid, &status, 0));
			data->counter++;
			if (data->commands[data->counter] != NULL)
			{
				fd0[0] = fd1[0];
				ft_init(data, fd1);
			}
		}
	}
}

int	ft_input_c(t_data *data, int i, int fd0[2], int fd1[2])
{
	char	*str;
	char	*temp;

	str = NULL;
	if (data->input[0].id != 1)
		return (1);
	if (data->input[data->counter].modes[i] == 1)
	{
		while (!ft_strnstr(str, data->input[data->counter].files[i], ft_strlen(str)))
		{
			temp = readline("> ");
			if (ft_strnstr(temp, data->input[data->counter].files[i], ft_strlen(temp)))
				break ;
			str = ft_strjoin_ms(str, temp, ft_strlen(str), ft_strlen(temp));
			str = ft_strjoin_ms(str, "\n", ft_strlen(str), 1);
			free (temp);
		}
		if (data->input[data->counter].files[i + 1] == NULL)
			write(fd0[1], str, ft_strlen(str));
	}
	else
		fd0[0] = open(data->input[data->counter].files[i], O_RDONLY);
	i++;
	if (data->input[data->counter].files[i] != NULL)
		ft_input_c(data, i, fd0, fd1);
	else
	{
		//ft_print_fd(fd0[0]);
		dup2(fd0[0], STDIN_FILENO);
	}
	close (fd0[1]);
	return (0);
}

int	ft_output_c(t_data *data, int i, int fd0[2], int fd1[2])
{
	int	fd;

	if (data->output[data->counter].id != 1)
		return (1);
	if (data->output[data->counter].modes[i] && data->output[data->counter].files[i + 1] != NULL)
		open(data->output[data->counter].files[i], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->output[data->counter].modes[i] && data->output[data->counter].files[i + 1] != NULL)
		open(data->output[data->counter].files[i], O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->output[data->counter].modes[i] && data->output[data->counter].files[i + 1] == NULL)
	{
		open(data->output[data->counter].files[i], O_TRUNC);
		fd = open(data->output[data->counter].files[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}

	else if (data->output[data->counter].modes[i] && data->output[data->counter].files[i + 1] == NULL)
	{
		fd = open(data->output[data->counter].files[i], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}
	i++;
	if (data->output[data->counter].files[i] != NULL)
		ft_output_c(data, i, fd0, fd1);
	return (0);
}

char	*ft_comma2(char **temp, char *str, int boo)
{
	int	x;
	int	i;
	int	index;

	i = 0;
	index = 0;
	x = 0;
	while(str[i] != '\0')
	{
		if (str[index] == '$')
		{
			i++;
			while (str[i] && ft_isalpha(str[i]))
				i++;
		}
		else
		{
			while (str[i] && str[i] != '$')
				i++;
		}
		//printf("[] i = %d index = %d\n", i, index);
		if (boo && str[index] == '$')
		{
			//printf("[] i = %d index = %d\n", i, index);
			temp[x] = getenv(ft_substr(str, index + 1, i - index - 1));
		}
		else
			temp[x] = ft_substr(str, index, i - index);
		if (temp[x] == NULL)
			temp[x] = "\0";
		index = i;
		x++;
	}
	temp[x] = NULL;
	return (ft_superjoin(temp));
}

char	*ft_comma(int boo, char *str)
{
	int		i;
	char	**temp;
	int		count;
	char	*final;

	temp = 0;
	count = 0;
	i = 0;
	if (boo)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '$')
				count++;
			i++;
		}
	}
	else
		count = 1;
	temp = malloc (sizeof(char *) * (count * 2 + 2));
	temp[count * 2 + 1] = NULL; 
	final = ft_comma2(temp, str, boo);
//	ft_superfree(temp);
	return (final);
}

void	ft_expansion(t_data *data, int k)
{
	int		j;
	char	*temp;

	j = 1;
	while (data->commands[k] != NULL && data->commands[k][j] != NULL)
	{
		printf("k = %d j = %d\n", k, j);
		if (data->commands[k][j] != NULL && data->commands[k][j][0] == '\'')
			temp = ft_comma(0, ft_substr(data->commands[k][j],
					1, ft_strlen(data->commands[k][j]) - 2));
		else if (data->commands[k][j][0] == '\"')
			temp = ft_comma(1, ft_substr(data->commands[k][j],
					1, ft_strlen(data->commands[k][j]) - 2));
		free (data->commands[k][j]);
		data->commands[k][j] = temp;
		j++;
	}
	k++;
	if (data->commands[k] != NULL)
		ft_expansion(data, k);
}