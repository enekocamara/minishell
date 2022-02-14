/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:22:24 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/14 12:40:31 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int	ft_cases(char *command, t_data *data)
{
	write(2, "cases\n", 6);
	if (command == NULL)
	{
		//printf("3exit\n");
		exit(0);
	}
	if (ft_strncmp_sh(command, "exit", 4))
	{
		printf("2exit\n");
		exit (0);
	}
	else if (ft_strncmp_sh(command, "env", 3))
		ft_superprintf(data->env);
	else if (ft_strncmp_sh(command, "echo -n", 7))
		ft_echo(1, command);
	else if (ft_strncmp_sh(command, "echo ", 6))
		ft_echo(0, command);
	else if (ft_strncmp_sh(command, "echo", 5))
		printf("\n");
	else if (ft_strncmp_sh(command, "pwd", 3))
		printf("%s\n", getenv("PWD"));
	else if (ft_strncmp_sh(command, "cd ", 4))
		ft_cd(command);
	else
		return (0);
	return (1);
}

void	ft_new_line(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(int signal, siginfo_t *a, void *b)
{
	(void)a;
	(void)b;
	if (signal == 2)
	{
		ft_new_line();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char				*str;
	t_data				data;
	struct sigaction	sa;
	char				**command;

	(void)argv;
	(void)argc;
	str = malloc(sizeof(char *) * 3);
	data.env = ft_copy_2d(env);
	data.path = ft_split(getenv("PATH"), ':');
	sa.sa_sigaction = sighandler;
	//rl_catch_signals = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	data.counter = -1;
	while (1)
	{
		str = readline("Notreallyshell > ");
		add_history(str);
		command = ft_split(str, '|');
		ft_superprintf(command);
		ft_clean_command2(&data, command);
		ft_init(&data, command);
		free (str);
		ft_superfree(command);
	}
}
