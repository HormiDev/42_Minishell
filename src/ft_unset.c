/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:31:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/01 19:45:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(char *envp, t_list **env_list)
{
	t_list	*tmp_list;
	t_list	*tmp_list_free;

	tmp_list = *env_list;
	if (!envp || !env_list)
		return ;
	if (!ft_strncmp_p(((t_env *)tmp_list->content)->name, envp,
			ft_strlen_p(envp) + 1))
	{
		*env_list = tmp_list->next;
		return ;
	}
	while (tmp_list->next)
	{
		if (!ft_strncmp_p(((t_env *)tmp_list->next->content)->name, envp,
			ft_strlen_p(envp) + 1))
		{
			tmp_list_free = tmp_list->next;
			tmp_list->next = tmp_list->next->next;
			ft_free_hash(tmp_list_free->content);
			ft_free_alloc(tmp_list_free);
			return ;
		}
		tmp_list = tmp_list->next;
	}
}

void	ft_unset_args(char **args, t_list **env_list, t_minishell *mini)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_unset(args[i], env_list);
		i++;
	}
	ft_refresh_env_array(mini->envp, mini);	
	mini->exit_code = 0;
}
