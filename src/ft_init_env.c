/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:53:38 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/13 19:30:33 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	ft_init_shlvl(t_minishell *minishell)
{
	int		shlvl;
	char	*shlvl_str;
	char	*shlvl_env;

	if (ft_getenv("SHLVL", minishell->envp) == NULL)
		ft_export("SHLVL=1", &minishell->envp);
	else if (!ft_isnumber(ft_getenv("SHLVL", minishell->envp)))
		ft_export("SHLVL=0", &minishell->envp);
	else
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", minishell->envp));
		shlvl++;
		shlvl_str = ft_add_to_alloc_lst_e(ft_itoa(shlvl));
		shlvl_env = ft_strjoin_ae("SHLVL=", shlvl_str);
		ft_export(shlvl_env, &minishell->envp);
	}
}

void	ft_init_env(t_minishell *minishell)
{
	if (ft_getenv("PWD", minishell->envp) == NULL)
		ft_export(ft_strjoin_ae("PWD=", minishell->cwd), &minishell->envp);
	ft_init_shlvl(minishell);
	if (ft_getenv("_", minishell->envp) == NULL)
		ft_export("_=./minishell", &minishell->envp);
}