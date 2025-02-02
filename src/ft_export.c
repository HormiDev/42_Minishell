/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:32:31 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/02 20:56:03 by ide-dieg         ###   ########.fr       */
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
	hash->full = ft_strdup_ae(envp);
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

char	**create_array_env_name(t_list *env_list)
{
	char	**array;
	int		i;

	array = (char **)ft_alloc_lst(sizeof(char *) * ft_lstsize(env_list) + 1, 3);
	i = 0;
	while (env_list)
	{
		if (ft_strncmp_p(((t_env *)env_list->content)->name, "_", 2))
		{
			array[i] = ((t_env *)env_list->content)->name;
			i++;
		}
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_alpha_orderer(char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strncmp_p(array[i], array[j], ft_strlen_p(array[j])) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export_args(char **args, t_list **env_list, t_minishell *mini)
{
	int		i;
	char	**array;

	i = 0;
	if (ft_splitlen(args) == 0)
	{
		array = create_array_env_name(*env_list);
		ft_alpha_orderer(array);
		while (array[i])
		{
			ft_printf("declare -x %s=\"%s\"\n", array[i], ft_getenv(array[i], *env_list));
			i++;
		}		
		return ;
	}
	while (args[i])
	{
		ft_export(args[i], env_list);
		i++;
	}
	mini->envp_array = ft_refresh_env_array(mini->envp, mini->envp_array);	
}
