/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:32:31 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/20 01:58:48 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(char *envp, t_list **envp_list)
{
	t_env	*hash;
	t_list	*tmp_list;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i])
		return ;
	hash = (t_env *)ft_alloc_lst(sizeof(t_env), 3);
	hash->name = ft_substr_ae(envp, 0, i);
	hash->value = ft_strdup_ae(envp + i + 1);
	tmp_list = *envp_list;
	while (tmp_list && (t_env *)tmp_list->content)
	{
		if (!ft_strncmp_p(((t_env *)tmp_list->content)->name, hash->name,
			ft_strlen_p(hash->name) + 1))
		{
			((t_env *)tmp_list->content)->value = hash->value;
			return ;
		}
		tmp_list = tmp_list->next;
	}
	ft_lstadd_back(envp_list, ft_lstnew_ae(hash));
}
void	ft_export_args(char **args, t_list **env_list)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_export(args[i], env_list);
		i++;
	}
}