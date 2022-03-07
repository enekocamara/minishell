#include "../minishell.h"

void	ft_echo(int boo, char **str)
{
	int	i;

	if (boo)
		i = 2;
	else
		i = 1;
	while (str[i] != NULL)
	{
		ft_putstr(str[i]);
		if (str[i][0] != '\0')
			ft_putstr(" ");
		i++;
	}
	if (!boo)
		ft_putstr("\n");
}

void	ft_cd(char *str, t_data *data)
{
	int		row;

	row = ft_search_str_ms(data->env, "PWD", 1);
	if (row == -1)
		return ;
	data->env[row] = ft_strjoin(data->env[row], "/");
	data->env[row] = ft_strjoin(data->env[row], str);;
	chdir(data->env[row]);
	opendir(data->env[row]);
}

void	ft_get_pwd(t_data *data)
{
	int		row;

	row = ft_search_str_ms(data->env, "PWD", 1);
	if (row == -1)
		return ;
	ft_putstr(data->env[row] + 4);
	ft_putstr("\n");
}