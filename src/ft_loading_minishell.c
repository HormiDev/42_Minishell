/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:30:21 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/08 23:28:57 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_hostname(t_list *envp)
{// proteger funcion y liverar memoria
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
		ft_array_to_list(envp, &minishell->envp);// crear copia de envp en forma de lista
		ft_init_env(minishell);
		ft_refresh_env_array(minishell->envp, minishell);
		minishell->user = ft_strdup_ae(ft_getenv("USER", minishell->envp));
		if (!minishell->user)
			minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = get_hostname(minishell->envp);
		if (!minishell->host)
			minishell->host = ft_strdup_ae("dagimeno");
		//minishell->user = ft_strdup_ae(ft_getenv("USER", envp));
		//minishell->host = get_hostname(envp);
	}
	else
	{
		// crear nuevo envp
		ft_init_env(minishell);
		ft_refresh_env_array(minishell->envp, minishell);
		minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = ft_strdup_ae("dagimeno");
	}
	ft_init_history(minishell);
	return (minishell);
}
