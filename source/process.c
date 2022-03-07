#include "../minishell.h"

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

void	ft_rc(t_data * data, int fd0[2], int fd1[2])
{
	if (data->commands[1] != NULL)
	{
		if (ft_input_c(data, 0, fd0, fd1) && data->counter)
			dup2(fd0[0], STDIN_FILENO);
		if (ft_output_c(data, 0, fd0, fd1) && data->commands[data->counter + 1] != NULL)
			dup2(fd1[1], STDOUT_FILENO);
		close(fd0[1]);
		close(fd1[1]);
		close(fd1[0]);
		close(fd0[0]);
	}
	if (ft_cases(data->commands[data->counter], data))
		exit(0);
	ft_search_command(data, data->commands[data->counter]);
}

void	ft_mother(t_data *data, int fd0[2])
{
	int	fd1[2];

	pipe(fd1);
	if (ft_input_c(data, 0, fd0, fd1) && data->counter)
		dup2(fd0[0], STDIN_FILENO);
	if (ft_output_c(data, 0, fd0, fd1) && data->commands[data->counter + 1] != NULL)
		dup2(fd1[1], STDOUT_FILENO);
	close(fd0[1]);
	close(fd1[1]);
	close(fd1[0]);
	close(fd0[0]);
}