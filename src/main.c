/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:28:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/21 15:09:37 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_minishell *minishell;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Error: invalid arguments\n", 2), 1);
	minishell = ft_loading_minishell(envp);
	//ft_export("USER_ZDOTDIR=hola que tal estamos", &minishell->envp);
	//ft_export("TARTA=hola que tal estamos", &minishell->envp);
	//ft_unset("LS_COLORS", &minishell->envp);
	while (1)
	{
		ft_update_prompt(minishell);
		//line = ft_input(minishell->prompt);//revisar reservade memoria y liberacion
		line = readline(minishell->prompt);
		if (!line)
			break;
		if (*line)
		{
			//add_history(line);
			ft_parsing_and_exec(line, minishell);
		}
		free(line);
	}
	//rl_clear_history();
	ft_alloc_lst(0, 0);
	return (0);
}