/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:22:24 by ecamara           #+#    #+#             */
/*   Updated: 2022/02/23 13:40:41 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int	ft_cases(char **command, t_data *data)
{
	if (command[0] == NULL)
	{
		//printf("3exit\n");
		exit(0);
	}
	if (ft_strncmp_sh(command[0], "exit", 4))
	{
		printf("exit\n");
		exit (0);
	}
	else if (ft_strncmp_sh(command[0], "env", 3))
		ft_superprintf(data->env);
	else if (ft_strncmp_sh(command[0], "echo", 5) && ft_strncmp_sh(command[1], "-n", 3))
		ft_echo(1, command[2]);
	else if (ft_strncmp_sh(command[0], "echo", 5))
		ft_echo(0, command[1]);
	/*else if (ft_strncmp_sh(command[0], "echo", 5))
		printf("\n");*/
	else if (ft_strncmp_sh(command[0], "pwd", 3))
		printf("%s\n", getenv("PWD"));
	else if (ft_strncmp_sh(command[0], "cd", 3))
		ft_cd(command[1]);
	else
		return (0);
	return (1);
}

void	ft_new_line(void)
{
	write(2, "\n", 1);
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
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

	(void)argv;
	(void)argc;
	data.env = ft_copy_2d(env);
	data.path = ft_split(getenv("PATH"), ':');
	sa.sa_sigaction = sighandler;
	//rl_catch_signals = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	data.counter = 0;
	while (1)
	{
		str = readline("Notreallyshell > ");
		add_history(str);
		ft_bucle(&data, str, 0, 0);
		//ft_print_data(&data);
		ft_init(&data);
		ft_print_data(&data);
		free (str);
		str = NULL;
		//ft_superfree(command);
	}
}
