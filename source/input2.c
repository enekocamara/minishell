#include "../minishell.h"

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