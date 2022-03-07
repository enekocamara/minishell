#include "../minishell.h"

int	ft_search_str_ms(char **str, char *str2, int cs)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strncmp_sh(str[i], str2, ft_strlen(str[i]), cs))
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_chrcmp_cis(char c1, char c2)
{
	if (c1 <= 122 && c1 >= 97)
		c1 -= 32;
	if (c2 <= 122 && c2 >= 97)
		c2 -= 32;
	if (c1 == c2)
		return (1);
	return (0);
}

int	ft_strncmp_sh(const char *str1, const char *str2, size_t n, int cs)
{
	unsigned int	c;
	int				i;

	c = 0;
	(void)n;
	if (!str1 || !str2 || str1[0] == '\0')
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (!cs && !ft_chrcmp_cis(str1[i], str2[i]))
			return (0);
		else if(cs && str1[i] !=  str2[i])
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
		printf("%s\n", str[c]);
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
	int		k;

	i = 0;
	j = 0;
	while (s[j] != NULL)
	{
		//printf("str = [%s]\n", s[j]);
		i = i + ft_strlen(s[j]);
		j++;
	}
	strjoin = (char *) malloc(i + 1);
	strjoin[i] = '\0';
	if (!strjoin)
		return (0);
	j = 0;
	k = 0;
	while (s[j] != NULL)
	{
		i = 0;
		while (s[j][i] != '\0')
		{
			strjoin[k] = s[j][i];
			i++;
			k++;
		}
		j++;
	}
	return (strjoin);
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}
