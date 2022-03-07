#include "../minishell.h"

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