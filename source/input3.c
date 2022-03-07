#include "../minishell.h"

char	*ft_comma2(char **temp, char *str, int boo)
{
	int	x;
	int	i;
	int	index;
	char	*hold;

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
		temp[x] = ft_substr(str, index, i - index);
		index = i;
		x++;
	}
	temp[x] = NULL;
	x = 0;
	while (temp[x] != NULL)
	{
		if (boo && temp[x][0] == '$')
		{
			hold = getenv(ft_substr(temp[x], 1, ft_strlen(temp[x])));
		}
		else
		{
			hold = getenv(ft_substr(temp[x], 0, ft_strlen(temp[x])));
			if (hold == NULL)
			{
				x++;
				continue ;
			}
		}
		free(temp[x]);
		temp[x] = hold;
		x++;
	}
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
	return (final);
}


void	ft_expansion(t_data *data, int k)
 {
	 int	j;
	 char	*temp;

	j = 0;
	 while (data->commands[k][j] != NULL)
	 {
		 if (data->commands[k][j][0] == '\'')
			temp = ft_comma(0, ft_substr(data->commands[k][j],
					1, ft_strlen(data->commands[k][j]) - 2));
		else if (data->commands[k][j][0] == '\"')
			temp = ft_comma(1, ft_substr(data->commands[k][j],
					1, ft_strlen(data->commands[k][j]) - 2));
		else
			temp = ft_comma(2, ft_substr(data->commands[k][j], 0, ft_strlen(data->commands[k][j])));
		free (data->commands[k][j]);
		data->commands[k][j] = temp;
		j++;
		
	 }
	 k++;
	 if (data->commands[k] != NULL)
	 	ft_expansion(data, k);
 }

