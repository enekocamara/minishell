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

void	ft_echo(int boo, char *str)
{
	if (boo)
		printf("%s", str);
	else
		printf("%s\n", str);
}

void	ft_cd(char *str)
{
	char	*temp;
	char	*path;

	temp = ft_strdup(getenv("PWD"));
	path = ft_strjoin(temp, str + 3);
	chdir(path);
	opendir(path);
	free (path);
	free (temp);
}
