/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:35:58 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:36:05 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

static t_env	*ft_check_input(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
		{
			printf("%sexport: %s: not a valid identifier%s\n", RED, env, RESET);
			return (NULL);
		}
		i++;
	}
	if (!env[i] || !env[i + 1] || i == 0)
	{
		if (i == 0)
			printf("%sexport: %s: not a valid identifier%s\n", RED, env, RESET);
		return (NULL);
	}
	return (ft_create_hash(env, i));
}

int	ft_export(char *env, t_list **envp_list)
{
	t_env	*hash;
	t_list	*tmp_list;

	hash = ft_check_input(env);
	if (!hash)
		return (1);
	tmp_list = *envp_list;
	while (tmp_list && (t_env *)tmp_list->content)
	{
		if (!ft_strncmp_p(((t_env *)tmp_list->content)->name, hash->name,
				ft_strlen_p(hash->name) + 1))
		{
			ft_free_hash((t_env *)tmp_list->content);
			tmp_list->content = hash;
			if (ft_strncmp_p(hash->name, "SHLVL", 6) == 0)
				ft_export_shlvl((t_env *)tmp_list->content);
			return (1);
		}
		tmp_list = tmp_list->next;
	}
	ft_lstadd_back(envp_list, ft_lstnew_ae(hash));
	return (0);
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

void	ft_export_args(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	char	**array;

	i = 0;
	if (ft_splitlen(cmd->args) == 1)
	{
		array = create_array_env_name(mini->envp);
		ft_alpha_orderer(array);
		while (array[i])
		{
			ft_dprintf(cmd->io_fd[1],
				"declare -x %s=\"%s\"\n", array[i],
				ft_getenv(array[i], mini->envp));
			i++;
		}
		ft_free_alloc(array);
		mini->exit_code = 0;
		return ;
	}
	while (cmd->args[++i])
		mini->exit_code = ft_export(cmd->args[i], &mini->envp);
	ft_refresh_env_array(mini->envp, mini);
}
