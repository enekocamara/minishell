#include "../minishell.h"

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
			i += ft_pass(str, str[i]);
			i++;
			break ;
		}
		else
			i++;
	}
	data->commands[j][*z] = ft_substr(str, 0, i);
	(*z)++;
	return (i);
}
