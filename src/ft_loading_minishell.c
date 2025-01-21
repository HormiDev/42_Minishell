/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:30:21 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/21 14:49:26 by dagimeno         ###   ########.fr       */
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
		minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = ft_strdup_ae("dagimeno");
	}
	return (minishell);
}
