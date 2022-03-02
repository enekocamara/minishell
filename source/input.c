
void	ft_allocate3(char *pipes, int *x, int *y, int *z)
{
	int	i;

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
		//printf("x = %d,  y = %d, z = %d, i = %d\n", x, y, z, i);
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
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			printf("return i = %d\n", ft_pass(str, str[i]));
			i += ft_pass(str, str[i]);
			i++;
			break ;
		}
		else
			i++;
	}
	printf("str = [%s] i = %d\n",str, i);
	data->commands[j][*z] = ft_substr(str, 0, i);
	(*z)++;
	return (i);
}
