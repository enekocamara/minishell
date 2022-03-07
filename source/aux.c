#include "../minishell.h"

int	ft_pass(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
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
