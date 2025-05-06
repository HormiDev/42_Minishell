/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_minishell_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:46:42 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:50:51 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

static char	*get_hostname(t_list *envp)
{
	char	*session_manager;
	char	**split;
	char	**split2;

	session_manager = ft_getenv("SESSION_MANAGER", envp);
	if (!session_manager)
		return (NULL);
	split = ft_split_ae(session_manager, '/');
	split2 = ft_split_ae(split[1], '.');
	return (ft_strdup_ae(split2[0]));
}

t_minishell	*ft_loading_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_alloc_lst(sizeof(t_minishell), 4);
	getcwd(minishell->cwd, PATH_MAX);
	if (envp)
	{
		ft_array_to_list(envp, &minishell->envp);
		ft_init_env(minishell);
		ft_refresh_env_array(minishell->envp, minishell);
		minishell->user = ft_strdup_ae(ft_getenv("USER", minishell->envp));
		if (!minishell->user)
			minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = get_hostname(minishell->envp);
		if (!minishell->host)
			minishell->host = ft_strdup_ae("dagimeno");
	}
	else
	{
		ft_init_env(minishell);
		ft_refresh_env_array(minishell->envp, minishell);
		minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = ft_strdup_ae("dagimeno");
	}
	ft_init_history(minishell);
	return (minishell);
}
