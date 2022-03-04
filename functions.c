/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:09:33 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/07 13:41:32 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int boo, char **str)
{
	int	i;

	if (boo)
		i = 2;
	else
		i = 1;
	while (str[i] != NULL)
	{
		if (boo)
			printf("%s", str[i]);
		else
			printf("%s\n", str[i]);
		i++;
	}
}

void	ft_cd(char *str, t_data *data)
{
	char	*temp;
	char	*path;
	int		row;

	temp = ft_strdup(getenv("PWD"));
	temp = ft_strjoin(temp, "/");
	path = ft_strjoin(temp, str);
	chdir(path);
	opendir(path);
	free (temp);
	row = ft_search_str_ms(data->env, "PWD", 1);
	if (row == -1)
		return ;
	free (data->env[row]);
	data->env[row] = path;
	free (path);
}
