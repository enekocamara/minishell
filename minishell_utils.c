/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:25:17 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/11 17:14:48 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp_sh(const char *str1, const char *str2, size_t n)
{
	unsigned int	c;
	int				i;

	c = 0;
	(void)n;
	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

char	**ft_copy_2d(char **str)
{
	int		c;
	char	**env;

	c = 0;
	if (!str)
		return (0);
	while (str[c])
	{
		c++;
	}
	env = (char **)malloc(sizeof(char *) * (c + 1));
	env[c] = NULL;
	c = 0;
	while (str[c])
	{
		env[c] = ft_strdup(str[c]);
		c++;
	}
	return (env);
}

void	ft_superprintf(char **str)
{
	int	c;

	c = 0;
	if (!str)
		return ;
	while (str[c])
	{
		printf("[%s]\n", str[c]);
		c++;
	}
}

char	*ft_index(char **str)
{
	int		c;
	char	*final;

	if (!*str)
		return (0);
	c = 0;
	while ((*str)[c] && (*str)[c] == ' ')
		c++;
	final = ft_strdup(*str + c);
	free (*str);
	return (final);
}

void	ft_superfree(char **str)
{
	int	c;

	c = 0;
	while (str[c] != NULL)
	{
		free(str[c]);
		c++;
	}
	free(str);
}

void	ft_putstr(char *s)
{
	if (s)
		write (2, (const char *)s, ft_strlen(s));
	else
		write(2, "(null)", 6);
}

char	*ft_strjoin_ms(char const *s1, char const *s2, int i, int c)
{
	char	*strjoin;
	int		j;

	strjoin = (char *) malloc(c + i + 1);
	if (!strjoin)
		return (0);
	strjoin[c + i] = '\0';
	j = 0;
	while (j < i)
	{
		strjoin[j] = s1[j];
		j++;
	}
	while (j < i + c)
	{
		strjoin[j] = s2[j - i];
		j++;
	}
	return (strjoin);
}

char	*ft_superjoin(char **s)
{
	char	*strjoin;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (s[j] != NULL)
	{
		i = i + ft_strlen(s[j]);
		j++;
	}
	strjoin = (char *) malloc(i + 1);
	if (!strjoin)
		return (0);
	j = 0;
	while (s[j] != NULL)
	{
		i = 0;
		while (s[j][i] != '\0')
		{
			strjoin[i] = s[j][i];
			i++;
		}
		j++;
	}
	strjoin[i] = '\0';
	//printf("str2 = [%s] %d \n", strjoin, j);
	return (strjoin);
}
