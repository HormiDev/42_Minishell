/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:28:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/08 23:51:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell *minishell;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Error: invalid arguments\n", 2), 1);
	minishell = ft_loading_minishell(envp);
	ft_config_signals();
	//ft_export("USER_ZDOTDIR=hola que tal estamos", &minishell->envp);
	//ft_export("TARTA=hola que tal estamos", &minishell->envp);
	//ft_unset("LS_COLORS", &minishell->envp);
	while (1)
	{
		ft_update_prompt(minishell);
		minishell->line = readline(minishell->prompt);//revisar reservade memoria y liberacion
		/*minishell->line = ft_input(minishell->prompt);
		if (minishell->line)//no necesario para readline, revisar
			minishell->line[ft_strlen_p(minishell->line) - 1] = '\0';//no necesario para readline*/
		if (!minishell->line)
		{	
			minishell->line = ft_strdup_ae("exit");
			ft_parsing_and_exec(minishell);
		}	
		else
			ft_add_to_alloc_lst_e(minishell->line);
		if (*minishell->line)
		{
			add_history(minishell->line);
			ft_dprintf(minishell->history_fd, "%s\n", minishell->line);
			ft_parsing_and_exec(minishell);
		}
		ft_free_alloc((minishell->line));//en caso de lentitud eliminar
		ft_config_signals();
	}
	rl_clear_history();
	ft_alloc_lst(0, 0);
	return (0);
}
