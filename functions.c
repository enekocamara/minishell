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
		printf("%s", str[i]);
		if (str[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (!boo)
		printf("\n");
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
	printf("%s\n",data->env[row] + 4);
}